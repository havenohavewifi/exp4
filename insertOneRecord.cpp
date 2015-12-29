//
//  insertOneRecord.cpp
//  loaddata
//
//  Created by IreneWu on 15/11/8.
//  Copyright (c) 2015年 IreneWu. All rights reserved.
//

#include "insertOneRecord.h"
#include "file.h"
#include "dbHead.h"
#include "indexOpt.h"
#include "dataDictionary.h"
#include <iostream>
using namespace std;


long insertOneRecord(struct dbSysHead *head , int fileID, char * oneRow){
    int fPhysicalID = queryFileID(head , fileID);
//did this make change??
//    relation *dic = &head->redef[fPhysicalID];
//    cout<<head->desc.fileDesc[fPhysicalID].filePageEndPos<<endl;
    long pos = (head->desc.fileDesc[fPhysicalID].filePageForWrite ) * SIZE_PER_PAGE + head->desc.fileDesc[fPhysicalID].filePageEndPos;
    if (head->desc.fileDesc[fPhysicalID].filePageEndPos + head->redef[fPhysicalID].getRecordLength() > SIZE_PER_PAGE) {
        head->desc.fileDesc[fPhysicalID].filePageForWrite ++;
        head->desc.fileDesc[fPhysicalID].filePageEndPos = 0;
        pos = (head->desc.fileDesc[fPhysicalID].filePageForWrite ) * SIZE_PER_PAGE;
    }
    wtFile(head, 0, fileID, pos, head->redef[fPhysicalID].getRecordLength(), oneRow);
    head->desc.fileDesc[fPhysicalID].filePageEndPos += head->redef[fPhysicalID].getRecordLength();
    if (head->desc.fileDesc[fPhysicalID].filePageEndPos >= SIZE_PER_PAGE) {
        head->desc.fileDesc[fPhysicalID].filePageEndPos = head->desc.fileDesc[fPhysicalID].filePageEndPos % SIZE_PER_PAGE;
        head->desc.fileDesc[fPhysicalID].filePageForWrite++;
    }
    int k = head->redef[fPhysicalID].getRecordNum() + 1;
    head->redef[fPhysicalID].changeRecordNum(k);
//if this file has index on this attribute?
//	if(true==insertInIndex(head, fileID, pos))
//        std::cout<<"insert in index true"<<std::endl;
	return pos;
}