//
//  createTable.cpp
//  
//
//  Created by IreneWu on 15/11/28.
//
//

#include "createTable.h"
#include "file.h"
#include "dbHead.h"
#include "datadictionary.h"
#include "string.h"
#include <iostream>

using namespace std;
/*
struct eachAttribute{
    char[A_NAME_LENGTH] attribute_name_;
    int attribute_type_;
    int attribute_length_;
};
 */
int createTable(struct dbSysHead * head, const char * relationName, const char * constructorName,  int attributeNum, struct eachAttribute * attributeList)
{
    int fid = creatFileSpace(head);
    int n = queryFileID(head, fid);
    if (n == -1)
    {
        cout<<"can't find file!"<<endl;
        return -1;
    }
    head->redef[n].initRelation(head, fid, relationName, constructorName);
    for (int i = 0 ; i < attributeNum; i++) {
        head->redef[n].insertAttribute(attributeList[i].attribute_name_, attributeList[i].attribute_type_, attributeList[i].attribute_length_);
    }
    cout<<"create table succeed!"<<endl;
    return  0;
}
//add some param such as tablename and attribute array?
int createTable(struct dbSysHead *head)
{
    int fid = creatFileSpace(head);
    int n = queryFileID(head, fid);
    if (n == -1)
    {
        cout<<"can't find file!"<<endl;
        return -1;
    }
    if (fid == 1) {
        
        head->redef[n].initRelation(head, fid, "customer", "TianzhenWu");
        head->redef[n].insertAttribute("custkey", 1, 4);
        head->redef[n].insertAttribute("name", 2, 32);
        head->redef[n].insertAttribute("address", 2, 40);
        head->redef[n].insertAttribute("nationkey", 1, 4);
        head->redef[n].insertAttribute("phone", 2, 16);
        head->redef[n].insertAttribute("acctbal", 2, 64);
        head->redef[n].insertAttribute("mktsegment", 2, 12);
        head->redef[n].insertAttribute("comment", 2, 128);
    }
    
    if (fid == 2) {
        head->redef[n].initRelation(head, fid, "nation", "IreneWu");
        head->redef[n].insertAttribute("nationkey", 1, 4);
        head->redef[n].insertAttribute("name", 2, 32);
        head->redef[n].insertAttribute("regionkey", 1, 4);
        head->redef[n].insertAttribute("comment", 2, 160);
    }
    return 0;
}
