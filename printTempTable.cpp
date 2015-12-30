//
//  printTempTable.cpp
//  
//
//  Created by IreneWu on 15/12/20.
//
//

#include "printTempTable.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dbHead.h"
#include "cursor.h"
#include "getaRecordbyCursor.h"
#include "recorder_char_general.h"
#include "dataDictionary.h"
#include "file.h"
#include "tableScan.h"
#include "cursorForTmptable.h"
#include "nestloop.h"

void printTempTable(struct dbSysHead *head, relation * temp_data_dict,int new_relation){
 //   showRelation(&temp_data_dict[new_relation]);
    showRelation(&temp_data_dict[new_relation]);
    if(temp_data_dict[new_relation].getRecordNum() == 0)
    {
        cout<<"query result num is 0."<<endl;
        strcpy(temp_data_dict[new_relation].getRelationName(),"");
        head->buff[-temp_data_dict[new_relation].fileID].emptyOrnot = true;
        return ;
    }
    RecordCursorTmp t2(head,1,temp_data_dict[new_relation].getRecordLength(), - temp_data_dict[new_relation].fileID,temp_data_dict[new_relation].getRecordNum());
    char * one_Row_ = (char *)malloc(sizeof(char)* temp_data_dict[new_relation].getRecordLength());
    while (true == t2.getNextRecord(one_Row_)) { //only scan
        getOneRecord(one_Row_, &temp_data_dict[new_relation]); //get each attribute value and print
    }
    
    free(one_Row_);
    strcpy(temp_data_dict[new_relation].getRelationName(),"");
    head->buff[-temp_data_dict[new_relation].fileID].emptyOrnot = true;
}
