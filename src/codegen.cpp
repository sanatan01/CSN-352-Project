#include <codegen.h>
#include <symtab.h>
#include <climits>
#include <string>
#include <algorithm>

namespace backend {

    int CodeGen::current_scope = 0;

    std::stringstream CodeGen::asm_stream;
    std::stringstream CodeGen::data_stream;

    // ================== GPR Functions ==================

    std::map<GPR, Register> gpr_map;

    void init_gpr_map() {
        for (int i = 0; i < 64; ++i) {
            GPR reg = static_cast<GPR>(i);
            gpr_map[reg] = Register();
            gpr_map[reg].reg_name = get_gpr_name(reg);
        }
    }

    void Register::free_reg() {
        value = 0;
        name = "";
    }

    bool Register::is_free() {
        return value == 0;
    }

    GPR temps[10] = { t0, t1, t2, t3, t4, t5, t6, t7, t8, t9 };
    GPR floats[32] = { f0, f1, f2, f3, f4, f5, f6, f7, f8, f9,
                                    f10, f11, f12, f13, f14, f15,
                                    f16, f17, f18, f19, f20, f21,
                                    f22, f23, f24, f25, f26, f27,
                                    f28, f29, f30, f31 };


    GPR empty_strategy_float() {
        for (auto i : floats) {
            Operand op = MMU::get_symbol(gpr_map[i].name);
            if (op.storage_loc != TEMP) {
                store_gpr(i, op.name);
                free_gpr(i);
                return i;
            }
        }
        return empty;
    }

    GPR empty_strategy_double() {
        for (auto i : floats) {
            Operand op = MMU::get_symbol(gpr_map[i].name);
            if (op.storage_loc != TEMP) {
                store_gpr(i, op.name);
                free_gpr(i);
                return i;
            }
        }
        for (int i = 0; i < 32; i += 2) {
            if (gpr_map[floats[i]].is_free() || gpr_map[floats[i + 1]].is_free()) {
                if (gpr_map[floats[i]].is_free()) {
                    Operand op2 = MMU::get_symbol(gpr_map[floats[i + 1]].name);
                    if (op2.storage_loc != TEMP) {
                        store_gpr(floats[i + 1], op2.name);
                        free_gpr(floats[i + 1]);
                        return floats[i];
                    }
                }
                if (gpr_map[floats[i + 1]].is_free()) {
                    Operand op2 = MMU::get_symbol(gpr_map[floats[i]].name);
                    if (op2.storage_loc != TEMP) {
                        store_gpr(floats[i], op2.name);
                        free_gpr(floats[i]);
                        return floats[i];
                    }
                }
                continue;
            }

            Operand op1 = MMU::get_symbol(gpr_map[floats[i]].name);
            Operand op2 = MMU::get_symbol(gpr_map[floats[i + 1]].name);
            if (op1.storage_loc != TEMP && op2.storage_loc != TEMP) {
                store_gpr(floats[i], op1.name);
                store_gpr(floats[i + 1], op2.name);
                free_gpr(floats[i]);
                free_gpr(floats[i + 1]);
                return floats[i];
            }
        }
        return empty;
    }

    GPR empty_strategy_gpr() {
        for (auto i : temps) {
            Operand op = MMU::get_symbol(gpr_map[i].name);
            if (op.storage_loc != TEMP) {
                store_gpr(i, op.name);
                free_gpr(i);
                return i;
            }
        }
        return empty;
    }

    bool is_float(GlobalType typ) {
        if (typ.type_tag == STANDARD_TYPE) {
            if (typ.standard_type->name == "float" ||
                typ.standard_type->name == "double" ||
                typ.standard_type->name == "long double") {
                return true;
            }
        }
        return false;
    }

    void load_gpr(GPR reg, Operand op) {
        switch (op.storage_loc) {
        case TEMP:
            break;
        case STACK:
        {
            int offset = MMU::get_offset(op.name);
            if (offset != -1) {
                if (is_float(op.type)) {
                    if (op.size == 8) {
                        add_to_asm("ldc1 " + get_gpr_name(reg) + ", " + std::to_string(offset) + "($sp)\n", true);
                        gpr_map[reg].value = 1;
                        gpr_map[reg].name = op.name;
                        gpr_map[static_cast<GPR>(int(reg) + 1)].value = 1;
                        gpr_map[static_cast<GPR>(int(reg) + 1)].name = op.name;
                    }
                    else if (op.size == 4) {
                        add_to_asm("lwc1 " + get_gpr_name(reg) + ", " + std::to_string(offset) + "($sp)\n", true);
                        gpr_map[reg].value = 1;
                        gpr_map[reg].name = op.name;
                    }
                }
                else {
                    add_to_asm("la " + gpr_map[reg].reg_name + ", " + std::to_string(offset) + "($sp)\n", true);
                }
            }
            else {
                error_msg("Invalid stack offset, found -1");
                return;
            }
        }
        break;
        case DATA:
        {
            if (is_float(op.type)) {
                if (op.size == 8) {
                    add_to_asm("la " + get_gpr_name(s0) + ", " + convert_to_valid(op.name) + "\n", true);
                    add_to_asm("ldc1 " + get_gpr_name(reg) + ", 0(" + get_gpr_name(s0) + ")\n", true);
                    gpr_map[reg].value = 1;
                    gpr_map[reg].name = op.name;
                    gpr_map[static_cast<GPR>(int(reg) + 1)].value = 1;
                    gpr_map[static_cast<GPR>(int(reg) + 1)].name = op.name;
                    free_gpr(s0);
                }
                else if (op.size == 4) {
                    add_to_asm("la " + get_gpr_name(s0) + ", " + convert_to_valid(op.name) + "\n", true);
                    add_to_asm("lwc1 " + get_gpr_name(reg) + ", 0(" + get_gpr_name(s0) + ")\n", true);
                    gpr_map[reg].value = 1;
                    gpr_map[reg].name = op.name;
                    free_gpr(s0);
                }
            }
            else {
                add_to_asm("la " + gpr_map[reg].reg_name + ", " + convert_to_valid(op.name) + "\n", true);
            }
        }
        break;
        }
    }

    GPR get_free_gpr(Operand op) {

        if (is_float(op.type)) {

            if (op.size == 8) {
                for (int i = 0; i < 32; i += 2) {
                    if (gpr_map[floats[i]].is_free() && gpr_map[floats[i + 1]].is_free()) {
                        load_gpr(floats[i], op);
                        return floats[i];
                    }
                }
                GPR ret = empty_strategy_double();
                load_gpr(ret, op);
                return ret;
            }
            else {
                for (int i = 0; i < 32; ++i) {
                    if (gpr_map[floats[i]].is_free()) {
                        load_gpr(floats[i], op);
                        return floats[i];
                    }
                }

                GPR ret = empty_strategy_float();
                load_gpr(ret, op);
                return ret;
            };
        }

        for (int i = 0; i < 10; ++i) {
            if (gpr_map[temps[i]].is_free()) {
                load_gpr(temps[i], op);
                return temps[i];
            }
        }
        GPR ret = empty_strategy_gpr();
        load_gpr(ret, op);
        return ret;
    }


    void set_gpr(GPR reg, std::string name) {
        gpr_map[reg].value = 1;
        gpr_map[reg].name = name;
    }

    void free_gpr(GPR reg) {
        gpr_map[reg].free_reg();
    }

    std::string convert_to_valid(std::string name) {
        // Change all '.' with '_'
        std::string valid_name = name;
        std::replace(valid_name.begin(), valid_name.end(), '.', '_');
        return valid_name;
    }

    void store_gpr(GPR reg, std::string name) {
        Operand op = MMU::get_symbol(name);
        switch (op.storage_loc) {
        case TEMP:
            break;
        case STACK:
        {
            int offset = MMU::get_offset(name);
            if (offset != -1) {
                add_to_asm("sw " + gpr_map[reg].reg_name + ", " + std::to_string(offset) + "($sp)\n", true);
            }
            else {
                error_msg("Invalid stack offset, found -1");
                return;
            }
        }
        break;
        case DATA:
        {
            add_to_asm("sw " + gpr_map[reg].reg_name + ", " + convert_to_valid(gpr_map[reg].name) + "\n", true);
        }
        break;
        }
    }

    GPR get_assigned_gpr(std::string name) {
        for (int i = 0; i < 10; ++i) {
            if (gpr_map[temps[i]].name == name) {
                return temps[i];
            }
        }
        return empty;
    }

    GPR get_gpr(Operand op) {
        for (int i = 0;i < 64;i++) {
            if (gpr_map[(GPR)i].name == op.name) {
                return (GPR)i;
            }
        }
        return get_free_gpr(op);
    }

    // ================== MMU Variables ==================

    std::vector<Operand> MMU::stack;
    std::map<std::string, Operand> MMU::symbol_map;

    // ================== MMU Functions ==================

    void MMU::push(Operand op) {
        stack.push_back(op);
    }

    void MMU::pop(int size) {
        int del_size = 0;
        while (del_size < size && !stack.empty()) {
            del_size += stack.back().size;
            stack.pop_back();
        }

        if (del_size != size) {
            error_msg("Invalid stack pop size");
        }
    }

    int MMU::get_offset(std::string name) {
        int offset = 0;
        for (int i = stack.size() - 1; i >= 0; --i) {
            if (stack[i].name == name) {
                return offset;
            }
            offset += stack[i].size;
        }

        return -1; // Not found
    }

    // ================== Symbol Map Functions ==================

    // Add symbol from the symbol table
    bool MMU::add_symbol(std::string name, int index) {
        Symbol symbol = SymbolTable::get_symbol_by_index(index);
        Operand op = Operand();
        op.name = symbol.identifier.name;
        if (name != op.name) {
            error_msg("Symbol name mismatch");
            return false;
        }
        op.size = symbol.identifier.type->getSize();
        op.type = GlobalType(*symbol.identifier.type);
        op.is_constant = false;

        switch (op.type.type_tag) {
        case STANDARD_TYPE:
        case ARRAY_TYPE:
        case STRUCT_TYPE:
        case UNION_TYPE:
        case ENUM_TYPE:
        case POINTER_TYPE:
            symbol_map[name] = op;
            return true;
        default:
            error_msg("Invalid symbol type");
            return false;
        }
    }

    // Add a temporary into the symbol table
    bool MMU::add_symbol(std::string name, int sz, GlobalType type) {
        Operand op = Operand();
        op.name = name;
        op.size = sz;
        op.type = type;
        op.is_constant = false;

        symbol_map[name] = op;
        return true;
    }

    bool MMU::is_symbol_present(std::string name) {
        return symbol_map.find(name) != symbol_map.end();
    }

    Operand MMU::get_symbol(std::string name) {
        if (symbol_map.find(name) != symbol_map.end()) {
            return symbol_map[name];
        }
        error_msg("Symbol not found in symbol map");
        return Operand(); // Not found
    }

    int MMU::get_symbol_size(std::string name) {
        if (symbol_map.find(name) != symbol_map.end()) {
            return symbol_map[name].size;
        }
        error_msg("Symbol not found in symbol map");
        return -1; // Not found
    }

    GlobalType* MMU::get_symbol_type(std::string name) {
        if (symbol_map.find(name) != symbol_map.end()) {
            return &symbol_map[name].type;
        }
        return nullptr; // Not found
    }


    // ================== Quad Functions ==================


    // ================== CodeGen Functions ==================

    std::vector<GPR> CodeGen::get_used_gprs(const TACStatement& statement) {
        std::vector<GPR> used_gprs;

        // We dont need variables for certain statements we can skip
        if (statement.get_type() == COMMON) {
            const CommonStatement* common_statement = dynamic_cast<const CommonStatement*>(&statement);
            if (common_statement->type == GOTO_St || common_statement->type == POP_St || common_statement->type == FUNC_St ||
                common_statement->type == LABEL_St || common_statement->type == ENTER_St || common_statement->type == EXIT_St) {
                return used_gprs;
            }
            else if (common_statement->type == RETURN_St) {
                if (statement.operands.size() == 1 && !statement.operands[0].is_constant) {
                    GPR reg = get_assigned_gpr(statement.operands[0].name);
                    if (reg != empty) {
                        used_gprs.push_back(reg);
                    }
                    else {
                        GPR reg = get_free_gpr();
                        set_gpr(reg, statement.operands[0].name);
                        output_msg("Assigned " + statement.operands[0].name + " to " + get_gpr_name(reg));
                        used_gprs.push_back(reg);
                    }
                }
            }
        }
        else if (statement.get_type() == VARIABLE) {
            const VariableStatement* var_statement = dynamic_cast<const VariableStatement*>(&statement);
            if (var_statement->type == LOCAL_St || var_statement->type == GLOBAL_St) {
                if (statement.operands.size() == 3 && !statement.operands[1].is_constant) {
                    GPR reg = get_assigned_gpr(statement.operands[1].name);
                    if (reg != empty) {
                        used_gprs.push_back(reg);
                    }
                    else {
                        GPR reg = get_free_gpr();
                        set_gpr(reg, statement.operands[1].name);
                        output_msg("Assigned " + statement.operands[1].name + " to " + get_gpr_name(reg));
                        used_gprs.push_back(reg);
                    }
                }
                GPR reg = get_assigned_gpr(statement.operands.back().name);
                if (reg != empty) {
                    used_gprs.push_back(reg);
                }
                else {
                    GPR reg = get_free_gpr();
                    set_gpr(reg, statement.operands.back().name);
                    output_msg("Assigned " + statement.operands.back().name + " to " + get_gpr_name(reg));
                    used_gprs.push_back(reg);
                }
            }
            else if (var_statement->type == STATIC_St) {
                GPR reg = get_assigned_gpr(statement.operands.back().name);
                if (reg != empty) {
                    used_gprs.push_back(reg);
                }
                else {
                    GPR reg = get_free_gpr();
                    set_gpr(reg, statement.operands.back().name);
                    output_msg("Assigned " + statement.operands.back().name + " to " + get_gpr_name(reg));
                    used_gprs.push_back(reg);
                }
            }
            return used_gprs;
        }

        for (const auto& operand : statement.operands) {
            if (operand.is_constant) {
                continue;
            }

            GPR reg = get_assigned_gpr(operand.name);
            if (reg == empty) {
                GPR reg = get_free_gpr();
                if (reg != empty) {
                    set_gpr(reg, operand.name);
                    output_msg("Assigned " + operand.name + " to " + get_gpr_name(reg));
                    used_gprs.push_back(reg);
                }
                else {
                    output_msg("No free registers available for " + operand.name);
                    error_msg("No free registers available");
                }
            }
            else {
                used_gprs.push_back(reg);
            }
        }

        return used_gprs;
    }



    std::stringstream CodeGen::generate_asm(const TACStatement& statement, std::vector<GPR>& used_gprs) {
        std::stringstream asm_stream;

        // if (statement.get_type() == COMMON) {
        //     const CommonStatement* common_statement = dynamic_cast<const CommonStatement*>(&statement);
        //     switch (common_statement->type) {
        //     case POP_St:
        //     {
        //         if (statement.operands.size() != 1) {
        //             error_msg("Invalid number of operands for POP statement");
        //             return asm_stream;
        //         }
        //         // Fetch the operands
        //         int sz = std::stoi(statement.operands[0].name);
        //         MMU::pop(sz);
        //         asm_stream << generate_asm_str("addi $sp, $sp, " + std::to_string(sz) + "\n");
        //         break;
        //     }
        //     case FUNC_St:
        //         if (current_scope == 1) {

        //             asm_stream << generate_asm_str(".globl " + statement.labels[0].name + "\n", false);
        //             asm_stream << generate_asm_str(statement.labels[0].name + ":\n", false);
        //             break;
        //         }
        //     case LABEL_St:
        //     {
        //         if (statement.labels.size() != 1) {
        //             error_msg("Invalid number of operands for FUNC/LABEL statement");
        //             return asm_stream;
        //         }
        //         // Fetch the operands
        //         std::string label = statement.labels[0].name;
        //         asm_stream << "\n"
        //             << label << ":\n";
        //         break;
        //     }
        //     case ENTER_St:
        //         current_scope++;
        //         break;

        //     case EXIT_St:
        //         current_scope--;
        //         break;

        //     case GOTO_St:
        //     {
        //         if (statement.labels.size() != 1) {
        //             error_msg("Invalid number of operands for GOTO statement");
        //             return asm_stream;
        //         }
        //         // Fetch the operands
        //         std::string label = statement.labels[0].name;
        //         asm_stream << generate_asm_str("j " + label + '\n');
        //         break;
        //     }
        //     default:
        //         asm_stream << "Not yet generated assembly for " << get_type_name(common_statement->type) << "\n";
        //         break;
        //     }
        // }
        // else if (statement.get_type() == VARIABLE) {
        //     const VariableStatement* var_statement = dynamic_cast<const VariableStatement*>(&statement);
        //     switch (var_statement->type) {
        //     case LOCAL_St:
        //     {
        //         if (statement.operands.size() == 2) {
        //             // Fetch the operands

        //             if (MMU::add_symbol(statement.operands[0].name, std::stoi(statement.operands[1].name))) {
        //                 Operand op = Operand();
        //                 op.name = statement.operands[0].name;
        //                 op.size = MMU::get_symbol_size(statement.operands[0].name);
        //                 op.type = MMU::get_symbol_type(statement.operands[0].name);
        //                 MMU::push(op);
        //                 asm_stream << generate_asm_str("addi $sp, $sp, -" + std::to_string(op.size) + '\n');
        //             }
        //             else {
        //                 error_msg("Failed to add symbol to stack");
        //             }
        //         }
        //         else if (statement.operands.size() == 3) {
        //             if (MMU::add_symbol(statement.operands[0].name, std::stoi(statement.operands[2].name))) {
        //                 Operand op = Operand();
        //                 op.name = statement.operands[0].name;
        //                 op.size = MMU::get_symbol_size(statement.operands[0].name);
        //                 op.type = MMU::get_symbol_type(statement.operands[0].name);
        //                 MMU::push(op);
        //                 asm_stream << generate_asm_str("addi $sp, $sp, -" + std::to_string(op.size) + '\n');
        //             }
        //             else {
        //                 error_msg("Failed to add symbol to stack");
        //             }
        //         }
        //         else {
        //             error_msg("Invalid number of operands for LOCAL statement");
        //             return asm_stream;
        //         }
        //         break;
        //     }
        //     default:
        //         asm_stream << "Not yet generated assembly for \n";
        //         break;
        //     }
            // case GLOBAL_St:
            // {
            //     if (statement.operands.size() != 2)
            //     {
            //         error_msg("Invalid number of operands for LOCAL statement");
            //         return asm_stream;
            //     }
            //     // Fetch the operands
            //     if (MMU::add_symbol(statement.operands[0].name, std::stoi(statement.operands[1].name)))
            //     {
            //         Operand op = Operand();
            //         op.name = statement.operands[0].name;
            //         op.size = MMU::get_symbol_size(statement.operands[0].name);
            //         op.type = MMU::get_symbol_type(statement.operands[0].name);
            //         MMU::push(op);
            //         asm_stream << "addi $sp, $sp, -" << op.size << "\n";
            //     }
            //     else
            //     {
            //         error_msg("Failed to add symbol to stack");
            //     }
            //     break;
            // }
            // }
        // }
        // else {
        //     asm_stream << "Not yet generated assembly for " << get_type_name(statement.get_type()) << "\n";
        // }

        return asm_stream;
    }

    std::stringstream CodeGen::generate_data(const TACStatement& statement) {
        std::stringstream data_stream;

        // switch (statement.get_type()) {
        // case VARIABLE:
        // {
        //     const VariableStatement* var_statement = dynamic_cast<const VariableStatement*>(&statement);
        //     switch (var_statement->type) {
        //     case GLOBAL_St:
        //     case STATIC_St:
        //     {
        //         if (statement.operands.size() == 2) {
        //             // Fetch the operands

        //             if (MMU::add_symbol(statement.operands[0].name, std::stoi(statement.operands[1].name))) {
        //                 Operand op = Operand();
        //                 op.name = statement.operands[0].name;
        //                 op.size = MMU::get_symbol_size(statement.operands[0].name);
        //                 op.type = MMU::get_symbol_type(statement.operands[0].name);
        //                 switch (op.type) {
        //                 case UNSIGNED:
        //                 case SIGNED:
        //                 case STRUCT:
        //                 case UNION:
        //                 case POINTER:
        //                 {
        //                     data_stream << data_str(statement.operands[0].name, op.size, true, 0) + '\n';
        //                     break;
        //                 }
        //                 case FLOAT:
        //                 {
        //                     data_stream << data_str_float(statement.operands[0].name, op.size, true, 0.0) + '\n';
        //                     break;
        //                 }
        //                 }
        //             }
        //             else {
        //                 error_msg("Failed to add symbol to stack");
        //             }
        //         }
        //     }
        //     }
        //     break;
        // }
        // default:
        //     break;
        // }

        return data_stream;
    }

    std::string generate_asm_str(std::string txt, bool indent) {
        if (indent) {
            return "\t\t" + txt;
        }
        return txt;
    }


    std::string data_str(std::string name, int size, bool is_assigned, long long val) {
        std::string data = name + ":\t";
        // Add padding to create consistent column alignment
        if (name.length() < 8) data += "\t";

        if (!is_assigned) {
            // If not assigned, just allocate space
            data += ".space " + std::to_string(size);
            return data;
        }

        // Handle initialized values
        switch (size) {
        case 1:
            data += ".byte\t" + std::to_string(val);
            break;
        case 2:
            data += ".half\t" + std::to_string(val);
            break;
        case 4:
            data += ".word\t" + std::to_string(val);
            break;
        case 8:
            data += ".dword\t" + std::to_string(val);
            break;
        default:
            data += ".space\t" + std::to_string(size);
            break;
        }
        return data;
    }

    std::string data_str_float(std::string name, int size, bool is_assigned, long double val) {
        std::string data = name + ":\t";
        // Add padding to create consistent column alignment
        if (name.length() < 8) data += "\t";

        if (!is_assigned) {
            // If not assigned, just allocate space
            data += ".space " + std::to_string(size);
            return data;
        }

        // Handle initialized values
        switch (size) {
        case 4:
            data += ".float\t" + std::to_string(val);
            break;
        case 8:
            data += ".double\t" + std::to_string(val);
            break;
        default:
            data += ".space\t" + std::to_string(size);
            break;
        }
        return data;
    }

    static void add_to_asm(std::string txt, bool indent) {
        if (indent) {
            CodeGen::asm_stream << "\t\t" + txt;
        }
        CodeGen::asm_stream << txt;
    };
    static void add_to_data(std::string txt, bool indent) {
        if (indent) {
            CodeGen::data_stream << "\t\t" + txt;
        }
        CodeGen::data_stream << txt;
    }
    static std::stringstream& get_asm_stream() {
        return CodeGen::asm_stream;
    }
    static std::stringstream& get_data_stream() {
        return CodeGen::data_stream;
    }

    std::pair<std::string, std::string> getHighLowBytes(const std::string& decimalStr) {
        // Convert the decimal string to an integer (assuming it fits in an int)
        long long num = std::stoll(decimalStr);  // Use stoll to handle large numbers

        // Extract low 4 bytes (least significant 32 bits)
        unsigned int lowWord = static_cast<unsigned int>(num & 0xFFFFFFFF);  // Mask to get low 4 bytes

        // Extract high 4 bytes (most significant 32 bits)
        unsigned int highWord = static_cast<unsigned int>((num >> 32) & 0xFFFFFFFF);  // Shift right by 32 bits and mask

        // Convert the high and low words to strings (in hex format)
        std::stringstream lowStream, highStream;
        lowStream << std::hex << std::setw(8) << std::setfill('0') << lowWord;
        highStream << std::hex << std::setw(8) << std::setfill('0') << highWord;

        // Return the high and low bytes as hex strings
        return { highStream.str(), lowStream.str() };
    }

    std::pair<std::string, std::string> floatToIEEEHex(const std::string& inputStr, bool isDouble) {
        // Check if the input string is a valid float or double
        double num = std::stod(inputStr);  // Convert string to double first (handles floats and doubles)

        if (isDouble) {
            // Double precision (64-bit) IEEE 754
            uint64_t ieeeRepresentation = *reinterpret_cast<uint64_t*>(&num);  // Cast the double to its IEEE 754 representation

            // Extract the high and low parts (64-bit -> two 32-bit parts)
            uint32_t highPart = static_cast<uint32_t>((ieeeRepresentation >> 32) & 0xFFFFFFFF);  // Upper 32 bits
            uint32_t lowPart = static_cast<uint32_t>(ieeeRepresentation & 0xFFFFFFFF);  // Lower 32 bits

            // Convert to hex
            std::stringstream highStream, lowStream;
            highStream << std::hex << std::setw(8) << std::setfill('0') << highPart;
            lowStream << std::hex << std::setw(8) << std::setfill('0') << lowPart;

            // Return the high and low parts
            return { highStream.str(), lowStream.str() };
        }
        else {
            // Single precision (32-bit) IEEE 754
            uint32_t ieeeRepresentation = *reinterpret_cast<uint32_t*>(&num);  // Cast the float to its IEEE 754 representation

            // Convert to hex
            std::stringstream singleStream;
            singleStream << std::hex << std::setw(8) << std::setfill('0') << ieeeRepresentation;

            // Return the single precision hex representation
            return { singleStream.str(), "" };  // Only return the high part for single precision
        }
    }

}