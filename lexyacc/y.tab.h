/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CREATE_TABLE = 258,
    DROP_TABLE = 259,
    INSERT = 260,
    VALUES = 261,
    DELETE = 262,
    SELECT = 263,
    FROM = 264,
    WHERE = 265,
    ORDER_BY = 266,
    ATTRIBUTE = 267,
    BEqual = 268,
    BUNEqual = 269,
    BSmaller = 270,
    BSmallerEqual = 271,
    BBigger = 272,
    BBiggerEqual = 273,
    BLike = 274,
    LEFT_PARENTHESIS = 275,
    RIGHT_PARENTHESIS = 276,
    COMMA = 277,
    AND = 278,
    OR = 279,
    INT_TYPE = 280,
    VARCHAR_TYPE = 281,
    DATE_TYPE = 282,
    VARIABLE = 283,
    NUMBER = 284,
    CHAR = 285,
    DATE = 286
  };
#endif
/* Tokens.  */
#define CREATE_TABLE 258
#define DROP_TABLE 259
#define INSERT 260
#define VALUES 261
#define DELETE 262
#define SELECT 263
#define FROM 264
#define WHERE 265
#define ORDER_BY 266
#define ATTRIBUTE 267
#define BEqual 268
#define BUNEqual 269
#define BSmaller 270
#define BSmallerEqual 271
#define BBigger 272
#define BBiggerEqual 273
#define BLike 274
#define LEFT_PARENTHESIS 275
#define RIGHT_PARENTHESIS 276
#define COMMA 277
#define AND 278
#define OR 279
#define INT_TYPE 280
#define VARCHAR_TYPE 281
#define DATE_TYPE 282
#define VARIABLE 283
#define NUMBER 284
#define CHAR 285
#define DATE 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
