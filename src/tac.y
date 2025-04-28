%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <backend_helper.h>
#include <iostream>
#include <tacgen.h>
#include <utils.h>

extern int tac_lex();
extern int tac_lineno;
extern char* tac_text;
extern FILE* tac_lex_file;
void tac_error(const char* msg);

using namespace backend;
%}

%define api.prefix {tac_}

%union {
    char* string;
    int op_type;
}

%define parse.error verbose

%token <string> IDENTIFIER TEMP STRING_LITERAL CONSTANT_LITERAL LABEL REFERENCE LPAREN RPAREN
%token <string> CALL RETURN PARAM PUSH POP GOTO STATIC IF FUNC ENTER EXIT DATA GLOBAL ARG
%token <string> COMMA ASSIGN AMPERSAND EXCLAMATION NEWLINE
%token <string> TILDE MINUS PLUS ASTERISK SLASH PERCENT DOT
%token <string> LESS_THAN GREATER_THAN CARET PIPE LE_OP GE_OP
%token <string> RIGHT_OP LEFT_OP AND_OP OR_OP EQ_OP NE_OP

%type <string> variable cast_type
%type <op_type> binary_operator unary_operator special_operator conditional_operator

%start program

%%

program
    : statement
    | statement program
    ;

binary_operator
    : PLUS              { $$ = ADD; }
    | MINUS             { $$ = SUB; } 
    | ASTERISK          { $$ = MUL; }
    | AMPERSAND         { $$ = BITWISE_AND; }
    | SLASH             { $$ = DIV; }
    | PERCENT           { $$ = MOD; }
    | CARET             { $$ = BITWISE_XOR; }
    | PIPE              { $$ = BITWISE_OR; }
    | AND_OP            { $$ = LOGICAL_AND; }
    | OR_OP             { $$ = LOGICAL_OR; }
    | LEFT_OP           { $$ = SHL; }
    | RIGHT_OP          { $$ = SHR; }
    | EQ_OP             { $$ = EQ; }
    | NE_OP             { $$ = NE; }
    | LESS_THAN         { $$ = LT; }
    | GREATER_THAN      { $$ = GT; }
    | GE_OP             { $$ = GE; }
    | LE_OP             { $$ = LE; }
    ;

unary_operator
    : REFERENCE         { $$ = REF_OP; }
    | ASTERISK          { $$ = DEREF_OP; }
    | TILDE             { $$ = TILDE_OP; }
    | EXCLAMATION       { $$ = EXCLAMATION_OP; }
    | MINUS             { $$ = NEG_OP; }
    | PLUS              { $$ = POS_OP; }
    ;

special_operator
    : AMPERSAND         { $$ = AMPERSAND_SP; }
    | ASTERISK          { $$ = ASTERISK_SP; }
    ;

conditional_operator
    : LESS_THAN         { $$ = LT; }
    | GREATER_THAN      { $$ = GT; }
    | LE_OP             { $$ = LE; }
    | GE_OP             { $$ = GE; }
    | EQ_OP             { $$ = EQ; }
    | NE_OP             { $$ = NE; }
    ;

statement
    : labeled_statement NEWLINE
    | add_variable_statement NEWLINE
    | if_statement NEWLINE
    | return_statement NEWLINE
    | call_statement NEWLINE
    | assignment_statement NEWLINE
    | param_statement NEWLINE
    | pop_statement NEWLINE
    | goto_statement NEWLINE
    | cast_statement NEWLINE
    | ENTER NEWLINE { create_enter_statement(); } 
    | EXIT NEWLINE { create_exit_statement(); }
    | NEWLINE { /* Ignore empty lines */ }
    ;

cast_statement
    : variable ASSIGN LPAREN cast_type RPAREN variable { create_cast_statement(std::string($1), std::string($4), std::string($6), false); }
    | variable ASSIGN LPAREN cast_type RPAREN CONSTANT_LITERAL { create_cast_statement(std::string($1), std::string($4), std::string($6), true); }
    ; 

cast_type
    : IDENTIFIER { $$ = $1; }
    | cast_type IDENTIFIER {
        char* temp = (char*) malloc(strlen($1) + strlen($2) + 1);
        strcpy(temp, $1);
        strcat(temp, $2);
        $$ = temp;
    }

quad_statement
    : variable ASSIGN variable binary_operator variable {
        create_quad(std::string($1), std::string($3), static_cast<BinaryOp>($4), std::string($5), false, false);
    }
    | variable ASSIGN variable binary_operator CONSTANT_LITERAL {
        create_quad(std::string($1), std::string($3), static_cast<BinaryOp>($4), std::string($5), false, true);
    }
    | variable ASSIGN CONSTANT_LITERAL binary_operator variable {
        create_quad(std::string($1), std::string($3), static_cast<BinaryOp>($4), std::string($5), true, false);
    }
    | variable ASSIGN CONSTANT_LITERAL binary_operator CONSTANT_LITERAL {
        create_quad(std::string($1), std::string($3), static_cast<BinaryOp>($4), std::string($5), true, true);
    }
    ;

triple_statement
    : variable ASSIGN unary_operator variable {
        create_triple(std::string($1), false, static_cast<UnaryOp>($3), NONE_SP, std::string($4));
    }
    | variable ASSIGN unary_operator CONSTANT_LITERAL {
        create_triple(std::string($1), true, static_cast<UnaryOp>($3), NONE_SP, std::string($4));
    }
    | special_operator variable ASSIGN variable {
        create_triple(std::string($2), false, NOP, static_cast<SpecialOp>($1), std::string($4));
    }
    | special_operator variable ASSIGN CONSTANT_LITERAL {
        create_triple(std::string($2), true, NOP, static_cast<SpecialOp>($1), std::string($4));
    }
    ;

double_statement
    : variable ASSIGN variable {
        create_double(std::string($1), std::string($3), false);
    }
    | variable ASSIGN CONSTANT_LITERAL {
        create_double(std::string($1), std::string($3), true);
    }
    ;

labeled_statement
    : LABEL { create_label_statement(std::string($1)); }
    | FUNC LABEL CONSTANT_LITERAL { create_func_statement(std::string($2), std::string($3)); }
    ;

if_statement
    : IF variable conditional_operator variable GOTO IDENTIFIER {
        create_if_statement(std::string($2), std::string($4), static_cast<BinaryOp>($3), std::string($6), false, false);
    }
    | IF variable conditional_operator CONSTANT_LITERAL GOTO IDENTIFIER{
        create_if_statement(std::string($2), std::string($4), static_cast<BinaryOp>($3), std::string($6), false, true);
    }
    | IF CONSTANT_LITERAL conditional_operator variable GOTO IDENTIFIER {
        create_if_statement(std::string($2), std::string($4), static_cast<BinaryOp>($3), std::string($6), true, false);
    }
    | IF CONSTANT_LITERAL conditional_operator CONSTANT_LITERAL GOTO IDENTIFIER {
        create_if_statement(std::string($2), std::string($4), static_cast<BinaryOp>($3), std::string($6), true, true);
    }
    ;

return_statement
    : RETURN variable { 
        create_return_statement(std::string($2), false);
    }
    | RETURN CONSTANT_LITERAL {
        create_return_statement(std::string($2), true);
    }
    | RETURN {
        create_return_statement("", false);
    }
    ;

call_statement
    : variable ASSIGN CALL IDENTIFIER COMMA CONSTANT_LITERAL { 
        create_call_statement(std::string($1), std::string($4), std::string($6));
    }
    ;

assignment_statement
    : quad_statement
    | triple_statement
    | double_statement
    ;

param_statement
    : PARAM variable {
        create_param_statement(std::string($2), false);
    }
    | PARAM CONSTANT_LITERAL {
        create_param_statement(std::string($2), true);
    }
    ;

add_variable_statement
    : PUSH variable CONSTANT_LITERAL {
        create_variable_statement(LOCAL_St, std::string($2), std::string($3));
    }
    | PUSH variable ASSIGN variable CONSTANT_LITERAL {
        create_variable_statement_assign(LOCAL_St, std::string($2), std::string($4), false, std::string($5));
    }
    | PUSH variable ASSIGN CONSTANT_LITERAL CONSTANT_LITERAL {
        create_variable_statement_assign(LOCAL_St, std::string($2), std::string($4), true, std::string($5));
    }
    | STATIC variable CONSTANT_LITERAL {
        create_variable_statement(STATIC_St, std::string($2), std::string($3));
    }
    | STATIC variable ASSIGN variable CONSTANT_LITERAL {
        error_msg("Cannot assign static variable non const-type");
    }
    | STATIC variable ASSIGN CONSTANT_LITERAL CONSTANT_LITERAL {
        create_variable_statement_assign(STATIC_St, std::string($2), std::string($4), true, std::string($5));
    }
    | GLOBAL variable CONSTANT_LITERAL {
        create_variable_statement(GLOBAL_St, std::string($2), std::string($3));
    }
    | GLOBAL variable ASSIGN variable CONSTANT_LITERAL {
        create_variable_statement_assign(GLOBAL_St, std::string($2), std::string($4), false, std::string($5));
    }
    | GLOBAL variable ASSIGN CONSTANT_LITERAL CONSTANT_LITERAL {
        create_variable_statement_assign(GLOBAL_St, std::string($2), std::string($4), true, std::string($5));
    }
    | DATA variable STRING_LITERAL {
        create_variable_statement(DATA_St, std::string($2), std::string($3));
    }
    | ARG variable CONSTANT_LITERAL {
        create_variable_statement(ARG_St, std::string($2), std::string($3));
    }
    ;

pop_statement
    : POP CONSTANT_LITERAL {
        create_pop_statement(std::string($2));
    }
    ;

goto_statement
    : GOTO IDENTIFIER {
        create_goto_statement(std::string($2));
    }
    ;

variable
    : IDENTIFIER { $$ = $1; }
    | TEMP { $$ = $1; }
    ;

%%

void tac_error(const char* msg) {
    fprintf(stderr, "TAC Parser error at line %d: %s\n", tac_lineno, msg);
}
