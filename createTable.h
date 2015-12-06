//
//  createTable.h
//  
//
//  Created by IreneWu on 15/11/28.
//
//

#ifndef createTable_h
#define createTable_h
#include "file.h"
#include "dbhead.h"
#define A_NAME_LENGTH 20
struct eachAttribute{
    char attribute_name_[A_NAME_LENGTH];
    int attribute_type_;
    int attribute_length_;
};

int createTable(struct dbSysHead *head);
int createTable(struct dbSysHead * head, const char * relationName, const char * constructorName,  int attributeNum, struct eachAttribute * attributeList);

#endif /* defined(____createTable__) */
