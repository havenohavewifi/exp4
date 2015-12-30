#include <iostream>
#include <string.h>
#include "join_indexjoin.h"
#include "cursor.h"
#include "cursorForTmptable.h"
#include "Buffer.h"
#include "file.h"
#include "indexOpt.h"
#include "dataDictionary.h"
#include "getaRecordbyCursor.h"
#include "nestloop.h"
#include "sortmergejoin.h"
#include "join_Hashjoin.h"
#include "join.h"
int choosejoin(struct dbSysHead *head, relation *temp_datadic,int old_relation_1, int old_relation_2, const char *name){
	int return_num=-1;
	int small_num=5;
	int big_num=5;
	int num_record_1=temp_datadic[old_relation_1].getRecordNum();
	int num_record_2=temp_datadic[old_relation_2].getRecordNum();
//	cout<<"record_1:"<<num_record_1<<"record_2:"<<num_record_2<<endl;
	int goal_2=-1;
	 for (int i = 0; i<MAX_FILE_NUM; i++) {
		if (strcmp((head->redef)[i].getRelationName(),temp_datadic[old_relation_2].getRelationName())==0) {
			goal_2=i;
			break;
		}
	 }
	int actual_2=(head->desc).fileDesc[goal_2].fileID;
	int goal_1=-1;
	 for (int i = 0; i<MAX_FILE_NUM; i++) {
		if (strcmp((head->redef)[i].getRelationName(),temp_datadic[old_relation_1].getRelationName())==0) {
			goal_1=i;
			break;
		}
	 }
	int actual_1=(head->desc).fileDesc[goal_2].fileID;	
	char* name_new = new char[100];//×ã¹»³¤
	strcpy(name_new,name);
	if(num_record_1<small_num&&num_record_2<small_num){
		//not too big choose nestloop
	//	cout<<"choose nestloop"<<endl;
		return_num=nestloop_equal_new(head,temp_datadic,old_relation_1,old_relation_2,name_new);
	}else{
		//if it has index choose index hash
	//	cout<<(int)true<<endl;
	//	cout<<"index:"<<head->redef[goal_2].getIndexedByName(name_new)<<endl;
		
		/*cout<<temp_datadic[old_relation_1].getAttributeByName(name_new).isIndexed()<<endl;
		cout<<((head->redef[goal_1].getAttributeByName(name_new).isIndexed())==1)<<endl;*/
		if(head->redef[goal_1].getIndexedByName(name_new)>0){
			cout<<"choose index 1 indexjoin"<<endl;
			return_num=indexjoin(head,temp_datadic,old_relation_2,old_relation_1,name_new);
		}else{
			if(head->redef[goal_2].getIndexedByName(name_new)>0){
				cout<<"choose index 2 indexjoin"<<endl;
				return_num=indexjoin(head,temp_datadic,old_relation_1,old_relation_2,name_new);
			}else
			{
				if(num_record_1>big_num||num_record_2>big_num){
					cout<<"choose hashjoin"<<endl;
					if(num_record_1<num_record_2){
						return_num=hashjoin(head,temp_datadic,old_relation_1,old_relation_2,name);
					}else{
						return_num=hashjoin(head,temp_datadic,old_relation_2,old_relation_1,name);
					}
				}else{
					cout<<"choose mergejoin"<<endl;
					return_num=sortmergejoin(head,temp_datadic,old_relation_1,old_relation_2,name_new);
				}
			}
		}
	}
	//cout<<"return_num"<<return_num<<endl;
	return return_num;
	//sortmergejoin(head,temp_datadic,old_relation_1,old_relation_2,name_new);
}
