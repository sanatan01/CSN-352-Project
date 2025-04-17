#include <symtab.h>
#include <tac.h>

// Initialize static members
std::unordered_map<std::string, std::vector<Symbol> > SymbolTable::symbol_map;
int SymbolTable::current_scope_level = 0;
std::vector<UserDefinedType> SymbolTable::udt;

void SymbolTable::enter_scope() {
    current_scope_level++;
}

int SymbolTable::current_scope() {
    return current_scope_level;
}

void SymbolTable::exit_scope() {

    size_t total_size = 0;
    // Remove all symbols at the current scope level
    for (auto it = symbol_map.begin(); it != symbol_map.end();) {
        auto& [name, symbols] = *it;
        while (!symbols.empty() && symbols.back().current_level == current_scope_level) {
            if(!(symbols.back().identifier.type->getSpecifiers()->is_static)) {
                total_size += symbols.back().identifier.type->getSize();
            }

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

    TAC::print_tac(".pop " + std::to_string(total_size));

    decrement_scope();
    current_scope_level--;
}

void SymbolTable::add_symbol(Identifier* id, int line, int column) {

    // Print TAC
    if(id->type->getSpecifiers()->is_static) {
        TAC::print_tac(".static " + id->name + " " + std::to_string(id->type->getSize()));
    } else if(id->type->type_tag != FUNCTION_TYPE )  {
        TAC::print_tac(".push " + id->name + " " + std::to_string(id->type->getSize()));
    }

    Symbol symbol(*id, current_scope_level, id->type->isDefined(), line, column);
    std::string name = symbol.identifier.name;
    symbol_map[name].push_back(symbol);
    SymbolTable::print_symbol(symbol);
}

void SymbolTable::add_symbols(VectorIdentifiers* ids, int line, int column) {
    for (auto& id : ids->identifiers) {
        debug_msg("Adding symbol of type " + id.type->getType());
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
        return new Symbol(symbol_map[identifier].back());
    }
    return nullptr;
}

void SymbolTable::print_symbol(Symbol symbol) {

    symbol_table_file << std::left << std::setw(15) << symbol.identifier.name << '|'
        << std::left << std::setw(15) << symbol.current_level << '|'
        << std::left << std::setw(15) << symbol.line_number << '|'
        << std::left << std::setw(15) << symbol.column_number << '|';


    class GlobalType* temp = get_global_type(symbol.identifier.type);

    std::string type_name;

    if (temp != nullptr) {
        if (temp->type_tag == STRUCT_TYPE) {
            type_name = symbol.identifier.type->getType() + " " + temp->struct_type->struct_name;
        }
        else if (temp->type_tag == UNION_TYPE) {
            type_name = symbol.identifier.type->getType() + " " + temp->union_type->union_name;
        }
        else if (temp->type_tag == ENUM_TYPE) {
            type_name = symbol.identifier.type->getType() + " " + temp->enum_type->enum_name;
        }
    }
    else {
        type_name = symbol.identifier.type->getType();
    }

    symbol_table_file << std::left << std::setw(30) << type_name << '\n';

}

void SymbolTable::initialize_built_ins() {
    // Create printf function
    Identifier* printf_id = new Identifier("printf");
    GlobalType* return_type = create_primitive_type(INT_T);
    printf_id->type = create_function_type(return_type);

    // Create scanf function
    Identifier* scanf_id = new Identifier("scanf");
    scanf_id->type = create_function_type(return_type);

    // Add to symbol table
    SymbolTable::add_symbol(printf_id);
    SymbolTable::add_symbol(scanf_id);
}

UserDefinedType::UserDefinedType(class Struct* struct_type, int scope_level) {
    type_name = struct_type->struct_name;
    current_scope = scope_level;
    type = GlobalType();
    type.struct_type = struct_type;
    type.type_tag = STRUCT_TYPE;
}

UserDefinedType::UserDefinedType(class Union* union_type, int scope_level) {
    type_name = union_type->union_name;
    current_scope = scope_level;
    type = GlobalType();
    type.union_type = union_type;
    type.type_tag = UNION_TYPE;
}

UserDefinedType::UserDefinedType(class EnumType* enum_type, int scope_level) {
    type_name = enum_type->enum_name;
    current_scope = scope_level;
    type = GlobalType();
    type.enum_type = enum_type;
    type.type_tag = ENUM_TYPE;
}

UserDefinedType::UserDefinedType(const UserDefinedType& other)
    : type(other.type),  // This will use GlobalType's copy constructor
    type_name(other.type_name),
    current_scope(other.current_scope),
    is_defined(other.is_defined) {}

void SymbolTable::add_udt(class GlobalType* global_type) {
    switch (global_type->type_tag) {
    case STRUCT_TYPE: {
        udt.push_back(UserDefinedType(global_type->struct_type, current_scope_level));
        break;
    }
    case UNION_TYPE: {
        udt.push_back(UserDefinedType(global_type->union_type, current_scope_level));
        break;
    }
    case ENUM_TYPE: {
        udt.push_back(UserDefinedType(global_type->enum_type, current_scope_level));
        global_type->enum_type->calculate_values(); 
        for(auto &pq : global_type->enum_type->enum_values.elements){
            Identifier* id = new Identifier(pq.name);
            id->type = create_primitive_type(INT_T, global_type->getSpecifiers());
            id->type->setDefined();
            Symbol symbol(*id, current_scope_level, id->type->isDefined());
            std::string name = pq.name;
            symbol_map[name].push_back(symbol);
            SymbolTable::print_symbol(symbol);
            TAC::print_tac(pq.name + " = " + std::to_string(pq.value));  
        }
        break;
    }
    case ARRAY_TYPE: {
        debug_msg("Trying to insert array in user defined types");
    }
    case POINTER_TYPE: {
        debug_msg("Trying to insert pointer in user defined types");
    }
    case FUNCTION_TYPE: {
        debug_msg("Trying to insert function in user defined types");
    }
    default: {
        debug_msg("Trying to insert standard type in user defined types");
    }

    }
}

void SymbolTable::decrement_scope() {

    std::vector<UserDefinedType> new_udt;
    for (auto typ : udt) {
        if (typ.current_scope != current_scope_level) {
            new_udt.push_back(typ);
        }
    }
    udt = new_udt;
}

class GlobalType* SymbolTable::get_global_type(class GlobalType* global_type) {
    switch (global_type->type_tag) {
    case STRUCT_TYPE: {
        for (auto& typ : udt) {
            if (typ.type.type_tag == STRUCT_TYPE) {

                if (typ.type_name == global_type->struct_type->struct_name) {
                    // if it is defined just return it
                    if (typ.is_defined && !global_type->struct_type->is_defined) {
                        debug_msg("Declaration of previously defined struct");

                    }
                    else if (!typ.is_defined && global_type->struct_type->is_defined) {
                        debug_msg("Definition of previously declared struct");
                        typ.type = *(global_type);

                    }

                    return &(typ.type);

                }
            }
        }
        add_udt(global_type);
        return global_type;
    }
    case UNION_TYPE: {

        for (auto& typ : udt) {
            if (typ.type.type_tag == UNION_TYPE) {
                if (typ.type_name == global_type->union_type->union_name) {
                    // if it is defined just return it
                    if (typ.is_defined && !(global_type->union_type->is_defined)) {
                        debug_msg("Declaration of previously defined union");

                    }
                    else if (!(typ.is_defined) && global_type->union_type->is_defined) {
                        debug_msg("Definition of previously declared union");
                        typ.type = *(global_type);

                    }
                    return &(typ.type);

                }
            }
        }
        add_udt(global_type);
        return global_type;
    }
    case ENUM_TYPE: {
        for (auto& typ : udt) {
            if (typ.type.type_tag == ENUM_TYPE) {
                if (typ.type_name == global_type->enum_type->enum_name) {
                    // if it is defined just return it
                    if (typ.is_defined && !(global_type->enum_type->is_defined)) {
                        debug_msg("Declaration of previously defined enum");
                        return &(typ.type);
                    }
                    else if (!(typ.is_defined) && global_type->enum_type->is_defined) {
                        debug_msg("Definition of previously declared enum");
                        typ.type = *(global_type);
                        return global_type;
                    }
                    return global_type;

                }
            }
        }
        add_udt(global_type);
        return global_type;
    }
    case ARRAY_TYPE: {
        debug_msg("Trying to fetch array from user defined types");
    }
    case POINTER_TYPE: {
        debug_msg("Trying to fetch pointer from user defined types");
    }
    case FUNCTION_TYPE: {
        debug_msg("Trying to fetch function from user defined types");
    }
    default: {
        debug_msg("Trying to fetch standard type from user defined types");
    }
    }

    return nullptr;
}

void SymbolTable::print_udt() {
    // Print all structs
    symbol_table_file << udt.size();
}
