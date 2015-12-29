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
void merge_relation_index(struct dbSysHead *head,relation datadic1,relation datadic2,relation *result){
	int a[20]={0};
	int length1=datadic1.getAttributeNum();
	int length2=datadic2.getAttributeNum();
	int signal=0;
	for(int j=0;j<length1;j++){
		signal=0;
		for(int k=0;k<length2;k++){
			if(strcmp(datadic1.getAttributeByNo(j).getName(),datadic2.getAttributeByNo(k).getName())==0){
				a[k]=1;
				signal=1;
				break;
			}
		}
		if(signal==0){
			(*result).insertAttribute(datadic1.getAttributeByNo(j).getName(),
			datadic1.getAttributeByNo(j).getType(),
			datadic1.getAttributeByNo(j).getLength());
		}else{
			(*result).insertAttribute(strcat(datadic1.getAttributeByNo(j).getName(),"_1"),
			datadic1.getAttributeByNo(j).getType(),
			datadic1.getAttributeByNo(j).getLength());
		}
		
		
	}
	
	for(int j=0;j<length2;j++){
		if(a[j]==0){
		(*result).insertAttribute(datadic2.getAttributeByNo(j).getName(),
			datadic2.getAttributeByNo(j).getType(),
			datadic2.getAttributeByNo(j).getLength());
		}else{
			(*result).insertAttribute(strcat(datadic2.getAttributeByNo(j).getName(),"_2"),
			datadic2.getAttributeByNo(j).getType(),
			datadic2.getAttributeByNo(j).getLength());
		}
	}
	
}

int indexjoin(struct dbSysHead *head, relation *temp_data_dict,int old_relation_1, int old_relation_2, const char *name){
	//find empty temp_datadic
    int new_relation=0;
	int temp_num=0;
    for (temp_num = 0; temp_num < MAX_FILE_NUM; temp_num++) {
        if (strcmp(temp_data_dict[temp_num].getRelationName(),"") == 0) {
            new_relation = temp_num;
      //      cout<<"new relation id: "<<new_relation<<endl;
            temp_data_dict[new_relation].init("temp_datadict_nestloop","WenHui");
			
			merge_relation_index(head,temp_data_dict[old_relation_1],temp_data_dict[old_relation_2],& temp_data_dict[new_relation]);
//			showRelation(&temp_data_dict[new_relation]);

            break;
        }
    }
    if (temp_num == MAX_FILE_NUM) {
        cout<<"no temp datadict for use!"<<endl;
        return -3;
    }
    //input error control
   
    int original_rec_length1 = temp_data_dict[old_relation_1].getRecordLength();
    int original_rec_length2 =temp_data_dict[old_relation_2].getRecordLength();
	int new_rec_length=temp_data_dict[new_relation].getRecordLength();
    int original_attribute_length1=temp_data_dict[old_relation_1].getAttributeNum();
    int original_attribute_length2=temp_data_dict[old_relation_2].getAttributeNum();

    //look up which buffer is empty
    int buffer_id_;
    int i;
    for (i = 0; i < BUFF_NUM; i++) {
        if (head->buff[i].emptyOrnot == true) {
            buffer_id_ = i;
            head->buff[i].emptyOrnot = false;   // ready for writein
            std::cout << "BufferID: " << i << std::endl;
            break;
        }
    }
    if (i == BUFF_NUM) {
        cout << "No Buffer Can be Used!" << endl;
        return -2;
    }else{
		//RecordCursor scanTable(head, temp_datadic->fileID, original_rec_length, -temp_datadic->fileID);
		RecordCursorTmp scanTable1(head, temp_data_dict[old_relation_1].fileID, original_rec_length1, -temp_data_dict[old_relation_1].fileID, temp_data_dict[old_relation_1].getRecordNum());
		
		
		char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
		char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
		char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
		Buffer t(head, -2); //to avoid positive number, no meaning
		int k = 0;
		int key=-1;
		int start1=0;
		int result_num=0;
		while (true == scanTable1.getNextRecord(one_Row_1)) { //only scan
	
			 for(int i=0;i<original_attribute_length1;i++){
			
                if(strcmp(temp_data_dict[old_relation_1].getAttributeByNo(i).getName(),name)==0){
					
                    start1=temp_data_dict[old_relation_1].getAttributeByNo(i).getRecordDeviation();
                    key=*((int*)(one_Row_1+start1));  //debug for key
                     cout<<"key:"<<key<<endl;
                    break;
                }
            }
			 char* name_new = new char[100];//×ã¹»³¤
			  strcpy(name_new,name);
			int goal=-1;
			 for (int i = 0; i<MAX_FILE_NUM; i++) {
					if (strcmp((head->redef)[i].getRelationName(),temp_data_dict[old_relation_2].getRelationName())==0) {
						goal=i;
						break;
						
					}
			 }
			 int actual=(head->desc).fileDesc[goal].fileID;					 
			 int pos = searchByColumnAndValue(head,actual,name_new,key);
		
			 if(pos<0){
				continue;
			 }
			 int rec_len_ = temp_data_dict[old_relation_2].getRecordLength();
          
			 result_num++;
			 //rdFile(head, 0, temp_data_dict[old_relation_2].fileID, pos, rec_len_,new_Row_);
			
			
    
			 //cout<<"actual"<<actual<<endl;
			  rdFile(head, 0, actual, pos, rec_len_,one_Row_2);
			  //cout<<"one_row1:"<<one_Row_1<<endl;
			  for(int i=0;i<original_rec_length1;i++)
					new_Row_[i]=one_Row_1[i];
				for(int i=0;i<original_rec_length2;i++)
					new_Row_[i+original_rec_length1]=one_Row_2[i];
				//getOneRecord(one_Row_1, &(temp_data_dict[old_relation_1]));
				//getOneRecord(new_Row_, &(temp_data_dict[new_relation]));
			 

				
				
				if (false == t.AppendBuffer(new_Row_, new_rec_length))
				{
					t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
					t.pageID++;
					if (t.pageID == SIZE_BUFF) {
						std::cout << "this buffer full" << std::endl;
						break;
					}
					memset(t.data_, 0, SIZE_PER_PAGE);
					memcpy(t.data_, new_Row_, new_rec_length);
					t.pointer_ = t.data_ + new_rec_length;
					t.current_size_ = new_rec_length;
				}
			

			

		}
		//write remainder
		t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
		temp_data_dict[new_relation].fileID = -buffer_id_;
		temp_data_dict[new_relation].changeRecordNum(result_num);
		strcpy(temp_data_dict[old_relation_1].getRelationName(),"");
        strcpy(temp_data_dict[old_relation_2].getRelationName(),"");
        head->buff[-temp_data_dict[old_relation_1].fileID].emptyOrnot = true;
        head->buff[-temp_data_dict[old_relation_2].fileID].emptyOrnot = true;
		free(one_Row_1);
		free(one_Row_2);
		free(new_Row_);
		return new_relation;
	}



}
