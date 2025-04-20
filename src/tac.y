%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <backend_helper.h>
#include <iostream>
#include <tacgen.h>

extern int tac_lex();
extern int tac_lineno;
extern char* tac_text;
extern FILE* tac_lex_file;
void tac_error(const char* msg);
%}

%define api.prefix {tac_}

%union {
    char* string;
}

%define parse.error verbose

%token <string> IDENTIFIER TEMP STRING_LITERAL CONSTANT_LITERAL LABEL REFERENCE
%token <string> CALL RETURN PARAM PUSH POP GOTO STATIC COPY IF FUNC ENTER EXIT INDEX
%token <string> COMMA ASSIGN AMPERSAND EXCLAMATION
%token <string> TILDE MINUS PLUS ASTERISK SLASH PERCENT DOT
%token <string> LESS_THAN GREATER_THAN CARET PIPE LE_OP GE_OP
%token <string> RIGHT_OP LEFT_OP AND_OP OR_OP EQ_OP NE_OP

%type <string> variable

%start program

%%

program
    : statement
    | statement program
    ;

binary_operator
    : PLUS
    | MINUS
    | ASTERISK
    | AMPERSAND
    | SLASH
    | PERCENT
    | CARET
    | PIPE
    | AND_OP
    | OR_OP
    | LEFT_OP
    | RIGHT_OP
    | EQ_OP
    | NE_OP
    | LESS_THAN
    | GREATER_THAN
    | GE_OP
    | LE_OP
    ;

unary_operator
    : REFERENCE    
    | ASTERISK      
    | PLUS          
    | MINUS         
    | TILDE         
    | EXCLAMATION  
    ;

special_operator
    : AMPERSAND
    | ASTERISK
    ;

statement
    : label_statement // Done
    | function_statement // Done
    | if_statement
    | return_statement // Done
    | call_statement // Done
    | assignment_statement
    | param_statement // Done
    | push_statement // Done
    | pop_statement // Done
    | goto_statement // Done
    | static_statement // Done
    | copy_statement // Done
    | ENTER // Done
    | EXIT // Done
    ;

conditional_operator
    : LESS_THAN
    | GREATER_THAN
    | LE_OP
    | GE_OP
    | EQ_OP
    | NE_OP
    ;

quad_statement
    : variable ASSIGN variable binary_operator variable
    | variable ASSIGN variable binary_operator CONSTANT_LITERAL
    | variable ASSIGN CONSTANT_LITERAL binary_operator variable
    | variable ASSIGN CONSTANT_LITERAL binary_operator CONSTANT_LITERAL
    ;

triple_statement
    : variable ASSIGN unary_operator variable
    | variable ASSIGN unary_operator CONSTANT_LITERAL
    | special_operator variable ASSIGN variable
    | special_operator variable ASSIGN CONSTANT_LITERAL
    ;

double_statement
    : variable ASSIGN variable
    | variable ASSIGN CONSTANT_LITERAL
    | variable ASSIGN STRING_LITERAL
    ;

label_statement
    : LABEL { create_label_statement(std::string($1), tac_lineno); }
    ;

function_statement
    : FUNC LABEL
    ;

if_statement
    : IF variable conditional_operator variable GOTO IDENTIFIER
    | IF variable conditional_operator CONSTANT_LITERAL GOTO IDENTIFIER
    | IF CONSTANT_LITERAL conditional_operator variable GOTO IDENTIFIER
    | IF CONSTANT_LITERAL conditional_operator CONSTANT_LITERAL GOTO IDENTIFIER
    ;

return_statement
    : RETURN variable 
    | RETURN CONSTANT_LITERAL
    | RETURN
    ;

call_statement
    : CALL IDENTIFIER COMMA CONSTANT_LITERAL
    ;

assignment_statement
    : quad_statement // Done
    | triple_statement // Done
    | double_statement // Done
    | variable ASSIGN CALL IDENTIFIER COMMA CONSTANT_LITERAL
    ;

param_statement
    : PARAM variable
    | PARAM CONSTANT_LITERAL
    ;

push_statement
    : PUSH variable CONSTANT_LITERAL INDEX CONSTANT_LITERAL
    ;

pop_statement
    : POP CONSTANT_LITERAL
    ;

goto_statement
    : GOTO IDENTIFIER
    ;

static_statement
    : STATIC variable CONSTANT_LITERAL INDEX CONSTANT_LITERAL
    | STATIC variable CONSTANT_LITERAL
// This is for string static
    ;

copy_statement
    : COPY variable COMMA variable
    ;

variable
    : IDENTIFIER { $$ = $1; }
    | TEMP { $$ = $1; }
    ;

%%

void tac_error(const char* msg) {
    fprintf(stderr, "TAC Parser error at line %d: %s\n", tac_lineno, msg);
}
