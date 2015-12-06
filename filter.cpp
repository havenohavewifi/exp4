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
//#include "b_plus_tree.h"

/**
 * @brief Equal Filter based on table Scan
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] old_temp_data_dict : relation*       // results of tablescan
 * @param [in] attributeName : char*
 * @param [in] value : char*
 * @param [in] new_temp_datadic : relation*     //filter results
 * @return  int         //number of filter result records, -1 means error
 *
 * @author weiyu
 * @date 2015/12/6
 **/
int tableScanEqualFilter(struct dbSysHead * head , relation * old_temp_data_dict, char* attributeName, char* value,relation * new_temp_datadic){

    int my_buffer_id_ ;
    int i;
    for (i = 0 ; i < BUFF_NUM; i++) {
        if (head->buff[i].emptyOrnot == true) {
            my_buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout<<"bufferID: "<<i<<std::endl;
            break;
        }
    }
    if (i == BUFF_NUM) {
        cout<<"No Buffer Can be Used!"<<endl;
        return -1;
    }
    else{
	//read the scanned table according to the temp_data_dict
        int buffer_ID_ = - old_temp_data_dict->fileID;   //find which buffer
        int record_num_ = old_temp_data_dict->getRecordNum();
        int record_len_ = old_temp_data_dict->getRecordLength();
        attribute tempAttr;
        tempAttr = old_temp_data_dict->getAttributeByName(attributeName);
        int offset = tempAttr.getRecordDeviation();
        int type = tempAttr.getType();
        int lengthOfAttr = tempAttr.getLength();
        RecordCursorTmp t1(head,old_temp_data_dict->fileID,record_len_,buffer_ID_,record_num_);
        //cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;

        Buffer t(head, -2);
        int hitRecordCount = 0;
        //printf("type %d\n",type);
        char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
        while (true == t1.getNextRecord(one_Row_)) { //only scan
	    //compare the current record with the wanting value, write in buffer if it hits
        switch(type){
		case INT:{
		    int recordValue = *((int *)(one_Row_ + offset));
		    //int compareValue = *((int *)value);
		    int compareValue = atoi(value);
		    if (recordValue == compareValue){
                printf("int record:%d\tcompare:%d\n",recordValue,compareValue);
                hitRecordCount++;
                if(false == t.AppendBuffer(one_Row_, record_len_)){
                    t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                    t.pageID++;
                    if (t.pageID == SIZE_BUFF) {
                        std::cout<<"this buffer full"<<std::endl;
                        break;
                    }
                    memset(t.data_, 0, SIZE_PER_PAGE);
                    memcpy(t.data_, one_Row_, record_len_);
                    t.pointer_ = t.data_+record_len_;
                    t.current_size_ = record_len_;
                }
		    }
            break;
		}
		case CHAR:{
            char* recordValue = (char *)malloc(sizeof(char)*lengthOfAttr);
            memcpy(recordValue,one_Row_ + offset,lengthOfAttr);
            //int compareValue = *((int *)value);
            char* compareValue = value;
            if (strcmp(recordValue,compareValue) == 0){
                printf("char record:%s\tcompare:%s\n",recordValue,compareValue);
                //getOneRecord(one_Row_, &temp_data_dict[0]);
                hitRecordCount++;
                if(false == t.AppendBuffer(one_Row_, record_len_)){
                        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                        t.pageID++;
                        if (t.pageID == SIZE_BUFF) {
                            std::cout<<"this buffer full"<<std::endl;
                            break;
                        }
                        memset(t.data_, 0, SIZE_PER_PAGE);
                        memcpy(t.data_, one_Row_, record_len_);
                        t.pointer_ = t.data_+record_len_;
                        t.current_size_ = record_len_;
                }
            }
            break;
		}
		case DATE:{
            break;
		}
	    }//end switch
            
    	}//end while
        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
        free(one_Row_);
        new_temp_datadic = old_temp_data_dict; //wrong, need to wait class copy
        new_temp_datadic->fileID = -my_buffer_id_; //negative number for temp datadict, value is for which buffer
        new_temp_datadic->changeRecordNum(hitRecordCount);
        //!!!free the old buffer
        head->buff[buffer_ID_].emptyOrnot = true;
        return hitRecordCount;
    }
}

/**
 * @brief Equal Filter based on index
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] fileID : long
 * @param [in] attributeName : char*
 * @param [in] value : char*
 * @param [in] new_temp_datadic : relation*     //filter results
 * @return  int         //number of filter result records, -1 means error
 *
 * @author weiyu
 * @date 2015/12/4
 **/
int indexScanEqualFilter(struct dbSysHead * head, int fileID, char* attributeName, char* value,relation * new_temp_datadic){
    int my_buffer_id_ ;
    int i;
    for (i = 0 ; i < BUFF_NUM; i++) {
        if (head->buff[i].emptyOrnot == true) {
            my_buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout<<"bufferID: "<<i<<std::endl;
            break;
        }
    }
    if (i == BUFF_NUM) {
        cout<<"No Buffer Can be Used!"<<endl;
	return -1;
    }
    int idx;
    idx =  queryFileID(head, fileID);
    if( idx<0 ) {
        isAvail(NULL,"createIndexOn",ARRAY);
    }
    int rec_len_ = head->redef[idx].getRecordLength();
    *new_temp_datadic = head->redef[idx]; //wrong, need to wait class copy
    new_temp_datadic->fileID = -my_buffer_id_; //negative number for temp datadict, value is for which buffer
    
    attribute tempAttr;
    tempAttr = head->redef[idx].getAttributeByName(attributeName);
    int offset = tempAttr.getRecordDeviation();
    int type = tempAttr.getType();
    if(type != INT){
	printf("The attribute is not INT type. Cannot scan by index.\n");
        return -1;
    }

	//read the scanned table according to the temp_data_dict
    
    int pos;
    int tmpvalue = atoi(value);
    pos = searchByColumnAndValue(head,fileID,attributeName,tmpvalue);

    int hitRecordCount = 0;
    if(pos ==-1){
        //
        int a;
    }
    else{
        hitRecordCount = 1;
//        printf("pos:::%d\n",pos);
        char* one_Row_ = (char *)malloc(sizeof(char)*rec_len_);
        rdFile( head, 0, fileID, pos, rec_len_,one_Row_);
        //printf("**************************reading from index:\n");
        //getOneRecord(one_Row_, &(head->redef[idx]));
        Buffer t(head, -2);
	
        if(false == t.AppendBuffer(one_Row_, rec_len_)){
		t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
		t.pageID++;
		if (t.pageID == SIZE_BUFF) {
		    std::cout<<"this buffer full"<<std::endl;
		}
		memset(t.data_, 0, SIZE_PER_PAGE);
		memcpy(t.data_, one_Row_, rec_len_);
		t.pointer_ = t.data_+rec_len_;
		t.current_size_ = rec_len_;
	    }
     	    
	t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
        free(one_Row_);
    }
    new_temp_datadic->changeRecordNum(hitRecordCount);
    return hitRecordCount;

}

/**
 * @brief semiScope filter based on table scan
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] old_temp_data_dict : relation*       //scan results
 * @param [in] attributeName : char*
 * @param [in] value : char*
 * @param [in] sign : int                       //LESS_THAN 0, NOT_LESS_THAN 1, MORE_THAN 2, NOT_MORE_THAN 3, NOT_EQUAL 4
 * @param [in] new_temp_datadic : relation*     //filter results
 * @return  int         //number of filter result records, -1 means error
 *
 * @author weiyu
 * @date 2015/12/6
 **/
int tableScanSemiscopeFilter(struct dbSysHead * head, relation * old_temp_data_dict, char* attributeName, char* value,int sign,relation * new_temp_datadic){

    int my_buffer_id_ ;
    int i;
    for (i = 0 ; i < BUFF_NUM; i++) {
        if (head->buff[i].emptyOrnot == true) {
            my_buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout<<"bufferID: "<<i<<std::endl;
            break;
        }
    }
    if (i == BUFF_NUM) {
        cout<<"No Buffer Can be Used!"<<endl;
	    return -1;
    }
    else{
	//read the scanned table according to the temp_data_dict
	
        int buffer_ID_ = - old_temp_data_dict->fileID;   //find which buffer
        int record_num_ = old_temp_data_dict->getRecordNum();
        int record_len_ = old_temp_data_dict->getRecordLength();
        attribute tempAttr;
        tempAttr = old_temp_data_dict->getAttributeByName(attributeName);
        int offset = tempAttr.getRecordDeviation();
        int type = tempAttr.getType();
        int lengthOfAttr = tempAttr.getLength();
        RecordCursorTmp t1(head, old_temp_data_dict->fileID,record_len_,buffer_ID_,record_num_);
        //cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;

        Buffer t(head, -2);
        int hitRecordCount = 0;
	
        char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
        while (true == t1.getNextRecord(one_Row_)) { //only scan
	    //compare the current record with the wanting value, write in buffer if it hits
        switch(type){
		case INT:{
		    int recordValue = *((int *)(one_Row_ + offset));
		    //int compareValue = *((int *)value);
		    int compareValue = atoi(value);
            switch(sign){
			case LESS_THAN:{
                    if (recordValue < compareValue){
                        printf("less_than_:record:%d\tcompare:%d\n",recordValue,compareValue);
                        //getOneRecord(one_Row_, &temp_data_dict[0]);
                        hitRecordCount++;
                        if(false == t.AppendBuffer(one_Row_, record_len_)){
                            t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                t.pageID++;
                                if (t.pageID == SIZE_BUFF) {
                                        std::cout<<"this buffer full"<<std::endl;
                                        break;
                                }
                                memset(t.data_, 0, SIZE_PER_PAGE);
                                memcpy(t.data_, one_Row_, record_len_);
                                t.pointer_ = t.data_+record_len_;
                                t.current_size_ = record_len_;
                        }
                        }  //end if
                        break;
			}
			case MORE_THAN:{
                            if (recordValue > compareValue){
                                printf("MORE_THAN:record:%d\tcompare:%d\n",recordValue,compareValue);
                                //getOneRecord(one_Row_, &temp_data_dict[0]);
                                hitRecordCount++;
                                if(false == t.AppendBuffer(one_Row_, record_len_)){
                                        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                        t.pageID++;
                                        if (t.pageID == SIZE_BUFF) {
                                            std::cout<<"this buffer full"<<std::endl;
                                            break;
                                        }
                                        memset(t.data_, 0, SIZE_PER_PAGE);
                                        memcpy(t.data_, one_Row_, record_len_);
                                        t.pointer_ = t.data_+record_len_;
                                        t.current_size_ = record_len_;
                                }
                            }  //end if
			    break;
			}
			case NOT_MORE_THAN:{
                            if (recordValue <= compareValue){
                                printf("NOT_MORE_THAN:record:%d\tcompare:%d\n",recordValue,compareValue);
                                //getOneRecord(one_Row_, &temp_data_dict[0]);
                                hitRecordCount++;
                                if(false == t.AppendBuffer(one_Row_, record_len_)){
                                        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                        t.pageID++;
                                        if (t.pageID == SIZE_BUFF) {
                                            std::cout<<"this buffer full"<<std::endl;
                                            break;
                                        }
                                        memset(t.data_, 0, SIZE_PER_PAGE);
                                        memcpy(t.data_, one_Row_, record_len_);
                                        t.pointer_ = t.data_+record_len_;
                                        t.current_size_ = record_len_;
                                }
                            }  //end if
			    break;
			}
			case NOT_LESS_THAN:{
                            if (recordValue >= compareValue){
                                printf("NOT_LESS_THAN:record:%d\tcompare:%d\n",recordValue,compareValue);
                                //getOneRecord(one_Row_, &temp_data_dict[0]);
                                hitRecordCount++;
                                if(false == t.AppendBuffer(one_Row_, record_len_)){
                                        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                        t.pageID++;
                                        if (t.pageID == SIZE_BUFF) {
                                            std::cout<<"this buffer full"<<std::endl;
                                            break;
                                        }
                                        memset(t.data_, 0, SIZE_PER_PAGE);
                                        memcpy(t.data_, one_Row_, record_len_);
                                        t.pointer_ = t.data_+record_len_;
                                        t.current_size_ = record_len_;
                                }
                            }  //end if
			    break;
			}
			case NOT_EQUAL:{
                            if (recordValue != compareValue){
                                printf("NOT_EQUAL:record:%d\tcompare:%d\n",recordValue,compareValue);
                                //getOneRecord(one_Row_, &temp_data_dict[0]);
                                hitRecordCount++;
                                if(false == t.AppendBuffer(one_Row_, record_len_)){
                                        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                        t.pageID++;
                                        if (t.pageID == SIZE_BUFF) {
                                            std::cout<<"this buffer full"<<std::endl;
                                            break;
                                        }
                                        memset(t.data_, 0, SIZE_PER_PAGE);
                                        memcpy(t.data_, one_Row_, record_len_);
                                        t.pointer_ = t.data_+record_len_;
                                        t.current_size_ = record_len_;
                                }
                            }  //end if

			}

		    }//end switch sign
                    break;
		}
		case CHAR:{
                    char* recordValue = (char *)malloc(sizeof(char)*lengthOfAttr);
                    memcpy(recordValue,one_Row_ + offset,lengthOfAttr);
                    //int compareValue = *((int *)value);
                    char* compareValue = value;
//                  printf("record:%d\tcompare:%d\n",recordValue,compareValue);
                    if (strcmp(recordValue,compareValue) == 0){
                        printf("record:%s\tcompare:%s\n",recordValue,compareValue);
                        //getOneRecord(one_Row_, &temp_data_dict[0]);
                        hitRecordCount++;
                        if(false == t.AppendBuffer(one_Row_, record_len_)){
                                t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                t.pageID++;
                                if (t.pageID == SIZE_BUFF) {
                                    std::cout<<"this buffer full"<<std::endl;
                                    break;
                                }
                                memset(t.data_, 0, SIZE_PER_PAGE);
                                memcpy(t.data_, one_Row_, record_len_);
                                t.pointer_ = t.data_+record_len_;
                                t.current_size_ = record_len_;
                        }
                    }
                    break;
		}
		case DATE:{

		}
	    }//end switch
            
    	}//end while
        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
        free(one_Row_);
        new_temp_datadic = old_temp_data_dict; //wrong, need to wait class copy
        new_temp_datadic->fileID = -my_buffer_id_; //negative number for temp datadict, value is for which buffer
        new_temp_datadic->changeRecordNum(hitRecordCount);
        //!!!free the old buffer
        head->buff[buffer_ID_].emptyOrnot = true;
        return hitRecordCount;
    }
}

/**
 * @brief  Filter based on table scan
 *
 * @param [in] head  : struct dbSysHead *
 * @param [in] old_temp_data_dict : relation*       //scan results
 * @param [in] attributeName : char*
 * @param [in] value1 : char*
 * @param [in] sign1 : int                      //LESS_THAN 0, NOT_LESS_THAN 1, MORE_THAN 2, NOT_MORE_THAN 3, NOT_EQUAL 4
 * @param [in] value2 : char*
 * @param [in] sign2 : int
 * @param [in] new_temp_datadic : relation*     //filter results
 * @return  int         //number of filter result records, -1 means error
 *
 * @author weiyu
 * @date 2015/12/6
 **/
//e.g. tableScanScopeFilter(head, fid, &temp_data_dict, attributeName, "210",LESS_THAN,"220",NOT_MORE_THAN,&new_temp_datadic)
//     means to find x that 210 < x <= 220
int tableScanScopeFilter(struct dbSysHead * head,  relation * old_temp_data_dict, char* attributeName, char* value1,int sign1,char* value2,int sign2,relation * new_temp_datadic){

    int my_buffer_id_ ;
    int i;
    for (i = 0 ; i < BUFF_NUM; i++) {
        if (head->buff[i].emptyOrnot == true) {
            my_buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout<<"bufferID: "<<i<<std::endl;
            break;
        }
    }
    if (i == BUFF_NUM) {
        cout<<"No Buffer Can be Used!"<<endl;
	return -1;
    }
    else{
	//read the scanned table according to the temp_data_dict
        int buffer_ID_ = - old_temp_data_dict->fileID;   //find which buffer
        int record_num_ = old_temp_data_dict->getRecordNum();
        int record_len_ = old_temp_data_dict->getRecordLength();
        attribute tempAttr;
        tempAttr = old_temp_data_dict->getAttributeByName(attributeName);
        int offset = tempAttr.getRecordDeviation();
        int type = tempAttr.getType();
        int lengthOfAttr = tempAttr.getLength();
        RecordCursorTmp t1(head,old_temp_data_dict->fileID,record_len_,buffer_ID_,record_num_);
        //cout<<buffer_ID_<<"~"<<record_len_<<"~"<<record_num_<<endl;
        if(type != INT){
            printf("Cannnot call tableScanScopeFilter when the attribute is not INT type.\n");
            return -1;
        }	
        Buffer t(head, -2);
        int hitRecordCount = 0;
	
        char * one_Row_ = (char *)malloc(sizeof(char)*record_len_);
        while (true == t1.getNextRecord(one_Row_)) { //only scan
	    //compare the current record with the wanting value, write in buffer if it hits
	    int recordValue = *((int *)(one_Row_ + offset));
		    //int compareValue = *((int *)value);
	    int compareValue1 = atoi(value1);
            int compareValue2 = atoi(value2);
//		    printf("record:%d\tcompare:%d\n",recordValue,compareValue);
            switch(sign1){
		case LESS_THAN:{
                    if(sign2 == LESS_THAN){
			if (compareValue1 < recordValue && recordValue < compareValue2){
                                printf("compareValue1 < recordValue < compareValue2:record:%d\n",recordValue);
                                //getOneRecord(one_Row_, &temp_data_dict[0]);
                                hitRecordCount++;
                                if(false == t.AppendBuffer(one_Row_, record_len_)){
                                        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                        t.pageID++;
                                        if (t.pageID == SIZE_BUFF) {
                                            std::cout<<"this buffer full"<<std::endl;
                                            break;
                                        }
                                        memset(t.data_, 0, SIZE_PER_PAGE);
                                        memcpy(t.data_, one_Row_, record_len_);
                                        t.pointer_ = t.data_+record_len_;
                                        t.current_size_ = record_len_;
                                }
                            }

		    }
		    else if(sign2 == NOT_MORE_THAN){
                        if (compareValue1 < recordValue && recordValue<= compareValue2){
                                printf("c1 < recordValue <= c2:record:%d\n",recordValue);
                                //getOneRecord(one_Row_, &temp_data_dict[0]);
                                hitRecordCount++;
                                if(false == t.AppendBuffer(one_Row_, record_len_)){
                                        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                        t.pageID++;
                                        if (t.pageID == SIZE_BUFF) {
                                            std::cout<<"this buffer full"<<std::endl;
                                            break;
                                        }
                                        memset(t.data_, 0, SIZE_PER_PAGE);
                                        memcpy(t.data_, one_Row_, record_len_);
                                        t.pointer_ = t.data_+record_len_;
                                        t.current_size_ = record_len_;
                                }
                            }


		    }
                    else{
			printf("Illegal sign2.\n");
                        return -1;
		    }
		    break;
		}
		case NOT_MORE_THAN:{
                    if(sign2 == LESS_THAN){
			if (compareValue1 <= recordValue && recordValue< compareValue2){
                                printf("compareValue1:%d <= recordValue:%d < compareValue2:%d\n",compareValue1,recordValue,compareValue2);
                                //getOneRecord(one_Row_, &temp_data_dict[0]);
                                hitRecordCount++;
                                if(false == t.AppendBuffer(one_Row_, record_len_)){
                                        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                        t.pageID++;
                                        if (t.pageID == SIZE_BUFF) {
                                            std::cout<<"this buffer full"<<std::endl;
                                            break;
                                        }
                                        memset(t.data_, 0, SIZE_PER_PAGE);
                                        memcpy(t.data_, one_Row_, record_len_);
                                        t.pointer_ = t.data_+record_len_;
                                        t.current_size_ = record_len_;
                                }
                            }

		    }
		    else if(sign2 == NOT_MORE_THAN){
                        if (compareValue1 <= recordValue && recordValue <= compareValue2){
                                printf("compareValue1 <= recordValue < compareValue2:record:%d\n",recordValue);
                                //getOneRecord(one_Row_, &temp_data_dict[0]);
                                hitRecordCount++;
                                if(false == t.AppendBuffer(one_Row_, record_len_)){
                                        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
                                        t.pageID++;
                                        if (t.pageID == SIZE_BUFF) {
                                            std::cout<<"this buffer full"<<std::endl;
                                            break;
                                        }
                                        memset(t.data_, 0, SIZE_PER_PAGE);
                                        memcpy(t.data_, one_Row_, record_len_);
                                        t.pointer_ = t.data_+record_len_;
                                        t.current_size_ = record_len_;
                                }
                            }
		    }
                    else{
			printf("Illegal sign2.\n");
                        return -1;
		    }
		    break;
		}
                default:{
			printf("Illegal sign1.\n");
                        return -1;
		}
           }//end of switch sign1 
    	}//end while
        t.writeBufferPage(t.filehead,my_buffer_id_ ,t.data_, t.current_size_);
        free(one_Row_);
        new_temp_datadic = old_temp_data_dict; //wrong, need to wait class copy
        new_temp_datadic->fileID = -my_buffer_id_; //negative number for temp datadict, value is for which buffer
        new_temp_datadic->changeRecordNum(hitRecordCount);
        //!!!free the old buffer
        head->buff[buffer_ID_].emptyOrnot = true;
        return hitRecordCount;
    }
}


