%{
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h> 
#include <memory.h>
#include <string.h>
#include "lex.yy.c"
%}

%start	program		
%token  CREATE_TABLE DROP_TABLE INSERT VALUES DELETE SELECT FROM WHERE ORDER_BY ATTRIBUTE
%token  BEqual BUNEqual BSmaller BSmallerEqual BBigger BBiggerEqual BLike
%token	LEFT_PARENTHESIS RIGHT_PARENTHESIS COMMA STAR
%token  AND OR
%token	INT_TYPE VARCHAR_TYPE DATE_TYPE
%token	VARIABLE
%token	NUMBER_VALUE
%token	VARCHAR_VALUE
%token	DATE_VALUE
%token	END

%%

program
	: command program
	| command
	;

command
	: create | drop | insert | delete | select;

create
	: CREATE_TABLE VARIABLE LEFT_PARENTHESIS attribute_type_list RIGHT_PARENTHESIS {
		// create table space
		int fid = creatFileSpace(&head);
		// find the table id in file list
		int n = queryFileID(&head, fid);
		if (n == -1) {
			printf("can't find file!\n");
			return -1;
		}
		// create and initiate table dictionary
		head.redef[n].initRelation(&head, fid, $2.name, "anonymous");
		// add attributes
		for(int i=0; i<cur_attribute; i++) {
			head.redef[n].insertAttribute(table_attributes[i].name, table_attributes[i].type, table_attributes[i].length);
		}
		// print succeed infomation
		printf("table name: %s\n", head.redef[n].getRelationName());
		for(int i=0; i<head.redef[n].getAttributeNum(); i++) {
			printf("%s %d\n", head.redef[n].getAttributeByNo(i).getName(), head.redef[n].getAttributeByNo(i).getType());
		}
		cur_attribute = 0;
	}
	;

attribute_type_list
	: attribute_type_list COMMA attribute_type
	| attribute_type
	;

attribute_type
	: VARIABLE INT_TYPE { add_attribute($1.name, $2.val, 4); }
	| VARIABLE VARCHAR_TYPE LEFT_PARENTHESIS NUMBER_VALUE RIGHT_PARENTHESIS  { add_attribute($1.name, $2.val, $4.val); }
	| VARIABLE DATE_TYPE { add_attribute($1.name, $2.val, 10);}
	;

drop
	: DROP_TABLE VARIABLE { 
	dropTable(&head, $2.name); }
	;

insert
	: INSERT VARIABLE VALUES LEFT_PARENTHESIS record RIGHT_PARENTHESIS  {
		char *tmp = (char *)malloc(sizeof(char)*(cur_value+1));
		memcpy(tmp, insert_value, cur_value+1);
		printf("length: %d, value:%s, table: %s\n", cur_value, tmp, $2.name);
		insertOneTuple(&head, $2.name, tmp);
		free(tmp);
		cur_value = 0;
	}
	;

record
	: record COMMA item
	| item
	;

item
	: NUMBER_VALUE {
		// memcpy(insert_value+cur_value, (void *)(&($1.val)), sizeof(int));
		char tmp[100];
		sprintf(tmp, "%d", $1.val);
		memcpy(insert_value+cur_value, tmp, strlen(tmp)*sizeof(char));
		cur_value += strlen(tmp)*sizeof(char); 
		memcpy(insert_value+cur_value, "|", sizeof(char));
		cur_value += sizeof(char); 
		insert_value[cur_value] = '\0'; } 
	| VARCHAR_VALUE {
		memcpy(insert_value+cur_value, $1.name, sizeof(char)*strlen($1.name)); 
		cur_value += strlen($1.name); 
		memcpy(insert_value+cur_value, "|", sizeof(char));
		cur_value += sizeof(char); 
		insert_value[cur_value] = '\0'; } 
	| DATE_VALUE {
		memcpy(insert_value+cur_value, $1.name, sizeof(char)*strlen($1.name));
		cur_value += strlen($1.name); 
		memcpy(insert_value+cur_value, "|", sizeof(char));
		cur_value += sizeof(char); 
		insert_value[cur_value] = '\0'; } 
	;

delete
	: DELETE STAR FROM VARIABLE { deleteAllTuples(&head, $4.name); } 
	| DELETE FROM VARIABLE WHERE where_list END{
		if (cur_condition == 1) {
			int fid = getLogicfidByName(&head, $3.name);
			deleteRecordWhere(&head, fid, condition_array[0].attribute_name, condition_array[0].attribute_value, condition_array[0].operation, 0);
		}
		cur_condition = 0;
	};

where_list
	: where_list AND condition
	| where_list OR condition
	| condition
	;

compare_opt
	: BEqual | BUNEqual | BSmaller | BSmallerEqual | BBigger | BBiggerEqual | BLike;

condition_const
	: NUMBER_VALUE {
		memcpy(condition_array[cur_condition].attribute_value, (void *)(&($1.val)), sizeof(int));
		condition_array[cur_condition].attribute_value[sizeof(int)] = '\0'; } 
	| VARCHAR_VALUE {
		strcpy(condition_array[cur_condition].attribute_value, $1.name); } 
	| DATE_VALUE {
		strcpy(condition_array[cur_condition].attribute_value, $1.name); } 
	;

c_attribute
	: VARIABLE { strcpy(condition_array[cur_condition].attribute_name, $1.name); }
	| ATTRIBUTE { strcpy(condition_array[cur_condition].attribute_name, $1.name); }
	;

cc_attribute
	: VARIABLE { strcpy(condition_array[cur_condition].attribute_value, $1.name); }
	| ATTRIBUTE { strcpy(condition_array[cur_condition].attribute_value, $1.name); }
	;

condition
	: c_attribute compare_opt condition_const {
		condition_array[cur_condition].operation = $2.val;
		cur_condition += 1; }
	| c_attribute compare_opt cc_attribute {
		condition_array[cur_condition].operation = $2.val;
		cur_condition += 1; }
	;

select
	: SELECT STAR FROM VARIABLE {
		int logicfid = getLogicfidByName(&head, $4.name);
		if (logicfid != -2) {
			TableScan(&head, logicfid, temp_data_dict);

			// have trouble reading the data after table scan
			
			int dictid = queryFileID(&head, logicfid);

			int buffer_ID_ = - temp_data_dict[dictid].fileID;
   			int record_num_ = temp_data_dict[dictid].getRecordNum();
   			// int record_num_ = 1;
    		int record_len_ = temp_data_dict[dictid].getRecordLength();

    		RecordCursorTmp t1(&head,dictid,record_len_,buffer_ID_,record_num_);
    		cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    		
    		char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
		    while (true == t1.getNextRecord(one_Row_)) { //only scan
		        getOneRecord(one_Row_, &temp_data_dict[dictid]);
		    }
		    free(one_Row_);
		    
		}
	}
	| SELECT attribute_list FROM table_list WHERE where_list END{
		for (int i=0; i<cur_sattr; i++) {
			printf("%s ", select_attributes[i]);
		}
		printf("\n");

		for (int i=0; i<cur_table; i++) {
			printf("%s ", table_array[i]);
		}
		printf("\n");

		for (int i=0; i<cur_condition; i++) {
			printf("%s %d %s\n", condition_array[i].attribute_name, condition_array[i].operation, condition_array[i].attribute_value);
		}

		// can't select
		/*
		if( cur_table == 1) {
			int logicfid = getLogicfidByName(&head, table_array[0]);
			int physicfid = queryFileID(&head, logicfid);
			relation c_result;
			c_result.init(table_array[0], "anonymous");
			for (int i=0; i<cur_attribute; i++) {
				
				c_result.insertAttribute(select_attributes[i], head.redef[physicfid].getAttributeByName(select_attributes[i]).getType(), head.redef[physicfid].getAttributeByName(select_attributes[i]).getLength());
				printf("%s %d %d\n", select_attributes[i], head.redef[physicfid].getAttributeByName(select_attributes[i]).getType(), head.redef[physicfid].getAttributeByName(select_attributes[i]).getLength());
			}
			project(&head, &(head.redef[physicfid]), &c_result);
		}
		*/
		
		cur_condition = 0;
		cur_sattr = 0;
		cur_table = 0;
	}
	;

attribute_list
	: attribute_list COMMA attribute
	| attribute
	;

attribute
	: VARIABLE { strcpy(select_attributes[cur_sattr], $1.name); cur_sattr++; }
	| ATTRIBUTE { strcpy(select_attributes[cur_sattr], $1.name); cur_sattr++; }
	;

table_list
	: table_list COMMA VARIABLE
	| VARIABLE { strcpy(table_array[cur_table], $1.name); cur_table++; }
	;


%%

void add_attribute(char *name, int type, int length) {
	strcpy(table_attributes[cur_attribute].name, name);
	table_attributes[cur_attribute].type = type;
	table_attributes[cur_attribute].length = length;
	cur_attribute += 1;
}

int init_database(struct dbSysHead *head)
{
	initSys(head);
	head->fpdesc = fopen(DBMS_DAT, "rb+");
	isAvail(head->fpdesc, "main", FOPEN);
	return 0;
}

int main() {
	init_database(&head);
	createTable(&head);
	loaddata(&head, 1);
	cur_attribute = 0;
	cur_condition = 0;
	cur_value = 0;
    yyparse();
}

void yyerror(char *s) {
    printf("parse error!\n");
}

int yywrap() {
	return 1;
}
