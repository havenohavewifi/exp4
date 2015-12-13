extern "C"{
#include <stdio.h>
};
#include "dbHead.h"
#include "file.h"
#include "tableScan.h"
#include "cursor.h"
#include "Buffer.h"
#include "dataDictionary.h"

#define LESS_THAN 0
#define NOT_LESS_THAN 1
#define MORE_THAN 2
#define NOT_MORE_THAN 3
#define NOT_EQUAL 4
#define EQUAL 5

//int tableScanEqualFilter(struct dbSysHead * head, relation * temp_datadic, char* attributeName, char * value,relation * new_temp_datadic);

int tableScanEqualFilter(struct dbSysHead * head , relation * temp_data_dict, int old_relation, char* attributeName, char* value);

//int indexScanEqualFilter(struct dbSysHead * head, int fileID, char* attributeName, char* value,relation * new_temp_datadic);
int indexScanEqualFilter(struct dbSysHead * head, int fileID, char* attributeName, char* value, relation * temp_datadic);
//int tableScanSemiscopeFilter(struct dbSysHead * head, relation * temp_data_dict, char* attributeName, char* value,int sign,relation * new_temp_datadic);
int tableScanSemiscopeFilter(struct dbSysHead * head, relation * temp_data_dic, int old_relation, char* attributeName, char* value,int sign);
//int tableScanScopeFilter(struct dbSysHead * head, relation * temp_data_dict, char* attributeName, char* value1,int sign1,char* value2,int sign2,relation * new_temp_datadic);
int tableScanScopeFilter(struct dbSysHead * head,  relation * temp_data_dic, int old_relation, char* attributeName, char* value1,int sign1,char* value2,int sign2);
