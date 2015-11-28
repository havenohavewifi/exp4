//
//  sortmergejoin.cpp
//  
//
//  Created by mengxi on 15/11/21.
//  Copyright (c) 2015Äê mengxi. All rights reserved.
//

#include "sortmergejoin.h"
#include "cursor.h"
#include "cursorForTmptable.h"
#include "Buffer.h"
#include "file.h"
#include "dataDictionary.h"
#include "getaRecordbyCursor.h"
#include <iostream>



int Comp(const void *p1,const void *p2)
{
	return (*(sortNode*)p1).value > (*(sortNode*)p2).value ? 1:-1;
}

void tempSort(struct dbSysHead *head, relation *tempTable, char *attr)
{
	int num = tempTable->getRecordNum();
	cout<<num<<endl;
	int length = tempTable->getRecordLength();
	cout<<length<<endl;
	int dv = tempTable->getAttributeByName(attr).getRecordDeviation();
	cout<<dv<<endl;
	struct sortNode* s;
	s = (sortNode*)malloc(sizeof(sortNode)*num);
	RecordCursorTmp scanTable(head, tempTable->fileID, length, -tempTable->fileID, num);
	for(int i=0;i<num;i++){
		s[i].record = (char*)malloc(sizeof(char)*length);
		if(scanTable.getNextRecord(s[i].record)==false){
			cout<<"can't read record!\n"<<endl;
			return;
		}
//		getOneRecord(s[i].record, tempTable);
//		for(int j=0;j<length;j++)
//			cout<<s[i].record[j];
//		cout<<endl;
		s[i].value = *(int*)(s[i].record+dv);
//		cout<<s[i].value<<endl;
	}
	qsort(s,num,sizeof(s[0]),Comp);
	int buffer_id = -tempTable->fileID;
	Buffer t(head, -2);
	for(int i=0;i<num;i++){
		cout<<s[i].value<<endl;
//		getOneRecord(s[i].record, tempTable);
		if (t.AppendBuffer(s[i].record, length) == false){
			t.writeBufferPage(t.filehead, buffer_id, t.data_, t.current_size_);
			t.pageID++;
			if (t.pageID == SIZE_BUFF) {
				std::cout << "this buffer full" << std::endl;
				return;
			}
			memset(t.data_, 0, SIZE_PER_PAGE);
			memcpy(t.data_, s[i].record, length);
			t.pointer_ = t.data_ + length;
			t.current_size_ = length;
		}
	}
	t.writeBufferPage(t.filehead, buffer_id, t.data_, t.current_size_);
	for(int i=0;i<num;i++){
		free(s[i].record);
	}
	free(s);
	return;
}

void sortmergejoin(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2, char *attr, relation *result)
{
	tempSort(head, temp_datadic1, attr);
	tempSort(head, temp_datadic2, attr);
	int original_rec_length1 = temp_datadic1->getRecordLength(); //record_length in original table*
	int original_rec_length2 = temp_datadic2->getRecordLength();
	int new_rec_length = result->getRecordLength();   //each record length in new temp table, in case SPJ use
	//look up which buffer is empty
	int buffer_id_;
	int i;
	for (i = 0; i < 3; i++) {
		if (head->buff[i].emptyOrnot == true) {
			buffer_id_ = i;
			head->buff[i].emptyOrnot = false;   // ready for writein
			std::cout << "sort merge join bufferID: " << i << std::endl;
			break;
		}
	}
	int type1 = temp_datadic1->getAttributeByName(attr).getType();
	int dv1 = temp_datadic1->getAttributeByName(attr).getRecordDeviation();
	int len1 = temp_datadic1->getAttributeByName(attr).getLength();
	int type2 = temp_datadic2->getAttributeByName(attr).getType();
	int dv2 = temp_datadic2->getAttributeByName(attr).getRecordDeviation();
	int len2 = temp_datadic2->getAttributeByName(attr).getLength();
	if(type1!=type2){
		cout<<"different type!"<<endl;
		return;
	}
	if (i == 3) {
		cout << "No Buffer Can be Used!" << endl;
	}
	else{
		char * one_Row_1 = (char *)malloc(sizeof(char) * original_rec_length1);
		char * one_Row_2 = (char *)malloc(sizeof(char) * original_rec_length2);
		char * new_Row_ = (char *)malloc(sizeof(char) * new_rec_length);
		RecordCursorTmp scanTable1(head, temp_datadic1->fileID, original_rec_length1, -temp_datadic1->fileID, temp_datadic1->getRecordNum());
		RecordCursorTmp scanTable2(head, temp_datadic2->fileID, original_rec_length2, -temp_datadic2->fileID, temp_datadic2->getRecordNum());
		Buffer t(head, -2); //to avoid positive number, no meaning
		if(scanTable1.getNextRecord(one_Row_1) == false){
			cout<<"can't read tmptable1!"<<endl;
		}
		if(scanTable2.getNextRecord(one_Row_2) == false){
			cout<<"can't read tmptable2!"<<endl;
		}
//		getOneRecord(one_Row_1, temp_datadic1);
//		getOneRecord(one_Row_2, temp_datadic2);
		int k = 0;
		while (true) {		
			int value1 = *((int *)(one_Row_1 + dv1));
			int value2 = *((int *)(one_Row_2 + dv2));
			if(value1 == value2){
                k++;
				for(int i=0;i<original_rec_length1;i++)
					new_Row_[i]=one_Row_1[i];
				for(int i=0;i<original_rec_length2;i++)
					new_Row_[i+original_rec_length1]=one_Row_2[i];
				//getOneRecord(new_Row_, result);
				if (false == t.AppendBuffer(new_Row_, new_rec_length))
				{
					t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
					t.pageID++;
					if (t.pageID == SIZE_BUFF) {
						std::cout << "this buffer full" << std::endl;
						return;
					}
					memset(t.data_, 0, SIZE_PER_PAGE);
					memcpy(t.data_, new_Row_, new_rec_length);
					t.pointer_ = t.data_ + new_rec_length;
					t.current_size_ = new_rec_length;
				}
				if(scanTable1.getNextRecord(one_Row_1)==false){
					break;
				}
			}
			else if(value1<value2){
				if(scanTable1.getNextRecord(one_Row_1)==false){
					break;
				}
			}
			else{
				if(scanTable2.getNextRecord(one_Row_2)==false){
					break;
				}
			}
		}
		t.writeBufferPage(t.filehead, buffer_id_, t.data_, t.current_size_);
		result->fileID = -buffer_id_;
        result->changeRecordNum(k);
		free(one_Row_1);
		free(one_Row_2);
		free(new_Row_);		
	}
	return;
}
