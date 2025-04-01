#include <symtab.h>

// Initialize static members
std::unordered_map<std::string, std::vector<Symbol>> SymbolTable::symbol_map;
int SymbolTable::current_scope_level = 0;

void SymbolTable::enter_scope() {
    current_scope_level++;
}

int SymbolTable::current_scope() {
    return current_scope_level;
}

void SymbolTable::exit_scope() {
    // Remove all symbols at the current scope level
    for (auto it = symbol_map.begin(); it != symbol_map.end();) {
        auto& [name, symbols] = *it;
        while (!symbols.empty() && symbols.back().current_level == current_scope_level) {
            symbols.pop_back();
        }
        // Remove empty entries
        if (symbols.empty()) {
            it = symbol_map.erase(it);
        }
        else {
            ++it;
        }
    }
    current_scope_level--;
}

void SymbolTable::add_symbol(Identifier* id, int line, int column) {
    Symbol symbol(*id, current_scope_level, line, column);
    std::string name = symbol.identifier.name;
    symbol_map[name].push_back(symbol);
    SymbolTable::print_symbol(symbol);
}

bool SymbolTable::lookup_symbol(const std::string& identifier) {
    return symbol_map.find(identifier) != symbol_map.end() && !symbol_map[identifier].empty();
}

Symbol* SymbolTable::get_symbol(const std::string& identifier) {
    if (symbol_map.find(identifier) != symbol_map.end() && !symbol_map[identifier].empty()) {
        return &symbol_map[identifier].back();
    }
    return nullptr;
}

void SymbolTable::print_symbol(Symbol symbol) {
    std::cout << "Symbol: " << symbol.identifier.name 
              << " | Scope: " << symbol.current_level 
              << " | Line: " << symbol.line_number
              << " | Column: " << symbol.column_number << std::endl
              << " | Return Type: " << symbol.identifier.type->getType() << std::endl;
}