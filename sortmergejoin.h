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
int tempSort(struct dbSysHead *head, relation *temp_datadic, int old_relation, char *attr);
int sortmergejoin(struct dbSysHead *head, relation *temp_datadic,int old_relation_1, int old_relation_2, char *attr);

#endif 
