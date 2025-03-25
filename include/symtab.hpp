#pragma once

#include <deque>
#include <map>
#include <string>
#include <sstream>
#include <ast.hpp>
#include <types.hpp>
#include <ast_entries.hpp>

void yyerror( const char *s );
extern int error_flag;

class Expression;
class Identifier;
class PrimaryExpression;
Expression *create_assignment_expression( Expression *ue, Node *n_op, Expression *ase );

extern unsigned int line_num;
extern unsigned int column;
extern unsigned int prev_line_num;
extern unsigned int prev_column;

extern std::stringstream text;
extern std::vector<std::string> code;

// All class declarations
class StructDefinition;
class AssignmentExpression;
class ParameterTypeList;
class CastExpression;
class Constant;
class StringLiteral;
class TopLevelExpression;

#define WORD_SIZE 4

// --------------------------------------------------------------------------------------------
// ----------------------------------------SYMBOL TABLE----------------------------------------
// --------------------------------------------------------------------------------------------

class SymTabEntry {
  public:
    std::string name;
    int level;
    GlobalType type;
    unsigned int line_num;
    unsigned int column;
    size_t offset;
    unsigned int id;

    SymTabEntry( std::string name_parameter, unsigned int line_num, unsigned int column );
};

class FunctionEntry : public SymTabEntry {
  public:
    std::string args;
    FunctionEntry( std::string name, std::string return_type, std::string args , unsigned int line_num, unsigned int column);
};

class SymbolTable {
  public:
    SymbolTable();
    
    // Not sure about the use of the following variables
    unsigned int symbol_id;
    std::stringstream ss;

    virtual SymTabEntry *get_symbol_from_table( std::string name );
    void delete_from_table( SymTabEntry *symbol );
    virtual void add_to_table( SymTabEntry *symbol );
    void print_table();
};

class GlobalSymbolTable {
  public:
    size_t offset;
    std::unordered_map<std::string, SymTabEntry *> sym_table;
    void add_symbol( DeclarationSpecifiers *declaration_specifiers, Declarator *declarator, int *error );
    void add_to_table( SymTabEntry *symbol, bool redef, Identifier *id );
    SymTabEntry *get_symbol_from_table( std::string name );
};

class LocalSymbolTable : public SymbolTable {
  public:
    std::unordered_map<std::string, std::deque<SymTabEntry *> &> sym_table;
    std::string function_name;
    size_t reqd_size;
    int current_level;
    size_t offset;
	  GlobalType return_type;

    void increase_level();
    void clear_current_level();
    void empty_table();
    LocalSymbolTable();
    void add_to_table( SymTabEntry *symbol, Identifier *id , bool is_fun_arg );
    SymTabEntry *get_symbol_from_table( std::string name );
    void add_function( DeclarationSpecifiers *declaration_specifiers, Declarator *declarator, int *error );
};

extern LocalSymbolTable local_symbol_table;
extern GlobalSymbolTable global_symbol_table;

extern int LOCAL_SYM_MASK = 0x10000000;
extern int GLOBAL_SYM_MASK = 0x20000000;
extern int FUN_ARG_MASK = 0x40000000;

// For writing to the symbol table file
extern std::stringstream sym_ss;
void write_to_symtab_file( std::string s );
