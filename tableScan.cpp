//
//  tableScan.cpp
//  exp2
//
//  Created by IreneWu on 15/11/14.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#include "tableScan.h"
#include "cursor.h"
#include "Buffer.h"
#include "file.h"
#include "dataDictionary.h"
#include <iostream>

int getLogicfidByName(struct dbSysHead *head, const char * tableName) {
    int logicfid;
    int i, j;
//    relation *dic;
    for (i = 0; i<MAX_FILE_NUM; i++) {
        if (strcmp((head->redef)[i].getRelationName(),tableName)==0) {
//            dic = &head->redef[i];
            break;
        }
    }
    if (i == MAX_FILE_NUM) {
        cout<<"this table not exists. check name plz."<<endl;
        return -2;
    }
    logicfid = (head->desc).fileDesc[i].fileID;
    return logicfid;
}
int TableScan(struct dbSysHead * head, relation * temp_datadic, const char * tableName){
    int logicfid = getLogicfidByName(head,tableName);
    if (logicfid == -2) {
        return -2;
    }
    int fid = queryFileID(head, logicfid);
    //find empty temp_datadic
    int dictID ;
    for (int i = 0; i < MAX_FILE_NUM; i++) {
        if (strcmp(temp_datadic[i].getRelationName(),"") == 0) {
            dictID = i;
            cout<<"new relation id for tablescan: "<<dictID<<endl;
            break;
        }
    }
    if (dictID == MAX_FILE_NUM) {
        cout<<"no temp datadict for use!"<<endl;
        return -3;
    }
    //look up which buffer is empty
    int buffer_id_ ;
    int i;
    for (i = 0 ; i < BUFF_NUM; i++) {
        if (head->buff[i].emptyOrnot == true) {
            buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout<<"TableScan bufferID: "<<i<<"  logicfileid: "<<logicfid<<endl;
            break;
        }
    }
    if (i == BUFF_NUM) {
        cout<<"No Buffer Can be Used!"<<endl;
        return -1;
    }
    int size_per_record = head->redef[fid].getRecordLength();
    RecordCursor scanTable(head, logicfid, size_per_record, 0); //0 for readin data buffer
    char * one_Row_ = (char *)malloc(sizeof(char) * size_per_record);
    Buffer t(head, -2); //to avoid positive number, no meaning
    int k = 0;
    while (true == scanTable.getNextRecord(one_Row_)) { //only scan
        k++;
        //if more than one page, write to file and reset Buffer t
        if(false == t.AppendBuffer(one_Row_, size_per_record))
        {
            t.writeBufferPage(t.filehead,buffer_id_ ,t.data_, t.current_size_);
            t.pageID++;
            if (t.pageID == SIZE_BUFF) {
                std::cout<<"this buffer full"<<std::endl;
                break;
            }
            memset(t.data_, 0, SIZE_PER_PAGE);
            memcpy(t.data_, one_Row_, size_per_record);
            t.pointer_ = t.data_+size_per_record;
            t.current_size_ = size_per_record;
        }
    }
    //write remainder
    t.writeBufferPage(t.filehead,buffer_id_ ,t.data_, t.current_size_);
    free(one_Row_);
    temp_datadic[dictID] = head->redef[fid]; //correct, class copy succeed
    temp_datadic[dictID].fileID = -buffer_id_; //negative number for temp datadict, value is for which buffer
    temp_datadic[dictID].changeRecordNum (k);
    return 0;
}
void TableScan(struct dbSysHead * head,int fileID, relation * temp_datadic){
    int fid = queryFileID(head, fileID);
//    cout<<"test tablescan fid: "<<fid<<endl;
    int dictID = fid;
    int original_rec_length = head->redef[fid].getRecordLength(); //record_length in original table
    int size_per_record = original_rec_length;   //each record length in new temp table, in case SPJ use
    //look up which buffer is empty
    int buffer_id_ ;
    int i;
    for (i = 0 ; i < BUFF_NUM; i++) {
        if (head->buff[i].emptyOrnot == true) {
            buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout<<"TableScan bufferID: "<<i<<"  logicfileid: "<<fileID<<endl;
            break;
        }
    }
    if (i == BUFF_NUM) {
        cout<<"No Buffer Can be Used!"<<endl;
    }
    else{
        RecordCursor scanTable(head, fileID, original_rec_length, 0); //0 for readin data buffer
        char * one_Row_ = (char *)malloc(sizeof(char) * size_per_record);
        Buffer t(head, -2); //to avoid positive number, no meaning
        int k = 0;
        while (true == scanTable.getNextRecord(one_Row_)) { //only scan
            k++;
            //if more than one page, write to file and reset Buffer t
            if(false == t.AppendBuffer(one_Row_, size_per_record))
            {
                t.writeBufferPage(t.filehead,buffer_id_ ,t.data_, t.current_size_);
                t.pageID++;
                if (t.pageID == SIZE_BUFF) {
                    std::cout<<"this buffer full"<<std::endl;
                    break;
                }
                memset(t.data_, 0, SIZE_PER_PAGE);
                memcpy(t.data_, one_Row_, size_per_record);
                t.pointer_ = t.data_+size_per_record;
                t.current_size_ = size_per_record;
            }

        }
        //write remainder
        t.writeBufferPage(t.filehead,buffer_id_ ,t.data_, t.current_size_);
        free(one_Row_);
        temp_datadic[dictID] = head->redef[fid]; //correct, class copy succeed
        temp_datadic[dictID].fileID = -buffer_id_; //negative number for temp datadict, value is for which buffer
        temp_datadic[dictID].changeRecordNum (k);
//        cout<<"temp dd length:" <<temp_datadic[dictID].getRecordLength()<<endl;
//        temp_datadic[dictID].recordLength = size_per_record;
//        strcpy(temp_datadic[dictID].relationName ,"temp datadict 1");
    }
}
