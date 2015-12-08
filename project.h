//
//  project.h
// 
//
//  Created by mengxi on 15/11/21.
//  Copyright (c) 2015Äê mengxi. All rights reserved.
//

#ifndef project_h
#define project_h
#include "dataDictionary.h"
#include <stdio.h>

void project(struct dbSysHead *head, relation *temp_datadic, relation *result);
int project(struct dbSysHead *head, relation *temp_datadic, int old_relation, int attribute_num, char attribute_list[][NAMELENGTH]);
#endif 
