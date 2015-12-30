extern "C"{
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
}

#include"dbHead.h"
#include "file.h"
#include "b_plus_tree.h"
#include "loaddata.h"
#include "cursor.h"
#include "getaRecordbyCursor.h"


/**
 * @brief 在表的某一属性上建立B+树索引
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid : long
 * @param [in] column : char*
 * @return  bool
 *
 * @author weiyu
 * @date 2015/11/8
 **/
bool createIndexOn(struct dbSysHead *head, long fid, char* column){
    

    printf("create index on %s....\n",column);
    int idx;
    char* index_filename;
    char* indexname = "b_plus_tree_index_";
    char fileID[5] = "";
    sprintf(fileID,"%d",fid);
    Element elem_insert;
    FILE *fp_create;
    FILE *fp;
    int key;
    int location;
    
    index_filename = (char *)malloc( 3*NAMELENGTH + 50);
    *index_filename = '\0';
    index_filename = strcat(index_filename, Index_Path);
    index_filename = strcat(index_filename,indexname);
    index_filename = strcat(index_filename,fileID);
    index_filename = strcat(index_filename,column);
    index_filename = strcat(index_filename,".dat");
    printf("%s\n",index_filename);
    
    //查询数据字典，获取属性序号
    idx =  queryFileID(head, fid);
    if( idx<0 ) {
        isAvail(NULL,"createIndexOn",ARRAY);
    }
/*
    if(head->redef[idx].getAttributeByName(column) == NULL){
        printf("No such attribute.\n");
        return false;
    }
*/
    //if indexed
    if(head->redef[idx].getIndexedByName(column) == true){
	printf("Index on %s is already existed. Rebuilding the index!\n", column);
        //return true;
    }
    
    //属性不是整型时，不建立索引，返回false
    if( head->redef[idx].getAttributeByName(column).getType() != INT){
        printf("Not an int attribute.\n");
        return false;
    }

    
    //打开索引文件
    fp_create = fopen(index_filename,"wb");
    fclose(fp_create);
    fp = fopen(index_filename,"rb+");
    if( fp==NULL){
        printf("fopen error!\n");
        exit(0);
    }
    free(index_filename);
    //遍历表中的数据
    
    int scanPointer = 0;
    int offset;
    long rec_length = (long)(head->redef[idx].getRecordLength());
    // default use the first buffer block
    RecordCursor scanTable(head, fid, rec_length,0);
    char * one_Row_ = (char *)malloc(sizeof(char)*rec_length);
    while (true == scanTable.getNextRecord(one_Row_)) { //only scan
        offset = head->redef[idx].getAttributeByName(column).getRecordDeviation();
        key = *((int *)(one_Row_ + offset));
        //getcLogicLocation() is the location of ccursor, not the record!
        location = scanTable.getcLogicLocation()-rec_length;
        //printf("key::%d, location::%d\n",key,location);
        elem_insert.key = key;
        elem_insert.pos = location;
        //将一个记录对应的elem写入索引文件
        insert(fp, elem_insert);
        scanPointer ++;
        //display(fp);
       // printf("\n");
        //if(scanPointer > 30)//暂时只建立30条索引
        //    break;
        //getOneRecord(one_Row_, (head->desc).redef[idx]); //get each attribute value and print
    }
    
 //   printf("inserted %d records.\n",scanPointer-1);
    //test
    /*
     printf("search(fp,-10):%d\n",search(fp,-10));
     printf("search(fp,1):%d\n",search(fp,1));
     printf("search(fp,2):%d\n",search(fp,2));
     printf("search(fp,50):%d\n",search(fp,50));
     */
    fclose(fp);
    //modify the data dictionary
    head->redef[idx].changeIndexedByName(column,true);
    return true;
}


/**
 * @brief 删除整个索引
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid : long
 * @param [in] column : char*
 * @return  bool
 *
 * @author weiyu
 * @date 2015/12/20
 **/
bool deleteIndex(struct dbSysHead *head, long fid, char* column){
    //check
    //查询数据字典，获取属性
    int idx;
    idx =  queryFileID(head, fid);
    if( idx<0 ) {
        isAvail(NULL,"createIndexOn",ARRAY);
    }
    //if indexed
    if(head->redef[idx].getIndexedByName(column) == false){
	printf("No index on attribute:%s.\n", column);
        return false;
    }
    printf("删除索引....\n");
    
    char* index_filename;
    char* indexname = "b_plus_tree_index_";
    char fileID[5] = "";
    sprintf(fileID,"%d",fid);
    index_filename = strcat(index_filename,indexname);
    index_filename = strcat(index_filename,fileID);
    index_filename = strcat(index_filename,column);
    index_filename = strcat(index_filename,".dat");
    
    if( remove(index_filename) == 0 ){
        printf("Removed index on attribute:%s.\n", column);
	head->redef[idx].changeIndexedByName(column,false);
        return true;
    }
    else{
        perror("remove index");
        return false;
    }
}


/**
 * @brief 表中插入一行数据时，在表的所有索引中插入一个element
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid : long
 * @param [in] position : long
 * @return  bool
 *
 * @author weiyu
 * @date 2015/11/6
 **/
bool insertInIndex(struct dbSysHead *head, long fid, int position){
    Element elem_insert;
    
    FILE *fp;
    int idx;
    char* column;
    char* index_filename;
    char* indexname = "b_plus_tree_index_";
    char fileID[5] = "";
    sprintf(fileID,"%d",fid);
    
    
    //查询数据字典，获取属性序号
    idx =  queryFileID(head, fid);
    if( idx<0 ) {
        isAvail(NULL,"createIndexOn",ARRAY);
    }
    if(head->redef[idx].getIndexedByName(column) == false){
        printf("No such index on attribute:%s.\n", column);
        return false;
    }
    int i;
    int offset;
    int key;
    long rec_length = (long)(head->redef[idx].getRecordLength());
    char * one_Row_ = (char *)malloc(sizeof(char)*rec_length);
    rdFile( head, 0, fid, position, rec_length,one_Row_);
    
    for( i = 0; i <= head->redef[idx].getAttributeNum(); i++) {
        if (head->redef[idx].getIndexedByName(column) == false)
		continue;//no index on the attribute
	//insert in the current index
        index_filename = (char *)malloc( 3*NAMELENGTH );
        *index_filename = '\0';
        column = (char *)malloc( NAMELENGTH );
        strcpy(column, head->redef[idx].getAttributeByNo(i).getName());
        index_filename = strcat(index_filename,indexname);
        index_filename = strcat(index_filename,fileID);
        index_filename = strcat(index_filename,column);
        index_filename = strcat(index_filename,".dat");
        fp = fopen(index_filename,"rb+");
        if( fp==NULL){	
            printf("error in inserting index:%s.\n",head->redef[idx].getAttributeByNo(i).getName());
	    continue;
        }
        
        offset = head->redef[idx].getAttributeByNo(i).getRecordDeviation();
        key = *((int *)(one_Row_ + offset));
        elem_insert.key = key;
        elem_insert.pos = position;
        insert(fp, elem_insert);
        printf("inserting in %s\n",index_filename);
        display(fp);
        fclose(fp);
        free(index_filename);
        free(column);
    }
    return true;
}


/**
 * @brief 表中删除一行数据时，在表的所有索引中删除一个elem
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid : long
 * @param [in] position : int
 * @return  bool
 *
 * @author weiyu
 * @date 2015/11/6
 **/
bool deleteInIndex(struct dbSysHead *head, long fid, int position){
    int idx;
    char* column;
    char* index_filename;
    char* indexname = "b_plus_tree_index_";
    char fileID[5] = "";
    sprintf(fileID,"%d",fid);
    
    FILE *fp;
    
    //查询数据字典，获取属性序号
    idx =  queryFileID(head, fid);
    if( idx<0 ) {
        isAvail(NULL,"createIndexOn",ARRAY);
    }
    
    
    int i;
    int offset;
    int key;
    long rec_length = (long)(head->redef[idx].getRecordLength());
    char * one_Row_ = (char *)malloc(sizeof(char)*rec_length);
    rdFile( head, 0, fid, position, rec_length,one_Row_);
    
    for( i = 0; i <= head->redef[idx].getAttributeNum(); i++) {
	//no index on the attribute
        if (head->redef[idx].getIndexedByName(column) == false)
		continue;
	//delete in the current index
        index_filename = (char *)malloc( 3*NAMELENGTH );
        *index_filename = '\0';
        column = (char *)malloc( NAMELENGTH );
        strcpy(column, head->redef[idx].getAttributeByNo(i).getName());
        index_filename = strcat(index_filename,indexname);
        index_filename = strcat(index_filename,fileID);
        index_filename = strcat(index_filename,column);
        index_filename = strcat(index_filename,".dat");
        fp = fopen(index_filename,"rb+");
        if( fp==NULL){
            printf("error in deleting in index:%s.\n",head->redef[idx].getAttributeByNo(i).getName());
	    continue;
        }
        
        offset = head->redef[idx].getAttributeByNo(i).getRecordDeviation();
        key = *((int *)(one_Row_ + offset));
        del(fp, key);
        printf("deleting in %s\n",index_filename);
        display(fp);
        fclose(fp);
        free(index_filename);
        free(column);
    }
    return true;
}


/**
 * @brief search by fid,column name and value
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fid : long
 * @param [in] name : char*
 * @param [in] value : int
 * @return  pos: int
 *
 * @author weiyu
 * @date 2015/11/21
 **/
int searchByColumnAndValue(struct dbSysHead *head, long fid, char* column, int value){
    //check if there is an index on column
    int idx;
    idx =  queryFileID(head, fid);
    if( idx<0 ) {
        isAvail(NULL,"createIndexOn",ARRAY);
    }
    //if indexed
    if(head->redef[idx].getIndexedByName(column) == false){
	printf("No index on attribute:%s.\n", column);
        return -2;
    }

//    printf("searchByColumnAndValue\n");
    char* index_filename;
    char* indexname = "b_plus_tree_index_";
    char fileID[5] = "";
    sprintf(fileID,"%d",fid);

    index_filename = (char *)malloc( 3*NAMELENGTH + 50);
    *index_filename = '\0';
    index_filename = strcat(index_filename, Index_Path);
    index_filename = strcat(index_filename,indexname);
    index_filename = strcat(index_filename,fileID);
    index_filename = strcat(index_filename,column);
    index_filename = strcat(index_filename,".dat");
    FILE* fp = fopen(index_filename,"rb+");
    int pos = search(fp,value);
    fclose(fp);
    return pos;
} 
