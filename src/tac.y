%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <backend_helper.h>
#include <iostream>
#include <codegen.h>

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

// Add type for non-terminal types
%type <string> condition variable binary_operator unary_operator special_operator conditional_operator

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
    | ENTER {
        Label* enterLabel = new Label(".enter");
        enterLabel->line_number = tac_lineno;
        tac_instructions.push_back(enterLabel);
    }
    | EXIT {
        Label* exitLabel = new Label(".exit");
        exitLabel->line_number = tac_lineno;
        tac_instructions.push_back(exitLabel);
    }
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
    : variable conditional_operator variable {
        // Store the condition parts for later use in if_statement
        $$ = (char*)malloc(strlen($1) + strlen($2) + strlen($3) + 3);
        sprintf($$, "%s %s %s", $1, $2, $3);
    }
    | variable conditional_operator CONSTANT_LITERAL {
        // Store the condition parts for later use in if_statement
        $$ = (char*)malloc(strlen($1) + strlen($2) + strlen($3) + 3);
        sprintf($$, "%s %s %s", $1, $2, $3);
    }
    | CONSTANT_LITERAL conditional_operator variable {
        // Store the condition parts for later use in if_statement
        $$ = (char*)malloc(strlen($1) + strlen($2) + strlen($3) + 3);
        sprintf($$, "%s %s %s", $1, $2, $3);
    }
    | CONSTANT_LITERAL conditional_operator CONSTANT_LITERAL {
        // Store the condition parts for later use in if_statement
        $$ = (char*)malloc(strlen($1) + strlen($2) + strlen($3) + 3);
        sprintf($$, "%s %s %s", $1, $2, $3);
    }
    ;

quad_statement
    : variable ASSIGN variable binary_operator variable {
        Quad* quad = new Quad($1, $3, $4, $5);
        quad->line_number = tac_lineno;
        tac_instructions.push_back(quad);
    }
    | variable ASSIGN variable binary_operator CONSTANT_LITERAL {
        Quad* quad = new Quad($1, $3, $4, $5);
        quad->line_number = tac_lineno;
        tac_instructions.push_back(quad);
    }
    | variable ASSIGN CONSTANT_LITERAL binary_operator variable {
        Quad* quad = new Quad($1, $3, $4, $5);
        quad->line_number = tac_lineno;
        tac_instructions.push_back(quad);
    }
    | variable ASSIGN CONSTANT_LITERAL binary_operator CONSTANT_LITERAL {
        Quad* quad = new Quad($1, $3, $4, $5);
        quad->line_number = tac_lineno;
        tac_instructions.push_back(quad);
    }
    ;

triple_statement
    : variable ASSIGN unary_operator variable {
        Triplet* triplet = new Triplet($1, $3, $4);
        triplet->line_number = tac_lineno;
        tac_instructions.push_back(triplet);
    }
    | variable ASSIGN unary_operator CONSTANT_LITERAL {
        Triplet* triplet = new Triplet($1, $3, $4);
        triplet->line_number = tac_lineno;
        tac_instructions.push_back(triplet);
    }
    | special_operator variable ASSIGN variable {
        // Special case handling for dereferencing and address-of
        Triplet* triplet = new Triplet($1, "", $4);
        triplet->line_number = tac_lineno;
        tac_instructions.push_back(triplet);
    }
    | special_operator variable ASSIGN CONSTANT_LITERAL {
        // Special case handling for dereferencing and address-of
        Triplet* triplet = new Triplet($1, "", $4);
        triplet->line_number = tac_lineno;
        tac_instructions.push_back(triplet);
    }
    ;

double_statement
    : variable ASSIGN variable {
        Double* assign = new Double($1, $3);
        assign->line_number = tac_lineno;
        tac_instructions.push_back(assign);
    }
    | variable ASSIGN CONSTANT_LITERAL {
        Double* assign = new Double($1, $3);
        assign->line_number = tac_lineno;
        tac_instructions.push_back(assign);
    }
    | variable ASSIGN STRING_LITERAL {
        Double* assign = new Double($1, $3);
        assign->line_number = tac_lineno;
        tac_instructions.push_back(assign);
    }
    ;

label_statement
    : LABEL {
        Label* label = new Label($1);
        label->line_number = tac_lineno;
        tac_instructions.push_back(label);
    }
    ;

function_statement
    : FUNC LABEL {
        // Create and push a Label for function
        Label* funcLabel = new Label($2);
        funcLabel->line_number = tac_lineno;
        tac_instructions.push_back(funcLabel);
    }
    ;

if_statement
    : IF condition goto_statement {
        // Extract parts from condition string
        char* condition_str = $2;
        
        // Create the conditional goto
        ConditionalGoto* cond_goto = new ConditionalGoto($2, "", "", "");
        cond_goto->line_number = tac_lineno;
        
        // Parse the condition string
        char op1[100], op[10], op2[100];
        sscanf(condition_str, "%s %s %s", op1, op, op2);
        
        cond_goto->op1 = op1;
        cond_goto->op = op;
        cond_goto->op2 = op2;
        
        // Link to the goto's label
        cond_goto->label = *((Goto*)tac_instructions.back());
        
        // Replace the simple goto with the conditional goto
        delete tac_instructions.back();
        tac_instructions.pop_back();
        tac_instructions.push_back(cond_goto);
        
        free(condition_str);
    }
    ;

return_statement
    : RETURN variable {
        Return* ret = new Return($2);
        ret->line_number = tac_lineno;
        tac_instructions.push_back(ret);
    }
    | RETURN CONSTANT_LITERAL {
        Return* ret = new Return($2);
        ret->line_number = tac_lineno;
        tac_instructions.push_back(ret);
    }
    | RETURN {
        Return* ret = new Return("");
        ret->line_number = tac_lineno;
        tac_instructions.push_back(ret);
    }
    ;

call_statement
    : CALL IDENTIFIER COMMA CONSTANT_LITERAL {
        Call* call = new Call($2, atoi($4));
        call->line_number = tac_lineno;
        tac_instructions.push_back(call);
    }
    ;

assignment_statement
    : quad_statement
    | triple_statement
    | double_statement
    | variable ASSIGN call_statement
    ;

param_statement
    : PARAM variable {
        Arg* arg = new Arg($2);
        arg->line_number = tac_lineno;
        tac_instructions.push_back(arg);
    }
    | PARAM CONSTANT_LITERAL {
        Arg* arg = new Arg($2);
        arg->line_number = tac_lineno;
        tac_instructions.push_back(arg);
    }
    ;

push_statement
    : PUSH variable CONSTANT_LITERAL INDEX CONSTANT_LITERAL {
        Push* push = new Push($2, $3, atoi($5));
        push->line_number = tac_lineno;
        tac_instructions.push_back(push);
    }
    ;

pop_statement
    : POP CONSTANT_LITERAL {
        Pop* pop = new Pop($2);
        pop->line_number = tac_lineno;
        tac_instructions.push_back(pop);
    }
    ;

goto_statement
    : GOTO IDENTIFIER {
        Goto* goto_stmt = new Goto($2);
        goto_stmt->line_number = tac_lineno;
        tac_instructions.push_back(goto_stmt);
    }
    ;

static_statement
    : STATIC variable CONSTANT_LITERAL INDEX CONSTANT_LITERAL {
        Static* static_stmt = new Static($2, $3, atoi($5));
        static_stmt->line_number = tac_lineno;
        tac_instructions.push_back(static_stmt);
    }
    | STATIC variable CONSTANT_LITERAL {
        Static* static_stmt = new Static($2, $3);
        static_stmt->line_number = tac_lineno;
        tac_instructions.push_back(static_stmt);
    }
    ;

copy_statement
    : COPY variable COMMA variable {
        Copy* copy = new Copy($1, $3);
        copy->line_number = tac_lineno;
        tac_instructions.push_back(copy);
    }
    ;

variable
    : IDENTIFIER
    | TEMP
    ;

%%

void tac_error(const char* msg) {
    fprintf(stderr, "TAC Parser error at line %d: %s\n", tac_lineno, msg);
}
