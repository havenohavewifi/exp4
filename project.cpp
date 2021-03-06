//
//  project.cpp
//  
//
//  Created by mengxi on 15/11/14.
//  Copyright (c) 2015�� mengxi. All rights reserved.
//

#include "project.h"
#include "cursor.h"
#include "cursorForTmptable.h"
#include "Buffer.h"
#include "file.h"
#include "dataDictionary.h"
#include "createTable.h"
#include <iostream>
using namespace std;
int project(struct dbSysHead *head, relation *temp_datadic, int old_relation, int attribute_num, char  attribute_list[][NAMELENGTH]){
    //find empty temp_datadic
    int new_relation ;
    for (int i = 0; i < MAX_FILE_NUM; i++) {
        if (strcmp(temp_datadic[i].getRelationName(),"") == 0) {
            new_relation = i;
    //        cout<<"new relation id: "<<new_relation<<endl;
            temp_datadic[new_relation].init(temp_datadic[old_relation].getRelationName(),"XXX");
            break;
        }
    }
    if (new_relation == MAX_FILE_NUM) {
        cout<<"no temp datadict for use!"<<endl;
        return -3;
    }
    //input error control
    int insert_num_ = 0;
 //   cout<<"#####"<<temp_datadic[old_relation].getAttributeNum()<<endl;
    for (int i = 0; i < temp_datadic[old_relation].getAttributeNum(); i++) {
//		cout<<"########project "<<temp_datadic[old_relation].getAttributeByNo(i).getName()<<endl;
        for (int j = 0; j < attribute_num; j++) {
		//	cout<<"inner ##### "<<attribute_list[j]<<endl;
            if (strcmp(attribute_list[j], temp_datadic[old_relation].getAttributeByNo(i).getName()) == 0) {
                temp_datadic[new_relation].insertAttribute(temp_datadic[old_relation].getAttributeByNo(i).getName(), temp_datadic[old_relation].getAttributeByNo(i).getType(), temp_datadic[old_relation].getAttributeByNo(i).getLength());
                temp_datadic[new_relation].changeIndexedByName(attribute_list[j], temp_datadic[old_relation].getIndexedByName(attribute_list[j]));
                insert_num_ ++;
              //  cout<<attribute_list[j] <<" "<<temp_datadic[old_relation].getAttributeByNo(i).getName() <<endl;
            }
        }
    }
   if (insert_num_ == attribute_num ) {
        //
    }
    else{
        cout<<"project input attributes error!"<<endl;
        return -1;
    }
    int original_rec_length = temp_datadic[old_relation].getRecordLength();
    int new_rec_length = temp_datadic[new_relation].getRecordLength();
    //look up which buffer is empty
    int buffer_id_;
    int i;
    for (i = 0; i < BUFF_NUM; i++) {
        if (head->buff[i].emptyOrnot == true) {
            buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
           // std::cout << "new temp table bufferID: " << i << std::endl;
            break;
        }
    }
    if (i == BUFF_NUM) {
        cout << "No Buffer Can be Used!" << endl;
        return -2;
    }
    RecordCursorTmp scanTable(head, temp_datadic[old_relation].fileID, original_rec_length, -temp_datadic[old_relation].fileID, temp_datadic[old_relation].getRecordNum());
    char * one_Row_ = (char *)malloc(sizeof(char) * original_rec_length);
    char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
    Buffer t(head, -2); //to avoid positive number, no meaning
    int k = 0;
    while (true == scanTable.getNextRecord(one_Row_)) { //only scan
        k++;
        for (int ptr1 = 0, ptr2 = 0; ptr1 < temp_datadic[old_relation].getAttributeNum() && ptr2 < temp_datadic[new_relation].getAttributeNum();){
            int offset1 = temp_datadic[old_relation].getAttributeByNo(ptr1).getRecordDeviation();
            int offset2 = temp_datadic[new_relation].getAttributeByNo(ptr2).getRecordDeviation();
            if (strcmp(temp_datadic[old_relation].getAttributeByNo(ptr1).getName(), temp_datadic[new_relation].getAttributeByNo(ptr2).getName()) == 0)
            {
                strncpy(new_Row_ + offset2, one_Row_ + offset1, temp_datadic[new_relation].getAttributeByNo(ptr2).getLength());
                if (temp_datadic[new_relation].getAttributeByNo(ptr2).getType() == 1){
                    int value = *((int *)(new_Row_ + offset2));
//                    cout << ptr2 << ":" << value << endl;
                }
                if (temp_datadic[new_relation].getAttributeByNo(ptr2).getType() == 2){
                    char * valuechar = (char *)malloc(sizeof(char)*temp_datadic[new_relation].getAttributeByNo(ptr2).getLength());
                    memcpy(valuechar, new_Row_ + offset2, temp_datadic[new_relation].getAttributeByNo(ptr2).getLength());
//                    cout << ptr2 << ":" << valuechar << endl;
                    free(valuechar);
                }
                ptr1++;
                ptr2++;
            }
            else
            {
                ptr1++;
            }
        }
        //if more than one page, write to file and reset Buffer t
        if (false == t.AppendBuffer(new_Row_, new_rec_length))
        {
            t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
            t.pageID++;
            if (t.pageID == SIZE_BUFF) {
                std::cout << "this buffer full" << std::endl;
                break;
            }
            memset(t.data_, 0, SIZE_PER_PAGE);
            memcpy(t.data_, new_Row_, new_rec_length);
            t.pointer_ = t.data_ + new_rec_length;
            t.current_size_ = new_rec_length;
        }
    }
    //write remainder
    t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
    temp_datadic[new_relation].fileID = -buffer_id_;
    //Attention!!!
    temp_datadic[new_relation].changeRecordNum(k);
    //delete old relation
    strcpy(temp_datadic[old_relation].getRelationName(),"");
    head->buff[-temp_datadic[old_relation].fileID].emptyOrnot = true;
    free(one_Row_);
    free(new_Row_);
    return new_relation;
}

