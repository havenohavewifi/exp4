//
//  join_Hashjoin.h
//  
//
//  Created by IreneWu on 15/11/23.
//
//

#ifndef _join_Hashjoin_h
#define _join_Hashjoin_h
#include "datadictionary.h"

class Buffer;
class BufferManager;
class InputTuples;
class InputRelation;
class InputView;
class OutputTuple;
class OutputRelation;
class HeapInputTuple;
class HashTable;
class HashJoin;
void hashjoin(struct dbSysHead *head, relation *temp_datadic1, relation *temp_datadic2 ,relation *result,char *name);
#endif
