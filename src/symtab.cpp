#include <symtab.h>

// Initialize static members
std::unordered_map<std::string, std::vector<Symbol> > SymbolTable::symbol_map;
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
    // Check if identifier is a struct
    if (id->type->type_tag == STRUCT_TYPE) {
        id->name = id->type->struct_type->struct_name;
    } else if (id->type->type_tag == UNION_TYPE) {
        id->name = id->type->union_type->union_name;
    } else if (id->type->type_tag == ENUM_TYPE) {
        id->name = id->type->enum_type->enum_name;
    }

    Symbol symbol(*id, current_scope_level, id->type->isDefined(), line, column);
    std::string name = symbol.identifier.name;
    symbol_map[name].push_back(symbol);
    SymbolTable::print_symbol(symbol);
}

void SymbolTable::add_symbols(VectorIdentifiers* ids, int line, int column) {
    for (auto& id : ids->identifiers) {
        add_symbol(&id, line, column);
    }
}

bool SymbolTable::lookup_symbol(const std::string& identifier) {
    return symbol_map.find(identifier) != symbol_map.end() && !symbol_map[identifier].empty();
}

bool SymbolTable::lookup_symbols(VectorIdentifiers* ids) {
    for (auto& id : ids->identifiers) {
        if (!lookup_symbol(id.name)) {
            return false;
        }
    }
    return true;
}

Symbol* SymbolTable::get_symbol(const std::string& identifier) {
    if (symbol_map.find(identifier) != symbol_map.end() && !symbol_map[identifier].empty()) {
        return &symbol_map[identifier].back();
    }
    return nullptr;
}

void SymbolTable::print_symbol(Symbol symbol) {
    symbol_table_file << std::left << std::setw(15) << symbol.identifier.name << '|'
              << std::left << std::setw(15) << symbol.current_level << '|'
              << std::left << std::setw(15) << symbol.line_number << '|'
              << std::left << std::setw(15) << symbol.column_number << '|'
              << std::left << std::setw(15) << symbol.identifier.type->getType() << '\n';


}




