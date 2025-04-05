#pragma once

#include <vector>
#include <types.h>
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <fstream>

class Identifier;

extern std::fstream symbol_table_file;

class Symbol {
public:
  Identifier identifier;
  int line_number;
  int column_number;
  int current_level;

  Symbol(Identifier& id, int level, int line = 0, int column = 0)
    : identifier(id), line_number(line), column_number(column), current_level(level) {}

  // Missing getter that was referenced in the code
  Identifier get_identifier() const { return identifier; }
};

// A static symbol table to store and manage symbols
class SymbolTable {
private:
  static std::unordered_map<std::string, std::vector<Symbol> > symbol_map;
  static int current_scope_level;

public:
  // Prevent instantiation
  SymbolTable() = delete;

  static void enter_scope();
  static int current_scope();
  static void exit_scope();
  static void add_symbol(Identifier* id, int line = 0, int column = 0);
  static void add_symbols(VectorIdentifiers* ids, int line = 0, int column = 0);
  static bool lookup_symbol(const std::string& identifier);
  static bool lookup_symbols(VectorIdentifiers* ids);
  static Symbol* get_symbol(const std::string& identifier);
  static void print_symbol(Symbol symbol);
};
