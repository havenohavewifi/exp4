//
//  insertOneTuple.cpp
//  
//
//  Created by IreneWu on 15/12/6.
//
//
#include "dataDictionary.h"
#include "recorder_char_general.h"
#include "insertOneRecord.h"
#include "insertOneTuple.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
//need to add input control, check error
//insert into customer values (‘501’, ‘Customer#000000001’, ‘VhzIApeRb ot,c,E’ ‘1525-989-741-2988’ , ‘711.56’, ‘BUILDING’, ‘to the even, regular platelets. regular, ironic epitHHH’);
int insertOneTuple(struct dbSysHead *head, const char * tableName, const char* content){
    int logicfid;
    int i, j;
    relation *dic;
    for (i = 0; i<MAX_FILE_NUM; i++) {
        if (strcmp((head->redef)[i].getRelationName(),tableName)==0) {
            dic = &head->redef[i];
            break;
        }
    }
    if (i == MAX_FILE_NUM) {
        cout<<"this table not exists. check name plz."<<endl;
        return -2;
    }
    else{
        for (j = 0; j<MAX_FILE_NUM; j++) {
            if ((head->desc).fileDesc[j].fileID == i ) {
                break;
            }
        }
        logicfid = (head->desc).fileDesc[i].fileID;
        int size_per_record = dic->getRecordLength();
        char *oneRec = (char *)malloc(sizeof(char)*size_per_record);
        char * content2 = (char *)malloc(sizeof(char)*256);
        strcpy(content2,content);
        parserOneLineFromFile(content2, oneRec, dic);
        insertOneRecord(head, logicfid, oneRec);
        free(oneRec);
        cout<<"insert finished."<<endl;
    }
}
