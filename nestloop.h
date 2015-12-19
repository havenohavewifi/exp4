#ifndef nestloop_h
#define nestloop_h
#include "dataDictionary.h"
#include <stdio.h>

int showRelation(relation *r);
void merge_relation_quit(struct dbSysHead *head,relation datadic1,relation datadic2,relation *result,char* name);
void nestloop_equal(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name);
int nestloop_cp_new(struct dbSysHead *head, relation *temp_datadic, int old_relation_1, int old_relation_2 );
void nestloop_cp(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result);
void merge_relation(struct dbSysHead *head,relation datadic1,relation datadic2,relation *result);
void nestloop_bigger(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name);
void nestloop_smaller_or_equal(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name);
void nestloop_bigger_or_equal(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name);
void nestloop_smaller(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name);
#endif 