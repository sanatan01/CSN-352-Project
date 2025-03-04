/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     CONSTANT = 259,
     STRING_LITERAL = 260,
     SIZEOF = 261,
     PTR_OP = 262,
     INC_OP = 263,
     DEC_OP = 264,
     LEFT_OP = 265,
     RIGHT_OP = 266,
     LE_OP = 267,
     GE_OP = 268,
     EQ_OP = 269,
     NE_OP = 270,
     AND_OP = 271,
     OR_OP = 272,
     MUL_ASSIGN = 273,
     DIV_ASSIGN = 274,
     MOD_ASSIGN = 275,
     ADD_ASSIGN = 276,
     SUB_ASSIGN = 277,
     LEFT_ASSIGN = 278,
     RIGHT_ASSIGN = 279,
     AND_ASSIGN = 280,
     XOR_ASSIGN = 281,
     OR_ASSIGN = 282,
     TYPE_NAME = 283,
     TYPEDEF = 284,
     EXTERN = 285,
     STATIC = 286,
     AUTO = 287,
     REGISTER = 288,
     CHAR = 289,
     SHORT = 290,
     INT = 291,
     LONG = 292,
     SIGNED = 293,
     UNSIGNED = 294,
     FLOAT = 295,
     DOUBLE = 296,
     CONST = 297,
     VOLATILE = 298,
     VOID = 299,
     STRUCT = 300,
     UNION = 301,
     ENUM = 302,
     ELLIPSIS = 303,
     SEMICOLON = 304,
     LEFT_BRACE = 305,
     RIGHT_BRACE = 306,
     COMMA = 307,
     COLON = 308,
     ASSIGN = 309,
     LEFT_PAREN = 310,
     RIGHT_PAREN = 311,
     LEFT_BRACKET = 312,
     RIGHT_BRACKET = 313,
     DOT = 314,
     AMPERSAND = 315,
     EXCLAMATION = 316,
     TILDE = 317,
     MINUS = 318,
     PLUS = 319,
     ASTERISK = 320,
     SLASH = 321,
     PERCENT = 322,
     LESS_THAN = 323,
     GREATER_THAN = 324,
     CARET = 325,
     PIPE = 326,
     QUESTION = 327,
     INVALID_ID = 328,
     INVALID_CHAR = 329,
     INVALID_OCT = 330,
     UNTERM_STRING = 331,
     CASE = 332,
     DEFAULT = 333,
     IF = 334,
     ELSE = 335,
     SWITCH = 336,
     WHILE = 337,
     DO = 338,
     FOR = 339,
     GOTO = 340,
     CONTINUE = 341,
     BREAK = 342,
     RETURN = 343,
     ERROR = 344
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CONSTANT 259
#define STRING_LITERAL 260
#define SIZEOF 261
#define PTR_OP 262
#define INC_OP 263
#define DEC_OP 264
#define LEFT_OP 265
#define RIGHT_OP 266
#define LE_OP 267
#define GE_OP 268
#define EQ_OP 269
#define NE_OP 270
#define AND_OP 271
#define OR_OP 272
#define MUL_ASSIGN 273
#define DIV_ASSIGN 274
#define MOD_ASSIGN 275
#define ADD_ASSIGN 276
#define SUB_ASSIGN 277
#define LEFT_ASSIGN 278
#define RIGHT_ASSIGN 279
#define AND_ASSIGN 280
#define XOR_ASSIGN 281
#define OR_ASSIGN 282
#define TYPE_NAME 283
#define TYPEDEF 284
#define EXTERN 285
#define STATIC 286
#define AUTO 287
#define REGISTER 288
#define CHAR 289
#define SHORT 290
#define INT 291
#define LONG 292
#define SIGNED 293
#define UNSIGNED 294
#define FLOAT 295
#define DOUBLE 296
#define CONST 297
#define VOLATILE 298
#define VOID 299
#define STRUCT 300
#define UNION 301
#define ENUM 302
#define ELLIPSIS 303
#define SEMICOLON 304
#define LEFT_BRACE 305
#define RIGHT_BRACE 306
#define COMMA 307
#define COLON 308
#define ASSIGN 309
#define LEFT_PAREN 310
#define RIGHT_PAREN 311
#define LEFT_BRACKET 312
#define RIGHT_BRACKET 313
#define DOT 314
#define AMPERSAND 315
#define EXCLAMATION 316
#define TILDE 317
#define MINUS 318
#define PLUS 319
#define ASTERISK 320
#define SLASH 321
#define PERCENT 322
#define LESS_THAN 323
#define GREATER_THAN 324
#define CARET 325
#define PIPE 326
#define QUESTION 327
#define INVALID_ID 328
#define INVALID_CHAR 329
#define INVALID_OCT 330
#define UNTERM_STRING 331
#define CASE 332
#define DEFAULT 333
#define IF 334
#define ELSE 335
#define SWITCH 336
#define WHILE 337
#define DO 338
#define FOR 339
#define GOTO 340
#define CONTINUE 341
#define BREAK 342
#define RETURN 343
#define ERROR 344




/* Copy the first part of user declarations.  */
#line 1 "src/mylang.y"

#include "helper.h"
void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
// Global variable to hold the current type for declaration
char *currentType = NULL;
int grammarErrorCount = 0;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 13 "src/mylang.y"
{
    char *nice;
}
/* Line 193 of yacc.c.  */
#line 289 "src/y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 302 "src/y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1525

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  229
/* YYNRULES -- Number of states.  */
#define YYNSTATES  388

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   344

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    13,    15,    17,    22,
      26,    31,    35,    39,    42,    45,    47,    51,    53,    56,
      59,    62,    65,    70,    72,    74,    76,    78,    80,    82,
      84,    89,    91,    95,    99,   103,   105,   109,   113,   115,
     119,   123,   125,   129,   133,   137,   141,   143,   147,   151,
     153,   157,   159,   163,   165,   169,   171,   175,   177,   181,
     183,   189,   191,   195,   197,   199,   201,   203,   205,   207,
     209,   211,   213,   215,   217,   219,   223,   227,   231,   233,
     236,   240,   245,   248,   252,   256,   260,   265,   269,   271,
     274,   276,   279,   281,   284,   286,   290,   292,   296,   300,
     304,   306,   308,   310,   312,   314,   316,   318,   320,   322,
     324,   326,   328,   330,   332,   334,   336,   338,   341,   347,
     352,   355,   357,   359,   361,   364,   368,   371,   373,   376,
     378,   380,   384,   386,   389,   393,   398,   404,   407,   409,
     413,   415,   419,   421,   423,   426,   428,   430,   434,   439,
     443,   448,   453,   457,   459,   462,   465,   469,   471,   474,
     476,   480,   482,   486,   489,   492,   494,   496,   500,   502,
     505,   507,   509,   512,   516,   519,   523,   527,   532,   535,
     539,   543,   548,   550,   554,   559,   561,   565,   567,   569,
     571,   573,   575,   577,   581,   586,   590,   593,   597,   601,
     606,   608,   611,   613,   616,   618,   621,   627,   635,   641,
     643,   645,   651,   659,   666,   674,   682,   686,   689,   692,
     695,   699,   701,   704,   706,   708,   713,   717,   721,   724
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     153,     0,    -1,     3,    -1,     4,    -1,     5,    -1,    55,
     110,    56,    -1,    89,    -1,    91,    -1,    92,    57,   110,
      58,    -1,    92,    55,    56,    -1,    92,    55,    93,    56,
      -1,    92,    59,     3,    -1,    92,     7,     3,    -1,    92,
       8,    -1,    92,     9,    -1,   108,    -1,    93,    52,   108,
      -1,    92,    -1,     8,    94,    -1,     9,    94,    -1,    95,
      96,    -1,     6,    94,    -1,     6,    55,   138,    56,    -1,
      60,    -1,    65,    -1,    64,    -1,    63,    -1,    62,    -1,
      61,    -1,    94,    -1,    55,   138,    56,    96,    -1,    96,
      -1,    97,    65,    96,    -1,    97,    66,    96,    -1,    97,
      67,    96,    -1,    97,    -1,    98,    64,    97,    -1,    98,
      63,    97,    -1,    98,    -1,    99,    10,    98,    -1,    99,
      11,    98,    -1,    99,    -1,   100,    68,    99,    -1,   100,
      69,    99,    -1,   100,    12,    99,    -1,   100,    13,    99,
      -1,   100,    -1,   101,    14,   100,    -1,   101,    15,   100,
      -1,   101,    -1,   102,    60,   101,    -1,   102,    -1,   103,
      70,   102,    -1,   103,    -1,   104,    71,   103,    -1,   104,
      -1,   105,    16,   104,    -1,   105,    -1,   106,    17,   105,
      -1,   106,    -1,   106,    72,   110,    53,   107,    -1,   107,
      -1,    94,   109,   108,    -1,    54,    -1,    18,    -1,    19,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    25,    -1,    26,    -1,    27,    -1,   108,    -1,   110,
      52,   108,    -1,    89,    52,   108,    -1,   108,    52,    89,
      -1,   107,    -1,   114,    49,    -1,   114,   115,    49,    -1,
     114,     3,   113,    49,    -1,    89,    49,    -1,    89,   115,
      49,    -1,   114,    89,    49,    -1,    57,   111,    58,    -1,
     113,    57,   111,    58,    -1,   113,    57,    58,    -1,   117,
      -1,   117,   114,    -1,   118,    -1,   118,   114,    -1,   129,
      -1,   129,   114,    -1,   116,    -1,   115,    52,   116,    -1,
     130,    -1,   130,    54,   141,    -1,    89,    54,   141,    -1,
     130,    54,    89,    -1,    29,    -1,    30,    -1,    31,    -1,
      32,    -1,    33,    -1,    44,    -1,    34,    -1,    35,    -1,
      36,    -1,    37,    -1,    40,    -1,    41,    -1,    38,    -1,
      39,    -1,   119,    -1,   126,    -1,    28,    -1,   118,   132,
      -1,   120,     3,    50,   121,    51,    -1,   120,    50,   121,
      51,    -1,   120,     3,    -1,    45,    -1,    46,    -1,   122,
      -1,   121,   122,    -1,   123,   124,    49,    -1,   118,   123,
      -1,   118,    -1,   129,   123,    -1,   129,    -1,   125,    -1,
     124,    52,   125,    -1,   130,    -1,    53,   111,    -1,   130,
      53,   111,    -1,    47,    50,   127,    51,    -1,    47,     3,
      50,   127,    51,    -1,    47,     3,    -1,   128,    -1,   127,
      52,   128,    -1,     3,    -1,     3,    54,   111,    -1,    42,
      -1,    43,    -1,   132,   131,    -1,   131,    -1,     3,    -1,
      55,   130,    56,    -1,   131,    57,   111,    58,    -1,   131,
      57,    58,    -1,   131,    55,   134,    56,    -1,   131,    55,
     137,    56,    -1,   131,    55,    56,    -1,    65,    -1,    65,
     133,    -1,    65,   132,    -1,    65,   133,   132,    -1,   129,
      -1,   133,   129,    -1,   135,    -1,   135,    52,    48,    -1,
     136,    -1,   135,    52,   136,    -1,   114,   130,    -1,   114,
     139,    -1,   114,    -1,     3,    -1,   137,    52,     3,    -1,
     123,    -1,   123,   139,    -1,   132,    -1,   140,    -1,   132,
     140,    -1,    55,   139,    56,    -1,    57,    58,    -1,    57,
     111,    58,    -1,   140,    57,    58,    -1,   140,    57,   111,
      58,    -1,    55,    56,    -1,    55,   134,    56,    -1,   140,
      55,    56,    -1,   140,    55,   134,    56,    -1,   108,    -1,
      50,   142,    51,    -1,    50,   142,    52,    51,    -1,   141,
      -1,   142,    52,   141,    -1,   144,    -1,   145,    -1,   148,
      -1,   149,    -1,   151,    -1,   152,    -1,     3,    53,   143,
      -1,    77,   111,    53,   143,    -1,    78,    53,   143,    -1,
      50,    51,    -1,    50,   147,    51,    -1,    50,   146,    51,
      -1,    50,   146,   147,    51,    -1,   112,    -1,   146,   112,
      -1,   143,    -1,   147,   143,    -1,    49,    -1,   110,    49,
      -1,    79,    55,   110,    56,   143,    -1,    79,    55,   110,
      56,   143,    80,   143,    -1,    81,    55,   110,    56,   143,
      -1,    49,    -1,   112,    -1,    82,    55,   110,    56,   143,
      -1,    83,   143,    82,    55,   110,    56,    49,    -1,    84,
      55,   148,   148,    56,   143,    -1,    84,    55,   150,   148,
     110,    56,   143,    -1,    84,    55,   148,   150,   110,    56,
     143,    -1,    85,     3,    49,    -1,    86,    49,    -1,    87,
      49,    -1,    88,    49,    -1,    88,   110,    49,    -1,   154,
      -1,   153,   154,    -1,   155,    -1,   112,    -1,   114,   130,
     146,   145,    -1,   114,   130,   145,    -1,   130,   146,   145,
      -1,   130,   145,    -1,    89,   145,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   109,   109,   110,   111,   112,   113,   121,   122,   123,
     124,   125,   126,   127,   128,   133,   134,   139,   140,   141,
     142,   143,   144,   148,   149,   150,   151,   152,   153,   158,
     159,   164,   165,   166,   167,   171,   172,   173,   177,   178,
     179,   184,   185,   186,   187,   188,   192,   193,   194,   199,
     200,   204,   205,   209,   210,   215,   216,   220,   221,   226,
     227,   232,   233,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   252,   253,   254,   258,   265,   270,
     273,   278,   286,   290,   294,   301,   302,   307,   315,   316,
     323,   324,   325,   326,   330,   331,   335,   336,   337,   341,
     349,   350,   351,   352,   353,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   379,   380,
     381,   385,   386,   390,   391,   395,   399,   400,   401,   402,
     406,   407,   411,   412,   413,   418,   419,   420,   424,   425,
     429,   430,   435,   436,   441,   442,   446,   447,   448,   449,
     450,   451,   452,   456,   457,   458,   459,   463,   464,   469,
     470,   474,   475,   479,   480,   481,   485,   486,   490,   491,
     495,   496,   497,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   514,   515,   516,   520,   521,   526,   527,   528,
     529,   530,   531,   535,   536,   537,   541,   542,   543,   544,
     548,   549,   553,   554,   558,   559,   564,   565,   566,   570,
     571,   575,   576,   577,   578,   579,   583,   584,   585,   586,
     587,   592,   593,   597,   598,   602,   605,   608,   611,   614
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT",
  "STRING_LITERAL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN",
  "TYPE_NAME", "TYPEDEF", "EXTERN", "STATIC", "AUTO", "REGISTER", "CHAR",
  "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST",
  "VOLATILE", "VOID", "STRUCT", "UNION", "ENUM", "ELLIPSIS", "SEMICOLON",
  "LEFT_BRACE", "RIGHT_BRACE", "COMMA", "COLON", "ASSIGN", "LEFT_PAREN",
  "RIGHT_PAREN", "LEFT_BRACKET", "RIGHT_BRACKET", "DOT", "AMPERSAND",
  "EXCLAMATION", "TILDE", "MINUS", "PLUS", "ASTERISK", "SLASH", "PERCENT",
  "LESS_THAN", "GREATER_THAN", "CARET", "PIPE", "QUESTION", "INVALID_ID",
  "INVALID_CHAR", "INVALID_OCT", "UNTERM_STRING", "CASE", "DEFAULT", "IF",
  "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK",
  "RETURN", "ERROR", "$accept", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration", "array_declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "declaration_list", "statement_list",
  "expression_statement", "selection_statement", "declaration_statement",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    91,    91,    91,    91,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    94,    94,    94,
      94,    94,    94,    95,    95,    95,    95,    95,    95,    96,
      96,    97,    97,    97,    97,    98,    98,    98,    99,    99,
      99,   100,   100,   100,   100,   100,   101,   101,   101,   102,
     102,   103,   103,   104,   104,   105,   105,   106,   106,   107,
     107,   108,   108,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   110,   110,   110,   111,   112,
     112,   112,   112,   112,   112,   113,   113,   113,   114,   114,
     114,   114,   114,   114,   115,   115,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   119,   119,
     119,   120,   120,   121,   121,   122,   123,   123,   123,   123,
     124,   124,   125,   125,   125,   126,   126,   126,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     131,   131,   131,   132,   132,   132,   132,   133,   133,   134,
     134,   135,   135,   136,   136,   136,   137,   137,   138,   138,
     139,   139,   139,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   141,   141,   141,   142,   142,   143,   143,   143,
     143,   143,   143,   144,   144,   144,   145,   145,   145,   145,
     146,   146,   147,   147,   148,   148,   149,   149,   149,   150,
     150,   151,   151,   151,   151,   151,   152,   152,   152,   152,
     152,   153,   153,   154,   154,   155,   155,   155,   155,   155
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     4,     3,
       4,     3,     3,     2,     2,     1,     3,     1,     2,     2,
       2,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     2,
       3,     4,     2,     3,     3,     3,     4,     3,     1,     2,
       1,     2,     1,     2,     1,     3,     1,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     5,     4,
       2,     1,     1,     1,     2,     3,     2,     1,     2,     1,
       1,     3,     1,     2,     3,     4,     5,     2,     1,     3,
       1,     3,     1,     1,     2,     1,     1,     3,     4,     3,
       4,     4,     3,     1,     2,     2,     3,     1,     2,     1,
       3,     1,     3,     2,     2,     1,     1,     3,     1,     2,
       1,     1,     2,     3,     2,     3,     3,     4,     2,     3,
       3,     4,     1,     3,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     4,     3,     2,     3,     3,     4,
       1,     2,     1,     2,     1,     2,     5,     7,     5,     1,
       1,     5,     7,     6,     7,     7,     3,     2,     2,     2,
       3,     1,     2,     1,     1,     4,     3,     3,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   146,   116,   100,   101,   102,   103,   104,   106,   107,
     108,   109,   112,   113,   110,   111,   142,   143,   105,   121,
     122,     0,     0,   153,     0,   224,     0,    88,    90,   114,
       0,   115,    92,     0,   145,     0,     0,   221,   223,   137,
       0,     0,   157,   155,   154,    82,     0,     0,     0,    94,
      96,   229,   146,    79,     0,     0,    96,    89,    91,   117,
     120,     0,    93,     0,   200,     0,   228,     0,     0,     0,
     144,     1,   222,     0,   140,     0,   138,   147,   158,   156,
       2,     3,     4,     0,     0,     0,   204,   196,     0,    23,
      28,    27,    26,    25,    24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     7,    17,    29,
       0,    31,    35,    38,    41,    46,    49,    51,    53,    55,
      57,    59,    61,    74,     0,   202,   187,   188,     0,     0,
     189,   190,   191,   192,     0,    83,     0,     0,     0,     0,
      84,    80,   226,     0,     0,   127,     0,   123,     0,   129,
     201,   227,   166,   152,   165,     0,   159,   161,     0,     2,
     149,     6,    29,    78,     0,     0,     0,   135,     0,     0,
       0,    21,     0,    18,    19,     6,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   217,   218,   219,
       0,     0,     0,    13,    14,     0,     0,     0,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    63,     0,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   205,     0,   198,     0,   197,   203,     0,   182,    98,
      95,     6,    97,     0,    81,     0,   225,     0,   126,   119,
     124,     0,     0,   130,   132,   128,     0,     0,   163,   170,
     164,   171,   150,     0,     0,   151,   148,   136,   141,   139,
     193,     0,     5,     0,   170,   169,     0,     0,   195,     0,
       0,     0,     0,   204,   210,     0,     0,   216,   220,    76,
      12,     9,     0,    15,     0,    11,    62,    32,    33,    34,
      37,    36,    39,    40,    44,    45,    42,    43,    47,    48,
      50,    52,    54,    56,    58,     0,    77,    75,   199,   185,
       0,    85,    87,     0,   118,   133,   125,     0,     0,   178,
       0,     0,   174,     0,   172,     0,     0,   160,   162,   167,
      22,    30,   194,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     8,     0,   183,     0,    86,   131,   134,   179,
     173,   175,   180,     0,   176,     0,   206,   208,   211,     0,
       0,     0,     0,    16,    60,   184,   186,   181,   177,     0,
       0,   213,     0,     0,   207,   212,   215,   214
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   107,   108,   292,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   209,
     124,   164,    64,   139,    65,    48,    49,    27,    28,    29,
      30,   146,   147,   148,   252,   253,    31,    75,    76,    32,
      50,    34,    35,    44,   330,   156,   157,   158,   178,   331,
     261,   239,   320,   125,   126,   127,    67,   129,   130,   131,
     286,   132,   133,    36,    37,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -179
static const yytype_int16 yypact[] =
{
     809,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,    40,     6,   -25,     8,  -179,    21,  1478,  1369,  -179,
      71,  -179,  1478,   747,   141,    11,   314,  -179,  -179,   -38,
      47,    24,  -179,  -179,   -25,  -179,   386,    35,    89,  -179,
      60,  -179,    48,  -179,    -2,   106,  1240,  -179,  -179,  -179,
      93,  1180,  -179,    64,  -179,    21,  -179,   747,  1302,   587,
     141,  -179,  -179,    47,    77,   194,  -179,  -179,  -179,  -179,
      73,  -179,  -179,  1076,  1091,  1091,  -179,  -179,   575,  -179,
    -179,  -179,  -179,  -179,  -179,  1124,    86,    91,   133,   177,
     746,   197,   254,   213,   251,   872,    10,  -179,   176,   636,
    1124,  -179,   114,   212,   269,   180,   274,   221,   239,   231,
     292,    20,  -179,   261,   159,  -179,  -179,  -179,   449,   620,
    -179,  -179,  -179,  -179,   891,  -179,    28,   954,  1124,    49,
    -179,  -179,  -179,   747,  1180,  1401,  1272,  -179,    69,  1180,
    -179,  -179,  -179,  -179,    46,   260,   266,  -179,    26,  -179,
    -179,  -179,  -179,  -179,   262,   232,  1124,  -179,    47,   746,
     575,  -179,  1139,  -179,  -179,   270,    76,    87,   265,   271,
     746,  1139,  1139,  1139,   241,   512,   276,  -179,  -179,  -179,
     185,  1124,   323,  -179,  -179,   965,  1139,   324,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  1124,
    -179,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,
    1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1124,  1139,
     240,  -179,  1124,  -179,   683,  -179,  -179,   891,  -179,  -179,
    -179,  -179,  -179,   273,  -179,   984,  -179,  1433,  -179,  -179,
    -179,  1124,   198,  -179,   275,  -179,  1202,   997,  -179,    39,
    -179,   196,  -179,  1457,   329,  -179,  -179,  -179,  -179,  -179,
    -179,   277,  -179,  1331,   203,  -179,  1124,   746,  -179,    98,
     134,   153,   279,  -179,  -179,   512,  1028,  -179,  -179,  -179,
    -179,  -179,   167,  -179,    -4,  -179,  -179,  -179,  -179,  -179,
     114,   114,   212,   212,   269,   269,   269,   269,   180,   180,
     274,   221,   239,   231,   292,   238,  -179,  -179,  -179,  -179,
     242,  -179,  -179,   280,  -179,  -179,  -179,    69,  1124,  -179,
     281,   283,  -179,   282,   196,   684,  1060,  -179,  -179,  -179,
    -179,  -179,  -179,   746,   746,   746,  1139,   285,  1139,  1139,
    1124,  -179,  -179,  1124,  -179,   854,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,   306,  -179,   305,   284,  -179,  -179,   168,
     746,   173,   188,  -179,  -179,  -179,  -179,  -179,  -179,   746,
     316,  -179,   746,   746,  -179,  -179,  -179,  -179
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,   -50,  -179,   -64,    81,    90,    51,
      75,   142,   143,   144,   140,   145,  -179,   -54,  -114,  -179,
      32,   -51,     2,  -179,     0,   -10,   235,  -179,    72,  -179,
    -179,   228,  -138,    94,  -179,    50,  -179,   301,   207,   166,
       3,   -29,   -18,  -179,   -67,  -179,   113,  -179,   214,   -98,
    -174,  -133,  -179,   -78,  -179,    -3,    79,   255,  -178,  -179,
      97,  -179,  -179,  -179,   349,  -179
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      26,   155,    25,    33,   242,    43,    70,   285,   250,     1,
      59,     1,    73,     1,     1,   163,    55,    16,    17,   162,
     238,    51,   184,   238,    52,    41,    79,    57,    58,    56,
      66,     1,    62,   171,   173,   174,    26,   228,    25,    33,
      23,   163,     1,    39,   179,   162,   210,   140,   232,     1,
      74,   236,   134,   142,   352,    55,   260,    45,    46,    45,
     162,    22,   191,    22,   151,    22,    22,     1,   154,   150,
      53,    23,     1,    23,    60,    23,    22,   289,   264,   275,
      77,   293,   265,    22,   163,   334,    23,   243,   162,   134,
      40,   270,   229,    23,   256,   296,   257,    47,   244,    47,
     334,   256,   278,   257,   319,   138,   245,   347,   349,   250,
      54,    23,   163,    45,   137,   268,   162,    47,   317,    22,
     176,    61,   251,   238,    22,   128,   169,    59,   232,    23,
     150,   166,   272,   145,    23,   143,   259,   190,   135,   180,
     246,   136,   273,   144,   257,   150,   181,   297,   298,   299,
     232,   254,    23,    47,   343,   141,   236,   258,   136,   274,
     145,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   211,
     212,   213,   177,   192,   193,   194,   232,   284,   182,    42,
     344,   163,   218,   219,   323,   162,    68,   163,    69,   342,
     325,   162,   176,   163,   176,   232,   333,   162,   231,   345,
      78,   232,   341,   279,   280,   281,   145,   145,   145,   350,
     232,   145,   376,   351,   380,   232,   162,   149,   294,   382,
      70,   195,   183,   196,   288,   197,   373,   232,   259,   248,
     232,   238,   145,   255,   383,   167,   168,   326,   220,   221,
     327,   335,   185,   336,   149,   274,   154,   186,   273,    41,
     257,   315,   187,   154,   177,   366,   367,   368,   363,   304,
     305,   306,   307,   154,   163,   214,   215,   358,   162,   216,
     217,   224,   163,   267,   168,   365,   162,   284,   222,   223,
     232,   353,   381,   354,   355,   300,   301,   308,   309,   374,
     188,   384,   226,   162,   386,   387,   302,   303,   227,   225,
     149,   149,   149,   230,    71,   149,   262,     1,   263,   145,
     266,   276,   191,   282,   277,   287,   290,   295,   328,   316,
     254,   321,   339,   340,   346,   154,   149,   359,   356,   360,
     361,   370,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,   377,   378,   379,   385,   310,   313,   311,    22,
     312,   240,   247,   314,   165,   269,   338,   357,   369,    23,
     371,   372,   348,   234,   271,    72,     0,     0,     0,    80,
      81,    82,    83,     0,    84,    85,     0,     0,     0,     0,
       0,     0,     0,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,    86,    46,    87,     0,     0,
       0,    88,     0,     0,     0,     0,    89,    90,    91,    92,
      93,    94,    80,    81,    82,    83,     0,    84,    85,     0,
       0,     0,     0,    95,    96,    97,     0,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     0,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,    86,    46,
     233,     0,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,    94,   159,    81,    82,    83,     0,
      84,    85,     0,     0,     0,     0,    95,    96,    97,     0,
      98,    99,   100,   101,   102,   103,   104,   105,   106,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,   283,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,    94,   159,    81,
      82,    83,     0,    84,    85,     0,     0,     0,     0,     0,
     159,    81,    82,    83,     0,    84,    85,     0,     0,     0,
       0,   106,     0,     2,     0,     0,     0,     0,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    80,    81,    82,    83,     0,    84,    85,
      88,     0,     0,     0,     0,    89,    90,    91,    92,    93,
      94,     0,    88,     0,     0,   160,     0,    89,    90,    91,
      92,    93,    94,     0,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   175,     0,     0,     0,     0,    86,
      46,   235,     0,     0,     0,    88,   161,     0,     0,     0,
      89,    90,    91,    92,    93,    94,    80,    81,    82,    83,
     208,    84,    85,     0,     0,     0,     0,    95,    96,    97,
       0,    98,    99,   100,   101,   102,   103,   104,   105,   175,
       0,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    86,    46,   318,     0,     0,     0,    88,     0,
     362,     0,     0,    89,    90,    91,    92,    93,    94,    80,
      81,    82,    83,     0,    84,    85,     0,     0,     0,     0,
      95,    96,    97,     0,    98,    99,   100,   101,   102,   103,
     104,   105,   175,     0,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    86,    46,    46,     0,     0,
       0,    88,     0,     0,     0,     0,    89,    90,    91,    92,
      93,    94,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,     0,    98,    99,   100,
     101,   102,   103,   104,   105,   175,    63,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,   159,    81,    82,
      83,     0,    84,    85,    22,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,   159,    81,    82,    83,     0,
      84,    85,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,    81,    82,    83,    24,    84,
      85,     0,     0,     0,   237,   375,     0,     0,     0,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,    94,
       0,   189,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,    89,    90,    91,    92,    93,    94,     0,     0,
       0,   237,     0,   161,     0,     0,    88,     0,     0,     0,
       0,    89,    90,    91,    92,    93,    94,   159,    81,    82,
      83,   175,    84,    85,     0,     0,     0,     0,   159,    81,
      82,    83,     0,    84,    85,     0,     0,     0,     0,     0,
     161,     0,     0,     0,     0,     0,     0,   159,    81,    82,
      83,     0,    84,    85,     0,     0,     0,     0,     0,     0,
     159,    81,    82,    83,   237,    84,    85,     0,     0,    88,
       0,     0,     0,     0,    89,    90,    91,    92,    93,    94,
      88,   291,     0,     0,     0,    89,    90,    91,    92,    93,
      94,   159,    81,    82,    83,     0,    84,    85,     0,    88,
       0,     0,   322,   241,    89,    90,    91,    92,    93,    94,
       0,     0,    88,     0,   161,   332,     0,    89,    90,    91,
      92,    93,    94,   159,    81,    82,    83,     0,    84,    85,
       0,     0,     0,   161,     0,     0,     0,    86,     0,   159,
      81,    82,    83,    88,    84,    85,   161,     0,    89,    90,
      91,    92,    93,    94,   159,    81,    82,    83,     0,    84,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,     0,   175,   364,     0,
      89,    90,    91,    92,    93,    94,     0,   159,    81,    82,
      83,   170,    84,    85,     0,     0,    89,    90,    91,    92,
      93,    94,   159,    81,    82,    83,   172,    84,    85,   161,
       0,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,     0,   161,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    88,
     161,     0,     0,     0,    89,    90,    91,    92,    93,    94,
       0,     0,     0,     0,    88,     0,     0,     0,     0,    89,
      90,    91,    92,    93,    94,     1,     0,     0,     2,     0,
       0,     0,     0,   161,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,   175,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,     0,     0,     0,     0,     0,   256,   329,   257,
       0,     0,     0,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,     0,
      46,     0,     0,     0,   137,     0,     0,     0,     0,     0,
       2,     0,     0,     0,     0,   152,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,     0,   249,     0,     0,     0,     0,     0,    63,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,     0,     0,     0,     0,     0,     0,     0,   153,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
       0,     0,     0,     0,     0,     0,   273,   329,   257,     0,
       0,     0,     0,     0,     0,     0,    23,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       0,     0,     0,     0,    23,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     0,     0,     0,     0,    23,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,     0,     0,   324,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,   337,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21
};

static const yytype_int16 yycheck[] =
{
       0,    68,     0,     0,   137,    23,    35,   185,   146,     3,
      28,     3,    50,     3,     3,    69,    26,    42,    43,    69,
     134,    24,   100,   137,     3,    22,    44,    27,    28,    26,
      33,     3,    32,    83,    84,    85,    36,    17,    36,    36,
      65,    95,     3,     3,    95,    95,   110,    49,    52,     3,
       3,   129,    54,    56,    58,    65,   154,    49,    50,    49,
     110,    55,    52,    55,    67,    55,    55,     3,    68,    67,
      49,    65,     3,    65,     3,    65,    55,   191,    52,   177,
      56,   195,    56,    55,   138,   259,    65,   138,   138,    54,
      50,   169,    72,    65,    55,   209,    57,    89,    49,    89,
     274,    55,   180,    57,   237,    57,    57,   285,   286,   247,
      89,    65,   166,    49,    54,   166,   166,    89,   232,    55,
      88,    50,    53,   237,    55,    46,    53,   145,    52,    65,
     128,    54,    56,    61,    65,    56,   154,   105,    49,    53,
     143,    52,    55,    50,    57,   143,    55,   211,   212,   213,
      52,   148,    65,    89,    56,    49,   234,   154,    52,   177,
      88,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,    65,
      66,    67,    88,     7,     8,     9,    52,   185,    55,    23,
      56,   245,    12,    13,   245,   245,    55,   251,    57,   277,
     251,   251,   170,   257,   172,    52,   257,   257,    49,    56,
      44,    52,   276,   181,   182,   183,   144,   145,   146,    52,
      52,   149,   355,    56,    56,    52,   276,    61,   196,    56,
     259,    55,    55,    57,    49,    59,   350,    52,   256,   145,
      52,   355,   170,   149,    56,    51,    52,    49,    68,    69,
      52,    55,    55,    57,    88,   273,   256,     3,    55,   256,
      57,   229,    49,   263,   170,   343,   344,   345,   335,   218,
     219,   220,   221,   273,   328,    63,    64,   328,   328,    10,
      11,    60,   336,    51,    52,   336,   336,   285,    14,    15,
      52,    53,   370,    51,    52,   214,   215,   222,   223,   353,
      49,   379,    71,   353,   382,   383,   216,   217,    16,    70,
     144,   145,   146,    52,     0,   149,    56,     3,    52,   247,
      58,    56,    52,    82,    53,    49,     3,     3,    53,    89,
     327,    58,     3,    56,    55,   335,   170,    56,    58,    56,
      58,    56,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    56,    58,    80,    49,   224,   227,   225,    55,
     226,   136,   144,   228,    73,   168,   263,   327,   346,    65,
     348,   349,   285,   128,   170,    36,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   247,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    89,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     3,     4,     5,     6,    -1,     8,     9,
      55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    -1,    55,    -1,    -1,    58,    -1,    60,    61,    62,
      63,    64,    65,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    89,    -1,    -1,    -1,    -1,    49,
      50,    51,    -1,    -1,    -1,    55,    89,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,     3,     4,     5,     6,
      54,     8,     9,    -1,    -1,    -1,    -1,    77,    78,    79,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    49,    50,    51,    -1,    -1,    -1,    55,    -1,
      56,    -1,    -1,    60,    61,    62,    63,    64,    65,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,
      77,    78,    79,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    49,    50,    50,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    89,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     3,     4,     5,
       6,    -1,     8,     9,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    89,     8,
       9,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    -1,    -1,
      -1,    50,    -1,    89,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,     3,     4,     5,
       6,    89,     8,     9,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    50,     8,     9,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      55,    56,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,     3,     4,     5,     6,    -1,     8,     9,    -1,    55,
      -1,    -1,    58,    89,    60,    61,    62,    63,    64,    65,
      -1,    -1,    55,    -1,    89,    58,    -1,    60,    61,    62,
      63,    64,    65,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    49,    -1,     3,
       4,     5,     6,    55,     8,     9,    89,    -1,    60,    61,
      62,    63,    64,    65,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    89,    58,    -1,
      60,    61,    62,    63,    64,    65,    -1,     3,     4,     5,
       6,    55,     8,     9,    -1,    -1,    60,    61,    62,    63,
      64,    65,     3,     4,     5,     6,    55,     8,     9,    89,
      -1,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      89,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,     3,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    89,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    89,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,     3,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    89,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    65,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    65,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    51,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    55,    65,    89,   112,   114,   117,   118,   119,
     120,   126,   129,   130,   131,   132,   153,   154,   155,     3,
      50,   130,   129,   132,   133,    49,    50,    89,   115,   116,
     130,   145,     3,    49,    89,   115,   130,   114,   114,   132,
       3,    50,   114,    89,   112,   114,   145,   146,    55,    57,
     131,     0,   154,    50,     3,   127,   128,    56,   129,   132,
       3,     4,     5,     6,     8,     9,    49,    51,    55,    60,
      61,    62,    63,    64,    65,    77,    78,    79,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    91,    92,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   110,   143,   144,   145,   146,   147,
     148,   149,   151,   152,    54,    49,    52,    54,    57,   113,
      49,    49,   145,   146,    50,   118,   121,   122,   123,   129,
     112,   145,     3,    56,   114,   134,   135,   136,   137,     3,
      58,    89,    94,   107,   111,   127,    54,    51,    52,    53,
      55,    94,    55,    94,    94,    89,   110,   123,   138,   111,
      53,    55,    55,    55,   143,    55,     3,    49,    49,    49,
     110,    52,     7,     8,     9,    55,    57,    59,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    54,   109,
      96,    65,    66,    67,    63,    64,    10,    11,    12,    13,
      68,    69,    14,    15,    60,    70,    71,    16,    17,    72,
      52,    49,    52,    51,   147,    51,   143,    50,   108,   141,
     116,    89,   141,   111,    49,    57,   145,   121,   123,    51,
     122,    53,   124,   125,   130,   123,    55,    57,   130,   132,
     139,   140,    56,    52,    52,    56,    58,    51,   111,   128,
     143,   138,    56,    55,   132,   139,    56,    53,   143,   110,
     110,   110,    82,    49,   112,   148,   150,    49,    49,   108,
       3,    56,    93,   108,   110,     3,   108,    96,    96,    96,
      97,    97,    98,    98,    99,    99,    99,    99,   100,   100,
     101,   102,   103,   104,   105,   110,    89,   108,    51,   141,
     142,    58,    58,   111,    51,   111,    49,    52,    53,    56,
     134,   139,    58,   111,   140,    55,    57,    48,   136,     3,
      56,    96,   143,    56,    56,    56,    55,   148,   150,   148,
      52,    56,    58,    53,    51,    52,    58,   125,   111,    56,
      56,    58,    56,   134,    58,   111,   143,   143,   143,   110,
      56,   110,   110,   108,   107,    51,   141,    56,    58,    80,
      56,   143,    56,    56,   143,    49,   143,   143
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:
#line 113 "src/mylang.y"
    {
		yyerror((yyvsp[(1) - (1)].nice));
		yyerrok;
	;}
    break;

  case 23:
#line 148 "src/mylang.y"
    { (yyval.nice) = "&"; ;}
    break;

  case 24:
#line 149 "src/mylang.y"
    { (yyval.nice) = "*"; ;}
    break;

  case 25:
#line 150 "src/mylang.y"
    { (yyval.nice) = "+"; ;}
    break;

  case 26:
#line 151 "src/mylang.y"
    { (yyval.nice) = "-"; ;}
    break;

  case 27:
#line 152 "src/mylang.y"
    { (yyval.nice) = "~"; ;}
    break;

  case 28:
#line 153 "src/mylang.y"
    { (yyval.nice) = "!"; ;}
    break;

  case 76:
#line 254 "src/mylang.y"
    {
		yyerror((yyvsp[(1) - (3)].nice));
		yyerrok;
	;}
    break;

  case 77:
#line 258 "src/mylang.y"
    {
		yyerror((yyvsp[(1) - (3)].nice));
		yyerrok;
	;}
    break;

  case 79:
#line 270 "src/mylang.y"
    {
		  insertSymbol((yyvsp[(1) - (2)].nice), "variable", (yyval.nice));
	  ;}
    break;

  case 80:
#line 273 "src/mylang.y"
    {
		  /* Use the variable name from init_declarator */
		  (yyval.nice) = (yyvsp[(1) - (3)].nice);
		  insertSymbol((yyvsp[(2) - (3)].nice), "variable", (yyval.nice));
	  ;}
    break;

  case 81:
#line 278 "src/mylang.y"
    {
		char *temp = malloc(strlen((yyvsp[(1) - (4)].nice)) + strlen((yyvsp[(3) - (4)].nice)) + 3);
		strcpy(temp, (yyvsp[(1) - (4)].nice));
		strcat(temp, strdup(" "));
		strcat(temp, (yyvsp[(3) - (4)].nice));
		(yyval.nice) = temp;
		insertSymbol((yyvsp[(2) - (4)].nice), "variable", (yyval.nice));
	;}
    break;

  case 82:
#line 286 "src/mylang.y"
    {
		yyerror((yyvsp[(1) - (2)].nice));
		yyerrok;
	;}
    break;

  case 83:
#line 290 "src/mylang.y"
    {
		yyerror((yyvsp[(1) - (3)].nice));
		yyerrok;
	;}
    break;

  case 84:
#line 294 "src/mylang.y"
    {
		yyerror((yyvsp[(1) - (3)].nice));
		yyerrok;
	;}
    break;

  case 85:
#line 301 "src/mylang.y"
    { (yyval.nice) = strdup("ARRAY");;}
    break;

  case 86:
#line 302 "src/mylang.y"
    {
		char *temp = malloc(strlen("ARRAY") + strlen((yyvsp[(1) - (4)].nice)) + 2);
		sprintf(temp, "ARRAY %s", (yyvsp[(1) - (4)].nice));
		(yyval.nice) = temp;
	;}
    break;

  case 87:
#line 307 "src/mylang.y"
    {
		char *temp = malloc(strlen("ARRAY") + strlen((yyvsp[(1) - (3)].nice)) + 2);
		sprintf(temp, "ARRAY %s", (yyvsp[(1) - (3)].nice));
		(yyval.nice) = temp;
	;}
    break;

  case 89:
#line 316 "src/mylang.y"
    {
		char * temp = malloc(strlen((yyvsp[(1) - (2)].nice)) + strlen((yyvsp[(2) - (2)].nice)) + 3);
		strcpy(temp, (yyvsp[(1) - (2)].nice));
		strcat(temp, strdup(" "));
		strcat(temp, (yyvsp[(2) - (2)].nice));
		(yyval.nice) = temp;
	;}
    break;

  case 98:
#line 337 "src/mylang.y"
    {
		yyerror((yyvsp[(1) - (3)].nice));
		yyerrok;
	;}
    break;

  case 99:
#line 341 "src/mylang.y"
    {
		yyerror((yyvsp[(1) - (3)].nice));
		yyerrok;
	;}
    break;

  case 105:
#line 358 "src/mylang.y"
    { (yyval.nice) = strdup("VOID"); ;}
    break;

  case 106:
#line 359 "src/mylang.y"
    { (yyval.nice) = strdup("CHAR");;}
    break;

  case 107:
#line 360 "src/mylang.y"
    { (yyval.nice) = strdup("SHORT");;}
    break;

  case 108:
#line 361 "src/mylang.y"
    { (yyval.nice) = strdup("INT");;}
    break;

  case 109:
#line 362 "src/mylang.y"
    { (yyval.nice) = strdup("LONG");;}
    break;

  case 110:
#line 363 "src/mylang.y"
    { (yyval.nice) = strdup("FLOAT");;}
    break;

  case 111:
#line 364 "src/mylang.y"
    { (yyval.nice) = strdup("DOUBLE");;}
    break;

  case 112:
#line 365 "src/mylang.y"
    { (yyval.nice) = strdup("SIGNED");;}
    break;

  case 113:
#line 366 "src/mylang.y"
    { (yyval.nice) = strdup("UNSIGNED");;}
    break;

  case 114:
#line 367 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(1) - (1)].nice); ;}
    break;

  case 115:
#line 368 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(1) - (1)].nice); ;}
    break;

  case 116:
#line 369 "src/mylang.y"
    { (yyval.nice) = strdup("TYPE_NAME");;}
    break;

  case 117:
#line 370 "src/mylang.y"
    {
		char*temp = malloc(strlen((yyvsp[(1) - (2)].nice)) + 2 );
		sprintf(temp, "%s*", (yyvsp[(1) - (2)].nice));
		(yyval.nice) = temp;
	;}
    break;

  case 118:
#line 379 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(2) - (5)].nice); ;}
    break;

  case 120:
#line 381 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(2) - (2)].nice); ;}
    break;

  case 142:
#line 435 "src/mylang.y"
    { (yyval.nice) = strdup("CONST"); ;}
    break;

  case 143:
#line 436 "src/mylang.y"
    { (yyval.nice) = strdup("VOLATILE"); ;}
    break;

  case 144:
#line 441 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(2) - (2)].nice); ;}
    break;

  case 145:
#line 442 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(1) - (1)].nice); ;}
    break;

  case 146:
#line 446 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(1) - (1)].nice); ;}
    break;

  case 147:
#line 447 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(2) - (3)].nice); ;}
    break;

  case 148:
#line 448 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(1) - (4)].nice); ;}
    break;

  case 149:
#line 449 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(1) - (3)].nice); ;}
    break;

  case 150:
#line 450 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(1) - (4)].nice); ;}
    break;

  case 151:
#line 451 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(1) - (4)].nice); ;}
    break;

  case 152:
#line 452 "src/mylang.y"
    { (yyval.nice) = (yyvsp[(1) - (3)].nice); ;}
    break;

  case 153:
#line 456 "src/mylang.y"
    { (yyval.nice) = NULL; ;}
    break;

  case 154:
#line 457 "src/mylang.y"
    { (yyval.nice) = NULL; ;}
    break;

  case 155:
#line 458 "src/mylang.y"
    { (yyval.nice) = NULL; ;}
    break;

  case 156:
#line 459 "src/mylang.y"
    { (yyval.nice) = NULL; ;}
    break;

  case 225:
#line 602 "src/mylang.y"
    {
		  insertSymbol((yyvsp[(2) - (4)].nice), "function", (yyvsp[(1) - (4)].nice)); /* Insert function with its return type */
	  ;}
    break;

  case 226:
#line 605 "src/mylang.y"
    {
		  insertSymbol((yyvsp[(2) - (3)].nice), "function", (yyvsp[(1) - (3)].nice));
	  ;}
    break;

  case 227:
#line 608 "src/mylang.y"
    {
		  insertSymbol((yyvsp[(1) - (3)].nice), "function", "auto"); /* Default to auto when return type isn't specified */
	  ;}
    break;

  case 228:
#line 611 "src/mylang.y"
    {
		  insertSymbol((yyvsp[(1) - (2)].nice), "function", "auto");
	  ;}
    break;

  case 229:
#line 614 "src/mylang.y"
    {
		yyerror((yyvsp[(1) - (2)].nice));
		yyerrok;
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2468 "src/y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 621 "src/mylang.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
    grammarErrorCount++;
}
