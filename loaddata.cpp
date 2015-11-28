//
//  main.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/3.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//
extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

};
#include <iostream>
#include <fstream>
#include <string>
#include "loaddata.h"
#include "dbHead.h"
#include "Buffer.h"
#include "file.h"
#include "recorder_char_general.h"

using namespace std;
string table1 = Customer_tbl;
string table2 = Nation_tbl;
void loaddata(struct dbSysHead * head, int fid)
{
    
    ifstream infile;
    if(fid == 1)    infile.open(table1.c_str());
    else if(fid == 2) infile.open(table2.c_str());
    if(!infile)
    {
        cout<<"open file failure"<<endl;
    }
    else{
        int n = queryFileID(head, fid);
        std::cout<<"load data by datadict: "<<n<<std::endl;
        relation *dic = &(*head).redef[n];
        int size_per_record = dic->getRecordLength();
//        int file_id_ = 1;
        char *oneRec = (char *)malloc(sizeof(char)*size_per_record);
        string tmp;
        //use buffer[0] when loading data
        int buffer_id_ = 0;
//        head->buff[buffer_id_].emptyOrnot = false;
        Buffer t(head, fid);
        int k=0;
        //get one line from customer.tbl
        while (getline(infile,tmp)) {
            int tmp_len = tmp.length();
            char * oneRow = new char[tmp_len+1];
            memcpy(oneRow, tmp.c_str(), tmp_len);
            //split this line and get one recorder
            parserOneLineFromFile(oneRow, oneRec, dic);
            //if more than one page, write to file and reset Buffer t
            if(false == t.AppendBuffer(oneRec, size_per_record))
            {
                t.writeBuffer(t.filehead, t.data_, t.current_size_);
                t.pageID++;
                memset(t.data_, 0, SIZE_PER_PAGE);
                memcpy(t.data_, oneRec, size_per_record);
                t.pointer_ = t.data_+size_per_record;
                t.current_size_ = size_per_record;
            }
            k++;
            if(k>250) break;
        }
        //write remainder
        t.writeBuffer(head, t.data_, t.current_size_);
//        head->buff[buffer_id_].emptyOrnot = true;
//		int fPhysicalID = queryFileID(head, file_id_);
        head->desc.fileDesc[n].filePageEndPos = t.current_size_;
        head->desc.fileDesc[n].filePageNum = t.pageID + 1;
        //Attention
//        dic->changeRecordNum(k);
        (*head).redef[n].changeRecordNum(k);
        cout<<"---datadict length: "<<head->redef[n].getRecordLength()<<"   Num: "<<cout<<head->redef[n].getRecordNum()<<endl;;
        free(oneRec);
        
//打印几个字符串检查一下
/*
        void * readcontent = malloc(64);
        rdFile(head, 1, 4, 64, readcontent);
        char *rec = (char *)readcontent;
        cout<<rec<<endl;
        
        rdFile(head, 1, 460, 64, readcontent);
        rec = (char *)readcontent;
        cout<<rec<<endl;
        free(readcontent);
*/
    }
}

