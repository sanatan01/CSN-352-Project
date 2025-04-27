#include <codegen.h>
#include <symtab.h>
#include <climits>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <iomanip>
namespace backend
{

    int CodeGen::current_scope = 0;
    int CodeGen::stack_pushed = 0;
    bool CodeGen::first_param = true;

    std::vector<std::vector<Register>> CodeGen::dump_map;
    std::map<std::string, GlobalType> MMU::function_map;

    std::stringstream CodeGen::asm_stream;
    std::stringstream CodeGen::data_stream;

    // ================== GPR Functions ==================

    std::map<GPR, Register> gpr_map;

    void init_gpr_map()
    {
        for (int i = 0; i < 64; ++i)
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
        case f0:
            return "$f0";
        case f1:
            return "$f1";
        case f2:
            return "$f2";
        case f3:
            return "$f3";
        case f4:
            return "$f4";
        case f5:
            return "$f5";
        case f6:
            return "$f6";
        case f7:
            return "$f7";
        case f8:
            return "$f8";
        case f9:
            return "$f9";
        case f10:
            return "$f10";
        case f11:
            return "$f11";
        case f12:
            return "$f12";
        case f13:
            return "$f13";
        case f14:
            return "$f14";
        case f15:
            return "$f15";
        case f16:
            return "$f16";
        case f17:
            return "$f17";
        case f18:
            return "$f18";
        case f19:
            return "$f19";
        case f20:
            return "$f20";
        case f21:
            return "$f21";
        case f22:
            return "$f22";
        case f23:
            return "$f23";
        case f24:
            return "$f24";
        case f25:
            return "$f25";
        case f26:
            return "$f26";
        case f27:
            return "$f27";
        case f28:
            return "$f28";
        case f29:
            return "$f29";
        case f30:
            return "$f30";
        case f31:
            return "$f31";
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
    GPR floats[32] = {f0, f1, f2, f3, f4, f5, f6, f7, f8, f9,
                      f10, f11, f12, f13, f14, f15,
                      f16, f17, f18, f19, f20, f21,
                      f22, f23, f24, f25, f26, f27,
                      f28, f29, f30, f31};

    GPR empty_strategy_float()
    {
        for (int i = 0; i < 32; i++)
        {
            if (i == 0 || i == 1 || (i >= 12 && i <= 14))
                continue;
            Operand op = MMU::get_symbol(gpr_map[floats[i]].name);
            if (op.storage_loc != TEMP)
            {
                store_gpr(floats[i], op.name);
                free_gpr(floats[i]);
                return floats[i];
            }
        }
        return empty;
    }

    GPR empty_strategy_double()
    {
        for (int i = 0; i < 32; i += 2)
        {
            if (i == 0 || i == 1 || (i >= 12 && i <= 14))
                continue;
            Operand op = MMU::get_symbol(gpr_map[floats[i]].name);
            if (op.storage_loc != TEMP)
            {
                store_gpr(floats[i], op.name);
                free_gpr(floats[i]);
                return floats[i];
            }
        }
        for (int i = 0; i < 32; i += 2)
        {
            if (i == 0 || i == 12 || i == 14)
                continue;

            if (gpr_map[floats[i]].is_free() || gpr_map[floats[i + 1]].is_free())
            {
                if (gpr_map[floats[i]].is_free())
                {
                    Operand op2 = MMU::get_symbol(gpr_map[floats[i + 1]].name);
                    if (op2.storage_loc != TEMP)
                    {
                        store_gpr(floats[i + 1], op2.name);
                        free_gpr(floats[i + 1]);
                        return floats[i];
                    }
                }
                if (gpr_map[floats[i + 1]].is_free())
                {
                    Operand op2 = MMU::get_symbol(gpr_map[floats[i]].name);
                    if (op2.storage_loc != TEMP)
                    {
                        store_gpr(floats[i], op2.name);
                        free_gpr(floats[i]);
                        return floats[i];
                    }
                }
                continue;
            }

            Operand op1 = MMU::get_symbol(gpr_map[floats[i]].name);
            Operand op2 = MMU::get_symbol(gpr_map[floats[i + 1]].name);
            if (op1.storage_loc != TEMP && op2.storage_loc != TEMP)
            {
                store_gpr(floats[i], op1.name);
                store_gpr(floats[i + 1], op2.name);
                free_gpr(floats[i]);
                free_gpr(floats[i + 1]);
                return floats[i];
            }
        }
        return empty;
    }

    GPR empty_strategy_gpr()
    {
        for (auto i : temps)
        {
            Operand op = MMU::get_symbol(gpr_map[i].name);
            if (op.storage_loc != TEMP)
            {
                store_gpr(i, op.name);
                free_gpr(i);
                return i;
            }
        }
        return empty;
    }

    bool is_float(GlobalType typ)
    {
        if (typ.type_tag == STANDARD_TYPE)
        {
            if (typ.standard_type->name == "float" ||
                typ.standard_type->name == "double" ||
                typ.standard_type->name == "long double")
            {
                return true;
            }
        }
        return false;
    }

    void load_gpr(GPR reg, Operand op, bool store_long = false)
    {
        switch (op.storage_loc)
        {
        case TEMP:
            set_gpr(reg, op.name);
            break;
        case STACK:
        {
            int offset = MMU::get_offset(op.name);
            if (offset != -1)
            {
                if (is_float(op.type))
                {
                    if (op.size == 8)
                    {
                        CodeGen::add_to_asm("ldc1 " + get_gpr_name(reg) + ", " + std::to_string(offset) + "($sp)", "Loading double into " + get_gpr_name(reg), true);
                        set_gpr(reg, op.name);
                        set_gpr(static_cast<GPR>(int(reg) + 1), op.name);
                    }
                    else if (op.size == 4)
                    {
                        CodeGen::add_to_asm("lwc1 " + get_gpr_name(reg) + ", " + std::to_string(offset) + "($sp)", "Loading float into " + get_gpr_name(reg), true);
                        set_gpr(reg, op.name);
                    }
                }
                else
                {
                    // TODO, make sure that hi lo are set properly
                    CodeGen::add_to_asm("lw " + get_gpr_name(reg) + ", " + std::to_string(offset) + "($sp)", "Loading into " + get_gpr_name(reg) + " from stack with name " + op.name, true);
                    set_gpr(reg, op.name);
                    if (store_long && op.size == 8)
                    {
                        CodeGen::add_to_asm("lw " + get_gpr_name(static_cast<GPR>(int(reg) + 1)) + ", " + std::to_string(offset + 4) + "($sp)", "Loading long long into " + get_gpr_name(reg), true);
                        set_gpr(static_cast<GPR>(int(reg) + 1), op.name);
                    }
                }
            }
            else
            {
                error_msg("Invalid stack offset, found -1");
                return;
            }
        }
        break;
        case DATA:
        {
            if (is_float(op.type))
            {
                if (op.size == 8)
                {
                    CodeGen::add_to_asm("lw " + get_gpr_name(s0) + ", " + CodeGen::convert_to_valid(op.name), "", true);
                    CodeGen::add_to_asm("ldc1 " + get_gpr_name(reg) + ", 0(" + get_gpr_name(s0) + ")", "Loading double into " + get_gpr_name(reg), true);
                    set_gpr(reg, op.name);
                    set_gpr(static_cast<GPR>(int(reg) + 1), op.name);
                    free_gpr(s0);
                }
                else if (op.size == 4)
                {
                    CodeGen::add_to_asm("lw " + get_gpr_name(s0) + ", " + CodeGen::convert_to_valid(op.name), "", true);
                    CodeGen::add_to_asm("lwc1 " + get_gpr_name(reg) + ", 0(" + get_gpr_name(s0) + ")", "Loading float into " + get_gpr_name(reg), true);
                    set_gpr(reg, op.name);
                    free_gpr(s0);
                }
            }
            else
            {
                CodeGen::add_to_asm("lw " + get_gpr_name(reg) + ", " + CodeGen::convert_to_valid(op.name), "Loading into " + get_gpr_name(reg), true);
                set_gpr(reg, op.name);
                if (store_long && op.size == 8)
                {
                    CodeGen::add_to_asm("lw " + get_gpr_name(static_cast<GPR>(int(reg) + 1)) + ", 4(" + CodeGen::convert_to_valid(op.name) + ")", "Loading long long into " + get_gpr_name(reg), true);
                    set_gpr(static_cast<GPR>(int(reg) + 1), op.name);
                }
            }
        }
        break;
        }
    }

    GPR get_free_gpr(Operand op, bool load)
    {

        if (is_float(op.type))
        {

            if (op.size == 8)
            {
                for (int i = 0; i < 32; i += 2)
                {
                    if (i == 0 || i == 12 || i == 14)
                        continue;

                    if (gpr_map[floats[i]].is_free() && gpr_map[floats[i + 1]].is_free())
                    {
                        if (load)
                            load_gpr(floats[i], op);
                        else
                        {
                            set_gpr(floats[i], op.name);
                            set_gpr(static_cast<GPR>(int(floats[i]) + 1), op.name);
                        }
                        return floats[i];
                    }
                }
                GPR ret = empty_strategy_double();
                if (load)
                    load_gpr(ret, op);
                else
                {
                    set_gpr(ret, op.name);
                    set_gpr(static_cast<GPR>(int(ret) + 1), op.name);
                }
                return ret;
            }
            else
            {
                for (int i = 0; i < 32; ++i)
                {
                    if (i == 0 || i == 1 || (i >= 12 && i <= 14))
                        continue;
                    if (gpr_map[floats[i]].is_free())
                    {
                        if (load)
                            load_gpr(floats[i], op);
                        else
                            set_gpr(floats[i], op.name);
                        return floats[i];
                    }
                }

                GPR ret = empty_strategy_float();
                if (load)
                    load_gpr(ret, op);
                else
                    set_gpr(ret, op.name);
                return ret;
            };
        }

        for (int i = 0; i < 10; ++i)
        {
            if (gpr_map[temps[i]].is_free())
            {
                if (load)
                    load_gpr(temps[i], op);
                else
                    set_gpr(temps[i], op.name);
                return temps[i];
            }
        }
        GPR ret = empty_strategy_gpr();
        if (load)
            load_gpr(ret, op);
        else
            set_gpr(ret, op.name);
        return ret;
    }

    void get_free_arg_gpr(std::vector<Operand> args, Operand ret)
    {
        GPR int_args[4] = {a0, a1, a2, a3};
        GPR float_args[4] = {f12, f14};

        if (ret.type.type_tag == POINTER_TYPE)
        {
            // Push to stack
            CodeGen::add_to_asm("addi $sp, $sp, -" + ret.type.pointer_type->return_type->getSize(), "Pushing return value to stack");
            CodeGen::add_to_asm("sw " + get_gpr_name(a0) + ", 0($sp)", "Pushing return value to stack");
            set_gpr(a0, ret.name);
        }

        for (int i = 0; i < args.size(); ++i)
        {
            if (args[i].is_constant)
            {
            }
            else
            {
                if (is_float(args[i].type))
                {
                    for (GPR j : float_args)
                    {
                        if (gpr_map[j].is_free())
                        {
                            load_gpr(j, args[i], true);
                            set_gpr(j, args[i].name);
                            break;
                        }
                    }

                    // Pushing to stack if no free registers
                    GPR temp = get_assigned_gpr(args[i].name);
                    if (temp != empty){
                        store_gpr(temp, args[i].name);
                    }

                    
                }
                else
                {
                    for (GPR j : int_args)
                    {
                        if (gpr_map[j].is_free())
                        {
                            load_gpr(j, args[i], true);
                            set_gpr(j, args[i].name);
                            break;
                        }
                    }

                    GPR temp = get_assigned_gpr(args[i].name);
                    if (temp != empty){
                        store_gpr(temp, args[i].name);
                    }

                    // Pushing to stack if no free registers
                    if (args[i].storage_loc == DATA)
                    {
                        // use s1 register to store address of data location
                        load_gpr(s1, args[i], false);
                        set_gpr(s1, args[i].name);
                    }
                    CodeGen::add_to_asm("addi $sp, $sp, -" + std::to_string(args[i].size), "Pushing argument to stack");
                    MMU::push(args[i]);
                    for (int j = 0; j < args[i].size; j += 4)
                    {
                        switch (args[i].storage_loc)
                        {
                        case STACK:
                            CodeGen::add_to_asm("sw " + get_gpr_name(s0) + ", " + std::to_string(MMU::get_offset(args[i].name) + j)+ "($sp)", "Pushing argument to stack");
                            break;
                        case DATA:
                            CodeGen::add_to_asm("sw " + get_gpr_name(s0) + ", " + std::to_string(j) + "(" +get_gpr_name(s1) + ")", "Pushing argument to stack from data section");
                            break;
                        default:
                            error_msg("Invalid storage location for argument");
                            break;
                        }
                        CodeGen::add_to_asm("sw " + get_gpr_name(s0) + ", " + std::to_string(j) + "($sp)", "Pushing argument to stack");
                    }
                    free_gpr(s1);
                    free_gpr(s0);
                }
            }
        }
    }

    void dump_all_regs()
    {
        // Dump all regs to dump_map
        std::vector<Register> dump;
        for (int i = 0; i < 10; ++i)
        {
            dump.push_back(gpr_map[temps[i]]);
        }
        CodeGen::add_to_asm("addi $sp, $sp, -40 ", "Dumping all registers");
        CodeGen::add_to_asm("sw $t0, 0($sp) ", "");
        CodeGen::add_to_asm("sw $t1, 4($sp) ", "");
        CodeGen::add_to_asm("sw $t2, 8($sp) ", "");
        CodeGen::add_to_asm("sw $t3, 12($sp)", "");
        CodeGen::add_to_asm("sw $t4, 16($sp) ", "");
        CodeGen::add_to_asm("sw $t5, 20($sp) ", "");
        CodeGen::add_to_asm("sw $t6, 24($sp) ", "");
        CodeGen::add_to_asm("sw $t7, 28($sp) ", "");
        CodeGen::add_to_asm("sw $t8, 32($sp) ", "");
        CodeGen::add_to_asm("sw $t9, 36($sp) ", "");
        CodeGen::dump_map.push_back(dump);

        // TODO: add floats
    }

    void free_all_regs()
    {
        for (int i = 0; i < 10; ++i)
        {
            gpr_map[temps[i]].free_reg();
        }
    }

    void restore_all_regs()
    {
        // Restore all regs from dump_map
        if (CodeGen::dump_map.empty())
        {
            return;
        }
        std::vector<Register> dump = CodeGen::dump_map.back();
        CodeGen::dump_map.pop_back();
        for (int i = 0; i < 10; ++i)
        {
            gpr_map[temps[i]] = dump[i];
            if (gpr_map[temps[i]].value == 1)
            {
                CodeGen::add_to_asm("lw " + gpr_map[temps[i]].reg_name + ", " + std::to_string(i * 4) + "($sp) ", "");
            }
        }
        CodeGen::add_to_asm("addi $sp, $sp, 40 ", "Pop store of temp regs");
    }

    void set_gpr(GPR reg, std::string name)
    {
        if(name == "")
        {
            error_msg("Invalid gpr name received empty string");
            return;
        }
        gpr_map[reg].value = 1;
        gpr_map[reg].name = name;
        CodeGen::add_to_asm("# Setting gpr " + get_gpr_name(reg) + " to " + name, "");
    }

    void free_gpr(GPR reg)
    {
        CodeGen::add_to_asm("", "Freeing gpr " + get_gpr_name(reg) + ", " + gpr_map[reg].name, true);
        gpr_map[reg].free_reg();
    }

    std::string CodeGen::convert_to_valid(std::string name)
    {
        // Change all '.' with '_'
        std::string valid_name = name;
        std::replace(valid_name.begin(), valid_name.end(), '.', '_');
        return valid_name;
    }

    void store_gpr(GPR reg, std::string name)
    {
        Operand op = MMU::get_symbol(name);
        switch (op.storage_loc)
        {
        case TEMP:
            break;
        case STACK:
        {
            int offset = MMU::get_offset(name);
            if (offset != -1)
            {
                CodeGen::add_to_asm("sw " + get_gpr_name(reg) + ", " + std::to_string(offset) + "($sp)", "Storing gpr from " + get_gpr_name(reg) + " into stack", true);
            }
            else
            {
                error_msg("Invalid stack offset, found -1");
                return;
            }
        }
        break;
        case DATA:
        {
            CodeGen::add_to_asm("sw " + get_gpr_name(reg) + ", " + CodeGen::convert_to_valid(gpr_map[reg].name), "Storing gpr from " + get_gpr_name(reg) + " into data", true);
        }
        break;
        }
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

    GPR get_gpr(Operand op, bool load)
    {
        for (int i = 0; i < 64; i++)
        {
            if (gpr_map[(GPR)i].name == op.name)
            {
                // CodeGen::add_to_asm("# " + op.name + " is in " + get_gpr_name((GPR)i), "");
                return (GPR)i;
            }
        }

        GPR temp = get_free_gpr(op, load);
        return temp;
    }

    // ================== MMU Variables ==================

    std::vector<Operand> MMU::stack;
    std::map<std::string, Operand> MMU::symbol_map;

    // ================== MMU Functions ==================

    void MMU::push(Operand op)
    {
        stack.push_back(op);
    }

    void MMU::pop(int size)
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

    int MMU::get_offset(std::string name)
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
    bool MMU::add_symbol(std::string name, int index, int loc)
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

        op.type = GlobalType(*symbol.identifier.type);
        op.is_constant = false;
        op.storage_loc = StorageLoc(loc);

        if (symbol.identifier.type->type_tag == ARRAY_TYPE)
        {
            op.type = *create_pointer_type(symbol.identifier.type->array_type->return_type, symbol.identifier.type->array_type->dim, symbol.identifier.type->getSpecifiers());
        }

        switch (op.type.type_tag)
        {
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
    bool MMU::add_symbol(std::string name, int sz, GlobalType type, int loc)
    {
        Operand op = Operand();
        op.name = name;
        op.size = sz;
        op.type = GlobalType(type);
        op.is_constant = false;
        op.storage_loc = StorageLoc(loc);

        symbol_map[name] = op;
        return true;
    }

    void MMU::add_to_func_map(std::string name, std::string index)
    {
        Symbol symbol = SymbolTable::get_symbol_by_index(std::stoi(index));
        if (symbol.identifier.type->type_tag == FUNCTION_TYPE)
        {
            GlobalType type = GlobalType(*symbol.identifier.type);
            function_map[name] = type;
        }
        else
        {
            error_msg("Invalid function type");
        }
    }

    bool MMU::is_symbol_present(std::string name)
    {
        return symbol_map.find(name) != symbol_map.end();
    }

    Operand MMU::get_symbol(std::string name)
    {
        if (symbol_map.find(name) != symbol_map.end())
        {
            return symbol_map[name];
        }
        error_msg("Symbol not found in symbol map");
        return Operand(); // Not found
    }

    int MMU::get_symbol_size(std::string name)
    {
        if (symbol_map.find(name) != symbol_map.end())
        {
            return symbol_map[name].size;
        }
        error_msg("Symbol not found in symbol map");
        return -1; // Not found
    }

    GlobalType *MMU::get_symbol_type(std::string name)
    {
        if (symbol_map.find(name) != symbol_map.end())
        {
            return &symbol_map[name].type;
        }
        return nullptr; // Not found
    }

    // ================== CodeGen Functions =================

    void CodeGen::add_to_asm(std::string txt, std::string comment, bool indent)
    {
        if (comment == "")
        {
            if (indent)
            {
                CodeGen::asm_stream << "\t\t" + txt + "\n";
                return;
            }
            CodeGen::asm_stream << txt + "\n";
            return;
        }

        if (indent)
        {
            CodeGen::asm_stream << "\t\t" << std::left << std::setw(40) << txt << "# " << comment << "\n";
            return;
        }
        CodeGen::asm_stream << std::left << std::setw(40) << txt << "# " << comment << "\n";
    };

    // TODO make sure the hi lo are set correctly
    void CodeGen::add_to_data(std::string name, int size, std::string val, int type)
    {
        // type = 0 for int, 1 for float, 2 for str

        std::string txt = name + ":\t";
        // Add padding to create consistent column alignment
        if (name.length() < 8)
            txt += "\t";

        // Handle initialized values
        switch (type)
        {
        case 0:
            if (size == 1)
                txt += ".byte\t" + val;
            else if (size == 2)
                txt += ".half\t" + val;
            else if (size == 4)
                txt += ".word\t" + val;
            else if (size == 8)
            {
                // TODO make sure this is correct
                auto [hi, lo] = getHighLowBytes(val);
                txt += ".word\t" + lo + "\n";
                txt += "\t\t\t.word\t" + hi;
            }
            else
                txt += ".space\t" + std::to_string(size);
            break;
        case 1:
            if (size == 4)
            {
                auto [hi, lo] = floatToIEEEHex(val, false);
                txt += ".float\t" + hi;
            }
            else if (size == 8)
            {
                auto [hi, lo] = floatToIEEEHex(val, true);
                txt += ".word\t" + lo + "\n";
                txt += "\t\t\t.word\t" + hi;
            }
            break;
        case 2:
            txt += ".asciiz\t" + val;
            break;

        default:
            error_msg("Invalid type for data");
            break;
        }

        // Add the data to the data stream
        CodeGen::data_stream << txt + "\n";
    }

    std::pair<std::string, std::string> getHighLowBytes(const std::string &decimalStr)
    {
        // Convert the decimal string to an integer (assuming it fits in an int)
        long long num = std::stoll(decimalStr); // Use stoll to handle large numbers

        // Extract low 4 bytes (least significant 32 bits)
        unsigned int lowWord = static_cast<unsigned int>(num & 0xFFFFFFFF); // Mask to get low 4 bytes

        // Extract high 4 bytes (most significant 32 bits)
        unsigned int highWord = static_cast<unsigned int>((num >> 32) & 0xFFFFFFFF); // Shift right by 32 bits and mask

        // Convert the high and low words to strings (in hex format)
        std::stringstream lowStream, highStream;
        lowStream << std::hex << std::setw(8) << std::setfill('0') << lowWord;
        highStream << std::hex << std::setw(8) << std::setfill('0') << highWord;

        // Return the high and low bytes as hex strings
        return {highStream.str(), lowStream.str()};
    }

    std::pair<std::string, std::string>
    floatToIEEEHex(const std::string &inputStr, bool isDouble)
    {
        if (isDouble)
        {
            // Double precision (64-bit)
            double num = std::stod(inputStr);
            uint64_t repr;
            std::memcpy(&repr, &num, sizeof(repr));

            uint32_t highPart = static_cast<uint32_t>((repr >> 32) & 0xFFFFFFFF);
            uint32_t lowPart = static_cast<uint32_t>(repr & 0xFFFFFFFF);

            std::stringstream highStream, lowStream;
            highStream << std::hex << std::setw(8) << std::setfill('0') << highPart;
            lowStream << std::hex << std::setw(8) << std::setfill('0') << lowPart;

            return {highStream.str(), lowStream.str()};
        }
        else
        {
            // Single precision (32-bit)
            float numf = std::stof(inputStr);
            uint32_t repr;
            std::memcpy(&repr, &numf, sizeof(repr));

            std::stringstream singleStream;
            singleStream << std::hex << std::setw(8) << std::setfill('0') << repr;

            return {singleStream.str(), ""};
        }
    }
}