%{
#include <helper.h>
#include <types.h>
#include <symtab.h>
#include <expression.h>
#include <tac.h>

// #include <statementh>
// #include <ast.h>
// #include <3ach>

void yyerror(const char *s);
 extern int yylex();
 extern int yylineno;
 extern FILE *yyin;
 int test_count = 0;
// // Global variable to hold the current type for declaration
// char *currentType = NULL;
// int grammarErrorCount = 0;
 %}

 %define parse.error verbose

 %union {
// 	Terminal* terminal;
    char *nice;
 	class Expression* expression;
// 	PrimaryExpression* primary_expression;
	class VectorExpression* argument_expression_list;
// 	UnaryExpression* unary_expression;
// 	CastExpression* cast_expression;
// 	PostfixExpression* postfix_expression;
// 	OpExpression* op_expression;
 	class Identifier* identifier;
// 	Constant* constant;
// 	StringLiteral* string_literal;
 	class GlobalType* global_type;
 	class PointerType* pointer_type;
 	class Struct* struct_type;
 	class Union* union_type;
 	class EnumType* enum_type;
 	class Specifiers* specifiers;
 	class EnumElement* enum_element;
 	class VectorEnumElement *vector_enum_element;
 	class VectorStructElement* struct_element_list;
 	class VectorIdentifiers* vector_identifiers;
 	class StructElement* struct_element;
 	class VectorExpression* vector_expression;
// 	FunctionType* function_type;
// 	ArrayType* array_type;
 }



 %token<nice> IDENTIFIER
 %token<nice> CONSTANT_LITERAL
 %token<nice> STRING_LITERAL
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

// /* %type<array_type> array_declaration */
 %type<nice> translation_unit
 %type<nice> external_declaration
 //%type<identifier> function_identifier
 %type<identifier> function_definition
 %type<identifier> function_declaration
 %type<vector_identifiers> declaration
 %type<vector_identifiers> declaration_list
 %type<nice> statement
 %type<nice> statement_list
 %type<nice> all_statements

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
%type<vector_expression> argument_expression_list
// %type<expression> constant_expression

%type<nice> empty_expression
%type<nice> init_clause

%type<nice> assignment_operator
%type<nice> unary_operator
%type<global_type> declaration_specifiers
%type<vector_identifiers> init_declarator_list
%type<identifier> init_declarator
%type<specifiers> storage_class_specifier
%type<specifiers> storage_class_specifier_list
%type<specifiers> qualifiers
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
%type<global_type> type_name
%type<global_type> abstract_declarator
%type<global_type> direct_abstract_declarator
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

// /* Handling multiple errors */
// error_statement_open
//     : error
// 	| ERROR 
//     | error_statement_open primary_expression 
// 	| error_statement_open type_specifier 
// 	| error_statement_open unary_operator 
// 	| error_statement_open storage_class_specifier
// 	| error_statement_open STRUCT
// 	| error_statement_open UNION
// 	| error_statement_open type_qualifier	
// 	| error_statement_open declarator
// 	| error_statement_open direct_declarator
// 	| error_statement_open pointer
// 	| error_statement_open type_qualifier_list
//     ;

// error_statement_closed
//     : error_statement_open SEMICOLON {
//         fprintf(stderr, "Syntax error recovered at line %d\n", yylineno);
//         yyerrok;
//     }
// 	| error_statement_open RIGHT_BRACE {
// 		fprintf(stderr, "Syntax error recovered at line %d\n", yylineno);
// 		yyerrok;
// 	}
//     ;

// /* Primary expressions */
primary_expression
 	: IDENTIFIER							{ $$ = create_expression_simple(IDENTIFIER_ET, std::string($1)); }
 	| CONSTANT_LITERAL 						{ $$ = create_expression_simple(CONSTANT_ET, std::string($1)); }
// 	| STRING_LITERAL 						{ $$ = create_primary_expression(&(ExpressionType){ .string_literal = $1 }); }
	| LEFT_PAREN expression RIGHT_PAREN 	{ $$ = $2; }
 	;

// /* Postfix expressions */
postfix_expression
 	: primary_expression 											{ $$ = $1; }
    | postfix_expression INC_OP 									{ $$ = create_postfix_expr_ido( "++", $1); } 
 	| postfix_expression DEC_OP 									{ $$ = create_postfix_expr_ido( "--", $1); } 
 	| postfix_expression LEFT_BRACKET expression RIGHT_BRACKET 		{ $$ = create_postfix_expr_arr($1, $3); }
    | IDENTIFIER LEFT_PAREN argument_expression_list RIGHT_PAREN 	{
		$$ = create_postfix_expr_fun (new Identifier($1), $3); 
	}
 	// | IDENTIFIER LEFT_PAREN RIGHT_PAREN 							{ $$ = create_postfix_expr_voidfun($1); }
 	// | postfix_expression DOT IDENTIFIER 							{ $$ = create_postfix_expr_struct(".", $1, $3); }
 	// | postfix_expression PTR_OP IDENTIFIER 							{ $$ = create_postfix_expr_struct("->", $1, $3); }
 	;

// /* Argument expression list for function calls */
 argument_expression_list
 	: assignment_expression 								{ 
		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
		$$ = ve; 
	}
 	| argument_expression_list COMMA assignment_expression 	{ 
		$$=$1;
		$$->add_element($3); 
	}
 	;

// /* Unary expressions */
unary_expression
 	: postfix_expression 						{ $$ = $1; }
 	| INC_OP unary_expression 					{ 
		VectorExpression* ve = new VectorExpression();
 		ve->add_element($2);
 		$$ = create_expression(UNARY, "++", ve); 
	}
 	| DEC_OP unary_expression 					{ 
		VectorExpression* ve = new VectorExpression();
 		ve->add_element($2);
 		$$ = create_expression(UNARY, "--", ve); 
	}
	| SIZEOF unary_expression 					{ 
		VectorExpression* ve = new VectorExpression();
 		ve->add_element($2);
 		$$ = create_expression(UNARY, "sizeof", ve); 
	}
 	| SIZEOF LEFT_PAREN type_name RIGHT_PAREN 	{ 
		class Expression* expr = new Expression($3);
		VectorExpression* ve = new VectorExpression();
 		ve->add_element(expr);
 		$$ = create_expression(UNARY, "sizeof", ve); 
	}
 	| unary_operator cast_expression 			{ 
		VectorExpression* ve = new VectorExpression();
 		ve->add_element($2);
 		$$ = create_expression(UNARY, std::string($1), ve); 
	}
 	;

unary_operator
	: AMPERSAND     { $$ = strdup("&"); }
	| ASTERISK      { $$ = strdup("*"); }
	| PLUS          { $$ = strdup("+"); }
	| MINUS         { $$ = strdup("-"); }
	| TILDE         { $$ = strdup("~"); }
	| EXCLAMATION   { $$ = strdup("!"); }
	;

// /* Type casting */
cast_expression
 	: unary_expression 										{ $$ = $1; }
 	| LEFT_PAREN type_name RIGHT_PAREN cast_expression 		{ 
		class Expression* expr = new Expression($2);
		VectorExpression* ve = new VectorExpression();
 		ve->add_element(expr);
		ve->add_element($4);
		$$ = create_expression(CAST_TYPE, "", ve); 
	}
 	;

// /* Arithmetic expressions */
multiplicative_expression
 	: cast_expression 										{ $$ = $1; }
 	| multiplicative_expression ASTERISK cast_expression 	{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(MULTIPLICATIVE, "*", ve); 
 	}
 	| multiplicative_expression SLASH cast_expression		{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(MULTIPLICATIVE, "/", ve); 
 	}
 	| multiplicative_expression PERCENT cast_expression		{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(MULTIPLICATIVE, "%", ve); 
 	}
 	;

additive_expression
 	: multiplicative_expression 							{ $$ = $1; }
 	| additive_expression PLUS multiplicative_expression 	{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(ADDITIVE, "+", ve); 
 	}
 	| additive_expression MINUS multiplicative_expression	{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3); 
		$$ = create_expression(ADDITIVE, "-", ve); 
 	}
 	;
shift_expression
 	: additive_expression									{ $$ = $1; }
 	| shift_expression LEFT_OP additive_expression			{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(SHIFT, "<<", ve); 
 	}
 	| shift_expression RIGHT_OP additive_expression			{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3); 
		$$ = create_expression(SHIFT, ">>", ve); 
 	}
	;
// /* Relational expressions */
relational_expression
 	: shift_expression										{ $$ = $1; }
 	| relational_expression LESS_THAN shift_expression		{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(RELATIONAL, "<", ve); 
 	}
 	| relational_expression GREATER_THAN shift_expression	{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(RELATIONAL, ">", ve); 
 	}
 	| relational_expression LE_OP shift_expression			{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(RELATIONAL, "<=", ve); 
 	}
 	| relational_expression GE_OP shift_expression			{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(RELATIONAL, ">=", ve); 
 	}
 	;
equality_expression
 	: relational_expression									{ $$ = $1; }
 	| equality_expression EQ_OP relational_expression		{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(EQUALITY, "==", ve); 
 	}
 	| equality_expression NE_OP relational_expression		{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(EQUALITY, "!=", ve); 
 	}
 	;

// /* Bitwise expressions */
and_expression
 	: equality_expression									{ $$ = $1; }
 	| and_expression AMPERSAND equality_expression			{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(AND, "&", ve); 
 	}
 	;

exclusive_or_expression
 	: and_expression 										{ $$ = $1; }
 	| exclusive_or_expression CARET and_expression			{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(XOR, "^", ve); 
 	}
 	;

inclusive_or_expression
 	: exclusive_or_expression								{ $$ = $1; }
 	| inclusive_or_expression PIPE exclusive_or_expression	{ 
 		VectorExpression* ve = new VectorExpression();
 		ve->add_element($1);
 		ve->add_element($3);
 		$$ = create_expression(OR, "|", ve); 
 	}
 	;

// /* Logical expressions */
logical_and_expression
 	: inclusive_or_expression								{ $$ = $1; }
 	| logical_and_expression AND_OP inclusive_or_expression	{
		VectorExpression* ve = new VectorExpression();
		ve->add_element($1);
		ve->add_element($3);
		$$ = create_expression(LOGICAL_AND, "&&", ve);
	}
 	;

 logical_or_expression
 	: logical_and_expression								{ $$ = $1; }
 	| logical_or_expression OR_OP logical_and_expression	{ 
		VectorExpression* ve = new VectorExpression();
		ve->add_element($1);
		ve->add_element($3);
		$$ = create_expression(LOGICAL_OR, "||",ve);
	}
 	;

// /* Conditional expression (ternary operator) */
conditional_expression
 	: logical_or_expression									{ $$ = $1; }
	| logical_or_expression QUESTION expression COLON conditional_expression { 
		VectorExpression* ve = new VectorExpression();
		ve->add_element($1);
		ve->add_element($3);
		ve->add_element($5);
		$$ = create_expression(CONDITIONAL, "?:", ve); 
	}
 	;

// /* Assignment */
assignment_expression
 	: conditional_expression								{ $$ = $1; }
 	| unary_expression assignment_operator assignment_expression { 
		VectorExpression *ve = new VectorExpression();
		ve->add_element($1);
		ve->add_element($3);
		$$ = create_expression(ASSIGNMENT, std::string($2), ve); 
		}
 	;

 assignment_operator
 	: ASSIGN		{ $$ = strdup("="); }
 	| MUL_ASSIGN	{ $$ = strdup("*="); }
 	| DIV_ASSIGN	{ $$ = strdup("/="); }
 	| MOD_ASSIGN	{ $$ = strdup("%="); }
 	| ADD_ASSIGN	{ $$ = strdup("+="); }
 	| SUB_ASSIGN	{ $$ = strdup("-="); }
 	| LEFT_ASSIGN	{ $$ = strdup("<<="); }
 	| RIGHT_ASSIGN	{ $$ = strdup(">>"); }
 	| AND_ASSIGN	{ $$ = strdup("&="); }
 	| XOR_ASSIGN	{ $$ = strdup("^="); }
 	| OR_ASSIGN		{ $$ = strdup("|"); }
 	;

// /* Expressions */
expression
 	: assignment_expression { $$ = $1; }
 	// | expression COMMA assignment_expression { 
 	// 	VectorExpression* ve = new VectorExpression();
 	// 	ve->add_element($1);
 	// 	ve->add_element($3);
 	// 	$$ = create_expression(TOPLEVEL, "", ve); 
 	// }
 	;

// constant_expression
// 	: conditional_expression { $$ = $1; }
// 	;

// /* Declarations */
declaration
 	: declaration_specifiers SEMICOLON {
 		  $$ = new VectorIdentifiers();
 		  $$->add_identifier(new Identifier($1));
 		  SymbolTable::add_symbols($$);
 	  }
 	| declaration_specifiers init_declarator_list SEMICOLON {
		/* Use the variable name from init_declarator */
		for(auto &element : $2->identifiers) {
			if (element.type->type_tag == FUNCTION_TYPE) {
				if (element.type->function_type->return_type != NULL && element.type->function_type->return_type->type_tag == POINTER_TYPE) {
					element.type->function_type->return_type->pointer_type->return_type = $1;
					element.type->function_type->return_type->pointer_type->specifiers = combine_specs(element.type->function_type->return_type->pointer_type->specifiers, $1->getSpecifiers());
				} else {
					element.type->function_type->return_type = $1;
				}
			} else if (element.type->type_tag == NONE) {
				element.type = $1;
			} else if (element.type->type_tag == POINTER_TYPE) {
				element.type->pointer_type->return_type = $1;
				element.type->pointer_type->specifiers = combine_specs(element.type->pointer_type->specifiers, $1->getSpecifiers());
			} else if (element.type->type_tag == ARRAY_TYPE) {
				element.type->array_type->return_type = $1;
				element.type->array_type->specifiers = combine_specs(element.type->array_type->specifiers, $1->getSpecifiers());
			} else {
				std::cerr << "Cannot create a type for the following identifier" << std::endl;
			}
		}
		$$=$2;
		SymbolTable::add_symbols($$);
 	  }
	;

declaration_specifiers
 	: type_specifier { $$ = $1; }
	| qualifiers type_specifier { $$ = $2; $$->setSpecifiers(combine_specs($$->getSpecifiers(), $1)); }
	;

qualifiers
	: storage_class_specifier_list { $$ = $1; }
	| type_qualifier_list { $$ = $1; }
	| storage_class_specifier_list qualifiers { $$ = combine_specs($1, $2); }
	| type_qualifier_list qualifiers { $$ = combine_specs($1, $2); }
	;
	

 init_declarator_list
 	: init_declarator{
 		$$ = new VectorIdentifiers();
 		$$->add_identifier($1);
 	}
 	| init_declarator_list COMMA init_declarator{
 		$$ = $1;
 		$$->add_identifier($3);
 	}
 	;

 init_declarator
 	: declarator{
 		$$ = $1;
 	}
 	/* | declarator ASSIGN initializer{
 		// TODO: type checking
 		$$ = $1;
 	} */
 	;

 /* Storage classes */
storage_class_specifier_list
	: storage_class_specifier { $$ = $1; }
	| storage_class_specifier storage_class_specifier_list { $$ = combine_specs($1, $2); }
	;


storage_class_specifier
 	: TYPEDEF { $$ = new Specifiers(); $$->is_typedef = true; }
 	| EXTERN { $$ = new Specifiers(); $$->is_extern = true; }
 	| STATIC { $$ = new Specifiers(); $$->is_static = true; }
 	| REGISTER { $$ = new Specifiers(); $$->is_register = true; }
 	;

/* Type specifiers */
type_specifier
	: INT      		{ $$ = create_primitive_type(INT_T); }
	| SIGNED		{ $$ = create_primitive_type(INT_T); }
	| VOID     		{ $$ = create_primitive_type(VOID_T); }
	| CHAR     		{ $$ = create_primitive_type(CHAR_T); }
	| SIGNED CHAR     		{ $$ = create_primitive_type(CHAR_T); }
	| UNSIGNED CHAR     		{ $$ = create_primitive_type(U_CHAR_T); }
	| SHORT    		{ $$ = create_primitive_type(SHORT_T); }
	| SIGNED SHORT    		{ $$ = create_primitive_type(SHORT_T); }
	| UNSIGNED SHORT    		{ $$ = create_primitive_type(U_SHORT_T); }
	| SHORT INT   	{ $$ = create_primitive_type(SHORT_T); }
	| UNSIGNED SHORT INT   	{ $$ = create_primitive_type(U_SHORT_T); }
	| SIGNED SHORT INT   	{ $$ = create_primitive_type(SHORT_T); }
	| SHORT UNSIGNED INT   	{ $$ = create_primitive_type(U_SHORT_T); }
	| SHORT SHORT INT   	{ $$ = create_primitive_type(SHORT_T); }
	| LONG     		{ $$ = create_primitive_type(LONG_T); }
	| SIGNED LONG     		{ $$ = create_primitive_type(LONG_T); }
	| UNSIGNED LONG     		{ $$ = create_primitive_type(U_LONG_T); }
	| LONG INT 		{ $$ = create_primitive_type(LONG_T); }
	| LONG SIGNED INT 		{ $$ = create_primitive_type(LONG_T); }
	| LONG UNSIGNED INT 		{ $$ = create_primitive_type(U_LONG_T); }
	| SIGNED LONG INT 		{ $$ = create_primitive_type(LONG_T); }
	| UNSIGNED LONG INT 		{ $$ = create_primitive_type(U_LONG_T); }
	| LONG LONG 	{ $$ = create_primitive_type(LLONG_T); }
	| UNSIGNED LONG LONG 	{ $$ = create_primitive_type(U_LLONG_T); }
	| SIGNED LONG LONG 	{ $$ = create_primitive_type(LLONG_T); }
	| LONG UNSIGNED LONG 	{ $$ = create_primitive_type(U_LLONG_T); }
	| LONG SIGNED LONG 	{ $$ = create_primitive_type(LLONG_T); }
	| LONG LONG INT { $$ = create_primitive_type(LLONG_T); }
	| UNSIGNED LONG LONG INT { $$ = create_primitive_type(U_LLONG_T); }
	| SIGNED LONG LONG INT { $$ = create_primitive_type(LLONG_T); }
	| LONG UNSIGNED LONG INT { $$ = create_primitive_type(U_LLONG_T); }
	| LONG SIGNED LONG INT { $$ = create_primitive_type(LLONG_T); }
	| LONG LONG UNSIGNED INT { $$ = create_primitive_type(U_LLONG_T); }
	| LONG LONG SIGNED INT { $$ = create_primitive_type(LLONG_T); }
	| FLOAT    		{ $$ = create_primitive_type(FLOAT_T); }
	| DOUBLE   		{ $$ = create_primitive_type(DOUBLE_T); }
	| LONG DOUBLE 	{ $$ = create_primitive_type(LONG_DOUBLE_T); }
 	| struct_specifier { $$ = create_struct_type($1); }
 	| union_specifier { $$ = create_union_type($1); }
 	| enum_specifier { $$ = create_enum_type($1); }
	| type_specifier pointer {
		$$ = create_pointer_type($1, $2->ptr_level, $1->getSpecifiers());
	}
	;

// /* Struct and union specifiers */
struct_specifier
  	: STRUCT IDENTIFIER { $$ = new Struct(std::string($2)); }
 	| STRUCT IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new Struct(std::string($2), $4); $$->is_defined = true; }
 	| STRUCT LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new Struct($3); $$->is_defined = true; }

 	;

 union_specifier
  	: UNION IDENTIFIER { $$ = new Union(std::string($2)); }
 	| UNION IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new Union(std::string($2), $4); $$->is_defined = true; }
 	| UNION LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = new Union($3); $$->is_defined = true; }
 	;

struct_declaration_list
 	: struct_declaration { $$ = $1; }
 	| struct_declaration_list struct_declaration {
 		$$ = $1;
 		$$->add_elements($2);
 	}
 	;

struct_declaration
 	: specifier_qualifier_list struct_declarator_list SEMICOLON {
 		$$ = new VectorStructElement();
 		for (auto &declarator : $2->elements) {
 			declarator.id->type = $1;
 		}
		$$->add_elements($2);
 	}
 	;

 struct_declarator_list
 	: struct_declarator {
 		$$ = new VectorStructElement();
 		$$->add_element($1);
 	}
 	| struct_declarator_list COMMA struct_declarator {
 		$$ = $1;
 		$$->add_element($3);
 	}
 	;

 specifier_qualifier_list
 	: type_specifier {
		$$ = $1;
	}
 	| qualifiers specifier_qualifier_list {
		// TODO: make sure here storage_class_specifier are not there as they are not possible
		$$=$2;
		$$->setSpecifiers(combine_specs($$->getSpecifiers(), $1));
	}
 	;

 struct_declarator
 	: declarator {
 		$$ = new StructElement($1, $1->type->getSize()); 
	}
	| COLON CONSTANT_LITERAL {
		unsigned int value = convert_to_unsigned(std::string($2));
		$$ = new StructElement(value);
	}
	| declarator COLON CONSTANT_LITERAL {
		unsigned int value = convert_to_unsigned(std::string($2));
		$$ = new StructElement($1, value);
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
 		$$ = new VectorEnumElement();
 		$$->add_element($1);
 	}
 	| enumerator_list COMMA enumerator{
 		$$ = $1;
 		$$->add_element($3);
 	}
 	;

 enumerator
 	: IDENTIFIER {
 		$$ = new EnumElement(std::string($1));
 	}
	| IDENTIFIER ASSIGN CONSTANT_LITERAL {
		int value = convert_to_signed(std::string($3));
		$$ = new EnumElement(std::string($1), value);
	}
	;

 /* Type qualifiers */
 type_qualifier
 	: CONST    { $$ = new Specifiers(); $$->is_const = true; }
 	| VOLATILE { $$ = new Specifiers(); $$->is_volatile = true; }
 	;

// /* Declarators */
declarator
 	: direct_declarator { $$ = $1; }
 	| pointer direct_declarator { 
 		$$ = $2; 
 		if($$->type->type_tag == NONE) {
 			$$->type = create_pointer_type(new GlobalType(), $1->ptr_level, $1->specifiers);
 		} else if ($$->type->type_tag == FUNCTION_TYPE) {
 			$$->type->function_type->return_type = create_pointer_type(new GlobalType(), $1->ptr_level, $1->specifiers);
 		} else if ($$->type->type_tag == POINTER_TYPE) {
			$$->type->pointer_type->ptr_level += $1->ptr_level;
			$$->type->pointer_type->specifiers = combine_specs($$->type->pointer_type->specifiers, $1->specifiers);
 		} else {
 			std::cerr << "Cannot create a pointer type for the following identifier" << std::endl;
 		}
 	}

 	;

 direct_declarator
 	: IDENTIFIER { $$ = new Identifier(std::string($1)); }
 	| LEFT_PAREN declarator RIGHT_PAREN { $$ = $2; }
	| direct_declarator LEFT_BRACKET RIGHT_BRACKET { 
 		$$ = $1;
		if ( $$->type->type_tag == NONE) {
			std::cerr << "Array type" << std::endl;
			$$->type = create_array_type($1->type);
			$$->type = add_dimension_array($$->type);
		}
 		else if ( $$->type->type_tag == ARRAY_TYPE ) {
			$$->type = add_dimension_array($1->type);
		} else {
			std::cerr << "Cannot create an array type for the following identifier" << std::endl;
		}
 	}
	| direct_declarator LEFT_PAREN RIGHT_PAREN { 
		$$ = $1;
		if ($$->type->type_tag == NONE) {
			$$->type = create_function_type($$->type);
		} else {
			std::cerr << "Cannot create a function type for the following identifier" << std::endl;
		}
	}
	| direct_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN { 
		$$ = $1;
		if ($$->type->type_tag == NONE) {
			$$->type = create_function_type($$->type, $3);
		} else {
			std::cerr << "Cannot create a function type for the following identifier" << std::endl;
		}
	}
	| direct_declarator LEFT_BRACKET CONSTANT_LITERAL RIGHT_BRACKET {
		unsigned int constant = convert_to_unsigned(std::string($3));
		$$ = $1;
		if ( $$->type->type_tag == NONE) {
			$$->type = create_array_type($1->type);
			$$->type = add_dimension_array($$->type, constant);
		}
 		else if ( $$->type->type_tag == ARRAY_TYPE ) {
			$$->type = add_dimension_array($1->type, constant);

		} else {
			std::cerr << "Cannot create an array type for the following identifier" << std::endl;
		}

	}
	// | direct_declarator LEFT_PAREN identifier_list RIGHT_PAREN { 
	// 	$$ = $1;
	// 	if ($$->type->type_tag == NONE) {
	// 		// This is a function call so we need to make sure all identifiers are present
	// 		// All identifiers must be defined in the symbol table
	// 		if (SymbolTable::lookup_symbols($3)) {
	// 			// Check if function is defined in the symbol table
	// 			if (SymbolTable::lookup_symbol($$->name)) {
					
	// 			}
	// 		}

	// 	} else {
	// 		std::cerr << "Cannot create a function type for the following identifier" << std::endl;
	// 	}
	// } 
	;

pointer
 	: ASTERISK { $$ = new PointerType(); }
 	| ASTERISK type_qualifier_list { 
 		$$ = new PointerType();
 		if ($$->specifiers == NULL) {
			$$->specifiers = new Specifiers();
		}
 		$$->specifiers = combine_specs($$->specifiers, $2);
 	 }
 	| ASTERISK pointer { 
 		$$ = $2;
 		$$->ptr_level++;
 	}
 	| ASTERISK type_qualifier_list pointer { 
 		$$ = $3;
 		$$->ptr_level++;
		if ($$->specifiers == NULL) {
			$$->specifiers = new Specifiers();
		}
 		$$->specifiers = combine_specs($$->specifiers, $2);
	}
 	;

type_qualifier_list
 	: type_qualifier { 
 		$$ = $1;
 	}
 	| type_qualifier_list type_qualifier{
 		$$ = combine_specs($1, $2);
 	}
 	;

/* Function parameters */
parameter_type_list
	: parameter_list{
		$$ = $1;
	}
	// | parameter_list COMMA ELLIPSIS{
	// 	//TODO: fix later
	// 	$$=$1;
	// }
	;

parameter_list
 	: parameter_declaration { $$ = new VectorIdentifiers(); $$->add_identifier($1); }
 	| parameter_list COMMA parameter_declaration { $$ = $1; $$->add_identifier($3); }
 	;

 parameter_declaration
 	: declaration_specifiers declarator {
 		$$ = $2;
		// Function 
		if ($$->type->type_tag == FUNCTION_TYPE) {
			if ($$->type->function_type->return_type != NULL && $$->type->function_type->return_type->type_tag == POINTER_TYPE) {
				$$->type->function_type->return_type->pointer_type->return_type = $1;;
				$$->type->function_type->return_type->pointer_type->specifiers = combine_specs($$->type->function_type->return_type->pointer_type->specifiers, $1->getSpecifiers());
			} else {
				$$->type->function_type->return_type = $1;
			}
		// We only got identifier
		} else if ($$->type->type_tag == NONE) {
			$$->type = $1;
		/// If we get array type
		} else if ($$->type->type_tag == ARRAY_TYPE) {
			$$->type->array_type->return_type = $1;
		// If we get somehing else
		} else if ($$->type->type_tag == POINTER_TYPE) {
			$$->type->pointer_type->return_type = $1;
			$$->type->pointer_type->specifiers = combine_specs($$->type->pointer_type->specifiers, $1->getSpecifiers());
		} else {
			std::cerr << "Cannot create a pointer type for the following identifier" << std::endl;
			$$->type = create_invalid_type("Cannot create a pointer type for the following identifier");
		}
 	}
	| declaration_specifiers abstract_declarator {
		$$ = new Identifier($2);
		// Function 
		if ($$->type->type_tag == FUNCTION_TYPE) {
			if ($$->type->function_type->return_type != NULL && $$->type->function_type->return_type->type_tag == POINTER_TYPE) {
				$$->type->function_type->return_type->pointer_type->return_type = $1;;
				$$->type->function_type->return_type->pointer_type->specifiers = combine_specs($$->type->function_type->return_type->pointer_type->specifiers, $1->getSpecifiers());
			} else {
				$$->type->function_type->return_type = $1;
			}
		// We only got identifier
		} else if ($$->type->type_tag == NONE) {
			$$->type = $1;
		// If we get array type
		} else if ($$->type->type_tag == ARRAY_TYPE) {
			$$->type->array_type->return_type = $1;
			$$->type->array_type->specifiers = combine_specs($$->type->array_type->specifiers, $1->getSpecifiers());
		// If we get somehing else
		} else if ($$->type->type_tag == POINTER_TYPE) {
			$$->type->pointer_type->return_type = $1;
			$$->type->pointer_type->specifiers = combine_specs($$->type->pointer_type->specifiers, $1->getSpecifiers());
		} else {
			std::cerr << "Cannot create a pointer type for the following identifier" << std::endl;
			$$->type = create_invalid_type("Cannot create a pointer type for the following identifier");
		}
	}
	| declaration_specifiers {
		$$ = new Identifier($1);
	}
 	;

identifier_list
 	: IDENTIFIER { $$ = new VectorIdentifiers(); $$->add_identifier(new Identifier(std::string($1))); }
 	| identifier_list COMMA IDENTIFIER { 
 		$$ = $1;
 		$$->add_identifier(new Identifier(std::string($3)));
 	}
 	;

type_name
 	: specifier_qualifier_list { $$ = $1; }
 	| specifier_qualifier_list abstract_declarator {
		$$ = $2;
		if ($$->type_tag == FUNCTION_TYPE) {
			if ($$->function_type->return_type != NULL && $$->function_type->return_type->type_tag == POINTER_TYPE) {
				$$->function_type->return_type->pointer_type->return_type = $1;
				$$->function_type->return_type->pointer_type->specifiers = combine_specs($$->function_type->return_type->pointer_type->specifiers, $1->getSpecifiers());
			} else {
				$$->function_type->return_type = $1;
			}
		} else if ($$->type_tag == ARRAY_TYPE) {
			$$->array_type->return_type = $1;
		} else if ($$->type_tag == POINTER_TYPE) {
			$$->pointer_type->return_type = $1;
		} else {
			std::cerr << "Cannot create a type name for the following abstract declarator" << std::endl;
		}
 	}
 	;

abstract_declarator
 	: pointer { 
		$$ = new GlobalType();
		$$->type_tag = POINTER_TYPE;
		$$->pointer_type = $1;
	}
 	| direct_abstract_declarator {
		$$ = $1;
	}
 	| pointer direct_abstract_declarator {
		$$ = $2;
		if ($$->type_tag == FUNCTION_TYPE) {
 			$$->function_type->return_type = create_pointer_type(new GlobalType(), $1->ptr_level, $1->specifiers);
 		} else if ($$->type_tag == POINTER_TYPE) {
			$$->pointer_type->ptr_level += $1->ptr_level;
			$$->pointer_type->specifiers = combine_specs($$->pointer_type->specifiers, $1->specifiers);
		} else {
			std::cerr << "Cannot create a pointer type for the following abstract declarator" << std::endl;
 		}
	}
 	;

direct_abstract_declarator
 	: LEFT_PAREN abstract_declarator RIGHT_PAREN { $$ = $2; }
 	| LEFT_BRACKET RIGHT_BRACKET {
		$$ = create_array_type(new GlobalType());
		$$ = add_dimension_array($$);
	}
 	| LEFT_BRACKET CONSTANT_LITERAL RIGHT_BRACKET {
		unsigned int constant = convert_to_unsigned(std::string($2));
		$$ = create_array_type(new GlobalType());
		$$ = add_dimension_array($$, constant);
	}
 	| direct_abstract_declarator LEFT_BRACKET RIGHT_BRACKET {
		$$ = $1;
		if ( $$->type_tag == NONE) {
			$$ = create_array_type($1);
			$$ = add_dimension_array($$);
		}
 		else if ( $$->type_tag == ARRAY_TYPE ) {
			$$ = add_dimension_array($1);
		} else {
			std::cerr << "Cannot create an array type for the following abstract declarator" << std::endl;
		}
	}
	| direct_abstract_declarator LEFT_BRACKET CONSTANT_LITERAL RIGHT_BRACKET {
		unsigned int constant = convert_to_unsigned(std::string($3));
		$$ = $1;
		if ( $$->type_tag == NONE) {
			$$ = create_array_type($1);
			$$ = add_dimension_array($$, constant);
		}
 		else if ( $$->type_tag == ARRAY_TYPE ) {
			$$ = add_dimension_array($1, constant);

		} else {
			std::cerr << "Cannot create an array type for the following abstract declarator" << std::endl;
		}
	}
 	| LEFT_PAREN RIGHT_PAREN {
		$$ = create_function_type(new GlobalType());
	}
 	| LEFT_PAREN parameter_type_list RIGHT_PAREN {
		$$ = create_function_type(new GlobalType(), $2);
	}
	;

// /* Initializers */
// initializer
// 	: assignment_expression
// 	| LEFT_BRACE initializer_list RIGHT_BRACE
// 	| LEFT_BRACE initializer_list COMMA RIGHT_BRACE
// 	;

// initializer_list
// 	: initializer
// 	| initializer_list COMMA initializer
// 	;

 /* Statements */
statement
 	: expression_statement
 	| iteration_statement
 	| compound_statement
 	| selection_statement
 	// | labeled_statement
 	// | jump_statement
// 	| error_statement_closed
 	;

// labeled_statement
// 	: IDENTIFIER COLON statement
// 	| CASE CONSTANT_LITERAL COLON statement
// 	| DEFAULT COLON statement
// 	;

compound_statement
 	: INC_SCOPE LEFT_BRACE RIGHT_BRACE { SymbolTable::exit_scope(); }
	| INC_SCOPE LEFT_BRACE all_statements RIGHT_BRACE { SymbolTable::exit_scope(); }
	;

all_statements
	: all_statements statement_list
	| all_statements declaration_list
	| statement_list
	| declaration_list
	;

 declaration_list
 	: declaration { $$ = $1; }
 	| declaration_list declaration{
		$$ = $1;
		$$->add_identifiers($2);
	}
 	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
 	: SEMICOLON {$$ = new Expression(); $$->name="empty";}
 	| expression SEMICOLON {
		$$ = $1;
		std::cout << "Expression statment" << std::endl;
	}
 	;

empty_else
	: %empty
	| ELSE INC_SCOPE statement { SymbolTable::exit_scope();}
	;

/* Control flow */
selection_statement
	: IF INC_SCOPE {TAC::create_if_statement(); } LEFT_PAREN expression { TAC::print_goto_conditional($5, FALSE_C); } RIGHT_PAREN statement { TAC::print_goto(TRUE_C, false); TAC::remove_false_label(); SymbolTable::exit_scope(); } empty_else { TAC::remove_true_label(); }
//	| SWITCH LEFT_PAREN expression RIGHT_PAREN statement
	;


init_clause
	: SEMICOLON
	| expression SEMICOLON
	| declaration SEMICOLON
	;

empty_expression
	: %empty
	| expression
	;

iteration_statement
	: WHILE INC_SCOPE { TAC::create_loop_statement(); } LEFT_PAREN expression { TAC::print_label(CONTINUE_C); TAC::print_goto_conditional($5, BREAK_C); } RIGHT_PAREN statement {
		TAC::remove_break_label();
		TAC::remove_continue_label();
		SymbolTable::exit_scope();
	}
	| DO INC_SCOPE {TAC::create_loop_statement(); TAC::print_label(CONTINUE_C); } statement WHILE LEFT_PAREN expression { TAC::print_goto_do_while($7); } RIGHT_PAREN SEMICOLON{
		TAC::remove_break_label();
		TAC::remove_continue_label();
		SymbolTable::exit_scope();
	}
	| FOR INC_SCOPE { TAC::create_loop_statement(); } LEFT_PAREN init_clause {TAC::print_label(CONTINUE_C);} expression_statement { TAC::print_goto_conditional($7, BREAK_C); TAC::dump_to_file(); } empty_expression { TAC::dump_to_temp(); } RIGHT_PAREN statement {
		TAC::get_from_temp();
		TAC::print_goto(CONTINUE_C, true);
		TAC::remove_break_label();
		SymbolTable::exit_scope();
	}
	;

// jump_statement
// 	: GOTO IDENTIFIER SEMICOLON
// 	| CONTINUE SEMICOLON
// 	| BREAK SEMICOLON
// 	| RETURN SEMICOLON
// 	| RETURN expression SEMICOLON
// 	;

 /* Top-level constructs */
 translation_unit
 	: external_declaration
	| translation_unit external_declaration
// 	| translation_unit error_statement_closed
 	;

 external_declaration
 	: function_definition
	| declaration
 	;

function_declaration
	: declaration_specifiers declarator {
		$$ = $2;
		if ($$->type->type_tag == FUNCTION_TYPE) {
			if ($$->type->function_type->return_type != NULL && $$->type->function_type->return_type->type_tag == POINTER_TYPE) {
				$$->type->function_type->return_type->pointer_type->return_type = $1;;
				$$->type->function_type->return_type->pointer_type->specifiers = combine_specs($$->type->function_type->return_type->pointer_type->specifiers, $1->getSpecifiers());
			} else {
				$$->type->function_type->return_type = $1;
			}
		} else{
			std::cerr << "Error: function declaration with non-function type" << std::endl;
		}
	}
	;

function_definition
 	: function_declaration INC_SCOPE { SymbolTable::add_symbols(&($1->type->function_type->args)); TAC::create_function_definition(std::string($1->name)); } compound_statement { 
 		$$ = $1;
		$$->type->setDefined();
		SymbolTable::exit_scope();
 		SymbolTable::add_symbol($$);
 	}
	; 

INC_SCOPE : { SymbolTable::enter_scope(); };
 %%

void yyerror(const char *s) {
 	fprintf(stderr, "Syntax Error: %s at line %d\n", s, yylineno);
}