%{
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h> 
#include <memory.h>
#include <string.h>
#include "lex.yy.c"
%}

%start	program		
%token  CREATE_TABLE DROP_TABLE INSERT VALUES DELETE SELECT FROM WHERE ORDER_BY ATTRIBUTE CREATE_INDEX
%token  BEqual BUNEqual BSmaller BSmallerEqual BBigger BBiggerEqual BLike
%token	LEFT_PARENTHESIS RIGHT_PARENTHESIS COMMA STAR
%token  AND OR
%token	INT_TYPE VARCHAR_TYPE DATE_TYPE
%token	VARIABLE
%token	NUMBER_VALUE
%token	VARCHAR_VALUE
%token	DATE_VALUE
%token	END
%token	EXIT

%%

program
	: command program
	| command
	;

command
	: create | drop | insert | delete | select | create_index
	| EXIT {exit(0);};
	
create_index
	: CREATE_INDEX VARIABLE LEFT_PARENTHESIS VARIABLE RIGHT_PARENTHESIS {
		int fid = getLogicfidByName(&head, $2.name);
		createIndexOn(&head, fid, $4.name);
	}
	;

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
		printf("create table %s succeed!\n", head.redef[n].getRelationName());
	/*	for(int i=0; i<head.redef[n].getAttributeNum(); i++) {
			printf("%s %d ", head.redef[n].getAttributeByNo(i).getName(), head.redef[n].getAttributeByNo(i).getType());
		}*/
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
		printf("insert into %s value %s\n", $2.name, tmp);
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
	| DELETE FROM VARIABLE WHERE where_list END {
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
		sprintf(condition_array[cur_condition].attribute_value, "%d", $1.val);
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
		condition_array[cur_condition].isjoin = false;
		cur_condition += 1; }
	| c_attribute compare_opt cc_attribute {
		condition_array[cur_condition].operation = $2.val;
		condition_array[cur_condition].isjoin = true;
		cur_condition += 1; }
	;

select
	: SELECT STAR FROM VARIABLE {
		int logicfid = getLogicfidByName(&head, $4.name);
		if (logicfid != -2) {
			int tmp_dict_id = TableScan(&head, temp_data_dict, $4.name);
		    
		    printTempTable(&head, temp_data_dict, tmp_dict_id);
		    
		}
	}
	| SELECT attribute_list FROM table_list WHERE where_list END{
		
	/*	printf("-------------------------------\n");
		printf("selected attributes: ");
		for (int i=0; i<cur_sattr; i++) {
			printf("%s ", select_attributes[i]);
		}
		printf("\n");

		printf("from %d tables: ", cur_table);
		for (int i=0; i<cur_table; i++) {
			printf("%s ", table_array[i]);
		}
		printf("\n"); 
		
		for (int i=0; i<cur_condition; i++) {
			printf("%d condition: %s %d %s\n", i+1, condition_array[i].attribute_name, condition_array[i].operation, condition_array[i].attribute_value);
		}
		printf("--------------------------------\n");*/
		
		if( cur_table == 1) {
			// fisrt projection, attributes in selected results and conditions
			int project_attrnum = cur_sattr;
			char project_attrname[10][NAMELENGTH];
			for (int i=0; i<cur_sattr; i++)
				strcpy(project_attrname[i], select_attributes[i]);

			for (int i=0; i<cur_condition; i++) {
				int j=0;
				for (j=0; j<project_attrnum; j++) {
					if (strcmp(condition_array[i].attribute_name, project_attrname[j])==0)
						break;
				}
				if (j == project_attrnum) {
					strcpy(project_attrname[project_attrnum], condition_array[i].attribute_name);
					project_attrnum++;
				}
			}
			/*
			for(int i=0; i<project_attrnum; i++)
				printf("project attr: %s\n", project_attrname[i]);
			for(int i=0; i<cur_sattr; i++)
				printf("selected attr: %s\n", select_attributes[i]);
			*/
			// table scan
			int tmp_dict_id = TableScan(&head, temp_data_dict, table_array[0]);
			// check
			for (int i=0; i<cur_sattr; i++) {
				if(!is_in_table(temp_data_dict, tmp_dict_id, select_attributes[i])) {
					cout<<"The attribute "<<select_attributes[i]<<" is not in table!"<<endl;
					exit(0);
				}
			}
			
			// projection
			tmp_dict_id = project(&head, temp_data_dict, tmp_dict_id, project_attrnum, project_attrname);
			// selection
			for (int i=0; i<cur_condition; i++) {
				if (condition_array[i].operation == EQUAL) {
					// not consider whether the index exists
					tmp_dict_id = tableScanEqualFilter(&head , temp_data_dict, tmp_dict_id, condition_array[i].attribute_name, condition_array[i].attribute_value);
				}
				// else just include <, <=, >, >=
				else {
					tmp_dict_id = tableScanSemiscopeFilter(&head, temp_data_dict, tmp_dict_id, condition_array[i].attribute_name, condition_array[i].attribute_value, condition_array[i].operation);
				}
			}
			// last projection
			if (project_attrnum > cur_sattr) {
				tmp_dict_id = project(&head, temp_data_dict, tmp_dict_id, cur_sattr, select_attributes);
			}
			// the results is in tmp_dict_id, how to read??
			printTempTable(&head, temp_data_dict, tmp_dict_id);
		}

		// multi tables join 
		else {
			// scan for each table
			int tmp_dict_id[cur_table];
			for (int k=0; k<cur_table; k++) {
				tmp_dict_id[k] = TableScan(&head, temp_data_dict, table_array[k]);
			}
			// first projection, attributes in selected results and conditions for each table
			int project_attrnum[cur_table] = {0, 0};
			char project_attrname[cur_table][10][NAMELENGTH];
			int single_condition_num[cur_table] = {0, 0};
			int single_condition_id[cur_table][10];
			int join_num = 0;
			int join_table[cur_table][2];
			char join_attrname[cur_table][NAMELENGTH];
			int final_project_attrnum = 0;
			char final_project_attrname[10][NAMELENGTH];

			// add the selected attributes into projection attribute
			for (int i=0; i<cur_sattr; i++) {
				// check the format: table.attribute or attribute
				int c = 0;
				int length = strlen(select_attributes[i]);
				for (c=0; c<length; c++) {
					if (select_attributes[i][c] == '.') {
						break;					
					}
				}
				// if format: table.attribute, then add to the table
				if (c < length) {
					strncpy(final_project_attrname[final_project_attrnum], select_attributes[i], c);
					final_project_attrname[final_project_attrnum][c] = '\0';
					for (int k=0; k<cur_table; k++) {
						if (strcmp(final_project_attrname[final_project_attrnum], table_array[k])==0) {
							// first projection
							strncpy(project_attrname[k][project_attrnum[k]], select_attributes[i]+c+1, length-c);
							project_attrnum[k]++;
							// final projection
							strcat(final_project_attrname[final_project_attrnum], "_");
							strcat(final_project_attrname[final_project_attrnum], select_attributes[i]+c+1);
							// test print
						//	printf("final project: %s\n", final_project_attrname[final_project_attrnum]);
							final_project_attrnum++;
						}
					}
				}
				// if format: attribute, find the table and add
				else {
					int is_confuse = 0;
					for (int k=0; k<cur_table; k++) {
						if (is_in_table(temp_data_dict, tmp_dict_id[k], select_attributes[i])) {
							is_confuse++;
							if (is_confuse > 1)
								break;
							strcpy(project_attrname[k][project_attrnum[k]], select_attributes[i]);
							project_attrnum[k]++;
							strcpy(final_project_attrname[final_project_attrnum], select_attributes[i]);
							final_project_attrnum++;
						}
					}
					if (is_confuse > 1) {
						printf("the attribute %s is in multiple tables\n", select_attributes[i]);
						exit(0);
					}
				}
			}
			// add the condition attributes into projection attribute, avoid repeatable attribute
			for (int i=0; i<cur_condition; i++) {
				// isjoin: table1.attr1 = table2.attr2; not isjoin: attr = const
				// printf("isjoin: %d\n", condition_array[i].isjoin);
				if (condition_array[i].isjoin) {
					// add table1.attr1 to table1's project_attrname
					int c = 0;
					int length = strlen(condition_array[i].attribute_name);
					for (c=0; c<length; c++) {
						if (condition_array[i].attribute_name[c] == '.') {
							break;					
						}
					}
					char tmp_name[NAMELENGTH];
					strncpy(tmp_name, condition_array[i].attribute_name, c);
					tmp_name[c] = '\0';
					// join the table1.attr = table2.attr, the attr is the same
					strncpy(join_attrname[join_num], condition_array[i].attribute_name+c+1, length-c);
		
					for (int k=0; k<cur_table; k++) {
						// printf("table name %s %s\n", tmp_name, table_array[k]);
						if (strcmp(tmp_name, table_array[k])==0) {
							join_table[join_num][0] = k;
							strncpy(project_attrname[k][project_attrnum[k]], condition_array[i].attribute_name+c+1, length-c);
							int j = 0;
							for (j=0; j<project_attrnum[k]; j++) {
								if (strcmp(project_attrname[k][project_attrnum[k]], project_attrname[k][j]) == 0)
									break;
							}
							if (j == project_attrnum[k])
								project_attrnum[k]++;
						}
					}
					// add table2.attr2 to table2's project_attrname
					c = 0;
					length = strlen(condition_array[i].attribute_value);
					for (c=0; c<length; c++) {
						if (condition_array[i].attribute_value[c] == '.') {
							break;					
						}
					}
					char tmp_name2[NAMELENGTH];
					strncpy(tmp_name2, condition_array[i].attribute_value, c);
					tmp_name2[c] = '\0';
					for (int k=0; k<cur_table; k++) {
						// printf("table 2 %s %s\n", tmp_name2, table_array[k]);
						if (strcmp(tmp_name2, table_array[k])==0) {
							join_table[join_num][1] = k;
							strncpy(project_attrname[k][project_attrnum[k]], condition_array[i].attribute_value+c+1, length-c);
							int j = 0;
							for (j=0; j<project_attrnum[k]; j++) {
								if (strcmp(project_attrname[k][project_attrnum[k]], project_attrname[k][j]) == 0)
									break;
							}
							if (j == project_attrnum[k])
								project_attrnum[k]++;
						}
					}
					
					join_num++;
				}
				// not isjoin: attr = const
				else {
					for (int k=0; k<cur_table; k++) {
						int is_confuse = 0;
						if (is_in_table(temp_data_dict, tmp_dict_id[k], condition_array[i].attribute_name)) {
							is_confuse++;
							if (is_confuse > 1) {
								printf("Error: the attribute %s is in multiple tables\n", condition_array[i].attribute_name);
								exit(0);
							}
							// add condition for each table
							single_condition_id[k][single_condition_num[k]] = i;
							single_condition_num[k]++;
							int j = 0;
							for (j=0; j<project_attrnum[k]; j++) {
								if (strcmp(condition_array[i].attribute_name, project_attrname[k][j])==0)
									break;
							}
							if (j == project_attrnum[k]) {							
								strcpy(project_attrname[k][project_attrnum[k]], condition_array[i].attribute_name);
								project_attrnum[k]++;
							}								
						}												
					}
				}
			}
		
		/*	printf("################################\n");
			for (int k=0; k<cur_table; k++) {
				for (int i=0; i<project_attrnum[k]; i++) {
					printf("table %d %s first projection: %s\n", k+1, table_array[k], project_attrname[k][i]);
				}
			}
			for (int k=0; k<cur_table; k++) {
				printf("table %s %d conditions\n", table_array[k], single_condition_num[k]);
				for (int i=0; i<single_condition_num[k]; i++) {
					int s = single_condition_id[0][i];
					printf("%d condition %s %s\n", i+1, condition_array[s].attribute_name, condition_array[s].attribute_value);
				}
			}
			for (int i=0; i<join_num; i++)
				printf("join %s %s condition attr: %s\n", table_array[join_table[i][0]], table_array[join_table[i][1]], join_attrname[i]);
			for (int i=0; i<final_project_attrnum; i++)
				printf("final project attr %s\n", final_project_attrname[i]);
			printf("###############################\n"); */
			
			
			// operation on single table
			for (int k=0; k<cur_table; k++) {
				// first projection
				tmp_dict_id[k] = project(&head, temp_data_dict, tmp_dict_id[k], project_attrnum[k], project_attrname[k]);
			//	printf("## join table id %d, tmp_dict id %d\n", join_table[0][0], tmp_dict_id[join_table[0][0]]);
			//	printf("### after project dict indexed %d\n", head.redef[1].getIndexedByName("nationkey"));
			//	printf("#### after project is indexed %d#########\n", temp_data_dict[tmp_dict_id[k]].getIndexedByName("nationkey"));
				// selection
				for (int i=0; i<single_condition_num[k]; i++) {
					if (condition_array[single_condition_id[k][i]].operation == EQUAL) {
						// not consider whether the index exists
						tmp_dict_id[k] = tableScanEqualFilter(&head , temp_data_dict, tmp_dict_id[k], condition_array[single_condition_id[k][i]].attribute_name, condition_array[single_condition_id[k][i]].attribute_value);
			//			printf("####after select is indexed %d#########\n", temp_data_dict[tmp_dict_id[k]].getIndexedByName(join_attrname[0]));
					}
					// else just include <, <=, >, >=
					else {
						tmp_dict_id[k] = tableScanSemiscopeFilter(&head, temp_data_dict, tmp_dict_id[k], condition_array[single_condition_id[k][i]].attribute_name, condition_array[single_condition_id[k][i]].attribute_value, condition_array[single_condition_id[k][i]].operation);
					}
				}
			}
			/*
			printf("###########table 1###############");
			printTempTable(&head, temp_data_dict, tmp_dict_id[0]);
			printf("###########table 2###############");
			printTempTable(&head, temp_data_dict, tmp_dict_id[1]);
			*/
		/*	for(int k=0; k<cur_table; k++)
				printf("####table %d is indexed %d on %s#########\n", k, temp_data_dict[tmp_dict_id[k]].getIndexedByName(join_attrname[0]), join_attrname[0]);
			*/
			// join 2 tables
			int tmp_join_dict_id;
			if (join_num == 1) {
				tmp_join_dict_id = choosejoin(&head, temp_data_dict, tmp_dict_id[join_table[0][0]], tmp_dict_id[join_table[0][1]], join_attrname[0]);
			}
			// join 3 tables
			else if (join_num == 2) {
			//	cout<<"before join"<<join_table[0][0]<<join_table[0][1]<<join_attrname[0]<<endl;
				tmp_join_dict_id = choosejoin(&head, temp_data_dict, tmp_dict_id[join_table[0][0]], tmp_dict_id[join_table[0][1]], join_attrname[0]);				
			//	cout<<"after join "<<temp_data_dict[tmp_join_dict_id].getAttributeNum()<<" name "<<temp_data_dict[tmp_join_dict_id].getRelationName()<<endl;
				//for(int i=0; i<temp_data_dict[tmp_join_dict_id].getAttributeNum(); i++)
				//	cout<<"-----------"<<temp_data_dict[tmp_join_dict_id].getAttributeByNo(i).getName()<<endl;
				for (int i=0; i<2; i++) {
				//	cout<<"not in "<<join_table[1][i]<<join_table[0][1]<<join_table[0][0]<<endl;
					if (join_table[1][i]==join_table[0][0] || join_table[1][i]==join_table[0][1]) {
					//	cout<<"---2 table"<<join_table[1][1-i]<<endl;
					//	for(int k=0; k<temp_data_dict[tmp_dict_id[join_table[1][1-i]]].getAttributeNum(); k++)
					//		cout<<"-----------"<<temp_data_dict[tmp_dict_id[join_table[1][1-i]]].getAttributeByNo(k).getName()<<endl;
						tmp_join_dict_id = choosejoin(&head, temp_data_dict, tmp_join_dict_id, tmp_dict_id[join_table[1][1-i]], join_attrname[1]);
				//		cout<<"after join "<<temp_data_dict[tmp_join_dict_id].getAttributeNum()<<" name "<<temp_data_dict[tmp_join_dict_id].getRelationName()<<endl;
					}
				}
			}
			// join multiple tables
			else {
				
			}
			
			
			/*
			printf("############join##############\n");
			printTempTable(&head, temp_data_dict, tmp_join_dict_id);
			*/
			
			// project final result
		//	cout<<"final project num "<<final_project_attrnum<<endl;
		/*	for(int i=0; i<final_project_attrnum; i++)
				cout<<final_project_attrname[i]<<endl;	*/
			tmp_join_dict_id = project(&head, temp_data_dict, tmp_join_dict_id, final_project_attrnum, final_project_attrname);
			
			// print results
		/*	printf("---------------------------------------------");
			printf("id %d\n", tmp_join_dict_id);*/
			printTempTable(&head, temp_data_dict, tmp_join_dict_id);	
		}
		
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
	: table_list COMMA single_table
	| single_table
	;
	
single_table
	: VARIABLE {strcpy(table_array[cur_table], $1.name); cur_table++; }
	;

%%

bool is_in_table(relation *temp_data_dict, int dict_id, char *attr_name) {
	for (int i = 0; i < temp_data_dict[dict_id].getAttributeNum(); i++) {
		if (strcmp(attr_name, temp_data_dict[dict_id].getAttributeByNo(i).getName()) == 0) {
			return true;
		}
	}
	return false;
}

int find_empty_tempdict(relation *temp_data_dict){
    int i = 0;
    for (i = 0; i < MAX_FILE_NUM; i++) {
        if (strcmp(temp_data_dict[i].getRelationName(),"") == 0) {
            temp_data_dict[i].init("temp_datadict","XXX");
            return i;
        }
    }
    if (i == MAX_FILE_NUM) {
        cout<<"no temp datadict for use!"<<endl;
        return -3;
    }
}

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

int main(int argc, char *argv[]) {
	cout<<"Welcome to Database Management System!"<<endl;
	init_database(&head);
	if (argc==2 && strcmp(argv[1], "big")==0) {
		createTable(&head);
		loaddata(&head, 1);
	//	createIndexOn(&head, 1, "custkey");

		createTable(&head);
		loaddata(&head, 2);
	//	createIndexOn(&head, 2, "nationkey");
		
		createTable(&head);
		loaddata(&head, 3);
	//	createIndexOn(&head, 3, "regionkey");
	}

	cur_attribute = 0;
	cur_condition = 0;
	cur_value = 0;
    yyparse();
}

void yyerror(char *s) {
    printf("Wrong Syntax, Please Try Again!\n");
    yyparse();
}

int yywrap() {
	return 1;
}
