extern "C"{
#include <stdio.h>
#include <string.h>
};

#include "dbHead.h"
#include "file.h"
#include "tableScan.h"
#include "cursor.h"
#include "Buffer.h"
#include "dataDictionary.h"
#include "cursorForTmptable.h"
#include "getaRecordbyCursor.h"
#include "indexOpt.h"
#include "filter.h"
#include "indexOpt.h"


/**
 * @brief delete Record
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fileID : long
 * @param [in] attributeName : char*		
 * @param [in] value : char*
 * @param [in] sign : int			//LESS_THAN 0, NOT_LESS_THAN 1, MORE_THAN 2, NOT_MORE_THAN 3, NOT_EQUAL 4, EQUAL 5
 * @return  int 	//number of records deleted, -1 means error
 *
 * @author weiyu
 * @date 2015/12/4
 **/
int deleteRecordWhere(struct dbSysHead *head, long fid, char* attributeName, char* value,int sign, int bufferID){
    int idx;
    //查询数据字典，获取属性序号
    idx =  queryFileID(head, fid);
    if( idx<0 ) {
        isAvail(NULL,"createIndexOn",ARRAY);
    }
    attribute tempAttr;
    tempAttr = (head->redef[idx]).getAttributeByName(attributeName);
    int offset = tempAttr.getRecordDeviation();
    int type = tempAttr.getType();
    int lengthOfAttr = tempAttr.getLength();


    long rec_length = (long)(head->redef[idx].getRecordLength());

    // default use the first buffer block
    RecordCursor scanTable(head, fid, rec_length,bufferID);
    char * one_Row_ = (char *)malloc(sizeof(char)*rec_length);
    int hitRecordCount = 0;
    char* erase = (char *)malloc(sizeof(char)*rec_length);
    for(int i=0;i<rec_length-1;i++){
	erase[i]='$';
    }
    erase[rec_length-1] = '\0';
    int location;

    while (true == scanTable.getNextRecord(one_Row_)) { //only scan
        switch (type){
	    case INT:{
		int recordValue;
		int compareValue;
		compareValue = atoi(value);
		recordValue = *((int *)(one_Row_ + offset));
		switch(sign){
		    case EQUAL:{

			if (recordValue == compareValue){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;				
		    printf("%d\n",location);
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }
		    case NOT_EQUAL:{
			if (recordValue != compareValue){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;	
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes			
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }
		    case LESS_THAN:{
			if (recordValue < compareValue){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;	
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes			
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }
		    case MORE_THAN:{
			//printf("recordValue > compareValue:%d,%d",recordValue,compareValue);
			if (recordValue > compareValue){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;		
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes		
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }		  
		    case NOT_LESS_THAN:{
			if (recordValue >= compareValue){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;	
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes			
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }
		    case NOT_MORE_THAN:{
			if (recordValue <= compareValue){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;	
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes			
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }  
		}
		break;
	    }//end of INT type
	    case DATE:{
		//same with char type
	    }
	    case CHAR:{
		char* recordValue = (char *)malloc(sizeof(char)*lengthOfAttr);
                memcpy(recordValue,one_Row_ + offset,lengthOfAttr);
                char* compareValue = value;
		switch(sign){
		    case EQUAL:{
			if (strcmp(recordValue,compareValue) == 0){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;		
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes		
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }
		    case NOT_EQUAL:{
			if (strcmp(recordValue,compareValue) != 0){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;		
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes		
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }
		    case LESS_THAN:{
			if (strcmp(recordValue,compareValue) < 0){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;				
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }
		    case MORE_THAN:{
			if (strcmp(recordValue,compareValue) > 0){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;			
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes	
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }		  
		    case NOT_LESS_THAN:{
			if (strcmp(recordValue,compareValue) >= 0){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;				
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }
		    case NOT_MORE_THAN:{
			if (strcmp(recordValue,compareValue) <= 0){
				hitRecordCount++;
				location = scanTable.getcLogicLocation()-rec_length;			
				deleteInIndex(head, fid, location);	//delete in indexes, if there exists indexes	
				wtFile(head, bufferID, fid, location, rec_length, erase);
			}
			break;
		    }  
		}
		break;
	    }// end of CHAR type


        }//end of switch
        
    }//end of while, scanning the table
    printf("deleted %d records!\n", hitRecordCount);
    return hitRecordCount;
}
