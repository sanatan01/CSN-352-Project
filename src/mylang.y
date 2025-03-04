%{
#include "helper.h"
void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
// Global variable to hold the current type for declaration
char *currentType = NULL;
int grammarErrorCount = 0;
%}

%union {
    char *nice;
}


%token<nice> IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token<nice> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token<nice> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token<nice> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token<nice> XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token<nice> TYPEDEF EXTERN STATIC AUTO REGISTER
%token<nice> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token<nice> STRUCT UNION ENUM ELLIPSIS

%token<nice> SEMICOLON LEFT_BRACE RIGHT_BRACE COMMA COLON ASSIGN 
%token<nice> LEFT_PAREN RIGHT_PAREN LEFT_BRACKET RIGHT_BRACKET DOT AMPERSAND EXCLAMATION 
%token<nice> TILDE MINUS PLUS ASTERISK SLASH PERCENT LESS_THAN GREATER_THAN CARET PIPE QUESTION

%token<nice> INVALID_ID INVALID_CHAR INVALID_OCT UNTERM_STRING

%token<nice> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%start translation_unit


%type<nice> translation_unit
%type<nice> external_declaration
%type<nice> function_definition
%type<nice> declaration
%type<nice> declaration_list
%type<nice> statement
%type<nice> statement_list
%type<nice> expression
%type<nice> assignment_expression
%type<nice> conditional_expression
%type<nice> logical_or_expression
%type<nice> logical_and_expression
%type<nice> inclusive_or_expression
%type<nice> exclusive_or_expression
%type<nice> and_expression
%type<nice> equality_expression
%type<nice> relational_expression
%type<nice> shift_expression
%type<nice> additive_expression
%type<nice> multiplicative_expression
%type<nice> cast_expression
%type<nice> unary_expression
%type<nice> unary_operator
%type<nice> postfix_expression
%type<nice> argument_expression_list
%type<nice> declaration_specifiers
%type<nice> init_declarator_list
%type<nice> init_declarator
%type<nice> storage_class_specifier
%type<nice> type_specifier
%type<nice> struct_or_union_specifier
%type<nice> struct_or_union
%type<nice> struct_declaration_list
%type<nice> struct_declaration
%type<nice> specifier_qualifier_list
%type<nice> struct_declarator_list
%type<nice> struct_declarator
%type<nice> enum_specifier
%type<nice> enumerator_list
%type<nice> enumerator
%type<nice> type_qualifier
%type<nice> declarator
%type<nice> direct_declarator
%type<nice> pointer
%type<nice> type_qualifier_list
%type<nice> parameter_type_list
%type<nice> parameter_list
%type<nice> parameter_declaration
%type<nice> identifier_list
%type<nice> type_name
%type<nice> abstract_declarator
%type<nice> direct_abstract_declarator
%type<nice> initializer
%type<nice> initializer_list
%type<nice> labeled_statement
%type<nice> compound_statement
%type<nice> expression_statement
%type<nice> selection_statement
%type<nice> iteration_statement
%type<nice> jump_statement
%type<nice> primary_expression

%%

/* Primary expressions */
primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| LEFT_PAREN expression RIGHT_PAREN
    | INVALID_ID    { 
        yyerror("Invalid identifier used in expression"); 
        $$ = "error";
    }
    | INVALID_CHAR  { 
        yyerror("Invalid character in expression"); 
        $$ = "error";
    }
    | INVALID_OCT   { 
        yyerror("Invalid octal constant in expression"); 
        $$ = "error";
    }
    | UNTERM_STRING { 
        yyerror("Unterminated string literal"); 
        $$ = "error";
    }
	;

/* Postfix expressions */
postfix_expression
	: primary_expression
	| postfix_expression LEFT_BRACKET expression RIGHT_BRACKET
	| postfix_expression LEFT_PAREN RIGHT_PAREN
	| postfix_expression LEFT_PAREN argument_expression_list RIGHT_PAREN
	| postfix_expression DOT IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

/* Argument expression list for function calls */
argument_expression_list
	: assignment_expression
	| argument_expression_list COMMA assignment_expression
	;

/* Unary expressions */
unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF LEFT_PAREN type_name RIGHT_PAREN
	;

unary_operator
	: AMPERSAND     { $$ = "&"; }
	| ASTERISK      { $$ = "*"; }
	| PLUS          { $$ = "+"; }
	| MINUS         { $$ = "-"; }
	| TILDE         { $$ = "~"; }
	| EXCLAMATION   { $$ = "!"; }
	;

/* Type casting */
cast_expression
	: unary_expression
	| LEFT_PAREN type_name RIGHT_PAREN cast_expression
	;

/* Arithmetic expressions */
multiplicative_expression
	: cast_expression
	| multiplicative_expression ASTERISK cast_expression
	| multiplicative_expression SLASH cast_expression
	| multiplicative_expression PERCENT cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression PLUS multiplicative_expression
	| additive_expression MINUS multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

/* Relational expressions */
relational_expression
	: shift_expression
	| relational_expression LESS_THAN shift_expression
	| relational_expression GREATER_THAN shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

/* Bitwise expressions */
and_expression
	: equality_expression
	| and_expression AMPERSAND equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression CARET and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression PIPE exclusive_or_expression
	;

/* Logical expressions */
logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

/* Conditional expression (ternary operator) */
conditional_expression
	: logical_or_expression
	| logical_or_expression QUESTION expression COLON conditional_expression
	;

/* Assignment */
assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: ASSIGN
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

/* Expressions */
expression
	: assignment_expression
	| expression COMMA assignment_expression
	;

constant_expression
	: conditional_expression
	;

/* Declarations */
declaration
	: declaration_specifiers SEMICOLON {
		  insertSymbol($1, "variable", currentType);
	  }
	| declaration_specifiers init_declarator_list SEMICOLON {
		  /* Use the variable name from init_declarator */
		  insertSymbol($2, "variable", currentType);
	  }
	;

declaration_specifiers
	: storage_class_specifier 
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier 
	| type_qualifier declaration_specifiers 
	;

init_declarator_list
	: init_declarator
	| init_declarator_list COMMA init_declarator
	;

init_declarator
	: declarator
	| declarator ASSIGN initializer
	;

/* Storage classes */
storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

/* Type specifiers */
type_specifier
	: VOID     { $$ = strdup("VOID"); currentType = $$; }
	| CHAR     { $$ = strdup("CHAR"); currentType = $$; }
	| SHORT    { $$ = strdup("SHORT"); currentType = $$; }
	| INT      { $$ = strdup("INT"); currentType = $$; }
	| LONG     { $$ = strdup("LONG"); currentType = $$; }
	| FLOAT    { $$ = strdup("FLOAT"); currentType = $$; }
	| DOUBLE   { $$ = strdup("DOUBLE"); currentType = $$; }
	| SIGNED   { $$ = strdup("SIGNED"); currentType = $$; }
	| UNSIGNED { $$ = strdup("UNSIGNED"); currentType = $$; }
	| struct_or_union_specifier { $$ = $1; }
	| enum_specifier { $$ = $1; }
	| TYPE_NAME { $$ = strdup("TYPE_NAME"); currentType = $$; }
	;

/* Struct and union specifiers */
struct_or_union_specifier
	: struct_or_union IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE 
	| struct_or_union LEFT_BRACE struct_declaration_list RIGHT_BRACE
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list COMMA struct_declarator
	;

struct_declarator
	: declarator
	| COLON constant_expression
	| declarator COLON constant_expression
	;

/* Enum specifiers */
enum_specifier
	: ENUM LEFT_BRACE enumerator_list RIGHT_BRACE 
	| ENUM IDENTIFIER LEFT_BRACE enumerator_list RIGHT_BRACE
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list COMMA enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER ASSIGN constant_expression
	;

/* Type qualifiers */
type_qualifier
	: CONST    { $$ = strdup("CONST"); }
	| VOLATILE { $$ = strdup("VOLATILE"); }
	;

/* Declarators */
declarator
	: pointer direct_declarator { $$ = $2; }
	| direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER { $$ = $1; }
	| LEFT_PAREN declarator RIGHT_PAREN { $$ = $2; }
	| direct_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET { $$ = $1; }
	| direct_declarator LEFT_BRACKET RIGHT_BRACKET { $$ = $1; }
	| direct_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN { $$ = $1; }
	| direct_declarator LEFT_PAREN identifier_list RIGHT_PAREN { $$ = $1; }
	| direct_declarator LEFT_PAREN RIGHT_PAREN { $$ = $1; }
	;

pointer
	: ASTERISK { $$ = NULL; }
	| ASTERISK type_qualifier_list { $$ = NULL; }
	| ASTERISK pointer { $$ = NULL; }
	| ASTERISK type_qualifier_list pointer { $$ = NULL; }
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

/* Function parameters */
parameter_type_list
	: parameter_list
	| parameter_list COMMA ELLIPSIS
	;

parameter_list
	: parameter_declaration
	| parameter_list COMMA parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list COMMA IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: LEFT_PAREN abstract_declarator RIGHT_PAREN
	| LEFT_BRACKET RIGHT_BRACKET
	| LEFT_BRACKET constant_expression RIGHT_BRACKET
	| direct_abstract_declarator LEFT_BRACKET RIGHT_BRACKET
	| direct_abstract_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET
	| LEFT_PAREN RIGHT_PAREN
	| LEFT_PAREN parameter_type_list RIGHT_PAREN
	| direct_abstract_declarator LEFT_PAREN RIGHT_PAREN
	| direct_abstract_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN
	;

/* Initializers */
initializer
	: assignment_expression
	| LEFT_BRACE initializer_list RIGHT_BRACE
	| LEFT_BRACE initializer_list COMMA RIGHT_BRACE
	;

initializer_list
	: initializer
	| initializer_list COMMA initializer
	;

/* Statements */
statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER COLON statement
	| CASE constant_expression COLON statement
	| DEFAULT COLON statement
	;

compound_statement
	: LEFT_BRACE RIGHT_BRACE
	| LEFT_BRACE statement_list RIGHT_BRACE
	| LEFT_BRACE declaration_list RIGHT_BRACE
	| LEFT_BRACE declaration_list statement_list RIGHT_BRACE
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: SEMICOLON
	| expression SEMICOLON
	;

/* Control flow */
selection_statement
	: IF LEFT_PAREN expression RIGHT_PAREN statement
	| IF LEFT_PAREN expression RIGHT_PAREN statement ELSE statement
	| SWITCH LEFT_PAREN expression RIGHT_PAREN statement
	;

iteration_statement
	: WHILE LEFT_PAREN expression RIGHT_PAREN statement
	| DO statement WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON
	| FOR LEFT_PAREN expression_statement expression_statement RIGHT_PAREN statement
	| FOR LEFT_PAREN expression_statement expression_statement expression RIGHT_PAREN statement
	;

jump_statement
	: GOTO IDENTIFIER SEMICOLON
	| CONTINUE SEMICOLON
	| BREAK SEMICOLON
	| RETURN SEMICOLON
	| RETURN expression SEMICOLON
	;

/* Top-level constructs */
translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement {
		  insertSymbol($2, "function", $1); /* Insert function with its return type */
	  }
	| declaration_specifiers declarator compound_statement {
		  insertSymbol($2, "function", $1);
	  }
	| declarator declaration_list compound_statement {
		  insertSymbol($1, "function", "auto"); /* Default to auto when return type isn't specified */
	  }
	| declarator compound_statement {
		  insertSymbol($1, "function", "auto");
	  }
	;

%%

void yyerror(const char *s) {
    fprintf(stderr, "\033[1;31mSyntax Error\033[0m at line %d: %s\n", yylineno, s);
    grammarErrorCount++;
}