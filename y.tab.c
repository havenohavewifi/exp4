/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "syntactic-analysis.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h> 
#include <memory.h>
#include <string.h>
#include "lex.yy.c"

#line 75 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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

/* Copy the second part of user declarations.  */

#line 196 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  27
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   79

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  97

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    26,    26,    27,    31,    31,    31,    31,    31,    31,
      32,    35,    42,    68,    69,    73,    74,    75,    79,    84,
      95,    96,   100,   109,   115,   124,   125,   134,   135,   136,
     140,   140,   140,   140,   140,   140,   140,   143,   146,   148,
     153,   154,   158,   159,   163,   167,   174,   183,   514,   515,
     519,   520,   524,   525,   529
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CREATE_TABLE", "DROP_TABLE", "INSERT",
  "VALUES", "DELETE", "SELECT", "FROM", "WHERE", "ORDER_BY", "ATTRIBUTE",
  "CREATE_INDEX", "BEqual", "BUNEqual", "BSmaller", "BSmallerEqual",
  "BBigger", "BBiggerEqual", "BLike", "LEFT_PARENTHESIS",
  "RIGHT_PARENTHESIS", "COMMA", "STAR", "AND", "OR", "INT_TYPE",
  "VARCHAR_TYPE", "DATE_TYPE", "VARIABLE", "NUMBER_VALUE", "VARCHAR_VALUE",
  "DATE_VALUE", "END", "EXIT", "$accept", "program", "command",
  "create_index", "create", "attribute_type_list", "attribute_type",
  "drop", "insert", "record", "item", "delete", "where_list",
  "compare_opt", "condition_const", "c_attribute", "cc_attribute",
  "condition", "select", "attribute_list", "attribute", "table_list",
  "single_table", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -25

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-25)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -3,   -24,   -21,   -17,     3,    -5,   -12,   -25,    20,    -3,
     -25,   -25,   -25,   -25,   -25,   -25,    16,   -25,    25,    13,
      32,   -25,    50,   -25,     5,   -25,    39,   -25,   -25,    34,
      40,    52,    35,    36,    37,    -4,    38,    11,    -7,   -25,
      21,    -1,   -25,   -25,   -25,     7,   -25,   -25,    41,   -25,
      48,   -25,   -25,    34,   -25,   -25,   -25,    33,   -25,   -25,
     -25,     8,    31,   -25,    -1,    37,   -25,    42,   -25,   -25,
      21,    -1,    -1,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,    -9,    10,   -25,    49,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    10,     0,     3,
       9,     4,     5,     6,     7,     8,     0,    18,     0,     0,
       0,    51,     0,    50,     0,    49,     0,     1,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
       0,     0,    25,    46,    54,     0,    53,    48,     0,    15,
       0,    17,    12,     0,    22,    23,    24,     0,    21,    41,
      40,     0,     0,    29,     0,     0,    11,     0,    13,    19,
       0,     0,     0,    26,    30,    31,    32,    33,    34,    35,
      36,     0,     0,    52,     0,    20,    27,    28,    43,    42,
      37,    38,    39,    44,    45,    47,    16
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -25,    61,   -25,   -25,   -25,   -25,    19,   -25,   -25,   -25,
       4,   -25,    12,   -25,   -25,   -25,   -25,   -14,   -25,   -25,
      43,   -25,    14
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    38,    39,    12,    13,    57,
      58,    14,    61,    81,    93,    62,    94,    63,    15,    24,
      25,    45,    46
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       1,     2,     3,    88,     4,     5,    16,    21,    21,    17,
       6,    59,    19,    18,    34,    52,    53,    64,    26,    22,
      27,    89,    90,    91,    92,    23,    23,    20,    35,    60,
      65,    30,     7,    71,    72,    71,    72,    29,    49,    50,
      51,    32,    73,    31,    95,    74,    75,    76,    77,    78,
      79,    80,    54,    55,    56,    69,    70,    86,    87,    33,
      36,    40,    41,    66,    37,    42,    43,    44,    48,    67,
      28,    96,    68,    84,    85,     0,    82,     0,    47,    83
};

static const yytype_int8 yycheck[] =
{
       3,     4,     5,    12,     7,     8,    30,    12,    12,    30,
      13,    12,     9,    30,     9,    22,    23,    10,    30,    24,
       0,    30,    31,    32,    33,    30,    30,    24,    23,    30,
      23,     6,    35,    25,    26,    25,    26,    21,    27,    28,
      29,     9,    34,    30,    34,    14,    15,    16,    17,    18,
      19,    20,    31,    32,    33,    22,    23,    71,    72,     9,
      21,    21,    10,    22,    30,    30,    30,    30,    30,    21,
       9,    22,    53,    31,    70,    -1,    64,    -1,    35,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,    13,    35,    37,    38,
      39,    40,    43,    44,    47,    54,    30,    30,    30,     9,
      24,    12,    24,    30,    55,    56,    30,     0,    37,    21,
       6,    30,     9,     9,     9,    23,    21,    30,    41,    42,
      21,    10,    30,    30,    30,    57,    58,    56,    30,    27,
      28,    29,    22,    23,    31,    32,    33,    45,    46,    12,
      30,    48,    51,    53,    10,    23,    22,    21,    42,    22,
      23,    25,    26,    34,    14,    15,    16,    17,    18,    19,
      20,    49,    48,    58,    31,    46,    53,    53,    12,    30,
      31,    32,    33,    50,    52,    34,    22
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    38,    38,    38,    38,    38,    38,
      38,    39,    40,    41,    41,    42,    42,    42,    43,    44,
      45,    45,    46,    46,    46,    47,    47,    48,    48,    48,
      49,    49,    49,    49,    49,    49,    49,    50,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      56,    56,    57,    57,    58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     3,     1,     2,     5,     2,     2,     6,
       3,     1,     1,     1,     1,     4,     6,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     4,     7,     3,     1,
       1,     1,     3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 10:
#line 32 "syntactic-analysis.y" /* yacc.c:1646  */
    {exit(0);}
#line 1338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 35 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		int fid = getLogicfidByName(&head, (yyvsp[-3]).name);
		createIndexOn(&head, fid, (yyvsp[-1]).name);
	}
#line 1347 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 42 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		// create table space
		int fid = creatFileSpace(&head);
		// find the table id in file list
		int n = queryFileID(&head, fid);
		if (n == -1) {
			printf("can't find file!\n");
			return -1;
		}
		// create and initiate table dictionary
		head.redef[n].initRelation(&head, fid, (yyvsp[-3]).name, "anonymous");
		// add attributes
		for(int i=0; i<cur_attribute; i++) {
			head.redef[n].insertAttribute(table_attributes[i].name, table_attributes[i].type, table_attributes[i].length);
		}
		
		// print succeed infomation
		printf("create table %s succeed!\n", head.redef[n].getRelationName());
	/*	for(int i=0; i<head.redef[n].getAttributeNum(); i++) {
			printf("%s %d ", head.redef[n].getAttributeByNo(i).getName(), head.redef[n].getAttributeByNo(i).getType());
		}*/
		cur_attribute = 0;
	}
#line 1375 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 73 "syntactic-analysis.y" /* yacc.c:1646  */
    { add_attribute((yyvsp[-1]).name, (yyvsp[0]).val, 4); }
#line 1381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 74 "syntactic-analysis.y" /* yacc.c:1646  */
    { add_attribute((yyvsp[-4]).name, (yyvsp[-3]).val, (yyvsp[-1]).val); }
#line 1387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 75 "syntactic-analysis.y" /* yacc.c:1646  */
    { add_attribute((yyvsp[-1]).name, (yyvsp[0]).val, 10);}
#line 1393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 79 "syntactic-analysis.y" /* yacc.c:1646  */
    { 
	dropTable(&head, (yyvsp[0]).name); }
#line 1400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 84 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		char *tmp = (char *)malloc(sizeof(char)*(cur_value+1));
		memcpy(tmp, insert_value, cur_value+1);
		printf("insert into %s value %s\n", (yyvsp[-4]).name, tmp);
		insertOneTuple(&head, (yyvsp[-4]).name, tmp);
		free(tmp);
		cur_value = 0;
	}
#line 1413 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 100 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		// memcpy(insert_value+cur_value, (void *)(&($1.val)), sizeof(int));
		char tmp[100];
		sprintf(tmp, "%d", (yyvsp[0]).val);
		memcpy(insert_value+cur_value, tmp, strlen(tmp)*sizeof(char));
		cur_value += strlen(tmp)*sizeof(char); 
		memcpy(insert_value+cur_value, "|", sizeof(char));
		cur_value += sizeof(char); 
		insert_value[cur_value] = '\0'; }
#line 1427 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 109 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		memcpy(insert_value+cur_value, (yyvsp[0]).name, sizeof(char)*strlen((yyvsp[0]).name)); 
		cur_value += strlen((yyvsp[0]).name); 
		memcpy(insert_value+cur_value, "|", sizeof(char));
		cur_value += sizeof(char); 
		insert_value[cur_value] = '\0'; }
#line 1438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 115 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		memcpy(insert_value+cur_value, (yyvsp[0]).name, sizeof(char)*strlen((yyvsp[0]).name));
		cur_value += strlen((yyvsp[0]).name); 
		memcpy(insert_value+cur_value, "|", sizeof(char));
		cur_value += sizeof(char); 
		insert_value[cur_value] = '\0'; }
#line 1449 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 124 "syntactic-analysis.y" /* yacc.c:1646  */
    { deleteAllTuples(&head, (yyvsp[0]).name); }
#line 1455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 125 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		if (cur_condition == 1) {
			int fid = getLogicfidByName(&head, (yyvsp[-3]).name);
			deleteRecordWhere(&head, fid, condition_array[0].attribute_name, condition_array[0].attribute_value, condition_array[0].operation, 0);
		}
		cur_condition = 0;
	}
#line 1467 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 143 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		sprintf(condition_array[cur_condition].attribute_value, "%d", (yyvsp[0]).val);
		condition_array[cur_condition].attribute_value[sizeof(int)] = '\0'; }
#line 1475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 146 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		strcpy(condition_array[cur_condition].attribute_value, (yyvsp[0]).name); }
#line 1482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 148 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		strcpy(condition_array[cur_condition].attribute_value, (yyvsp[0]).name); }
#line 1489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 153 "syntactic-analysis.y" /* yacc.c:1646  */
    { strcpy(condition_array[cur_condition].attribute_name, (yyvsp[0]).name); }
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 154 "syntactic-analysis.y" /* yacc.c:1646  */
    { strcpy(condition_array[cur_condition].attribute_name, (yyvsp[0]).name); }
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 158 "syntactic-analysis.y" /* yacc.c:1646  */
    { strcpy(condition_array[cur_condition].attribute_value, (yyvsp[0]).name); }
#line 1507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 159 "syntactic-analysis.y" /* yacc.c:1646  */
    { strcpy(condition_array[cur_condition].attribute_value, (yyvsp[0]).name); }
#line 1513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 163 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		condition_array[cur_condition].operation = (yyvsp[-1]).val;
		condition_array[cur_condition].isjoin = false;
		cur_condition += 1; }
#line 1522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 167 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		condition_array[cur_condition].operation = (yyvsp[-1]).val;
		condition_array[cur_condition].isjoin = true;
		cur_condition += 1; }
#line 1531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 174 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		int logicfid = getLogicfidByName(&head, (yyvsp[0]).name);
		if (logicfid != -2) {
			int tmp_dict_id = TableScan(&head, temp_data_dict, (yyvsp[0]).name);
		    
		    printTempTable(&head, temp_data_dict, tmp_dict_id);
		    
		}
	}
#line 1545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 183 "syntactic-analysis.y" /* yacc.c:1646  */
    {
		
	/*	printf("-------------------------------\n");
		printf("selected attributes: ");
		for (int i=0; i<cur_sattr; i++) {
			printf("%s ", select_attributes[i]);
		}
		printf("\n");

		printf("from %d tables: ", cur_table);
		for (int i=0; i<cur_table; i++) {
			printf("%s ", table_array[i]);
		}
		printf("\n"); 
		
		for (int i=0; i<cur_condition; i++) {
			printf("%d condition: %s %d %s\n", i+1, condition_array[i].attribute_name, condition_array[i].operation, condition_array[i].attribute_value);
		}
		printf("--------------------------------\n");*/
		
		if( cur_table == 1) {
			// fisrt projection, attributes in selected results and conditions
			int project_attrnum = cur_sattr;
			char project_attrname[10][NAMELENGTH];
			for (int i=0; i<cur_sattr; i++)
				strcpy(project_attrname[i], select_attributes[i]);

			for (int i=0; i<cur_condition; i++) {
				int j=0;
				for (j=0; j<project_attrnum; j++) {
					if (strcmp(condition_array[i].attribute_name, project_attrname[j])==0)
						break;
				}
				if (j == project_attrnum) {
					strcpy(project_attrname[project_attrnum], condition_array[i].attribute_name);
					project_attrnum++;
				}
			}
			/*
			for(int i=0; i<project_attrnum; i++)
				printf("project attr: %s\n", project_attrname[i]);
			for(int i=0; i<cur_sattr; i++)
				printf("selected attr: %s\n", select_attributes[i]);
			*/
			// table scan
			int tmp_dict_id = TableScan(&head, temp_data_dict, table_array[0]);
			// check
			for (int i=0; i<cur_sattr; i++) {
				if(!is_in_table(temp_data_dict, tmp_dict_id, select_attributes[i])) {
					cout<<"The attribute "<<select_attributes[i]<<" is not in table!"<<endl;
					exit(0);
				}
			}
			
			// projection
			tmp_dict_id = project(&head, temp_data_dict, tmp_dict_id, project_attrnum, project_attrname);
			// selection
			for (int i=0; i<cur_condition; i++) {
				if (condition_array[i].operation == EQUAL) {
					// not consider whether the index exists
					tmp_dict_id = tableScanEqualFilter(&head , temp_data_dict, tmp_dict_id, condition_array[i].attribute_name, condition_array[i].attribute_value);
				}
				// else just include <, <=, >, >=
				else {
					tmp_dict_id = tableScanSemiscopeFilter(&head, temp_data_dict, tmp_dict_id, condition_array[i].attribute_name, condition_array[i].attribute_value, condition_array[i].operation);
				}
			}
			// last projection
			if (project_attrnum > cur_sattr) {
				tmp_dict_id = project(&head, temp_data_dict, tmp_dict_id, cur_sattr, select_attributes);
			}
			// the results is in tmp_dict_id, how to read??
			printTempTable(&head, temp_data_dict, tmp_dict_id);
		}

		// multi tables join 
		else {
			// scan for each table
			int tmp_dict_id[cur_table];
			for (int k=0; k<cur_table; k++) {
				tmp_dict_id[k] = TableScan(&head, temp_data_dict, table_array[k]);
			}
			// first projection, attributes in selected results and conditions for each table
			int project_attrnum[cur_table] = {0, 0};
			char project_attrname[cur_table][10][NAMELENGTH];
			int single_condition_num[cur_table] = {0, 0};
			int single_condition_id[cur_table][10];
			int join_num = 0;
			int join_table[cur_table][2];
			char join_attrname[cur_table][NAMELENGTH];
			int final_project_attrnum = 0;
			char final_project_attrname[10][NAMELENGTH];

			// add the selected attributes into projection attribute
			for (int i=0; i<cur_sattr; i++) {
				// check the format: table.attribute or attribute
				int c = 0;
				int length = strlen(select_attributes[i]);
				for (c=0; c<length; c++) {
					if (select_attributes[i][c] == '.') {
						break;					
					}
				}
				// if format: table.attribute, then add to the table
				if (c < length) {
					strncpy(final_project_attrname[final_project_attrnum], select_attributes[i], c);
					final_project_attrname[final_project_attrnum][c] = '\0';
					for (int k=0; k<cur_table; k++) {
						if (strcmp(final_project_attrname[final_project_attrnum], table_array[k])==0) {
							// first projection
							strncpy(project_attrname[k][project_attrnum[k]], select_attributes[i]+c+1, length-c);
							project_attrnum[k]++;
							// final projection
							strcat(final_project_attrname[final_project_attrnum], "_");
							strcat(final_project_attrname[final_project_attrnum], select_attributes[i]+c+1);
							// test print
						//	printf("final project: %s\n", final_project_attrname[final_project_attrnum]);
							final_project_attrnum++;
						}
					}
				}
				// if format: attribute, find the table and add
				else {
					int is_confuse = 0;
					for (int k=0; k<cur_table; k++) {
						if (is_in_table(temp_data_dict, tmp_dict_id[k], select_attributes[i])) {
							is_confuse++;
							if (is_confuse > 1)
								break;
							strcpy(project_attrname[k][project_attrnum[k]], select_attributes[i]);
							project_attrnum[k]++;
							strcpy(final_project_attrname[final_project_attrnum], select_attributes[i]);
							final_project_attrnum++;
						}
					}
					if (is_confuse > 1) {
						printf("the attribute %s is in multiple tables\n", select_attributes[i]);
						exit(0);
					}
				}
			}
			// add the condition attributes into projection attribute, avoid repeatable attribute
			for (int i=0; i<cur_condition; i++) {
				// isjoin: table1.attr1 = table2.attr2; not isjoin: attr = const
				// printf("isjoin: %d\n", condition_array[i].isjoin);
				if (condition_array[i].isjoin) {
					// add table1.attr1 to table1's project_attrname
					int c = 0;
					int length = strlen(condition_array[i].attribute_name);
					for (c=0; c<length; c++) {
						if (condition_array[i].attribute_name[c] == '.') {
							break;					
						}
					}
					char tmp_name[NAMELENGTH];
					strncpy(tmp_name, condition_array[i].attribute_name, c);
					tmp_name[c] = '\0';
					// join the table1.attr = table2.attr, the attr is the same
					strncpy(join_attrname[join_num], condition_array[i].attribute_name+c+1, length-c);
		
					for (int k=0; k<cur_table; k++) {
						// printf("table name %s %s\n", tmp_name, table_array[k]);
						if (strcmp(tmp_name, table_array[k])==0) {
							join_table[join_num][0] = k;
							strncpy(project_attrname[k][project_attrnum[k]], condition_array[i].attribute_name+c+1, length-c);
							int j = 0;
							for (j=0; j<project_attrnum[k]; j++) {
								if (strcmp(project_attrname[k][project_attrnum[k]], project_attrname[k][j]) == 0)
									break;
							}
							if (j == project_attrnum[k])
								project_attrnum[k]++;
						}
					}
					// add table2.attr2 to table2's project_attrname
					c = 0;
					length = strlen(condition_array[i].attribute_value);
					for (c=0; c<length; c++) {
						if (condition_array[i].attribute_value[c] == '.') {
							break;					
						}
					}
					char tmp_name2[NAMELENGTH];
					strncpy(tmp_name2, condition_array[i].attribute_value, c);
					tmp_name2[c] = '\0';
					for (int k=0; k<cur_table; k++) {
						// printf("table 2 %s %s\n", tmp_name2, table_array[k]);
						if (strcmp(tmp_name2, table_array[k])==0) {
							join_table[join_num][1] = k;
							strncpy(project_attrname[k][project_attrnum[k]], condition_array[i].attribute_value+c+1, length-c);
							int j = 0;
							for (j=0; j<project_attrnum[k]; j++) {
								if (strcmp(project_attrname[k][project_attrnum[k]], project_attrname[k][j]) == 0)
									break;
							}
							if (j == project_attrnum[k])
								project_attrnum[k]++;
						}
					}
					
					join_num++;
				}
				// not isjoin: attr = const
				else {
					for (int k=0; k<cur_table; k++) {
						int is_confuse = 0;
						if (is_in_table(temp_data_dict, tmp_dict_id[k], condition_array[i].attribute_name)) {
							is_confuse++;
							if (is_confuse > 1) {
								printf("Error: the attribute %s is in multiple tables\n", condition_array[i].attribute_name);
								exit(0);
							}
							// add condition for each table
							single_condition_id[k][single_condition_num[k]] = i;
							single_condition_num[k]++;
							int j = 0;
							for (j=0; j<project_attrnum[k]; j++) {
								if (strcmp(condition_array[i].attribute_name, project_attrname[k][j])==0)
									break;
							}
							if (j == project_attrnum[k]) {							
								strcpy(project_attrname[k][project_attrnum[k]], condition_array[i].attribute_name);
								project_attrnum[k]++;
							}								
						}												
					}
				}
			}
		
		/*	printf("################################\n");
			for (int k=0; k<cur_table; k++) {
				for (int i=0; i<project_attrnum[k]; i++) {
					printf("table %d %s first projection: %s\n", k+1, table_array[k], project_attrname[k][i]);
				}
			}
			for (int k=0; k<cur_table; k++) {
				printf("table %s %d conditions\n", table_array[k], single_condition_num[k]);
				for (int i=0; i<single_condition_num[k]; i++) {
					int s = single_condition_id[0][i];
					printf("%d condition %s %s\n", i+1, condition_array[s].attribute_name, condition_array[s].attribute_value);
				}
			}
			for (int i=0; i<join_num; i++)
				printf("join %s %s condition attr: %s\n", table_array[join_table[i][0]], table_array[join_table[i][1]], join_attrname[i]);
			for (int i=0; i<final_project_attrnum; i++)
				printf("final project attr %s\n", final_project_attrname[i]);
			printf("###############################\n"); */
			
			
			// operation on single table
			for (int k=0; k<cur_table; k++) {
				// first projection
				tmp_dict_id[k] = project(&head, temp_data_dict, tmp_dict_id[k], project_attrnum[k], project_attrname[k]);
			//	printf("## join table id %d, tmp_dict id %d\n", join_table[0][0], tmp_dict_id[join_table[0][0]]);
			//	printf("### after project dict indexed %d\n", head.redef[1].getIndexedByName("nationkey"));
			//	printf("#### after project is indexed %d#########\n", temp_data_dict[tmp_dict_id[k]].getIndexedByName("nationkey"));
				// selection
				for (int i=0; i<single_condition_num[k]; i++) {
					if (condition_array[single_condition_id[k][i]].operation == EQUAL) {
						// not consider whether the index exists
						tmp_dict_id[k] = tableScanEqualFilter(&head , temp_data_dict, tmp_dict_id[k], condition_array[single_condition_id[k][i]].attribute_name, condition_array[single_condition_id[k][i]].attribute_value);
			//			printf("####after select is indexed %d#########\n", temp_data_dict[tmp_dict_id[k]].getIndexedByName(join_attrname[0]));
					}
					// else just include <, <=, >, >=
					else {
						tmp_dict_id[k] = tableScanSemiscopeFilter(&head, temp_data_dict, tmp_dict_id[k], condition_array[single_condition_id[k][i]].attribute_name, condition_array[single_condition_id[k][i]].attribute_value, condition_array[single_condition_id[k][i]].operation);
					}
				}
			}
			/*
			printf("###########table 1###############");
			printTempTable(&head, temp_data_dict, tmp_dict_id[0]);
			printf("###########table 2###############");
			printTempTable(&head, temp_data_dict, tmp_dict_id[1]);
			*/
		/*	for(int k=0; k<cur_table; k++)
				printf("####table %d is indexed %d on %s#########\n", k, temp_data_dict[tmp_dict_id[k]].getIndexedByName(join_attrname[0]), join_attrname[0]);
			*/
			// join 2 tables
			int tmp_join_dict_id;
			if (join_num == 1) {
				tmp_join_dict_id = choosejoin(&head, temp_data_dict, tmp_dict_id[join_table[0][0]], tmp_dict_id[join_table[0][1]], join_attrname[0]);
			}
			// join 3 tables
			else if (join_num == 2) {
			//	cout<<"before join"<<join_table[0][0]<<join_table[0][1]<<join_attrname[0]<<endl;
				tmp_join_dict_id = choosejoin(&head, temp_data_dict, tmp_dict_id[join_table[0][0]], tmp_dict_id[join_table[0][1]], join_attrname[0]);				
			//	cout<<"after join "<<temp_data_dict[tmp_join_dict_id].getAttributeNum()<<" name "<<temp_data_dict[tmp_join_dict_id].getRelationName()<<endl;
				//for(int i=0; i<temp_data_dict[tmp_join_dict_id].getAttributeNum(); i++)
				//	cout<<"-----------"<<temp_data_dict[tmp_join_dict_id].getAttributeByNo(i).getName()<<endl;
				for (int i=0; i<2; i++) {
				//	cout<<"not in "<<join_table[1][i]<<join_table[0][1]<<join_table[0][0]<<endl;
					if (join_table[1][i]==join_table[0][0] || join_table[1][i]==join_table[0][1]) {
					//	cout<<"---2 table"<<join_table[1][1-i]<<endl;
					//	for(int k=0; k<temp_data_dict[tmp_dict_id[join_table[1][1-i]]].getAttributeNum(); k++)
					//		cout<<"-----------"<<temp_data_dict[tmp_dict_id[join_table[1][1-i]]].getAttributeByNo(k).getName()<<endl;
						tmp_join_dict_id = choosejoin(&head, temp_data_dict, tmp_join_dict_id, tmp_dict_id[join_table[1][1-i]], join_attrname[1]);
				//		cout<<"after join "<<temp_data_dict[tmp_join_dict_id].getAttributeNum()<<" name "<<temp_data_dict[tmp_join_dict_id].getRelationName()<<endl;
					}
				}
			}
			// join multiple tables
			else {
				
			}
			
			
			/*
			printf("############join##############\n");
			printTempTable(&head, temp_data_dict, tmp_join_dict_id);
			*/
			
			// project final result
		//	cout<<"final project num "<<final_project_attrnum<<endl;
		/*	for(int i=0; i<final_project_attrnum; i++)
				cout<<final_project_attrname[i]<<endl;	*/
			tmp_join_dict_id = project(&head, temp_data_dict, tmp_join_dict_id, final_project_attrnum, final_project_attrname);
			
			// print results
		/*	printf("---------------------------------------------");
			printf("id %d\n", tmp_join_dict_id);*/
			printTempTable(&head, temp_data_dict, tmp_join_dict_id);	
		}
		
		cur_condition = 0;
		cur_sattr = 0;
		cur_table = 0;
	}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 519 "syntactic-analysis.y" /* yacc.c:1646  */
    { strcpy(select_attributes[cur_sattr], (yyvsp[0]).name); cur_sattr++; }
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 520 "syntactic-analysis.y" /* yacc.c:1646  */
    { strcpy(select_attributes[cur_sattr], (yyvsp[0]).name); cur_sattr++; }
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 529 "syntactic-analysis.y" /* yacc.c:1646  */
    {strcpy(table_array[cur_table], (yyvsp[0]).name); cur_table++; }
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1900 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 532 "syntactic-analysis.y" /* yacc.c:1906  */


bool is_in_table(relation *temp_data_dict, int dict_id, char *attr_name) {
	for (int i = 0; i < temp_data_dict[dict_id].getAttributeNum(); i++) {
		if (strcmp(attr_name, temp_data_dict[dict_id].getAttributeByNo(i).getName()) == 0) {
			return true;
		}
	}
	return false;
}

int find_empty_tempdict(relation *temp_data_dict){
    int i = 0;
    for (i = 0; i < MAX_FILE_NUM; i++) {
        if (strcmp(temp_data_dict[i].getRelationName(),"") == 0) {
            temp_data_dict[i].init("temp_datadict","XXX");
            return i;
        }
    }
    if (i == MAX_FILE_NUM) {
        cout<<"no temp datadict for use!"<<endl;
        return -3;
    }
}

void add_attribute(char *name, int type, int length) {
	strcpy(table_attributes[cur_attribute].name, name);
	table_attributes[cur_attribute].type = type;
	table_attributes[cur_attribute].length = length;
	cur_attribute += 1;
}

int init_database(struct dbSysHead *head)
{
	initSys(head);
	head->fpdesc = fopen(DBMS_DAT, "rb+");
	isAvail(head->fpdesc, "main", FOPEN);
	return 0;
}

int main(int argc, char *argv[]) {
	cout<<"Welcome to Database Management System!"<<endl;
	init_database(&head);
	if (argc==2 && strcmp(argv[1], "big")==0) {
		createTable(&head);
		loaddata(&head, 1);
	//	createIndexOn(&head, 1, "custkey");

		createTable(&head);
		loaddata(&head, 2);
	//	createIndexOn(&head, 2, "nationkey");
		
		createTable(&head);
		loaddata(&head, 3);
	//	createIndexOn(&head, 3, "regionkey");
	}

	cur_attribute = 0;
	cur_condition = 0;
	cur_value = 0;
    yyparse();
}

void yyerror(char *s) {
    printf("Wrong Syntax, Please Try Again!\n");
    yyparse();
}

int yywrap() {
	return 1;
}
