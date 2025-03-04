/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 13 "src/mylang.y"
{
    char *nice;
}
/* Line 1529 of yacc.c.  */
#line 231 "src/y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

