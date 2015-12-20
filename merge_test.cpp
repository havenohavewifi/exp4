
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
#include "createTable.h"
#include "sortmergejoin.h"
#include "insertOneTuple.h"
#include "deleteRecords.h"
#include "deleteAllTuples.h"

int init_database(struct dbSysHead *head)
{
	initSys(head);
	head->fpdesc = fopen(DBMS_DAT, "rb+");
	isAvail(head->fpdesc, "main", FOPEN);
	return 0;
}

int exit_database(struct dbSysHead *head)
{
	sysUpdate(head);
	fclose(head->fpdesc);
	free(head->bitMap);
	return 0;
}


int showRelation(relation *r)
{
	printf("TableName: %s\n", r->getRelationName());
	printf("Constructor: %s\n", r->getConstructor());
	printf("AttributeNum: %d\n", r->getAttributeNum());
	for (int j = 0; j < r->getAttributeNum(); j++)
	{
		printf("%d:%s\n", j + 1, r->getAttributeByNo(j).getName());
	}
	printf("RecordLength: %d\n", r->getRecordLength());
	return 0;
}

int main()
{
	struct dbSysHead head;
	long fid1, fid2;

	init_database(&head);
	showDesc(&head);
	showFileDesc(&head);

    if(createTable(&head) == -1)
        printf("Create Table failed\n");
    if(createTable(&head) == -1)
        printf("Create Table failed\n");
	 if(createTable(&head) == -1)
        printf("Create Table failed\n");
   
   
    //read customer.tbl and write into our file1, 一次性
    loaddata(&head, FIRST_FID);
    loaddata(&head, FIRST_FID + 1);
    loaddata(&head, FIRST_FID + 2);
    sysUpdate(&head);


    relation * temp_data_dict = new relation[MAX_FILE_NUM];
    //Scan Table
    int customer_scan = -1;
    customer_scan = TableScan(&head, temp_data_dict, "customer");
    if (customer_scan>=0) {
        printf("customer_scan succeed!\n");
    }
	int nation_scan = -1;
    nation_scan = TableScan(&head, temp_data_dict, "nation");
    if (nation_scan>=0) {
        printf("nation_scan succeed!\n");
    }
	
    cout<<"is indexed:"<<head.redef[1].getIndexedByName("nationkey")<<endl;
    head.redef[1].changeIndexedByName("nationkey",true);
    cout<<"is indexed:"<<head.redef[1].getIndexedByName("nationkey")<<endl;
    head.redef[1].changeIndexedByName("nationkey",false);
    cout<<"is indexed:"<<head.redef[1].getIndexedByName("nationkey")<<endl;



/*
    int result = sortmergejoin(&head, temp_data_dict, customer_scan, nation_scan, "nationkey");
    
    int buffer_ID_ = - temp_data_dict[result].fileID;   //find which buffer
    int record_num_ = temp_data_dict[result].getRecordNum();
    int record_len_ = temp_data_dict[result].getRecordLength();
    RecordCursorTmp t2(&head,-11,record_len_,buffer_ID_,record_num_);
    cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
    while (true == t2.getNextRecord(one_Row_)) { //only scan
        getOneRecord(one_Row_, &temp_data_dict[result]); //get each attribute value and print
    }
    free(one_Row_);*/

    sysUpdate(&head);
    showFileDesc(&head);
    exit_database(&head);
	system("pause");
	return 0;
}

