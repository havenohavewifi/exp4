
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

	/*
	≥ı ºªØ£¨»ª∫Û¥Ú”°≥ˆµ±«∞œµÕ≥µƒ–≈œ¢
	*/
	init_database(&head);
	showDesc(&head);

//	printf("create file1...\n");
	
	showFileDesc(&head);
/*	printf("extend 10 pages for file1...\n");
	extendFileSpace(&head, fid1, 10);//¿©’π Æ“≥
	showFileDesc(&head);
	printf("extend 10 pages for file1...\n");
	extendFileSpace(&head, fid1, 10);//‘Ÿ¿©’π Æ“≥
	showFileDesc(&head);

	printf("create file2...\n");
	fid2 = creatFileSpace(&head);
	showFileDesc(&head);
	printf("extend 10 pages for file2...\n");
	extendFileSpace(&head, fid2, 10);
	showFileDesc(&head);
	printf("extend 10 pages for file2...\n");
	extendFileSpace(&head, fid2, 10);
	showFileDesc(&head);

	printf("delete file1...\n");
	recyFileSpace(&head, fid1);
	showFileDesc(&head);
	printf("delete file2...\n");
	recyFileSpace(&head, fid2);
	showFileDesc(&head);*/
    //use dictID to scan file1
    /*
     int dictID = 1;
     int scanPointer = 0;
     int rec_length = head.redef[dictID].getRecordLength();
     printf("attributeName::%s", head.redef[dictID].getAttributeByNo(0).getName());
     RecordCursor scanTable(&head, 1, rec_length, 0);
     char * one_Row_ = (char *)malloc(sizeof(char)*rec_length);
     while (true == scanTable.getNextRecord(one_Row_)) { //only scan
     scanPointer ++;
     if(scanPointer > 230)
     getOneRecord(one_Row_, head.redef[dictID]); //get each attribute value and print
     }
     free(one_Row_);
     */
/*
    fid1 = creatFileSpace(&head);//Œ™Œƒº˛“ª∑÷≈‰ø’º‰
    fid2 = creatFileSpace(&head);
	
    if(initTable(&head, FIRST_FID) == 0)
		printf("1 initTable: customer.tbl\n");
	if(showTable(&head, "customer") == -1 )
		printf("2 showTable: customer\n");
    
    if(initTable(&head, FIRST_FID+1) == 0)
        printf("1 initTable: nation.tbl\n");
    if(showTable(&head, "nation") == -1 )
        printf("2 showTable: nation\n");
*/

    if(createTable(&head) == -1)
        printf("Create Table failed\n");
    if(createTable(&head) == -1)
        printf("Create Table failed\n");
 /*
    struct eachAttribute * nation_att = new struct eachAttribute[12];
    strcpy(nation_att[0].attribute_name_,"custkey");
    nation_att[0].attribute_type_ = 1;
    nation_att[0].attribute_length_ = 4;
    strcpy(nation_att[1].attribute_name_,"name");
    nation_att[1].attribute_type_ = 2;
    nation_att[1].attribute_length_ =32;
    strcpy(nation_att[2].attribute_name_,"address");
    nation_att[2].attribute_type_ = 2;
    nation_att[2].attribute_length_ =40;
    strcpy(nation_att[3].attribute_name_,"nationkey");
    nation_att[3].attribute_type_ = 1;
    nation_att[3].attribute_length_ = 4;
    strcpy(nation_att[4].attribute_name_,"phone");
    nation_att[4].attribute_type_ = 2;
    nation_att[4].attribute_length_ =16;
    strcpy(nation_att[5].attribute_name_,"acctbal");
    nation_att[5].attribute_type_ = 2;
    nation_att[5].attribute_length_ =64;
    strcpy(nation_att[6].attribute_name_,"mktsemgent");
    nation_att[6].attribute_type_ = 2;
    nation_att[6].attribute_length_ =12;
    strcpy(nation_att[7].attribute_name_,"comment");
    nation_att[7].attribute_type_ = 2;
    nation_att[7].attribute_length_ =128;
    if (createTable( &head, "customer", "TianzhenWu",  8, nation_att) == -1) {
        printf("Create Table failed\n");
    }
*/
    struct eachAttribute * region_att = new struct eachAttribute[3];
    strcpy(region_att[0].attribute_name_,"regionkey");
    region_att[0].attribute_type_ = 1;
    region_att[0].attribute_length_ = 4;
    strcpy(region_att[1].attribute_name_,"regionname");
    region_att[1].attribute_type_ = 2;
    region_att[1].attribute_length_ = 12;
    strcpy(region_att[2].attribute_name_,"regioncomment");
    region_att[2].attribute_type_ = 2;
    region_att[2].attribute_length_ = 152;
    if (createTable( &head, "region", "Mengxi", 3, region_att) == -1) {
        printf("Create Table failed\n");
    }
    relation * temp_data_dict = new relation[MAX_FILE_NUM];
    //read customer.tbl and write into our file1, 一次性
    loaddata(&head, FIRST_FID);
    loaddata(&head, FIRST_FID + 1);
    loaddata(&head, FIRST_FID + 2);
    sysUpdate(&head);

    insertOneTuple(&head, "customer", "501|Customer#000000501|IVhzIApeRb ot,c,E|15|25-989-741-2988|711.56|BUILDING|to the even, regular platelets.H|");
    
    insertOneTuple(&head, "customer", "1002|Customer#000001001|IVhzIApeRb ot,c,E|15|25-989-741-2988|711.56|BUILDING|to the even, regular platelets.HH|");
    
    insertOneTuple(&head, "customer", "1003|Customer#000001002|IVhzIApeRb ot,c,E|15|25-989-741-2988|711.56|BUILDING|to the even, regular platelets.HHH|");
    sysUpdate(&head);

    //Scan Table
    int customer_scan = -1;
    customer_scan = TableScan(&head, temp_data_dict, "customer");
    if (customer_scan>=0) {
        printf("tablescan succeed!\n");
    }
    //char attribute_list[3][NAMELENGTH] = {"address", "name", "custkey"};
    //if(project(&head, temp_data_dict, customer_scan, 3, attribute_list)>=0)
    //    printf("project succeed!\n");
    //for each old table, only one time SPJ operator allowed, because it will be freed by this SPJ operator.
    /*
    printf("start tableScanEqualFilter()...\n");
    relation filter_result1;
    if(true == tableScanEqualFilter(&head, &temp_data_dict[0],"custkey","3", &filter_result1)){
        printf("tableScanEqualFilter()\n");
    }

    relation filter_result2;
    if(true == tableScanEqualFilter(&head, &temp_data_dict[0],"name","Customer#000000009", &filter_result2)){
        printf("tableScanEqualFilter()\n");
    }

    relation filter_result3;
    if(true == tableScanScopeFilter(&head,  &temp_data_dict[0],"custkey","220",NOT_MORE_THAN,"230",LESS_THAN,&filter_result3)){
        printf("tableScanScopeFilter()\n");
    }
    RecordCursorTmp t2(&head,-2,filter_result3.getRecordLength(), - filter_result3.fileID,filter_result3.getRecordNum());
    char * one_Row_ = (char *)malloc(sizeof(char)* filter_result3.getRecordLength());
    while (true == t2.getNextRecord(one_Row_)) { //only scan
        getOneRecord(one_Row_, &filter_result3); //get each attribute value and print
    }
    free(one_Row_);
*/
    

/*
    //get the output of tablescan, temporarily according to datadict1, other than temp_data_dict[1]
    int buffer_ID_ = - temp_data_dict[1].fileID;   //find which buffer
    int record_num_ = temp_data_dict[1].getRecordNum();
    int record_len_ = temp_data_dict[1].getRecordLength();
    RecordCursorTmp t1(&head,1,record_len_,buffer_ID_,record_num_);
    cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
    while (true == t1.getNextRecord(one_Row_)) { //only scan
        getOneRecord(one_Row_, &temp_data_dict[1]); //get each attribute value and print
    }
    free(one_Row_);
*/
printf("customer_scan:%d\n",customer_scan);
    	deleteRecordWhere(&head, FIRST_FID, "name", "Customer#000000005",LESS_THAN,0);

    printf("start tableScanEqualFilter()...\n");
    
    int filterFlag=-1;
//    filterFlag = tableScanSemiscopeFilter(&head, temp_data_dict, customer_scan,"custkey","3",LESS_THAN);

    filterFlag = tableScanSemiscopeFilter(&head, temp_data_dict,customer_scan, "name","Customer#000000009",NOT_MORE_THAN);

    int buffer_ID_,record_num_,record_len_; 
    buffer_ID_ = - temp_data_dict[filterFlag].fileID;   //find which buffer
    record_num_ = temp_data_dict[filterFlag].getRecordNum();
    record_len_ = temp_data_dict[filterFlag].getRecordLength();
    RecordCursorTmp t2(&head,1,record_len_,buffer_ID_,record_num_);
    cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
    while (true == t2.getNextRecord(one_Row_)) { //only scan
        //printf("%s\n",one_Row_);
	//if(strcpy(one_Row_,"\0") == 0)
           // break;
    //    getOneRecord(one_Row_, &temp_data_dict[filterFlag]); //get each attribute value and print
    }
    free(one_Row_);
 printf("HERE~~~\n\n");
    deleteRecordWhere(&head, FIRST_FID, "name", "Customer#000000005",EQUAL,0); 
    customer_scan = -1;
    customer_scan = TableScan(&head, temp_data_dict, "customer");
    if (customer_scan>=0) {
        printf("tablescan succeed!\n");
    }
    printf("customer_scan:%d\n",customer_scan);
    buffer_ID_ = - temp_data_dict[customer_scan].fileID;   //find which buffer
    record_num_ = temp_data_dict[customer_scan].getRecordNum();
    record_len_ = temp_data_dict[customer_scan].getRecordLength();
    RecordCursorTmp t3(&head,1,record_len_,buffer_ID_,record_num_);
    cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    while (true == t3.getNextRecord(one_Row_)) { //only scan
        //printf("%s\n",one_Row_);
        //if(strcpy(one_Row_,"\0") == 0)
           // break;
        getOneRecord(one_Row_, &temp_data_dict[filterFlag]); //get each attribute value and print
    }
    free(one_Row_);


//    TableScan(&head, FIRST_FID + 1, temp_data_dict);
/*
    //get the output of tablescan, temporarily according to datadict1, other than temp_data_dict[1]
    buffer_ID_ = - temp_data_dict[1].fileID;   //find which buffer
    record_num_ = temp_data_dict[1].getRecordNum();
    record_len_ = temp_data_dict[1].getRecordLength();
    cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    RecordCursorTmp t2(&head,2,record_len_,buffer_ID_,record_num_);
    one_Row_ = (char *)malloc(sizeof(char)*record_len_);
    while (true == t2.getNextRecord(one_Row_)) { //only scan
        getOneRecord(one_Row_, &temp_data_dict[1]); //get each attribute value and print
    }
    free(one_Row_);
 */
    // create index
/*
    printf("recordNum:%d\n",head.redef[dictID].recordNum);
	if(true == createIndexOn(&head, 1, "custkey")){
		char* index_filename= "b_plus_tree_index_1custkey.dat";
		
		FILE* fp = fopen(index_filename,"rb+");
		printf("search(fp,-10):%d\n",search(fp,-10));
		printf("search(fp,1):%d\n",search(fp,1));
		printf("search(fp,2):%d\n",search(fp,2));
		printf("search(fp,50):%d\n",search(fp,50));
		display(fp);
		fclose(fp);
	}
	
    // insert one record
	relationDefine dic = head.redef[0];
    int size_per_record = dic.recordLength;
    char *oneRec = (char *)malloc(sizeof(char)*size_per_record);
        
	char * insertTest = (char *)malloc(sizeof(char)* 256);
    strcpy(insertTest,"501|Customer#000000001|IVhzIApeRb ot,c,E|15|25-989-741-2988|711.56|BUILDING|to the even, regular platelets. regular, ironic epitaphs nag eHHHHHH|");
    parserOneLineFromFile(insertTest, oneRec, dic);
    insertOneRecord(&head, 1, oneRec);//≤Â»Î“ªÃı ˝æ›£¨◊‘∂Ø∏¸–¬À˜“˝
	free(insertTest);
    free(oneRec);
    
    // look up key in index
	char* index_filename= "b_plus_tree_index_1custkey.dat";
	FILE* fp = fopen(index_filename,"rb+");
	int pos = search(fp,501);
	printf("pos:::%d\n",pos);
	fclose(fp);
 
	one_Row_ = (char *)malloc(sizeof(char)*rec_length);
	rdFile( &head, 0, 1, pos, rec_length,one_Row_);
	printf("reading from index:\n");
	getOneRecord(one_Row_, dic);
*/
 /*   //nestloop_cp
    relation result;
    result.init("cus_nation", "zhangwenhui");
    /*merge_relation_cp(&head,temp_data_dict[0],temp_data_dict[1],&result);
     showRelation(&result);
     
     nestloop_cp(&head, &temp_data_dict[0],&temp_data_dict[1], &result);*/
/*
    //nestloop_equal
    merge_relation(&head,temp_data_dict[0],temp_data_dict[1],&result);
    //nestloop_equal(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");
    //nestloop_bigger(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");
    //nestloop_smaller(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");
    nestloop_smaller_or_equal(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");
    //nestloop_bigger_or_equal(&head, &temp_data_dict[0],&temp_data_dict[1], &result,"nationkey");

*/
    //project customer
/*	relation c_result;
	c_result.init("customer", "TianzhenWu");
	c_result.insertAttribute("name", 2, 64);
    c_result.insertAttribute("nationkey",1,4);
	c_result.insertAttribute("phone", 2, 64);
	showRelation(&c_result);
	project(&head, &temp_data_dict[0], &c_result);

    //project nation.tbl
    relation n_result;
    n_result.init("nation", "MengxiZhou");
    n_result.insertAttribute("nationkey", 1, 4);
    n_result.insertAttribute("name", 2, 16);
    n_result.insertAttribute("regionkey", 1, 4);
    showRelation(&n_result);
    project(&head, &temp_data_dict[1], &n_result);
*/
 /*
//    relation hashjoin_result_;
//    hashjoin_result_.init("customer_nation_hash", "irenewu");
//    hashjoin(&head, &c_result, &n_result, &hashjoin_result_,"nationkey");
    
    relation result;
    result.init("sortmergejoin zmx","zmx");
//    	merge_relation(&head, c_result, n_result, &result);
//    result.insertAttribute("custkey", 1, 4);
    result.insertAttribute("name", 2, 32);
//    result.insertAttribute("address", 2, 40);
    result.insertAttribute("nationkey", 1, 4);
    result.insertAttribute("phone", 2, 16);
//    result.insertAttribute("acctbal", 2, 64);
//    result.insertAttribute("mktsegment", 2, 12);
//    result.insertAttribute("comment", 2, 128);
    result.insertAttribute("nationkey", 1, 4);
    result.insertAttribute("name", 2, 32);
    result.insertAttribute("regionkey", 1, 4);
//    result.insertAttribute("comment", 2, 160);
    showRelation(&result);
    sortmergejoin(&head, &c_result, &n_result, "nationkey", &result);
    
    int buffer_ID_ = - result.fileID;   //find which buffer
    int record_num_ = result.getRecordNum();
    int record_len_ = result.getRecordLength();
    RecordCursorTmp t2(&head,-11,record_len_,buffer_ID_,record_num_);
    cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
    while (true == t2.getNextRecord(one_Row_)) { //only scan
        getOneRecord(one_Row_, &result); //get each attribute value and print
    }
    free(one_Row_);
/*
    //filter
    printf("start tableScanEqualFilter()...\n");
    
    if(true == tableScanEqualFilter(&head, FIRST_FID, temp_data_dict,"custkey","3",&temp_data_dict[5])){
        printf("tableScanEqualFilter()\n");
    }

    if(true == tableScanEqualFilter(&head, FIRST_FID, temp_data_dict,"name","Customer#000000009",&temp_data_dict[5])){
        printf("tableScanEqualFilter()\n");
    }
  
    buffer_ID_ = - temp_data_dict[5].fileID;   //find which buffer
    record_num_ = temp_data_dict[5].getRecordNum();
    record_len_ = temp_data_dict[5].getRecordLength();
    RecordCursorTmp t2(&head,1,record_len_,buffer_ID_,record_num_);
    cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
    char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
    while (true == t2.getNextRecord(one_Row_)) { //only scan
        getOneRecord(one_Row_, &temp_data_dict[5]); //get each attribute value and print
    }
    free(one_Row_);
    //head.buff[buffer_ID_].emptyOrnot = false;
 
    if(true == tableScanScopeFilter(&head, FIRST_FID, temp_data_dict,"custkey","220",NOT_MORE_THAN,"230",LESS_THAN,&temp_data_dict[5])){
        printf("tableScanScopeFilter()\n");
    }
*/

    showFileDesc(&head);
    dropTable(&head,"customer");
    deleteAllTuples(&head,"nation");
    dropTable(&head,"nation");

/*
   if(true == createIndexOn(&head, FIRST_FID, "custkey")){
        char* index_filename = "/Users/Irene/Desktop/b_plus_tree_index_1custkey.dat";
        FILE* fp;
        int pos;

        if( !(fp = fopen(index_filename,"rb+")))
                printf("error indexFile name.\n");
        printf("search(fp,-10):%d\n",search(fp,-10));
        printf("search(fp,1):%d\n",search(fp,1));
        printf("search(fp,2):%d\n",search(fp,2));
        printf("search(fp,50):%d\n",search(fp,50));
        //display(fp);


        deleteRecordWhere(&head, FIRST_FID, "name", "Customer#000000005",LESS_THAN,0);
        pos = search(fp,5);

        fclose(fp);
        printf("%d\n",pos);

        printf("start indexScanEqualFilter()...\n");
        if(true == indexScanEqualFilter(&head, FIRST_FID, "custkey","4",&temp_data_dict[5])){
          printf("indexScanEqualFilter(9) end!\n");

          buffer_ID_ = - temp_data_dict[5].fileID;   //find which buffer
          record_num_ = temp_data_dict[5].getRecordNum();
          record_len_ = temp_data_dict[5].getRecordLength();
          RecordCursorTmp t3(&head,1,record_len_,buffer_ID_,record_num_);
          cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
          one_Row_ = (char *)malloc(sizeof(char)*record_len_);
          while (true == t3.getNextRecord(one_Row_)) { //only scan
                if(one_Row_[0] == '$')
                        printf("empty\n");
           //getOneRecord(one_Row_, &temp_data_dict[5]); //get each attribute value and print
          }
          free(one_Row_);
          head.buff[buffer_ID_].emptyOrnot = true;

        }
    }//end of createIndexOn if
*/
    sysUpdate(&head);
    showFileDesc(&head);
    exit_database(&head);
	system("pause");
	return 0;
}

