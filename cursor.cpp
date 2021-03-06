//
//  cursor.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/6.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#include "cursor.h"

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

};
/**/

#include <iostream>
#include "dbHead.h"

using namespace std;

/*
bool RecordCursor::getNextRecord(void *des) {
    // all the data is read
    if(this->cLogicPage >= this->filePageNum ||((this->cLogicPage == this->filePageNum - 1) && this->bufferOffset >= head->desc.fileDesc[queryFileID(head, fid)].filePageEndPos)) {
//        cout<<this->cLogicPage<<"-" <<this->bufferOffset<<endl;
        return false;
    }
    // if the next record is out of the buffer page
    // then read the next page into buffer
    if(this->start==true || (this->bufferOffset+recordLength)>SIZE_PER_PAGE) {
        this->cLogicPage += 1;
        long pageID = mapPage(this->head, this->fid, this->cLogicPage);
        this->cBufferPage = reqPage(this->head, this->bufferID, pageID);
        this->bufferOffset = 0;
        this->start = false;
    }
    // read the record into des
    memcpy(des, this->head->buff[this->bufferID].data[this->cBufferPage]+bufferOffset, sizeof(char)*recordLength);
    this->bufferOffset += recordLength;
    
    return true;
}
*/

bool RecordCursor::getNextRecord(void *des) {
    // all the data is read
    if(this->cLogicPage > this->filePageNum ||((this->cLogicPage == this->filePageNum ) && this->bufferOffset >= head->desc.fileDesc[queryFileID(head, fid)].filePageEndPos)) {
//        cout<<this->cLogicPage<<"-" <<this->bufferOffset<<endl;
        return false;
    }
    // if the next record is out of the buffer page
    // then read the next page into buffer
    if(this->start==true || (this->bufferOffset+recordLength)>SIZE_PER_PAGE) {
        this->cLogicPage += 1;
        long pageID = mapPage(this->head, this->fid, this->cLogicPage);
        this->cBufferPage = reqPage(this->head, this->bufferID, pageID);
        this->bufferOffset = 0;
        this->start = false;
    }
    // read the record into des
    char * one_Row_ = (char *)malloc(sizeof(char)*recordLength);
    char* erase = (char *)malloc(sizeof(char)*recordLength);
    for(int i=0;i<recordLength-1;i++){
        erase[i]='$';
    }
    erase[recordLength-1] = '\0';
    memcpy(one_Row_, this->head->buff[this->bufferID].data[this->cBufferPage]+bufferOffset, sizeof(char)*recordLength);

    while (strcmp(one_Row_, erase) == 0){
    //printf("one_Row_[0] == erase[0]::%c,%c\n",one_Row_[0] , erase[0]);
    	this->bufferOffset += recordLength;
        bool flag = getNextRecord(one_Row_);
        if (flag == false)
            return false;
        this->bufferOffset -= recordLength;
    }

    memcpy(des, this->head->buff[this->bufferID].data[this->cBufferPage]+bufferOffset, sizeof(char)*recordLength);
    this->bufferOffset += recordLength;
    return true;
}


long RecordCursor::getcLogicLocation() {
    return this->cLogicPage*SIZE_PER_PAGE+this->bufferOffset;
}

long RecordCursor::getcLogicPage() {
    return this->cLogicPage;
}

long RecordCursor::getcBufferOffset() {
    return this->cBufferPage;
}

int RecordCursor::getBufferID() {
    return this->bufferID;
}

// int getNextPage(struct dbSysHead *head, long fid, long num) {

// 	int pageIdInDisk = mapPage(head, fid, num+1);

// 	return reqPage(head, pageIdInDisk);
// }

// int getNextRecord(struct dbSysHead *head, long mapNo, long offset, long recordLen) {

// 	return head->buff.data[mapNo][offset:offset+recordLen]
// }
