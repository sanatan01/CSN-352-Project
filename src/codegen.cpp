#include <codegen.h>
#include <symtab.h>

namespace backend
{

    bool CodeGen::is_text_section = false;
    int CodeGen::current_scope = 0;

    // ================== GPR Functions ==================

    std::map<GPR, Register> gpr_map;

    void init_gpr_map()
    {
        for (int i = 0; i < 32; ++i)
        {
            GPR reg = static_cast<GPR>(i);
            gpr_map[reg] = Register();
            gpr_map[reg].reg_name = get_gpr_name(reg);
        }
    }

    std::string get_gpr_name(GPR reg)
    {
        switch (reg)
        {
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

    void Register::free_reg()
    {
        value = 0;
        name = "";
    }

    bool Register::is_free()
    {
        return value == 0;
    }

    GPR temps[10] = {t0, t1, t2, t3, t4, t5, t6, t7, t8, t9};

    GPR get_free_gpr()
    {
        for (int i = 0; i < 10; ++i)
        {
            if (gpr_map[temps[i]].is_free())
            {
                return temps[i];
            }
        }
        return empty;
    }

    void set_gpr(GPR reg, std::string name)
    {
        gpr_map[reg].value = 1;
        gpr_map[reg].name = name;
    }

    void free_gpr(GPR reg)
    {
        gpr_map[reg].free_reg();
    }

    GPR get_assigned_gpr(std::string name)
    {
        for (int i = 0; i < 10; ++i)
        {
            if (gpr_map[temps[i]].name == name)
            {
                return temps[i];
            }
        }
        return empty;
    }

    // ================== Stack Variables ==================

    std::vector<Operand> Stack::stack;
    std::map<std::string, Operand> Stack::symbol_map;

    // ================== Stack Functions ==================

    void Stack::push(Operand op)
    {
        stack.push_back(op);
    }

    void Stack::pop(int size)
    {
        int del_size = 0;
        while (del_size < size && !stack.empty())
        {
            del_size += stack.back().size;
            stack.pop_back();
        }

        if (del_size != size)
        {
            error_msg("Invalid stack pop size");
        }
    }

    int Stack::get_offset(std::string name)
    {
        int offset = 0;
        for (int i = stack.size() - 1; i >= 0; --i)
        {
            if (stack[i].name == name)
            {
                return offset;
            }
            offset += stack[i].size;
        }

        return -1; // Not found
    }

    // ================== Symbol Map Functions ==================

    // Add symbol from the symbol table
    bool Stack::add_symbol(std::string name, int index)
    {
        Symbol symbol = SymbolTable::get_symbol_by_index(index);
        Operand op = Operand();
        op.name = symbol.identifier.name;
        if (name != op.name)
        {
            error_msg("Symbol name mismatch");
            return false;
        }
        op.size = symbol.identifier.type->getSize();

        bool ret_value;

        switch (symbol.identifier.type->type_tag)
        {
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
            if (symbol.identifier.type->standard_type->name.find("unsigned") != std::string::npos)
            {
                op.type = UNSIGNED;
            }
            else
            {
                op.type = SIGNED;
            }
            ret_value = true;
            break;
        default:
            error_msg("Unknown type in symbol map");
            ret_value = false;
        }

        if (ret_value)
        {
            symbol_map[name] = op;
            return true;
        }
        else
        {
            error_msg("Failed to add symbol to stack");
            return false;
        }
    }

    // Add a temporary into the symbol table
    bool Stack::add_symbol(std::string name, int sz, OpType type)
    {
        Operand op = Operand();
        op.name = name;
        op.size = sz;
        op.type = type;

        symbol_map[name] = op;
        return true;
    }

    bool Stack::is_symbol_present(std::string name)
    {
        return symbol_map.find(name) != symbol_map.end();
    }

    int Stack::get_symbol_size(std::string name)
    {
        if (symbol_map.find(name) != symbol_map.end())
        {
            return symbol_map[name].size;
        }
        error_msg("Symbol not found in symbol map");
        return -1; // Not found
    }

    OpType Stack::get_symbol_type(std::string name)
    {
        if (symbol_map.find(name) != symbol_map.end())
        {
            return symbol_map[name].type;
        }
        return SIGNED; // Default type
    }

    // ================== CodeGen Functions ==================

    std::vector<GPR> CodeGen::get_used_gprs(const TACStatement &statement)
    {
        std::vector<GPR> used_gprs;

        // We dont need variables for certain statements we can skip
        if (statement.get_type() == COMMON)
        {
            const CommonStatement *common_statement = dynamic_cast<const CommonStatement *>(&statement);
            if (common_statement->type == GOTO_St || common_statement->type == POP_St || common_statement->type == FUNC_St ||
                common_statement->type == LABEL_St || common_statement->type == ENTER_St || common_statement->type == EXIT_St)
            {
                return used_gprs;
            }
        }

        for (const auto &operand : statement.operands)
        {
            if (operand.type == CONSTANT)
            {
                continue;
            }

            GPR reg = get_assigned_gpr(operand.name);
            if (reg == empty)
            {
                GPR reg = get_free_gpr();
                if (reg != empty)
                {
                    set_gpr(reg, operand.name);
                    output_msg("Assigned " + operand.name + " to " + get_gpr_name(reg));
                    used_gprs.push_back(reg);
                }
                else
                {
                    output_msg("No free registers available for " + operand.name);
                    error_msg("No free registers available");
                }
            }
            else
            {
                used_gprs.push_back(reg);
            }
        }

        return used_gprs;
    }

    std::stringstream CodeGen::generate_asm(const TACStatement &statement, std::vector<GPR> &used_gprs)
    {
        std::stringstream asm_stream;

        if (statement.get_type() == COMMON)
        {
            const CommonStatement *common_statement = dynamic_cast<const CommonStatement *>(&statement);
            switch (common_statement->type)
            {
            case POP_St:
            {
                if (statement.operands.size() != 1)
                {
                    error_msg("Invalid number of operands for POP statement");
                    return asm_stream;
                }
                // Fetch the operands
                int sz = std::stoi(statement.operands[0].name);
                Stack::pop(sz);
                asm_stream << generate_asm_str("addi $sp, $sp, " + std::to_string(sz) + "\n", true);
                break;
            }
            case FUNC_St:
                if (current_scope == 1)
                {

                    asm_stream << generate_asm_str(".globl " + statement.labels[0].name + "\n", true, false);
                    asm_stream << generate_asm_str(statement.labels[0].name + ":\n", true, false);
                    break;
                }
            case LABEL_St:
            {
                if (statement.labels.size() != 1)
                {
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
                if (statement.labels.size() != 1)
                {
                    error_msg("Invalid number of operands for GOTO statement");
                    return asm_stream;
                }
                // Fetch the operands
                std::string label = statement.labels[0].name;
                asm_stream << generate_asm_str("j " + label + '\n', true);
                break;
            }
            default:
                asm_stream << "Not yet generated assembly for " << get_type_name(common_statement->type) << "\n";
                break;
            }
        }
        else if (statement.get_type() == VARIABLE)
        {
            const VariableStatement *var_statement = dynamic_cast<const VariableStatement *>(&statement);
            switch (var_statement->type)
            {
            case LOCAL_St:
            {
                if (statement.operands.size() != 2)
                {
                    error_msg("Invalid number of operands for LOCAL statement");
                    return asm_stream;
                }
                // Fetch the operands
                if (Stack::add_symbol(statement.operands[0].name, std::stoi(statement.operands[1].name)))
                {
                    Operand op = Operand();
                    op.name = statement.operands[0].name;
                    op.size = Stack::get_symbol_size(statement.operands[0].name);
                    op.type = Stack::get_symbol_type(statement.operands[0].name);
                    Stack::push(op);
                    asm_stream << generate_asm_str("addi $sp, $sp, -" + std::to_string(op.size) + '\n', true);
                }
                else
                {
                    error_msg("Failed to add symbol to stack");
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
        else
        {
            asm_stream << "Not yet generated assembly for " << get_type_name(statement.get_type()) << "\n";
        }

        return asm_stream;
    }

    std::string generate_asm_str(std::string txt, bool is_text, bool indent)
    {
        if (is_text)
        {
            if (CodeGen::is_text_section)
            {
                if (indent)
                {
                    return "\t\t" + txt;
                }
                return txt;
            }
            else
            {
                CodeGen::is_text_section = true;
                if (indent)
                {
                    return ".text\n\t\t" + txt;
                }
                return ".text\n" + txt;
            }
        }
        else
        {
            if (CodeGen::is_text_section)
            {
                CodeGen::is_text_section = false;
                if (indent)
                {
                    return ".data\n\t\t" + txt;
                }
                return ".data\n" + txt;
            }
            else
            {
                if (indent)
                {
                    return "\t\t" + txt;
                }
                return txt;
            }
        }
    }
}
