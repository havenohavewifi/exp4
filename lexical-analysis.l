%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "define.h"
	#include "y.tab.h"
	extern YYSTYPE yylval;
%}
letter			[a-zA-Z]


%%
"CREATE TABLE"	{return CREATE_TABLE;}
"DROP TABLE"	{return DROP_TABLE;}
"INSERT INTO"	{return INSERT;}
"VALUES"		{return VALUES;}
"DELETE"		{return DELETE;}
"SELECT"		{return SELECT;}
"FROM"			{return FROM;}
"WHERE"			{return WHERE;}
"ORDER BY"		{return ORDER_BY;}
"*"				{return STAR;}
"AND"			{return AND;}
"OR"			{return OR;}

"CREATE INDEX ON"	{return CREATE_INDEX;}

"EXIT"			{return EXIT;}

"("		{return LEFT_PARENTHESIS;}
")"		{return RIGHT_PARENTHESIS;}
","		{return COMMA;}

"int"		{yylval.val=1; return INT_TYPE;}
"varchar"	{yylval.val=2; return VARCHAR_TYPE;}
"date"		{yylval.val=3; return DATE_TYPE;}

{letter}({letter}|[0-9])*	{sscanf(yytext, "%s", yylval.name); return VARIABLE;}

{letter}({letter}|[0-9])*"."{letter}({letter}|[0-9])*	{sscanf(yytext, "%s", yylval.name); return ATTRIBUTE;}

\"({letter}|[0-9]|"-")*\"		{ memcpy(yylval.name,yytext+1,strlen(yytext)-2); yylval.name[strlen(yytext)-2] = '\0'; return VARCHAR_VALUE;}
[0-9]+		{sscanf(yytext, "%d", &yylval.val); return NUMBER_VALUE;}

[0-9]{4}"-"[0-1][0-9]"-"[0-3][0-9]	{sscanf(yytext, "%s", yylval.name); return DATE_VALUE;}

"="		{yylval.val=5; return BEqual;}
"<>"	{yylval.val=4; return BUNEqual;}
"<"		{yylval.val=0; return BSmaller;}
"<="	{yylval.val=3; return BSmallerEqual;}
">"		{yylval.val=2; return BBigger;}
">="	{yylval.val=1; return BBiggerEqual;}
"LIKE"	{yylval.val=7; return BLike;}

";"	{return END;}

[ |\t]+ ;
\n ;

.	{return yytext[0]; }
%%
