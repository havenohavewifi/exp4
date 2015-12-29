//
//  deleteTable.cpp
//  
//
//  Created by IreneWu on 15/11/28.
//
//

#include "deleteAllTuples.h"
#include "dataDictionary.h"
#include "dbHead.h"
#include "file.h"
#include "string.h"
#include <iostream>
using namespace std;

int deleteAllTuples(struct dbSysHead *head, const char * tableName){
    int logicfid;
    int i, j;
    for (i = 0; i<MAX_FILE_NUM; i++) {
        if (strcmp((head->redef)[i].getRelationName(),tableName)==0) {
            break;
        }
    }
    if (i == MAX_FILE_NUM) {
        cout<<"this table not exists. check name plz."<<endl;
        return -2;
    }
    else{
        /*
        for (j = 0; j<MAX_FILE_NUM; j++) {
            if ((head->desc).fileDesc[j].fileID == i ) {
                break;
            }
        }*/
        logicfid = (head->desc).fileDesc[i].fileID;
        int k = queryFileID(head, logicfid);
        if(k < 0)
        {
            cout<<"delete table in disk failed."<<endl;
            return -1;
        }
        else
        {
            recyPage(head, (head->desc).fileDesc[k].fileAddr);
            head->desc.fileDesc[k].filePageForWrite = 0;
            head->desc.fileDesc[k].filePageEndPos = 0;
            (head->desc).pageAvai += (head->desc).fileDesc[k].filePageNum;
            cout<<"delete all tuples from this table succeed."<<endl;
            sysUpdate(head);
            return 0;
        }
    }
}
