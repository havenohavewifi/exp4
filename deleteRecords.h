extern "C"{
#include <stdio.h>
#include <string.h>
};

#include "dbHead.h"
#include "Buffer.h"


int deleteRecordWhere(struct dbSysHead *head, long fid, char* 
attributeName, char* value,int sign,int bufferID);
