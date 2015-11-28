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
%token	LEFT_PARENTHESIS RIGHT_PARENTHESIS COMMA
%token  AND OR
%token	INT_TYPE VARCHAR_TYPE DATE_TYPE
%token	VARIABLE
%token	NUMBER
%token	CHAR
%token	DATE

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
		int fid = createFileSpace(&head);
		// create and initiate table dictionary
		relation table_dict = new relation();
		table_dict.initRelation(head, fid, $2.name, 'anonymous');
		// add attributes
		for(int i=0; i<cur_attribute; i++) {
			table_dict.insertAttribute(table_attributes[i].name, table_attribute[i].type, table_attribute[i].length);
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
	| VARIABLE VARCHAR_TYPE LEFT_PARENTHESIS NUMBER RIGHT_PARENTHESIS  { add_attribute($1.name, $2.val, $4.val); }
	| VARIABLE DATE_TYPE { add_attribute($1.name, $2.val, 10);}
	;

drop
	: DROP_TABLE VARIABLE {printf("drop table %s\n", $2.name); destroy_table(head, $2.name); }
	;

insert
	: INSERT VARIABLE VALUES LEFT_PARENTHESIS record RIGHT_PARENTHESIS  {
		int fid = findfidbyname($2.name);
		char *tmp = malloc(sizeof(char)*cur_value);
		strcpy(tmp, insert_value);
		insertOneRecord(head, fid, tmp);
		free(tmp);
		cur_value = 0;
	}
	;

record
	: record COMMA item
	| item
	;

item
	: NUMBER {sprintf(insert_value+cur_value, "%d", $1.val); cur_value += 4; } 
	| CHAR {sprintf(insert_value+cur_value, "%s", $1.name); cur_value += strlen($1.name); } 
	| DATE {sprintf(insert_value+cur_value, "%s", $1.name); cur_value += strlen($1.name); } 
	;

delete
	: DELETE VARIABLE WHERE where_list {printf("delete from table %s ", $2.name);};

where_list
	: where_list AND condition
	| where_list OR condition
	| condition
	;

compare_opt
	: BEqual | BUNEqual | BSmaller | BSmallerEqual | BBigger | BBiggerEqual | BLike;

condition
	: attribute compare_opt item {printf("condition: %s %d ", $1.name, $2.val);}
	| attribute compare_opt attribute {printf("condition: %s %d ", $1.name, $2.val);}
	;

select
	: SELECT attribute_list FROM variable_list WHERE where_list
	| SELECT attribute_list FROM variable_list WHERE where_list ORDER_BY variable_list
	;

attribute_list
	: attribute_list COMMA attribute
	| attribute
	;

attribute
	: VARIABLE {printf("attribute: %s\n", $1.name);}
	| ATTRIBUTE {printf("attribute: %s\n", $1.name);}
	;

variable_list
	: variable_list COMMA VARIABLE {printf("variable: %s\n", $3.name);}
	| VARIABLE {printf("variable: %s\n", $1.name);}
	;

%%

void add_attribute(char *name, int type, int length) {
	strcpy(table_attributes[cur_attribute].name, name);
	table_attributes[cur_attribute].type = type;
	table_attributes[cur_attribute].length = length;
	cur_attribute += 1;
}

int main() {
	init_database(&head);
	cur_attribute = 0;
    yyparse();
}

void yyerror(char *s) {
    printf("parse error!\n");
}

int yywrap() {
	return 1;
}
