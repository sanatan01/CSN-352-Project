%{
#include <helper.hpp>
#include <types.hpp>
#include <symtab.hpp>
#include <statement.hpp>
#include <expression.hpp>
#include <ast_entries.hpp>
#include <ast.hpp>
#include <3ac.hpp>

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
	Expression* expression;
	PrimaryExpression* primary_expression;
	ArguemmentExpressionList* argument_expression_list;
	UnaryExpression* unary_expression;
	CastExpression* cast_expression;
	PostfixExpression* postfix_expression;
	OpExpression* op_expression;
	Identifier* Identifier;
	Constant* constant;
	StringLiteral* string_literal;
}



%token<identifier> IDENTIFIER
%token<constant> CONSTANT
%token<string_literal> STRING_LITERAL
%token<nice> SIZEOF
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

%token<nice> ERROR

%start translation_unit

%type<nice> array_declaration
%type<nice> translation_unit
%type<nice> external_declaration
%type<nice> function_definition
%type<nice> declaration
%type<nice> declaration_list
%type<nice> statement
%type<nice> statement_list

%type<expression> expression
%type<expression> assignment_expression
%type<expression> conditional_expression
%type<expression> logical_or_expression
%type<expression> logical_and_expression
%type<expression> inclusive_or_expression
%type<expression> exclusive_or_expression
%type<expression> and_expression
%type<expression> equality_expression
%type<expression> relational_expression
%type<expression> shift_expression
%type<expression> additive_expression
%type<expression> multiplicative_expression
%type<expression> cast_expression
%type<expression> unary_expression
%type<expression> postfix_expression
%type<expression> primary_expression
%type<expression> expression_statement
%type<argument_expression_list> argument_expression_list

%type<nice> unary_operator
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
%type<nice> selection_statement
%type<nice> iteration_statement
%type<nice> jump_statement
%type<nice> error_statement_closed
%type<nice> error_statement_open

%%

/* Handling multiple errors */
error_statement_open
    : error
	| ERROR 
    | error_statement_open primary_expression 
	| error_statement_open type_specifier 
	| error_statement_open unary_operator 
	| error_statement_open storage_class_specifier
	| error_statement_open struct_or_union
	| error_statement_open type_qualifier	
	| error_statement_open declarator
	| error_statement_open direct_declarator
	| error_statement_open pointer
	| error_statement_open type_qualifier_list
    ;

error_statement_closed
    : error_statement_open SEMICOLON {
        fprintf(stderr, "Syntax error recovered at line %d\n", yylineno);
        yyerrok;
    }
	| error_statement_open RIGHT_BRACE {
		fprintf(stderr, "Syntax error recovered at line %d\n", yylineno);
		yyerrok;
	}
    ;

/* Primary expressions */
primary_expression
	: IDENTIFIER							{ $$ = create_primary_expression(&(ExpressionType){ .id = $1 }); }
	| CONSTANT 								{ $$ = create_primary_expression(&(ExpressionType){ .constant = $1 }); }
	| STRING_LITERAL 						{ $$ = create_primary_expression(&(ExpressionType){ .string_literal = $1 }); }
	| LEFT_PAREN expression RIGHT_PAREN 	{ $$ = $2 }
	;

/* Postfix expressions */
postfix_expression
	: primary_expression 											{ $$ = $1; }
	| postfix_expression LEFT_BRACKET expression RIGHT_BRACKET 		{ $$ = create_postfix_expr_arr($1, $3); }
	| IDENTIFIER LEFT_PAREN RIGHT_PAREN 							{ $$ = create_postfix_expr_voidfun($1); }
	| IDENTIFIER LEFT_PAREN argument_expression_list RIGHT_PAREN 	{ $$ = create_postfix_expr_fun ($1, $3); }
	| postfix_expression DOT IDENTIFIER 							{ $$ = create_postfix_expr_struct(".", $1, $3); }
	| postfix_expression PTR_OP IDENTIFIER 							{ $$ = create_postfix_expr_struct("->", $1, $3); }
	| postfix_expression INC_OP 									{ $$ = create_postfix_expr_ido( $2, $1); } 
	| postfix_expression DEC_OP 									{ $$ = create_postfix_expr_ido( $2, $1); } 
	;

/* Argument expression list for function calls */
argument_expression_list
	: assignment_expression 								{ $$ = create_argument_expr_assignement($1); }
	| argument_expression_list COMMA assignment_expression 	{ $$ = create_argument_expr_list($1, $3); }
	;

/* Unary expressions */
unary_expression
	: postfix_expression 						{ $$ = $1; }
	| INC_OP unary_expression 					{ $$ = create_unary_expression($1, $2); }
	| DEC_OP unary_expression 					{ $$ = create_unary_expression($1, $2); }
	| unary_operator cast_expression 			{ $$ = create_unary_expression_cast($1, $2); }
	| SIZEOF unary_expression 					{ $$ = create_unary_expression($1, $2); }
	| SIZEOF LEFT_PAREN type_name RIGHT_PAREN 	{ $$ = create_unary_expression($1, $3); }
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
	: unary_expression 										{ $$ = $1; }
	| LEFT_PAREN type_name RIGHT_PAREN cast_expression 		{ $$ = create_cast_expression_typename($2, $4); }
	;

/* Arithmetic expressions */
multiplicative_expression
	: cast_expression 										{ $$ = $1; }
	| multiplicative_expression ASTERISK cast_expression 	{ $$ = create_expression(MULTIPLICATIVE, "*", $1, $3); }
	| multiplicative_expression SLASH cast_expression		{ $$ = create_expression(MULTIPLICATIVE, "/", $1, $3); }
	| multiplicative_expression PERCENT cast_expression		{ $$ = create_expression(MULTIPLICATIVE, "%", $1, $3); }
	;

additive_expression
	: multiplicative_expression 							{ $$ = $1; }
	| additive_expression PLUS multiplicative_expression 	{ $$ = create_expression(ADDITIVE, "+", $1, $3); }
	| additive_expression MINUS multiplicative_expression	{ $$ = create_expression(ADDITIVE, "-", $1, $3); }
	;

shift_expression
	: additive_expression									{ $$ = $1; }
	| shift_expression LEFT_OP additive_expression			{ $$ = create_expression(SHIFT, "<<", $1, $3); }
	| shift_expression RIGHT_OP additive_expression			{ $$ = create_expression(SHIFT, ">>", $1, $3); }
	;

/* Relational expressions */
relational_expression
	: shift_expression										{ $$ = $1; }
	| relational_expression LESS_THAN shift_expression		{ $$ = create_expression(RELATIONAL, "<", $1, $3); }
	| relational_expression GREATER_THAN shift_expression	{ $$ = create_expression(RELATIONAL, ">", $1, $3); }
	| relational_expression LE_OP shift_expression			{ $$ = create_expression(RELATIONAL, "<=", $1, $3); }
	| relational_expression GE_OP shift_expression			{ $$ = create_expression(RELATIONAL, ">=", $1, $3); }
	;

equality_expression
	: relational_expression									{ $$ = $1; }
	| equality_expression EQ_OP relational_expression		{ $$ = create_expression(EQUALITY, "==", $1, $3); }
	| equality_expression NE_OP relational_expression		{ $$ = create_expression(EQUALITY, "!=", $1, $3); }
	;

/* Bitwise expressions */
and_expression
	: equality_expression									{ $$ = $1; }
	| and_expression AMPERSAND equality_expression			{ $$ = create_expression(AND, "&", $1, $3); }
	;

exclusive_or_expression
	: and_expression 										{ $$ = $1; }
	| exclusive_or_expression CARET and_expression			{ $$ = create_expression(XOR, "^", $1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression								{ $$ = $1; }
	| inclusive_or_expression PIPE exclusive_or_expression	{ $$ = create_expression(OR, "|", $1, $3); }
	;

/* Logical expressions */
logical_and_expression
	: inclusive_or_expression								{ $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression	
	;

logical_or_expression
	: logical_and_expression								{ $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression	
	;

/* Conditional expression (ternary operator) */
conditional_expression
	: logical_or_expression									{ $$ = $1; }
	| logical_or_expression QUESTION expression COLON conditional_expression { $$ = create_expression(CONDITIONAL, "?:", $1, $3, $5); }
	;

/* Assignment */
assignment_expression
	: conditional_expression								{ $$ = $1; }
	| unary_expression assignment_operator assignment_expression { $$ = create_expression(ASSIGNMENT, $1, $2, $3); }
	;

assignment_operator
	: ASSIGN		{ $$ = $1; }
	| MUL_ASSIGN	{ $$ = $1; }
	| DIV_ASSIGN	{ $$ = $1; }
	| MOD_ASSIGN	{ $$ = $1; }
	| ADD_ASSIGN	{ $$ = $1; }
	| SUB_ASSIGN	{ $$ = $1; }
	| LEFT_ASSIGN	{ $$ = $1; }
	| RIGHT_ASSIGN	{ $$ = $1; }
	| AND_ASSIGN	{ $$ = $1; }
	| XOR_ASSIGN	{ $$ = $1; }
	| OR_ASSIGN		{ $$ = $1; }
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
		  insertSymbol($1, "variable", $$);
	  }
	| declaration_specifiers init_declarator_list SEMICOLON {
		  /* Use the variable name from init_declarator */
		  $$ = $1;
		  insertSymbol($2, "variable", $$);
	  }
	| declaration_specifiers IDENTIFIER array_declaration SEMICOLON {
		char *temp = malloc(strlen($1) + strlen($3) + 3);
		strcpy(temp, $1);
		strcat(temp, strdup(" "));
		strcat(temp, $3);
		$$ = temp;
		insertSymbol($2, "variable", $$);
	}
	;

array_declaration
	: LEFT_BRACKET constant_expression RIGHT_BRACKET { $$ = strdup("[]");}
	| array_declaration LEFT_BRACKET constant_expression RIGHT_BRACKET {
		char *temp = malloc(strlen("[]") + strlen($1) + 2);
		sprintf(temp, "[]%s", $1);
		$$ = temp;
	}
	| array_declaration LEFT_BRACKET RIGHT_BRACKET {
		char *temp = malloc(strlen("[]") + strlen($1) + 2);
		sprintf(temp, "[]%s", $1);
		$$ = temp;
	}
	;

declaration_specifiers
	: storage_class_specifier 
	| storage_class_specifier declaration_specifiers {
		char * temp = malloc(strlen($1) + strlen($2) + 3);
		strcpy(temp, $1);
		strcat(temp, strdup(" "));
		strcat(temp, $2);
		$$ = temp;
	}
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
	: VOID     { $$ = strdup("VOID"); }
	| CHAR     { $$ = strdup("CHAR");}
	| SHORT    { $$ = strdup("SHORT");}
	| INT      { $$ = strdup("INT");}
	| LONG     { $$ = strdup("LONG");}
	| FLOAT    { $$ = strdup("FLOAT");}
	| DOUBLE   { $$ = strdup("DOUBLE");}
	| SIGNED   { $$ = strdup("SIGNED");}
	| UNSIGNED { $$ = strdup("UNSIGNED");}
	| struct_or_union_specifier { $$ = $1; }
	| enum_specifier { $$ = $1; }
	| TYPE_NAME { $$ = strdup("TYPE_NAME");}
	| type_specifier pointer {
		char*temp = malloc(strlen($1) + 2 );
		sprintf(temp, "%s*", $1);
		$$ = temp;
	}
	;

/* Struct and union specifiers */
struct_or_union_specifier
	: struct_or_union IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = $2; }
	| struct_or_union LEFT_BRACE struct_declaration_list RIGHT_BRACE
	| struct_or_union IDENTIFIER { $$ = $2; }
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
	| error_statement_closed
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

declaration_statement
	: SEMICOLON
	| declaration
	;

iteration_statement
	: WHILE LEFT_PAREN expression RIGHT_PAREN statement
	| DO statement WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON
	| FOR LEFT_PAREN expression_statement expression_statement RIGHT_PAREN statement
	| FOR LEFT_PAREN declaration_statement expression_statement expression RIGHT_PAREN statement
	| FOR LEFT_PAREN expression_statement declaration_statement expression RIGHT_PAREN statement
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
	| translation_unit error_statement_closed
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
	fprintf(stderr, "Syntax Error: %s at line %d\n", s, yylineno);
}