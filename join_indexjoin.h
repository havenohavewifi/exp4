#ifndef join_indexjoin_h
#define join_indexjoin_h
#include "dataDictionary.h"
#include <stdio.h>
int indexjoin(struct dbSysHead *head, relation *temp_datadic,int old_relation_1, int old_relation_2, const char *name,int actual_fid);
void merge_relation_index(struct dbSysHead *head,relation datadic1,relation datadic2,relation *result);
#endif 