#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "dbHead.h"
#include "loaddata.h"
#include "cursor.h"
#include "getaRecordbyCursor.h"
#include "b_plus_tree.h"
#include "insertOneRecord.h"
#include "recorder_char_general.h"
#include "indexOpt.h"
#include "dataDictionary.h"
#include "file.h"
#include "tableScan.h"
#include "cursorForTmptable.h"
#include "project.h"
#include "filter.h"
#include "join_Hashjoin.h"
#include "nestloop.h"


#ifndef YYSTYPE
typedef union {
	char name[100];
	int val;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

typedef struct attribute_info {
	char name[100];
	int type;
	int length;
}attribute_info;

void yyerror(char *str);

struct dbSysHead head;

// in order to create table
attribute_info table_attributes[12];
int cur_attribute = 0;

// in order to insert value
char insert_value[100];
int cur_value = 0;