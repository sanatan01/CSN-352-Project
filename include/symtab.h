#pragma once

#include <vector>
#include <types.h>
#include <expression.h>
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <utils.h>

class Identifier;

extern std::fstream symbol_table_file;

class Symbol
{
public:
	Identifier identifier;
	int line_number;
	int column_number;
	int current_level;

	bool is_defined;

	Symbol(Identifier &id, int level, bool is_defined, int line = 0, int column = 0)
		: identifier(id), is_defined(is_defined), line_number(line), column_number(column), current_level(level) {}

	Symbol(const Symbol &other)
		: identifier(other.identifier),
		  line_number(other.line_number),
		  column_number(other.column_number),
		  current_level(other.current_level),
		  is_defined(other.is_defined) {}

	// Missing getter that was referenced in the code
	Identifier get_identifier() const { return identifier; }

	class Symbol *copy_symbol() const { return new Symbol(*this); }
};

class UserDefinedType
{
public:
	class GlobalType type;
	std::string type_name;
	int current_scope = 0;
	bool is_defined = false;

	UserDefinedType(class Struct *struct_type, int scope_level);
	UserDefinedType(class Union *union_Type, int scope_level);
	UserDefinedType(class EnumType *enum_type, int scope_level);
	UserDefinedType(const UserDefinedType &other);
};

// A static symbol table to store and manage symbols
class SymbolTable
{
private:
	static std::unordered_map<std::string, std::vector<Symbol>> symbol_map;
	static std::vector<Symbol> all_symbols;
	static int current_scope_level;
	static std::vector<UserDefinedType> udt;

public:
	// Prevent instantiation
	SymbolTable() = delete;

	static void enter_scope();
	static int current_scope();
	static void exit_scope();
	static void add_symbol(Identifier *id, int line = 0, int column = 0);
	static void add_symbols(VectorIdentifiers *ids, int line = 0, int column = 0);
	static bool lookup_symbol(const std::string &identifier);
	static bool lookup_symbols(VectorIdentifiers *ids);
	static Symbol *get_symbol(const std::string &identifier);
	static void print_symbol(Symbol symbol);
	static void initialize_built_ins();

	static void add_udt(class GlobalType *type);
	static void decrement_scope();
	static class GlobalType *get_global_type(class GlobalType *global_type);
	static void print_udt();

	static Symbol get_symbol_by_index(int index);
};

void formatSymbolTable();