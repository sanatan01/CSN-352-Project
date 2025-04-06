%{
#include <helper.h>
#include <types.h>
#include <symtab.h>
#include <statement.h>
#include <expression.h>
#include <ast.h>
#include <3ac.h>

void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;
// Global variable to hold the current type for declaration
char *currentType = NULL;
int grammarErrorCount = 0;
%}


%union {
	Terminal* terminal;
    char *nice;
	Expression* expression;
	PrimaryExpression* primary_expression;
	ArguemmentExpressionList* argument_expression_list;
	UnaryExpression* unary_expression;
	CastExpression* cast_expression;
	PostfixExpression* postfix_expression;
	OpExpression* op_expression;
	Identifier* identifier;
	Constant* constant;
	StringLiteral* string_literal;
	GlobalType* global_type;
	PointerType* pointer_type;
	StructType* struct_type;
	UnionType* union_type;
	EnumType* enum_type;
	Specifiers* specifiers;
	EnumElement* enum_element;
	std::vector<EnumElement>* vector_enum_element;
	std::vector<StructElement>* struct_element_list;
	std::vector<Identifier>* vector_identifiers;
	StructElement* struct_element;
	FunctionType* function_type;
	ArrayType* array_type;
}



%token<nice> IDENTIFIER
%token<constant> CONSTANT
%token<string_literal> STRING_LITERAL
%token<nice> SIZEOF
%token<nice> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token<nice> AND_OP OR_OP
%token<nice> TYPE_NAME
%token<nice> ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN

%token<nice> TYPEDEF EXTERN STATIC AUTO REGISTER
%token<nice> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token<nice> STRUCT UNION ENUM ELLIPSIS

%token<nice> SEMICOLON LEFT_BRACE RIGHT_BRACE COMMA COLON 
%token<nice> LEFT_PAREN RIGHT_PAREN LEFT_BRACKET RIGHT_BRACKET DOT AMPERSAND EXCLAMATION 
%token<nice> TILDE MINUS PLUS ASTERISK SLASH PERCENT LESS_THAN GREATER_THAN CARET PIPE QUESTION

%token<nice> INVALID_ID INVALID_CHAR INVALID_OCT UNTERM_STRING

%token<nice> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token<nice> ERROR

%start translation_unit

/* %type<array_type> array_declaration */
%type<nice> translation_unit
%type<nice> external_declaration
%type<identifier> function_identifier
%type<identifier> function_definition
%type<identifier> function_declaration
%type<vector_identifiers> declaration
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
%type<expression> constant_expression

%type<nice> assignment_operator
%type<nice> unary_operator
%type<global_type> declaration_specifiers
%type<vector_identifiers> init_declarator_list
%type<identifier> init_declarator
%type<specifiers> storage_class_specifier
%type<global_type> type_specifier
%type<union_type> union_specifier
%type<struct_type> struct_specifier
%type<struct_element_list> struct_declaration_list
%type<struct_element_list> struct_declaration
%type<global_type> specifier_qualifier_list
%type<struct_element_list> struct_declarator_list
%type<struct_element> struct_declarator
%type<enum_type> enum_specifier
%type<vector_enum_element> enumerator_list
%type<enum_element> enumerator
%type<specifiers> type_qualifier
%type<identifier> declarator
%type<identifier> direct_declarator
%type<pointer_type> pointer
%type<specifiers> type_qualifier_list
%type<vector_identifiers> parameter_type_list
%type<vector_identifiers> parameter_list
%type<identifier> parameter_declaration
%type<vector_identifiers> identifier_list
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
	| error_statement_open STRUCT
	| error_statement_open UNION
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
	| unary_expression assignment_operator assignment_expression { $$ = create_expression(ASSIGNMENT, std::string($1), $2, $3); }
	;

assignment_operator
	: ASSIGN		{ $$ = strdup("="); }
	| MUL_ASSIGN	{ $$ = strdup("*="); }
	| DIV_ASSIGN	{ $$ = strdup("/="); }
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
	: assignment_expression { $$ = $1; }
	| expression COMMA assignment_expression { $$ = create_expression(TOPLEVEL, ' ', $1, $3); }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

/* Declarations */
declaration
	: declaration_specifiers SEMICOLON {
		  $$ = new std::vector<Identifier>();
		  $$->push_back(new Identifier());
		  $$->back()->type = $1;
		  for(auto &element : *$$) {
			  SymbolTable::add_symbol(element);
		  }
	  }
	| declaration_specifiers init_declarator_list SEMICOLON {
		  /* Use the variable name from init_declarator */
		  $$ = $2;
		  for(auto &element : *$$) {
			  element->type = $1;
			  SymbolTable::add_symbol(element);
		  }
	  }
	/* | declaration_specifiers IDENTIFIER array_declaration SEMICOLON {
		$$ = new std::vector<Identifier>();
		$$->push_back(new Identifier(std::string($2)));
		$$->back()->type->array_type = $3;
		$$->back()->type->array_type->return_type = $1;
	} */
	;

/* array_declaration
	: LEFT_BRACKET constant_expression RIGHT_BRACKET {
		$$ = new ArrayType();
		$$->dim=1;
		// to be seen
		// $$->dims.push_back($2);
	}
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
	; */

declaration_specifiers
	: storage_class_specifier declaration_specifiers {
		char * temp = malloc(strlen($1) + strlen($2) + 3);
		strcpy(temp, $1);
		strcat(temp, strdup(" "));
		strcat(temp, $2);
		$$ = temp;
	}
	| type_specifier { $$ = $1; }
	| type_specifier declaration_specifiers { 
		$$ = combine_types($1, $2);

	}
	// TODO: implement later| type_qualifier 
	| type_qualifier declaration_specifiers {
		$$ = $2;
		$$ = combine_specifiers($1, $2);
	}
		// TODO: implement later: storage_class_specifier { $$ = new GlobalType(); }
	;

init_declarator_list
	: init_declarator{
		$$ = new std::vector<Identifier>();
		$$->push_back($1);
	}
	| init_declarator_list COMMA init_declarator{
		$$ = $1;
		$$->push_back($3);
	}
	;

init_declarator
	: declarator{
		$$ = $1;
	}
	| declarator ASSIGN initializer{
		// TODO: type checking
		$$ = $1;
	}
	;

/* Storage classes */
storage_class_specifier
	: TYPEDEF { $$ = new Specifier(); $$->is_typedef = true; }
	| EXTERN { $$ = new Specifier(); $$->is_extern = true; }
	| STATIC { $$ = new Specifier(); $$->is_static = true; }
	| REGISTER { $$ = new Specifier(); $$->is_register = true; }
	;

/* Type specifiers */
type_specifier
	: VOID     { $$ = new GlobalType(); $$->standard_type = type_specifiers[VOID_T]; }
	| CHAR     { $$ = new GlobalType(); $$->standard_type = type_specifiers[CHAR_T]; }
	| SHORT    { $$ = new GlobalType(); $$->standard_type = type_specifiers[SHORT_T]; }
	| INT      { $$ = new GlobalType(); $$->standard_type = type_specifiers[INT_T]; }
	| LONG     { $$ = new GlobalType(); $$->standard_type = type_specifiers[LONG_T]; }
	| FLOAT    { $$ = new GlobalType(); $$->standard_type = type_specifiers[FLOAT_T]; }
	| DOUBLE   { $$ = new GlobalType(); $$->standard_type = type_specifiers[DOUBLE_T]; }
	/* | SIGNED   { $$ = new GlobalType(); $$->standard_type = type_specifiers[SIGNED_T]; } */
	/* | UNSIGNED { $$ = new GlobalType(); $$->standard_type = type_specifiers[UNSIGNED_T]; } */
	| struct_specifier { $$ = new GlobalType(); $$->struct_type = $1; }
	| union_specifier { $$ = new GlobalType(); $$->union_type = $1; }
	| enum_specifier { $$ = new GlobalType(); $$->enum_type = $1; }
	/* | TYPE_NAME { $$ = new GlobalType(); $$->type_name = $1; } */
	| type_specifier pointer {
		$$ = new GlobalType();
		$$->pointer_type = $2;
		$$->pointer_type->type = $1;
	}
	;

/* Struct and union specifiers */
struct_specifier
	: STRUCT IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new Struct(std::string($2), *$4); }
	| STRUCT LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new Struct(*$3); }
	| STRUCT IDENTIFIER { $$ = new Struct(std::string($2)); }
	;

union_specifier
	: UNION IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new Union(std::string($2), *$4); }
	| UNION LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new Union(*$3); }
	| UNION IDENTIFIER { $$ = new Union(std::string($2)); }
	;

struct_declaration_list
	: struct_declaration { $$ = $1; }
	| struct_declaration_list struct_declaration {
		$$ = $1;
		for (auto &element : *$2) {
			$$->push_back(element);
		}
	}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON {
		$$ = new std::vector<StructElement>();
		for (auto &declarator : *$2) {
			StructElement *element = new StructElement(declarator->id, declarator->size);
			element->id->type = $1;  // Set the globalType of each element to specifier_qualifier_list
			$$->push_back(*element);
		}
	}
	;

struct_declarator_list
	: struct_declarator {
		$$ = new std::vector<StructElement>();
		$$->push_back($1);
	}
	| struct_declarator_list COMMA struct_declarator {
		$$ = $1;
		$$->push_back($3);
	}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list {
		$$ = $2;

	}
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator
	: declarator {
		$$ = new StructElement($1, $1->type.getSize()); // TODO: Fix this as declarator should not return Identifier
	}
	| COLON constant_expression {
		$$ = new StructElement($1, 0 /* Get return value from constant expression*/);
	}
	| declarator COLON constant_expression {
		$$ = new StructElement($1, 0 /* Get return value from constant expression*/);
	}
	;

/* Enum specifiers */
enum_specifier
	: ENUM LEFT_BRACE enumerator_list RIGHT_BRACE {
		$$ = new EnumType($3);
	}
	| ENUM IDENTIFIER LEFT_BRACE enumerator_list RIGHT_BRACE{
		$$ = new EnumType(std::string($2),$4);
	}
	| ENUM IDENTIFIER{
		$$ = new EnumType(std::string($2));
	}
	;

enumerator_list
	: enumerator { 
		$$ = new std::vector<EnumElement>();
		$$->push_back($1); 
	}
	| enumerator_list COMMA enumerator{
		$$ = $1;
		$$->push_back($3);
	}
	;

enumerator
	: IDENTIFIER{
		$$ = new EnumElement(std::string($1));
	}
	| IDENTIFIER ASSIGN constant_expression{
		$$ = new EnumElement(std::string($1), /* to do $3*/);
	}
	;

/* Type qualifiers */
type_qualifier
	: CONST    { $$ = new Specifiers(); $$->is_const = true; }
	| VOLATILE { $$ = new Specifiers(); $$->is_volatile = true; }
	;

/* Declarators */
declarator
	: pointer direct_declarator { 
		$$ = $2;
		if ($$->type->pointer_type == NULL) {
			$$->type->pointer_type = $1;
			$$->type->pointer_type->return_type = $2->type;
		}
		else {
			$$->type->pointer_type->ptr_level+= $1->ptr_level;
		}

	}
	| direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER { $$ = new Identifier(std::string($1)); }
	| LEFT_PAREN declarator RIGHT_PAREN { $$ = $2; }
	| direct_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET {
		$$ = $1;
		if ($$->type->array_type == NULL) {
			$$->type->array_type = new ArrayType();
			$$->type->array_type->return_type = $1->type;
		}
		$$->type->array_type->dim++;
		$$->type->array_type->dims.push_back($3);

	}
	| direct_declarator LEFT_BRACKET RIGHT_BRACKET { 
		$$ = $1;
		if ($$->type->array_type == NULL) {
			$$->type->array_type = new ArrayType();
			$$->type->array_type->return_type = $1->type;
		}
		$$->type->array_type->dim++;
		$$->type->array_type->dims.push_back(0);
	}
	| direct_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN { 
		$$ = $1;
		if($$->type == NULL) {
			$$->type = new GlobalType();
			$$->type->function_type = new FunctionType($1, &($3));
		}
		else{
			GlobalType *temp = $$->type;
			temp->pointer_type->return_type = $1;
			$$->type = new GlobalType();
			$$->type->function_type = new FunctionType(temp,&($3));
		}

	} // Function defnition?
	// TODO : | direct_declarator LEFT_PAREN identifier_list RIGHT_PAREN { $$ = $1; } // Fimctopm ca;;
	// TODO: | direct_declarator LEFT_PAREN RIGHT_PAREN { $$ = $1; } // Function call
	;

pointer
	: ASTERISK { $$ = *new PointerType(); }
	| ASTERISK type_qualifier_list { 
		$$ = *new PointerType();
		$$->specifiers = $2;
	 }
	| ASTERISK pointer { 
		$$ = $2;
		$$->ptr_level++;
	 }
	| ASTERISK type_qualifier_list pointer { 
		$$ = $3;
		$$->ptr_level++;
		$$->specifiers->combine($2);
	 }
	;

type_qualifier_list
	: type_qualifier { 
		$$ = $1
	}
	| type_qualifier_list type_qualifier{
		$$ = $1;
		$$->combine($2);
	}
	;

/* Function parameters */
parameter_type_list
	: parameter_list{
		$$ = $1;
	}
	| parameter_list COMMA ELLIPSIS{
		//TODO: fix later
		$$=$1;
	}
	;

parameter_list
	: parameter_declaration { $$ = new std::vector<Identifier>(); $$->push_back($1); }
	| parameter_list COMMA parameter_declaration { $$ = $1; $$->push_back($3); }
	;

parameter_declaration
	: declaration_specifiers declarator {
		// Todo: fix later
		$$ = $2;
		$$->type = combine_types($1, $2->type);
	}
	// Todo: | declaration_specifiers abstract_declarator
	// todo: later| declaration_specifiers
	;

identifier_list
	: IDENTIFIER { $$ = new std::vector<Identifier>(); $$->push_back(new Identifier($1)); }
	| identifier_list COMMA IDENTIFIER { 
		$$ = $1;
		$$->push_back(new Identifier($3));
	}
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
	: increment_scope LEFT_BRACE RIGHT_BRACE { SymbolTable::exit_scope(); }
	| increment_scope LEFT_BRACE statement_list RIGHT_BRACE { SymbolTable::exit_scope(); }
	| increment_scope LEFT_BRACE declaration_list RIGHT_BRACE { SymbolTable::exit_scope(); }
	| increment_scope LEFT_BRACE declaration_list statement_list RIGHT_BRACE { SymbolTable::exit_scope(); }
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
	| function_declaration
	| declaration
	;

function_identifier
	: IDENTIFIER { $$ = new Identifier($1); }
	| pointer function_identifier{ 
		$$ = $2; 
		if($$->type == NULL) {
			$$->type = new GlobalType();
			$$->type->pointer_type = new PointerType();
		}
		else{
			$$->type->pointer_type->ptr_level++;
		}
	}
	;

function_declaration
	: declaration_specifiers function_identifier LEFT_PAREN parameter_list RIGHT_PAREN{
		$$ = $2;
		if($$->type == NULL) {
			$$->type = new GlobalType();
			$$->type->function_type = new FunctionType($1, &($3));
		}
		else{
			GlobalType *temp = $$->type;
			temp->pointer_type->return_type = $1;
			$$->type = new GlobalType();
			$$->type->function_type = new FunctionType(temp, &($3));
		}
	}
	| declaration_specifiers function_identifier LEFT_PAREN RIGHT_PAREN {

		$$ = $2;
		if($$->type == NULL) {
			$$->type = new GlobalType();
			$$->type->function_type = new FunctionType($1,std::vector<Identifier>());
		}
		else{
			GlobalType *temp = $$->type;
			temp->pointer_type->return_type = $1;
			$$->type = new GlobalType();
			$$->type->function_type = new FunctionType(temp,std::vector<Identifier>());
		}
	}
	;

function_definition
	 :  increment_scope function_declaration compound_statement	 { 
		SymbolTable::exit_scope();
		SymbolTable::add_symbol($$);
		}/*{ 
		$$ = $2;
		for (auto &element : $$->type->function_type->args) {
			SymbolTable::add_symbol(element);
		} */
	 
	;

	//: declaration_specifiers declarator declaration_list compound_statement {
	//	  insertSymbol($2, "function", $1); /* Insert function with its return type */
	//  }
	// | declaration_specifiers declarator compound_statement {
	//	  insertSymbol($2, "function", $1);
	//  }
	//| declarator declaration_list compound_statement {
	//	  insertSymbol($1, "function", "auto"); /* Default to auto when return type isn't specified */
	//  }
	//| declarator compound_statement {
	//	  insertSymbol($1, "function", "auto");
	//} 
	/* ; */

increment_scope: %empty { SymbolTable::enter_scope(); }

%%

void yyerror(const char *s) {
	fprintf(stderr, "Syntax %s at line %d\n", s, yylineno);
}