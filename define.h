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
#include "deleteTable.h"
#include "insertOneTuple.h"
#include "deleteRecords.h"
#include "createTable.h"


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

typedef struct where_condition {
	char attribute_name[100];
	char attribute_value[100];
	int operation;
} where_condition;

void yyerror(char *str);

struct dbSysHead head;
relation * temp_data_dict = new relation[MAX_FILE_NUM];

// in order to create table
attribute_info table_attributes[12];
int cur_attribute = 0;

// in order to insert value
char insert_value[1000];
int cur_value = 0;

// in order to select: where conditions
where_condition condition_array[10];
int cur_condition = 0;

char select_attributes[10][100];
int cur_sattr = 0;

char table_array[10][100];
int cur_table = 0;

void add_attribute(char *name, int type, int length);