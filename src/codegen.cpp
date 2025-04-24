#include <codegen.h>
#include <symtab.h>

namespace backend {

    int CodeGen::current_scope = 0;

    // ================== GPR Functions ==================

    std::map<GPR, Register> gpr_map;

    void init_gpr_map() {
        for (int i = 0; i < 32; ++i) {
            GPR reg = static_cast<GPR>(i);
            gpr_map[reg] = Register();
            gpr_map[reg].reg_name = get_gpr_name(reg);
        }
    }

    std::string get_gpr_name(GPR reg) {
        switch (reg) {
        case r0:
            return "$zero";
        case at:
            return "$at";
        case v0:
            return "$v0";
        case v1:
            return "$v1";
        case a0:
            return "$a0";
        case a1:
            return "$a1";
        case a2:
            return "$a2";
        case a3:
            return "$a3";
        case t0:
            return "$t0";
        case t1:
            return "$t1";
        case t2:
            return "$t2";
        case t3:
            return "$t3";
        case t4:
            return "$t4";
        case t5:
            return "$t5";
        case t6:
            return "$t6";
        case t7:
            return "$t7";
        case s0:
            return "$s0";
        case s1:
            return "$s1";
        case s2:
            return "$s2";
        case s3:
            return "$s3";
        case s4:
            return "$s4";
        case s5:
            return "$s5";
        case s6:
            return "$s6";
        case s7:
            return "$s7";
        case t8:
            return "$t8";
        case t9:
            return "$t9";
        case k0:
            return "$k0";
        case k1:
            return "$k1";
        case gp:
            return "$gp";
        case sp:
            return "$sp";
        case fp:
            return "$fp";
        case ra:
            return "$ra";
        default:
            return "empty";
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

    GPR get_free_gpr() {
        for (int i = 0; i < 10; ++i) {
            if (gpr_map[temps[i]].is_free()) {
                return temps[i];
            }
        }
        return empty;
    }

    void set_gpr(GPR reg, std::string name) {
        if(reg == empty) {
            error_msg("Invalid register");
            return;
        }
        if (gpr_map[reg].is_free()) {
            gpr_map[reg].value = 1;
            gpr_map[reg].name = name;
        }
        else {

            error_msg("Register already assigned");
        }
    }

    void free_gpr(GPR reg) {
        gpr_map[reg].free_reg();
    }

    GPR get_assigned_gpr(std::string name) {
        for (int i = 0; i < 10; ++i) {
            if (gpr_map[temps[i]].name == name) {
                return temps[i];
            }
        }
        return empty;
    }

    // ================== Stack Variables ==================

    std::vector<Operand> Stack::stack;
    std::map<std::string, Operand> Stack::symbol_map;

    // ================== Stack Functions ==================

    void Stack::push(Operand op) {
        stack.push_back(op);
    }

    void Stack::pop(int size) {
        int del_size = 0;
        while (del_size < size && !stack.empty()) {
            del_size += stack.back().size;
            stack.pop_back();
        }

        if (del_size != size) {
            error_msg("Invalid stack pop size");
        }
    }

    int Stack::get_offset(std::string name) {
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
    bool Stack::add_symbol(std::string name, int index) {
        Symbol symbol = SymbolTable::get_symbol_by_index(index);
        Operand op = Operand();
        op.name = symbol.identifier.name;
        if (name != op.name) {
            error_msg("Symbol name mismatch");
            return false;
        }
        op.size = symbol.identifier.type->getSize();

        bool ret_value;

        switch (symbol.identifier.type->type_tag) {
        case STRUCT_TYPE:
            op.type = STRUCT;
            ret_value = true;
            break;
        case UNION_TYPE:
            op.type = UNION;
            ret_value = true;
            break;
        case ENUM_TYPE:
            op.type = SIGNED;
            ret_value = true;
            break;
        case POINTER_TYPE:
            op.type = POINTER;
            ret_value = true;
            break;
        case FUNCTION_TYPE:
            error_msg("Function type not allowed in symbol map");
            break;
        case ARRAY_TYPE:
            op.type = POINTER;
            ret_value = true;
            break;
        case STANDARD_TYPE:
            if (symbol.identifier.type->standard_type->name.find("bool") != std::string::npos) {
                op.type = UNSIGNED;
            }
            else if (symbol.identifier.type->standard_type->name.find("unsigned") != std::string::npos) {
                op.type = UNSIGNED;
            }
            else if (symbol.identifier.type->standard_type->name.find("float") != std::string::npos || symbol.identifier.type->standard_type->name.find("double") != std::string::npos) {
                op.type = FLOAT;
            }
            else {
                op.type = SIGNED;
            }
            ret_value = true;
            break;
        default:
            error_msg("Unknown type in symbol map");
            ret_value = false;
        }

        if (ret_value) {
            symbol_map[name] = op;
            return true;
        }
        else {
            error_msg("Failed to add symbol to stack");
            return false;
        }
    }

    // Add a temporary into the symbol table
    bool Stack::add_symbol(std::string name, int sz, OpType type) {
        Operand op = Operand();
        op.name = name;
        op.size = sz;
        op.type = type;

        symbol_map[name] = op;
        return true;
    }

    bool Stack::is_symbol_present(std::string name) {
        return symbol_map.find(name) != symbol_map.end();
    }

    int Stack::get_symbol_size(std::string name) {
        if (symbol_map.find(name) != symbol_map.end()) {
            return symbol_map[name].size;
        }
        error_msg("Symbol not found in symbol map");
        return -1; // Not found
    }

    OpType Stack::get_symbol_type(std::string name) {
        if (symbol_map.find(name) != symbol_map.end()) {
            return symbol_map[name].type;
        }
        return SIGNED; // Default type
    }

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
        }
        else if (statement.get_type() == VARIABLE) {
            const VariableStatement* var_statement = dynamic_cast<const VariableStatement*>(&statement);
            return used_gprs;
        }

        for (const auto& operand : statement.operands) {
            if (operand.type == CONSTANT) {
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

        if (statement.get_type() == COMMON) {
            const CommonStatement* common_statement = dynamic_cast<const CommonStatement*>(&statement);
            switch (common_statement->type) {
            case POP_St:
            {
                if (statement.operands.size() != 1) {
                    error_msg("Invalid number of operands for POP statement");
                    return asm_stream;
                }
                // Fetch the operands
                int sz = std::stoi(statement.operands[0].name);
                Stack::pop(sz);
                asm_stream << generate_asm_str("addi $sp, $sp, " + std::to_string(sz) + "\n");
                break;
            }
            case FUNC_St:
                if (current_scope == 1) {

                    asm_stream << generate_asm_str(".globl " + statement.labels[0].name + "\n", false);
                    asm_stream << generate_asm_str(statement.labels[0].name + ":\n", false);
                    break;
                }
            case LABEL_St:
            {
                if (statement.labels.size() != 1) {
                    error_msg("Invalid number of operands for FUNC/LABEL statement");
                    return asm_stream;
                }
                // Fetch the operands
                std::string label = statement.labels[0].name;
                asm_stream << "\n"
                    << label << ":\n";
                break;
            }
            case ENTER_St:
                current_scope++;
                break;

            case EXIT_St:
                current_scope--;
                break;

            case GOTO_St:
            {
                if (statement.labels.size() != 1) {
                    error_msg("Invalid number of operands for GOTO statement");
                    return asm_stream;
                }
                // Fetch the operands
                std::string label = statement.labels[0].name;
                asm_stream << generate_asm_str("j " + label + '\n');
                break;
            }
            case PARAM_St:
            {
                if (statement.operands.size() != 1) {
                    error_msg("Invalid number of operands for PARAM statement");
                    return asm_stream;
                }
                // Fetch the operands
                Operand param = statement.operands[0];
                // TODO: check if argument registers are full
                if (param.type == CONSTANT) {
                    // TODO: use argument registers
                    asm_stream << generate_asm_str("li $a0, " + param.name + '\n');
                }
                // TODO: add other types
                else if (param.type == SIGNED) {
                    // TODO: check if already in some register
                    asm_stream << generate_asm_str("mov $a0, " + param.name + '\n');
                }
                break;
            }
            default:
                asm_stream << "Not yet generated assembly for " << get_type_name(common_statement->type) << "\n";
                break;
            }
        }
        else if (statement.get_type() == VARIABLE) {
            const VariableStatement* var_statement = dynamic_cast<const VariableStatement*>(&statement);
            switch (var_statement->type) {
            case LOCAL_St:
            {
                if (statement.operands.size() == 2) {
                    // Fetch the operands
                    if (Stack::add_symbol(statement.operands[0].name, std::stoi(statement.operands[1].name))) {
                        Operand op = Operand();
                        op.name = statement.operands[0].name;
                        op.size = Stack::get_symbol_size(statement.operands[0].name);
                        op.type = Stack::get_symbol_type(statement.operands[0].name);
                        Stack::push(op);
                        asm_stream << generate_asm_str("addi $sp, $sp, -" + std::to_string(op.size) + '\n');

                    }
                    else {
                        error_msg("Failed to add symbol to stack");
                    }
                }
                else if (statement.operands.size() == 3) {
                    if (Stack::add_symbol(statement.operands[0].name, std::stoi(statement.operands[2].name))) {
                        Operand op = Operand();
                        op.name = statement.operands[0].name;
                        op.size = Stack::get_symbol_size(statement.operands[0].name);
                        op.type = Stack::get_symbol_type(statement.operands[0].name);
                        Stack::push(op);
                        asm_stream << generate_asm_str("addi $sp, $sp, -" + std::to_string(op.size) + '\n');
                    }
                    else {
                        error_msg("Failed to add symbol to stack");
                    }
                }
                else {
                    error_msg("Invalid number of operands for LOCAL statement");
                    return asm_stream;
                }
                break;
            }
            default:
                asm_stream << "Not yet generated assembly for \n";
                break;
            }
            // case GLOBAL_St:
            // {
            //     if (statement.operands.size() != 2)
            //     {
            //         error_msg("Invalid number of operands for LOCAL statement");
            //         return asm_stream;
            //     }
            //     // Fetch the operands
            //     if (Stack::add_symbol(statement.operands[0].name, std::stoi(statement.operands[1].name)))
            //     {
            //         Operand op = Operand();
            //         op.name = statement.operands[0].name;
            //         op.size = Stack::get_symbol_size(statement.operands[0].name);
            //         op.type = Stack::get_symbol_type(statement.operands[0].name);
            //         Stack::push(op);
            //         asm_stream << "addi $sp, $sp, -" << op.size << "\n";
            //     }
            //     else
            //     {
            //         error_msg("Failed to add symbol to stack");
            //     }
            //     break;
            // }
            // }
        }
        else if (statement.get_type() == DOUBLE) {
            const Double* double_statement = dynamic_cast<const Double*>(&statement);
            if (double_statement->operands.size() != 2) {
                error_msg("Invalid number of operands for DOUBLE statement, STRING_LITERAL not handled yet");
                return asm_stream;
            }

            Operand op = double_statement->operands[0];
            Operand result = double_statement->operands[1];
            bool imm = false;
            if (op.type == CONSTANT) {
                imm = true;
            }
            GPR result_reg = get_assigned_gpr(result.name);
            GPR op_reg = get_assigned_gpr(op.name);
            if (result_reg == empty) {
                result_reg = get_free_gpr();
                if (result_reg != empty) {
                    set_gpr(result_reg, result.name);
                }
                else {
                    error_msg("No free registers available");
                }
            }

            if (imm) {
                asm_stream << generate_asm_str("li " + get_gpr_name(result_reg) + ", " + op.name + '\n');
            }
            else {
                // TODO: check if op_reg is empty load it again , if no register is already allocated
                asm_stream << generate_asm_str("mov " + get_gpr_name(result_reg) + ", " + get_gpr_name(op_reg) + '\n');
            }
        }else if (statement.get_type() == QUAD) {
            const Quad* quad_statement = dynamic_cast<const Quad*>(&statement);
            if (quad_statement->operands.size() != 3) {
                error_msg("Invalid number of operands for QUAD statement");
                return asm_stream;
            }
            Operand op1 = quad_statement->operands[0];
            Operand op2 = quad_statement->operands[1];
            Operand result = quad_statement->operands[2];

            BinaryOp op = quad_statement->op;
            bool imm=false;
            GPR result_reg = get_assigned_gpr(result.name);
            GPR op1_reg = get_assigned_gpr(op1.name);
            GPR op2_reg = get_assigned_gpr(op2.name);
            if (result_reg == empty) {
                result_reg = get_free_gpr();
                if (result_reg != empty) {
                    set_gpr(result_reg, result.name);
                }
                else {
                    error_msg("No free registers available");
                }
            }
            if (op1.type != CONSTANT && op1_reg == empty) {
                error_msg(op1.name + " not assigned to a register");
            }
            if (op2.type != CONSTANT && op2_reg == empty) {
                error_msg(op2.name + " not assigned to a register");
            }
            if(op1.type == CONSTANT || op2.type == CONSTANT) {
                imm = true;
            }
            
            switch (op) {
            case ADD:
                if(imm) {
                    if(op1.type == CONSTANT) {
                        asm_stream << generate_asm_str("addi " + get_gpr_name(result_reg) + ", " + get_gpr_name(op2_reg) + ", " + op1.name + '\n');
                    }
                    else {
                        asm_stream << generate_asm_str("addi " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + op2.name + '\n');
                    }
                }
                else {
                    asm_stream << generate_asm_str("add " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + get_gpr_name(op2_reg) + '\n');
                }
                break;
            case SUB:
                if(imm) {
                    if(op1.type == CONSTANT) {
                        asm_stream << generate_asm_str("subi " + get_gpr_name(result_reg) + ", " + get_gpr_name(op2_reg) + ", " + op1.name + '\n');
                    }
                    else {
                        asm_stream << generate_asm_str("subi " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + op2.name + '\n');
                    }
                }
                else {
                    asm_stream << generate_asm_str("sub " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + get_gpr_name(op2_reg) + '\n');
                }
                break;
            case MUL:
                if(imm) {
                    error_msg("Multiplication with immediate value not supported");
                }else{
                    asm_stream << generate_asm_str("mul " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + get_gpr_name(op2_reg) + '\n');
                }
                break;
            case LOGICAL_AND:
                if (imm) {
                    if(op1.type == CONSTANT) {
                        asm_stream << generate_asm_str("andi " + get_gpr_name(result_reg) + ", " + get_gpr_name(op2_reg) + ", " + op1.name + '\n');
                    }
                    else {
                        asm_stream << generate_asm_str("andi " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + op2.name + '\n');
                    }
                }
                else {
                    asm_stream << generate_asm_str("and " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + get_gpr_name(op2_reg) + '\n');
                }
                break;
            case LOGICAL_OR:
                 if (imm) {
                    if(op1.type == CONSTANT) {
                        asm_stream << generate_asm_str("andi " + get_gpr_name(result_reg) + ", " + get_gpr_name(op2_reg) + ", " + op1.name + '\n');
                    }
                    else {
                        asm_stream << generate_asm_str("andi " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + op2.name + '\n');
                    }
                }
                else {
                    asm_stream << generate_asm_str("or " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + get_gpr_name(op2_reg) + '\n');
                }
                break;
            case BITWISE_XOR:
                if (imm) {
                    if(op1.type == CONSTANT) {
                        asm_stream << generate_asm_str("xori " + get_gpr_name(result_reg) + ", " + get_gpr_name(op2_reg) + ", " + op1.name + '\n');
                    }
                    else {
                        asm_stream << generate_asm_str("xori " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + op2.name + '\n');
                    }
                }else{
                    asm_stream << generate_asm_str("xor " + get_gpr_name(result_reg) + ", " + get_gpr_name(op1_reg) + ", " + get_gpr_name(op2_reg) + '\n');
                }
                break;
            default:
                asm_stream << "Not yet generated assembly for " << op << "\n";
                break;
            }
        }
        // else if (statement.get_type() == TRIPLE) {
        //     const Triple* triple_statement = dynamic_cast<const Triple*>(&statement);
        //     if (triple_statement->operands.size() != 3) {
        //         error_msg("Invalid number of operands for TRIPLE statement");
        //         return asm_stream;
        //     }
        //     Operand op1 = triple_statement->operands[0];
        //     Operand op2 = triple_statement->operands[1];
        //     Operand result = triple_statement->operands[2];
        //     if (op1.type == CONSTANT) {
        //         GPR reg = get_assigned_gpr(result.name);
        //         if (reg != empty) {
        //             asm_stream << generate_asm_str("li " + get_gpr_name(reg) + ", " + op1.name + '\n');
        //         }
        // }
        else {
            asm_stream << "Not yet generated assembly for " << get_type_name(statement.get_type()) << "\n";
        }

        return asm_stream;
    }

    std::stringstream CodeGen::generate_data(const TACStatement& statement) {
        std::stringstream data_stream;

        switch (statement.get_type()) {
        case VARIABLE:
        {
            const VariableStatement* var_statement = dynamic_cast<const VariableStatement*>(&statement);
            switch (var_statement->type) {
            case GLOBAL_St:
            case STATIC_St:
            {
                if (statement.operands.size() == 2) {
                    // Fetch the operands

                    if (Stack::add_symbol(statement.operands[0].name, std::stoi(statement.operands[1].name))) {
                        Operand op = Operand();
                        op.name = statement.operands[0].name;
                        op.size = Stack::get_symbol_size(statement.operands[0].name);
                        op.type = Stack::get_symbol_type(statement.operands[0].name);
                        switch (op.type) {
                        case UNSIGNED:
                        case SIGNED:
                        case STRUCT:
                        case UNION:
                        case POINTER:
                        {
                            data_stream << data_str(statement.operands[0].name, op.size, true, 0) + '\n';
                            break;
                        }
                        case FLOAT:
                        {
                            data_stream << data_str_float(statement.operands[0].name, op.size, true, 0.0) + '\n';
                            break;
                        }
                        }
                    }
                    else {
                        error_msg("Failed to add symbol to stack");
                    }
                }
            }
            }
            break;
        }
        default:
            break;
        }

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

}