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
    CREATE_INDEX = 268,
    BEqual = 269,
    BUNEqual = 270,
    BSmaller = 271,
    BSmallerEqual = 272,
    BBigger = 273,
    BBiggerEqual = 274,
    BLike = 275,
    LEFT_PARENTHESIS = 276,
    RIGHT_PARENTHESIS = 277,
    COMMA = 278,
    STAR = 279,
    AND = 280,
    OR = 281,
    INT_TYPE = 282,
    VARCHAR_TYPE = 283,
    DATE_TYPE = 284,
    VARIABLE = 285,
    NUMBER_VALUE = 286,
    VARCHAR_VALUE = 287,
    DATE_VALUE = 288,
    END = 289,
    EXIT = 290
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
#define CREATE_INDEX 268
#define BEqual 269
#define BUNEqual 270
#define BSmaller 271
#define BSmallerEqual 272
#define BBigger 273
#define BBiggerEqual 274
#define BLike 275
#define LEFT_PARENTHESIS 276
#define RIGHT_PARENTHESIS 277
#define COMMA 278
#define STAR 279
#define AND 280
#define OR 281
#define INT_TYPE 282
#define VARCHAR_TYPE 283
#define DATE_TYPE 284
#define VARIABLE 285
#define NUMBER_VALUE 286
#define VARCHAR_VALUE 287
#define DATE_VALUE 288
#define END 289
#define EXIT 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
