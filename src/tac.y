%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <backend_helper.h>
#include <iostream>

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
    : label_statement
    | function_statement
    | if_statement
    | return_statement
    | call_statement
    | assignment_statement
    | param_statement
    | push_statement
    | pop_statement
    | goto_statement
    | static_statement
    | copy_statement
    | ENTER
    | EXIT
    ;

conditional_operator
    : LESS_THAN
    | GREATER_THAN
    | LE_OP
    | GE_OP
    | EQ_OP
    | NE_OP
    ;

condition
    : variable conditional_operator variable
    | variable conditional_operator CONSTANT_LITERAL
    | CONSTANT_LITERAL conditional_operator variable
    | CONSTANT_LITERAL conditional_operator CONSTANT_LITERAL
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
    : LABEL {
        std::cerr << "Label: " << $1 << std::endl;
    }
    ;

function_statement
    : FUNC LABEL
    ;

if_statement
    : IF condition goto_statement
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
    : quad_statement
    | triple_statement
    | double_statement
    | variable ASSIGN call_statement
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
    : IDENTIFIER
    | TEMP
    ;

%%

void tac_error(const char* msg) {
    fprintf(stderr, "TAC Parser error at line %d: %s\n", tac_lineno, msg);
}
