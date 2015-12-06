//
//  sortmergejoin.h
// 
//
//  Created by mengxi on 15/11/21.
//  Copyright (c) 2015Äê mengxi. All rights reserved.
//

#ifndef sortmergejoin_h
#define sortmergejoin_h
#include "dataDictionary.h"
#include <stdio.h>

struct sortNode
{
	int value;
	char *record;
};

int Comp(const void *p1,const void *p2);
void tempSort(struct dbSysHead *head, relation *tempTable, char *attr);
void sortmergejoin(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2, char *attr, relation *result);

#endif 
