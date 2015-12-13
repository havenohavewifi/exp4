//
//  deleteTable.cpp
//  
//
//  Created by IreneWu on 15/11/28.
//
//

#include "dropTable.h"
#include "dataDictionary.h"
#include "dbHead.h"
#include "file.h"
#include "string.h"
#include <iostream>
using namespace std;

int dropTable(struct dbSysHead *head, const char * tableName){
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
        for (j = 0; j<MAX_FILE_NUM; j++) {
            if ((head->desc).fileDesc[j].fileID == i ) {
                break;
            }
        }
        logicfid = (head->desc).fileDesc[i].fileID;
        (head->redef)[i].deleteRelation();
        if(recyFileSpace(head, logicfid)!=  0)
        {
            cout<<"this table is already empty."<<endl;
        }
        cout<<"drop table succeed."<<i<<endl;
        return 0;
    }
}
