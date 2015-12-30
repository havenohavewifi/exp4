lex lexical-analysis.l 
yacc -d syntactic-analysis.y 
g++ -o demo y.tab.c bit.o err.o init.o Buffer.o cursor.o filter.o update.o diskOpt.o fileOpt.o project.o indexOpt.o loaddata.o nestloop.o tableScan.o buffManage.o b_plus_tree.o createTable.o dropTable.o deleteRecords.o deleteAllTuples.o dataDictionary.o insertOneTuple.o insertOneRecord.o cursorForTmptable.o getaRecordbyCursor.o recorder_char_general.o printTempTable.o join.o join_hashjoin.o sortmergejoin.o join_indexjoin.o
