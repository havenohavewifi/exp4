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
#include "dropTable.h"
#include "deleteAllTuples.h"
#include "insertOneTuple.h"
#include "deleteRecords.h"
#include "createTable.h"
#include "printTempTable.h"
#include "join.h"
#include "sortmergejoin.h"
#include "join_indexjoin.h"


#ifndef YYSTYPE
typedef union {
	char name[NAMELENGTH];
	int val;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

typedef struct attribute_info {
	char name[NAMELENGTH];
	int type;
	int length;
}attribute_info;

typedef struct where_condition {
	char attribute_name[NAMELENGTH];
	char attribute_value[NAMELENGTH];
	int operation;
	bool isjoin;
} where_condition;

void yyerror(char *str);

struct dbSysHead head;
relation *temp_data_dict = new relation[MAX_FILE_NUM]();

// in order to create table
attribute_info table_attributes[12];
int cur_attribute = 0;

// in order to insert value
char insert_value[1000];
int cur_value = 0;

// in order to select: where conditions
where_condition condition_array[10];
int cur_condition = 0;

char select_attributes[10][NAMELENGTH];
int cur_sattr = 0;

char table_array[10][NAMELENGTH];
int cur_table = 0;

void add_attribute(char *name, int type, int length);
int find_empty_tempdict(relation *temp_data_dict);
bool is_in_table(relation *temp_data_dict, int dict_id, char *attr_name);
