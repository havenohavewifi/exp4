//
//  tableScan.h
//  exp2
//
//  Created by IreneWu on 15/11/14.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#ifndef tableScan_h
#define tableScan_h
#include "dataDictionary.h"
#include <stdio.h>
int getLogicfidByName(struct dbSysHead *head, const char * tableName);
void TableScan(struct dbSysHead * head,int fileID, relation * temp_datadic);
int TableScan(struct dbSysHead * head, relation * temp_datadic, const char * tableName);
#endif 
