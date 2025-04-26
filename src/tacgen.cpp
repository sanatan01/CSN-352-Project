#include <tacgen.h>
#include <utils.h>
#include <codegen.h>
#include <climits>

namespace backend {
    // Extern variables
    std::map<std::string, int> last_used;
    std::vector<std::unique_ptr<TACStatement>> statements;
    std::map<std::string, Label> tac_labels;

    int curr_line = 1;

    void add_operand(Operand op) {
        if (op.is_constant) {
            return;
        }

        last_used[op.name] = curr_line;
    }

    // Enum functions

    std::string get_type_name(StatementType type) {
        switch (type) {
        case GOTO_St:
            return "GOTO";
        case POP_St:
            return "POP";
        case PARAM_St:
            return "PARAM";
        case CALL_St:
            return "CALL";
        case RETURN_St:
            return "RETURN";
        case FUNC_St:
            return "FUNC";
        case LABEL_St:
            return "LABEL";
        case ENTER_St:
            return "ENTER";
        case EXIT_St:
            return "EXIT";
        default:
            return "";
        }
    }

    std::string get_type_name(TACType type) {
        switch (type) {
        case QUAD:
            return "QUAD";
        case TRIPLE:
            return "TRIPLE";
        case DOUBLE:
            return "DOUBLE";
        case COMMON:
            return "COMMON";
        default:
            return "";
        }
    }

    // Class Constructors
    size_t get_const_size(std::string value) {
        if (value.find("0x") == 0) {
            return 4; // Assuming 4 bytes for hex constants
        }
        else if (value.find(".") != std::string::npos ||
                 value.find("e") != std::string::npos ||
                 value.find("E") != std::string::npos) {
            // This is a floating point number
            try {
                long double num = std::stold(value);
                float float_val = static_cast<float>(num);
                // Check if conversion to float caused loss of precision
                if (static_cast<long double>(float_val) != num) {
                    return 8; // Need double precision (8 bytes)
                }
                return 4; // Float precision is sufficient (4 bytes)
            } catch (...) {
                return 4; // Default to float if conversion fails
            }
        }
        else {
            // This is an integer number
            try {
                long long val = std::stoll(value);
                if (val >= INT_MIN && val <= INT_MAX) {
                    return 4; // int (4 bytes)
                }
                else {
                    return 8; // long long (8 bytes)
                }
            } catch (...) {
                return 4; // Default to int if conversion fails
            }
        }
    }

    Operand::Operand(std::string name, bool is_const): name(name), is_constant(is_const), size(4), storage_loc(TEMP) {
        if (is_const) {
            size = get_const_size(name);

            // Set the type based on the value
            if (name.find(".") != std::string::npos ||
                name.find("e") != std::string::npos ||
                name.find("E") != std::string::npos) {
                if (size == 4) {
                    type = *(create_primitive_type(FLOAT_T));
                }
                else {
                    type = *(create_primitive_type(DOUBLE_T));
                }
            }
            else {
                if (size == 4) {
                    type = *(create_primitive_type(INT_T));
                }
                else if (size == 8) {
                    type = *(create_primitive_type(LLONG_T));
                }
                else if (size == 2) {
                    type = *(create_primitive_type(SHORT_T));
                }
                else {
                    type = *(create_primitive_type(CHAR_T));
                }
            }
        }
    }

    // =================== Quad Functions ===================

    void Quad::set_operands() {
        // Set the operands for the Quad statement
        for (auto& operand : operands) {
            if (operand.is_constant) {
                continue;
            }

            if (MMU::is_symbol_present(operand.name)) {
                operand = Operand(MMU::get_symbol(operand.name));
                continue;
            }

            switch (op) {
            case ADD:
            {
                Operand old_op = Operand(operands[0]);
                if (old_op.type.type_tag == STRUCT_TYPE) {
                    Operand op = Operand();
                    GlobalType* typ = old_op.type.struct_type->get_member(std::stoi(operands[1].name));
                    op.type = *(create_pointer_type(typ));
                    op.name = operands.back().name;
                    op.is_constant = false;
                    op.size = typ->getSize();
                    operands.back() = Operand(op);
                    operands.back().storage_loc = TEMP;
                    break;
                }
            }
            case SUB:
            case MUL:
            case DIV:
            case MOD:
            case BITWISE_AND:
            case BITWISE_OR:
            case BITWISE_XOR:
            {
                if (!operands[0].is_constant) {
                    std::string name = operands.back().name;
                    operands.back() = Operand(operands[0]);
                    operands.back().name = name;
                    operands.back().is_constant = false;
                    MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                }
                else {
                    std::string name = operands.back().name;
                    operands.back() = Operand(operands[1]);
                    operands.back().name = name;
                    operands.back().is_constant = false;
                    MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                }
            }
            break;
            case SHL:
            case SHR:
            {
                std::string name = operands.back().name;
                operands.back() = Operand(operands[0]);
                operands.back().name = name;
                operands.back().is_constant = false;
                operands.back().storage_loc = TEMP;
                MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
            }
            break;
            case EQ:
            case NE:
            case LT:
            case GT:
            case GE:
            case LE:
            {
                Operand op = Operand();
                op.name = operands.back().name;
                op.is_constant = false;
                op.type = *(create_primitive_type(CHAR_T));
                operands.back() = Operand(op);
                operands.back().storage_loc = TEMP;
                MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
            }
            break;
            default:
                break;
            }
        }
    }

    void Quad::generate_asm() const {
        switch (op) {
        case ADD:
        {
            GPR rvalue1 = get_gpr(operands[0]);
            GPR rvalue2 = get_gpr(operands[1]);
            GPR lvalue = get_gpr(operands[2]);

            if (operands[1].is_constant) {

            }
            else {
                CodeGen::add_to_asm("add " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Addition operation");
            }
        }
        break;
        case SUB:
        {
            GPR rvalue = get_gpr(operands[0]);
            GPR lvalue = get_gpr(operands[1]);
            CodeGen::add_to_asm("sub " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue) + ", " + get_gpr_name(lvalue), "Subtraction operation");
        }
        break;

        };
    }

    // =================== Triple Functions ===================

    void Triple::set_operands() {
        // Set the operands for the Triple statement
        for (auto& operand : operands) {
            if (operand.is_constant) {
                continue;
            }

            if (MMU::is_symbol_present(operand.name)) {
                operand = Operand(MMU::get_symbol(operand.name));
                continue;
            }

            switch (special_op) {
            case NONE_SP:
            {
                switch (op) {
                case TILDE_OP:
                case EXCLAMATION_OP:
                case POS_OP:
                case NEG_OP:
                {
                    std::string name = operands.back().name;
                    operands.back() = Operand(operands[0]);
                    operands.back().name = name;
                    operands.back().is_constant = false;
                    operands.back().storage_loc = TEMP;
                    MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                }
                break;
                case REF_OP:
                {
                    Operand old_op = Operand(operands[0]);
                    if (old_op.type.type_tag == POINTER_TYPE) {
                        Operand op = Operand(old_op);
                        op.name = operands.back().name;
                        op.is_constant = false;
                        op.type.pointer_type->ptr_level++;
                        operands.back() = Operand(op);
                        operands.back().storage_loc = TEMP;
                        MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    }
                    else if (old_op.type.type_tag == ARRAY_TYPE) {
                        output_msg("Converting array to pointer");
                        Operand op = Operand();
                        op.name = operands.back().name;
                        op.is_constant = false;
                        op.type = *create_pointer_type(old_op.type.array_type->return_type, old_op.type.array_type->dim, old_op.type.getSpecifiers());
                        op.type.pointer_type->ptr_level++;
                        operands.back() = Operand(op);
                        operands.back().storage_loc = TEMP;
                        MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    }
                    else {
                        Operand op = Operand();
                        op.name = operands.back().name;
                        op.is_constant = false;
                        op.type = *(create_pointer_type(&old_op.type));
                        operands.back() = Operand(op);
                        operands.back().storage_loc = TEMP;
                        MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    }
                }
                break;
                case DEREF_OP:
                {
                    Operand old_op = Operand(operands[0]);
                    if (old_op.type.type_tag == POINTER_TYPE) {
                        Operand op = Operand(old_op);
                        op.name = operands.back().name;
                        op.is_constant = false;
                        op.type.pointer_type->ptr_level--;

                        if (op.type.pointer_type->ptr_level == 0) {
                            op.type = *(op.type.pointer_type->return_type);
                        }

                        operands.back() = Operand(op);
                        operands.back().storage_loc = TEMP;
                        MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    }
                    else if (old_op.type.type_tag == ARRAY_TYPE) {
                        Operand op = Operand();
                        op.name = operands.back().name;
                        op.is_constant = false;
                        op.type = *create_pointer_type(old_op.type.array_type->return_type, old_op.type.array_type->dim, old_op.type.getSpecifiers());
                        op.type.pointer_type->ptr_level--;
                        if (op.type.pointer_type->ptr_level == 0) {
                            op.type = *(op.type.pointer_type->return_type);
                        }

                        operands.back() = Operand(op);
                        operands.back().storage_loc = TEMP;
                        MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    }
                    else {
                        error_msg("Invalid TAC, cannot dereference a non-pointer type");
                    }
                }
                break;
                default:
                    break;
                }
            }
            break;
            default:
                error_msg("Incorrect TAC code, because lval should be declared before being used");
                break;
            }
        }
    }

    void Triple::generate_asm() const {
        GPR lvalue = get_gpr(operands.back());
        CodeGen::add_to_asm("# " + operands.back().name + " is in " + get_gpr_name(lvalue), "");
        switch (special_op) {
        case NONE_SP:
        {
            switch (op) {
            case REF_OP:
            {
                StorageLoc loctype = operands[0].storage_loc;

                switch (loctype) {
                case STACK:
                {
                    CodeGen::add_to_asm("lw " + get_gpr_name(lvalue) + ", " + std::to_string(MMU::get_offset(operands[0].name)) + "($sp)", "Loading address of " + operands[0].name);

                }
                break;
                case DATA:
                {
                    CodeGen::add_to_asm("la " + get_gpr_name(lvalue) + ", " + CodeGen::convert_to_valid(operands[0].name), "Loading address of " + operands[0].name);
                }
                break;
                default:
                    error_msg("dereferencing a rvalue, need lvalue");
                    break;
                }
            }
            break;
            case DEREF_OP:
            {
                GPR rvalue = get_gpr(operands[0]);
                CodeGen::add_to_asm("lw " + get_gpr_name(lvalue) + ", " + "0(" + get_gpr_name(rvalue) + ")", "Loading value of " + operands[0].name);
                check_last_use(rvalue, line_number);
            }
            break;
            case EXCLAMATION_OP:
            {
                GPR rvalue = get_gpr(operands[0]);
                CodeGen::add_to_asm("sltiu " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue) + ", 1", "Loading value of " + operands[0].name);
                check_last_use(rvalue, line_number);
            }
            break;
            case TILDE_OP:
            {
                // TODO: handle constant
                GPR rvalue = get_gpr(operands[0]);
                if (operands[0].is_constant) {
                    CodeGen::add_to_asm("li " + get_gpr_name(rvalue) + ", " + operands[0].name, "Loading value of " + operands[0].name);
                }

                CodeGen::add_to_asm("nor " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue) + ", $zero", "Negation operation");
                switch (operands.back().size) {
                case 1:
                {
                    CodeGen::add_to_asm("andi " + get_gpr_name(lvalue) + ", " + get_gpr_name(lvalue) + ", 0xFF", "Masking to 1 byte");
                }
                break;
                case 2:
                {
                    CodeGen::add_to_asm("andi " + get_gpr_name(lvalue) + ", " + get_gpr_name(lvalue) + ", 0xFFFF", "Masking to 2 bytes");
                }
                break;
                case 4:
                {

                }
                break;
                case 8:
                default:
                {
                    error_msg("Not supported yet");
                }
                }
                check_last_use(rvalue, line_number);
                if (operands[0].is_constant) {
                    free_gpr(rvalue);
                }
            }
            break;
            case POS_OP:
            {
                GPR rvalue = get_gpr(operands[0]);
                CodeGen::add_to_asm("move " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue), "Loading value of " + operands[0].name);
                check_last_use(rvalue, line_number);
            }
            break;
            case NEG_OP:
            {
                GPR rvalue = get_gpr(operands[0]);
                CodeGen::add_to_asm("neg " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue), "Loading value of " + operands[0].name);
                check_last_use(rvalue, line_number);
            }
            break;
            default:
            {

            }
            }
        }
        break;
        case ASTERISK_SP:
        {
            GPR rvalue = get_gpr(operands[0]);
            if (operands[0].is_constant) {
                CodeGen::add_to_asm("li " + get_gpr_name(rvalue) + ", " + operands[0].name, "Loading value of " + operands[0].name);
            }

            CodeGen::add_to_asm("sw " + get_gpr_name(rvalue) + ", 0(" + get_gpr_name(lvalue) + ")", "Storing value of " + operands[0].name);
            check_last_use(rvalue, line_number);
            if (operands[0].is_constant) {
                free_gpr(rvalue);
            }
        }
        break;
        case AMPERSAND_SP:
        {
            error_msg("& found  in lvalue, not possible");
        }
        break;
        default: {
            error_msg("Incorrect special op, not found of  any type");
        }

        }
        check_last_use(lvalue, line_number);
    };

    // =================== Double Functions ===================

    void Double::set_operands() {
        // Set the operands for the Double statement
        for (auto& operand : operands) {
            if (operand.is_constant) {
                continue;
            }

            if (MMU::is_symbol_present(operand.name)) {
                operand = Operand(MMU::get_symbol(operand.name));
                continue;
            }
            if (string_lit) {
                output_msg("Need to handle string literals");
            }
            else {
                std::string name = operands.back().name;
                operands.back() = Operand(operands[0]);
                operands.back().name = name;
                operands.back().is_constant = false;
                operands.back().storage_loc = TEMP;
                MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
            }
        }
    }

    void Double::generate_asm() const {
        GPR resultReg = get_gpr(operands.back());

        if (operands[0].is_constant) {
            if (is_float(operands.back().type)) {
                if (operands.back().size == 4) {
                    auto [hi, lo] = floatToIEEEHex(operands[0].name, false);
                    CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading float constant");
                    CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(resultReg), "Moving float constant");
                    CodeGen::add_to_asm("s.s " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing float constant");

                }
                else {
                    auto [hi, lo] = floatToIEEEHex(operands[0].name, true);
                    CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading double constant high");
                    CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(resultReg), "Moving double constant high");
                    CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + lo, "Loading double constant low");
                    CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(static_cast<GPR>((int)resultReg + 1)), "Moving double constant low");
                    CodeGen::add_to_asm("s.d " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing double constant");

                }
            }
            else {
                if (operands.back().size <= 4) {
                    CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + operands[0].name, "Loading int constant");
                    //TODO: No need
                    // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing int constant");
                }
                else {
                    //TODO: handle  long long
                    auto [hi, lo] = getHighLowBytes(operands[0].name);
                    CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + hi, "Loading high part of long long");
                    CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name) + 4) + "($sp)", "Storing high part of long long");
                    CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + lo, "Loading low part of long long");
                    CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing low part of long long");
                }
            }
        }
        else {
            if ((operands[0].type.type_tag != operands.back().type.type_tag) || operands[0].type.type_tag == FUNCTION_TYPE) {
                error_msg("Types of operands are" + operands[0].type.getType() + " and " + operands.back().type.getType());
                error_msg("Incompatible types for variable assignment");
                return;
            }
            if (operands[0].type.type_tag == STANDARD_TYPE) {

                if (operands[0].type.standard_type->name == operands.back().type.standard_type->name) {

                    //get rvalue register
                    GPR secondReg = get_gpr(operands[0]);

                    if (operands.back().size <= 4) {
                        if (!is_float(operands[0].type)) {
                            CodeGen::add_to_asm("move " + get_gpr_name(resultReg) + ", " + get_gpr_name(secondReg), "Loading int constant");
                            // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)");
                        }
                        else {
                            CodeGen::add_to_asm("mov.s " + get_gpr_name(resultReg) + ", " + get_gpr_name(secondReg), "Loading float constant");
                        }
                    }
                    else {
                        if (!is_float(operands.back().type)) {
                            //TODO: handle  long long
                            // CodeGen::add_to_asm("move "+ get_gpr_name(resultReg)+ ", "+ get_gpr_name(secondReg) );
                        }
                        else {
                            CodeGen::add_to_asm("mov.d " + get_gpr_name(resultReg) + ", " + get_gpr_name(secondReg), "Loading double constant");
                        }
                    }

                    check_last_use(secondReg, line_number);
                }
                else {
                    // Handle type conversion between standard types
                    // Integer to float
                    // TODO: currently this one is for float not double

                    // Get register for rvalue  operand
                    GPR secondReg = get_gpr(operands[0]);


                    if (!is_float(operands[0].type) && is_float(operands.back().type)) {

                        // allocate temporary FP register 
                        GPR fpReg = f0;

                        // move to FP register
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(secondReg) + ", " + get_gpr_name(fpReg), "Move to FP register");

                        // Assign the value to result resultReg
                        CodeGen::add_to_asm("cvt.s.w " + get_gpr_name(resultReg) + ", " + get_gpr_name(fpReg), "Convert int to float");


                        free_gpr(fpReg);
                    }
                    // Float to integer
                    else if (is_float(operands[0].type) && !is_float(operands.back().type)) {
                        // allocate FP register
                        GPR fpReg = f0;

                        // Convert float to int
                        CodeGen::add_to_asm("cvt.w.s " + get_gpr_name(fpReg) + ", " + get_gpr_name(secondReg), "Convert float to int");

                        // Store result to resultReg
                        CodeGen::add_to_asm("mfc1 " + get_gpr_name(resultReg) + ", " + get_gpr_name(fpReg), "Move from FP register");



                        free_gpr(fpReg);
                    }
                    else {
                        output_msg("Unsupported type conversion");
                    }

                    check_last_use(resultReg, line_number);

                }
            }
            else {
                // We perform a shallow copy of the pointers for any other type
                GPR lvalue = get_gpr(operands[0]);
                CodeGen::add_to_asm("move " + get_gpr_name(resultReg) + ", " + get_gpr_name(lvalue), "Shallow copy of pointer");
                check_last_use(lvalue, line_number);
            }
        }
        check_last_use(resultReg, line_number);
    };

    // ================ Common Functions ======================

    void CommonStatement::set_operands() {
        // Set the operands for the CommonStatement
        for (auto& operand : operands) {
            if (operand.is_constant) {
                continue;
            }

            if (MMU::is_symbol_present(operand.name)) {
                operand = Operand(MMU::get_symbol(operand.name));
                continue;
            }

            if (type == CALL_St) {
                if (operands.size() != 1) {
                    error_msg("Invalid number of operands for CALL statement");
                    return;
                }
                operands[0].type = MMU::function_map[labels[0].name];
            }
            error_msg("Invalid TAC code, because lval should be declared before being used");
        }
    }

    void CommonStatement::generate_asm() const {
        switch (type) {
        case POP_St:
        {
            if (operands.size() != 1) {
                error_msg("Invalid number of operands for POP statement");
                return;
            }
            // Fetch the operands
            int sz = std::stoi(operands[0].name);
            CodeGen::add_to_asm("addi $sp, $sp, " + std::to_string(sz), "Pop " + std::to_string(sz) + " bytes from stack");
            MMU::pop(sz);
        }
        break;
        case FUNC_St:
        {
            if (CodeGen::current_scope == 0) {
                CodeGen::add_to_asm("\n.globl " + labels[0].name, "", false);
            }
            // Function Prolouge
            CodeGen::add_to_asm(labels[0].name + ":", "", false);
            CodeGen::add_to_asm("addi $sp, $sp, -16", "Allocate stack space for function");
            CodeGen::add_to_asm("sw $ra, 12($sp)", "Store return address");
            CodeGen::add_to_asm("sw $fp, 8($sp)", "Store frame pointer");
            CodeGen::add_to_asm("addi $fp, $sp, 16", "Set frame pointer");

            // TODO: load params

            break;
        }
        case LABEL_St:
        {
            if (labels.size() != 1) {
                error_msg("Invalid number of operands for FUNC/LABEL statement");
                return;
            }
            // Fetch the operands
            std::string label = labels[0].name;
            CodeGen::add_to_asm(label + ":",
                                "Define label " + label, false);
        }
        break;
        case ENTER_St:
            CodeGen::current_scope++;
            break;
        case EXIT_St:
            CodeGen::current_scope--;
            break;
        case GOTO_St:
        {
            if (labels.size() != 1) {
                error_msg("Invalid number of operands for GOTO statement");
                return;
            }
            // Fetch the operands
            std::string label = labels[0].name;
            CodeGen::add_to_asm("j " + label,
                                "Jump to label " + label);
        }
        break;
        case RETURN_St:
        {
            // TODO
            // Do type checking here
            // if 64 byte return value use v0 v1 else use v0
            // if
            if (operands.size() == 1) {
                if (operands[0].is_constant) {
                    CodeGen::add_to_asm("li $v0, " + operands[0].name, "Loading return value");
                }
                else {
                    GPR reg = get_gpr(operands[0]);

                    CodeGen::add_to_asm("move $v0, " + get_gpr_name(reg), "Loading return value");
                    free_gpr(reg);
                }
            }
            // Function Epilogue
            // CodeGen::add_to_asm("move $sp, $fp", "Restore stack pointer");
            // CodeGen::add_to_asm("lw $fp, 8($sp)", "Restore frame pointer");
            // CodeGen::add_to_asm("lw $ra, 12($sp)", "Restore return address");
            // CodeGen::add_to_asm("jr $ra", "Return to caller");
        }
        break;
        case CALL_St:
            free_all_regs();
            CodeGen::add_to_asm("need to implement call", "");
            // Remove parameters from stack
            restore_all_regs();
            CodeGen::first_param = true;
            break;
        case PARAM_St:
            if (CodeGen::first_param) {
                dump_all_regs();
                CodeGen::first_param = false;
            }
            CodeGen::add_to_asm("need to implement param", "");
            break;
        default:
            break;
        }
    }

    // ================ Variable Functions ======================

    void VariableStatement::set_operands() {
        // Set the operands for the VariableStatement
        for (auto& operand : operands) {
            if (operand.is_constant) {
                continue;
            }

            if (MMU::is_symbol_present(operand.name)) {
                operand = Operand(MMU::get_symbol(operand.name));
                continue;
            }

            switch (type) {
            case LOCAL_St:
            {
                MMU::add_symbol(operands.back().name, std::stoi(operands[0].name), static_cast<int>(STACK));
                Operand op = MMU::get_symbol(operands.back().name);
                operands.back() = Operand(op);
                operands.back().is_constant = false;
            }
            break;
            case GLOBAL_St:
            case STATIC_St:
            {
                MMU::add_symbol(operands.back().name, std::stoi(operands[0].name), static_cast<int>(DATA));
                Operand op = MMU::get_symbol(operands.back().name);
                operands.back() = Operand(op);
                operands.back().is_constant = false;
            }
            break;
            case DATA_St:
            {
                // Nothing to do here, sed
                Operand op = Operand(operands.back());
                op.type = *(create_pointer_type(create_primitive_type(CHAR_T)));
                op.is_constant = false;
                op.storage_loc = DATA;
                operands.back() = Operand(op);
                MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type, static_cast<int>(DATA));
            }
            }
            break;
        }
    }

    void VariableStatement::generate_asm() const {
        switch (type) {
        case LOCAL_St:
        {
            if (operands.size() == 2) {
                // Fetch the operands

                MMU::push(operands.back());
                CodeGen::add_to_asm("addi $sp, $sp, -" + std::to_string((operands.back()).size), "Allocating space for " + operands.back().name);
            }
            else if (operands.size() == 3) {

                MMU::push(operands.back());
                CodeGen::add_to_asm("addi $sp, $sp, -" + std::to_string((operands.back()).size), "Allocating space for " + operands.back().name);

                GPR resultReg = get_gpr(operands.back(), false);

                if (operands[1].is_constant) {
                    if (is_float(operands.back().type)) {
                        if (operands.back().size == 4) {
                            auto [hi, lo] = floatToIEEEHex(operands[1].name, false);
                            CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading float constant");
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(resultReg), "Moving float constant");
                            CodeGen::add_to_asm("s.s " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing float constant");

                        }
                        else {
                            auto [hi, lo] = floatToIEEEHex(operands[1].name, true);
                            CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading double constant high");
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(resultReg), "Moving double constant high");
                            CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + lo, "Loading double constant low");
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(static_cast<GPR>((int)resultReg + 1)), "Moving double constant low");
                            CodeGen::add_to_asm("s.d " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing double constant");

                        }
                    }
                    else {
                        if (operands.back().size <= 4) {
                            CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + operands[1].name, "Loading int constant");
                            //TODO: No need
                            // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing int constant");
                        }
                        else {
                            //TODO: handle  long long
                            auto [hi, lo] = getHighLowBytes(operands[1].name);
                            CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + hi, "Loading high part of long long");
                            CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name) + 4) + "($sp)", "Storing high part of long long");
                            CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + lo, "Loading low part of long long");
                            CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing low part of long long");
                        }
                    }
                }
                else {
                    if ((operands[1].type.type_tag != operands.back().type.type_tag) || operands[1].type.type_tag == FUNCTION_TYPE) {
                        error_msg("Incompatible types for variable assignment");
                        return;
                    }
                    if (operands[1].type.type_tag == STANDARD_TYPE) {

                        if (operands[1].type.standard_type->name == operands.back().type.standard_type->name) {

                            //get rvalue register
                            GPR secondReg = get_gpr(operands[1]);

                            if (operands.back().size <= 4) {
                                if (!is_float(operands[1].type)) {
                                    CodeGen::add_to_asm("move " + get_gpr_name(resultReg) + ", " + get_gpr_name(secondReg), "Loading int constant");
                                    // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)");
                                }
                                else {
                                    CodeGen::add_to_asm("mov.s " + get_gpr_name(resultReg) + ", " + get_gpr_name(secondReg), "Loading float constant");
                                }
                            }
                            else {
                                if (!is_float(operands.back().type)) {
                                    //TODO: handle  long long
                                    // CodeGen::add_to_asm("move "+ get_gpr_name(resultReg)+ ", "+ get_gpr_name(secondReg) );
                                }
                                else {
                                    CodeGen::add_to_asm("mov.d " + get_gpr_name(resultReg) + ", " + get_gpr_name(secondReg), "Loading double constant");
                                }
                            }

                            check_last_use(secondReg, line_number);
                        }
                        else {
                            // Handle type conversion between standard types
                            // Integer to float
                            // TODO: currently this one is for float not double

                            // Get register for rvalue  operand
                            GPR secondReg = get_gpr(operands[1]);


                            if (!is_float(operands[1].type) && is_float(operands.back().type)) {

                                // allocate temporary FP register 
                                GPR fpReg = f0;

                                // move to FP register
                                CodeGen::add_to_asm("mtc1 " + get_gpr_name(secondReg) + ", " + get_gpr_name(fpReg), "Move to FP register");

                                // Assign the value to result resultReg
                                CodeGen::add_to_asm("cvt.s.w " + get_gpr_name(resultReg) + ", " + get_gpr_name(fpReg), "Convert int to float");


                                free_gpr(fpReg);
                            }
                            // Float to integer
                            else if (is_float(operands[1].type) && !is_float(operands.back().type)) {
                                // allocate FP register
                                GPR fpReg = f0;

                                // Convert float to int
                                CodeGen::add_to_asm("cvt.w.s " + get_gpr_name(fpReg) + ", " + get_gpr_name(secondReg), "Convert float to int");

                                // Store result to resultReg
                                CodeGen::add_to_asm("mfc1 " + get_gpr_name(resultReg) + ", " + get_gpr_name(fpReg), "Move from FP register");



                                free_gpr(fpReg);
                            }
                            else {
                                output_msg("Unsupported type conversion");
                            }

                            check_last_use(resultReg, line_number);

                        }
                    }
                    else {
                        // We perform a shallow copy of the pointers for any other type
                        GPR lvalue = get_gpr(operands[1]);
                        CodeGen::add_to_asm("move " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands[1].name)), "Shallow copy of pointer");
                        check_last_use(lvalue, line_number);
                    }

                }
                check_last_use(resultReg, line_number);
            }
            else {
                error_msg("Invalid number of operands for LOCAL statement");
                return;
            }
            break;
        }
        break;
        case GLOBAL_St:
        {
            CodeGen::add_to_asm(".globl " + CodeGen::convert_to_valid(operands.back().name), "", false);
        }
        case STATIC_St:
        {
            if (operands.size() == 2) {
                int typ = is_float(operands.back().type) ? 1 : 0;
                CodeGen::add_to_data(CodeGen::convert_to_valid(operands.back().name), operands.back().size, "0", typ);
            }
            else if (operands.size() == 3) {
                int typ = is_float(operands.back().type) ? 1 : 0;
                CodeGen::add_to_data(CodeGen::convert_to_valid(operands.back().name), operands.back().size, operands[1].name, typ);
            }
        }
        break;
        case DATA_St:
        {
            CodeGen::add_to_data(CodeGen::convert_to_valid(operands.back().name), operands.back().size, operands[0].name, 2);
        }
        break;
        default:
        {
            error_msg("Invalid VariableStatement type");
        }
        }
    };

    // Function implementations

    void create_quad(std::string result, std::string op1, BinaryOp op, std::string op2, bool left_const, bool right_const) {
        Quad quad;
        quad.is_conditional = false;
        quad.op = op;
        quad.line_number = curr_line;

        if (left_const) {
            quad.operands.push_back(Operand(op1, true));
        }
        else {
            quad.operands.push_back(Operand(op1, false));
        }

        if (right_const) {
            quad.operands.push_back(Operand(op2, true));
        }
        else {
            quad.operands.push_back(Operand(op2, false));
        }

        quad.operands.push_back(Operand(result, false));
        statements.push_back(std::make_unique<Quad>(quad));

        // Add operands to map
        for (const auto& operand : quad.operands) {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_triple(std::string result, bool is_const, UnaryOp op, SpecialOp special_op, std::string op1) {
        Triple triple;
        triple.op = op;
        triple.special_op = special_op;
        triple.line_number = curr_line;

        if (is_const) {
            triple.operands.push_back(Operand(op1, true));
        }
        else {
            triple.operands.push_back(Operand(op1, false));
        }

        triple.operands.push_back(Operand(result, false));

        statements.push_back(std::make_unique<Triple>(triple));

        // Add operands to map
        for (const auto& operand : triple.operands) {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_double(std::string result, std::string op1, bool is_const, bool is_str) {
        Double double_stmt;
        double_stmt.string_lit = is_str;
        double_stmt.str = op1;
        double_stmt.line_number = curr_line;

        if (!is_str) {
            if (is_const) {
                double_stmt.operands.push_back(Operand(op1, true));
            }
            else {
                double_stmt.operands.push_back(Operand(op1, false));
            }
        }

        double_stmt.operands.push_back(Operand(result, false));

        statements.push_back(std::make_unique<Double>(double_stmt));

        // Add operands to map
        for (const auto& operand : double_stmt.operands) {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_label_statement(std::string _name) {
        // _name will be of the form identifier:
        // So we remove the last colon
        if (_name[_name.length() - 1] == ':') {
            _name = _name.substr(0, _name.length() - 1);
        }

        auto it = tac_labels.find(_name);
        if (it == tac_labels.end()) {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(_name, Label(_name, curr_line));
        }
        else {
            it->second = Label(_name, curr_line);
        }

        CommonStatement _statement = CommonStatement();
        _statement.type = LABEL_St;
        _statement.labels.push_back(tac_labels.at(_name));
        _statement.line_number = curr_line;
        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_func_statement(std::string function_name, std::string index) {
        if (function_name[function_name.length() - 1] == ':') {
            function_name = function_name.substr(0, function_name.length() - 1);
        }

        auto it = tac_labels.find(function_name);
        if (it == tac_labels.end()) {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(function_name, Label(function_name, curr_line));
        }
        else {
            it->second = Label(function_name, curr_line);
        }
        CommonStatement _statement = CommonStatement();
        _statement.type = FUNC_St;
        _statement.labels.push_back(tac_labels.at(function_name));
        _statement.line_number = curr_line;
        statements.push_back(std::make_unique<CommonStatement>(_statement));

        MMU::add_to_func_map(function_name, index);
        curr_line++;
    }

    void create_if_statement(std::string op1, std::string op2, BinaryOp op, std::string label, bool left_const, bool right_const) {
        Quad quad;
        quad.is_conditional = true;
        quad.op = op;
        quad.line_number = curr_line;

        if (op < 12) {
            // Throw error message
            return;
        }

        if (left_const) {
            quad.operands.push_back(Operand(op1, true));
        }
        else {
            quad.operands.push_back(Operand(op1, false));
        }

        if (right_const) {
            quad.operands.push_back(Operand(op2, true));
        }
        else {
            quad.operands.push_back(Operand(op2, false));
        }

        if (tac_labels.find(label) == tac_labels.end()) {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(label, Label(label, -1));
        }
        quad.labels.push_back(tac_labels.at(label));

        statements.push_back(std::make_unique<Quad>(quad));

        // Add operands to map
        for (const auto& operand : quad.operands) {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_return_statement(std::string result, bool is_const) {
        CommonStatement _statement = CommonStatement();
        _statement.type = RETURN_St;
        _statement.line_number = curr_line;

        if (result != "") {
            if (is_const) {
                _statement.operands.push_back(Operand(result, true));
            }
            else {
                _statement.operands.push_back(Operand(result, false));
            }
        }

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        // Add operands to map
        for (const auto& operand : _statement.operands) {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_call_statement(std::string function_name, std::string arg_count) {
        CommonStatement _statement = CommonStatement();
        _statement.type = CALL_St;
        if (tac_labels.find(function_name) == tac_labels.end()) {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(function_name, Label(function_name, -1));
        }
        _statement.labels.push_back(tac_labels.at(function_name));
        _statement.operands.push_back(Operand(arg_count, true));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_call_statement(std::string ret, std::string function_name, std::string arg_count) {
        CommonStatement _statement = CommonStatement();
        _statement.type = CALL_St;
        if (tac_labels.find(function_name) == tac_labels.end()) {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(function_name, Label(function_name, -1));
        }
        _statement.labels.push_back(tac_labels.at(function_name));
        _statement.operands.push_back(Operand(arg_count, true));
        _statement.operands.push_back(Operand(ret, false));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_param_statement(std::string param, bool is_const) {
        CommonStatement _statement = CommonStatement();
        _statement.type = PARAM_St;
        _statement.line_number = curr_line;

        if (is_const) {
            _statement.operands.push_back(Operand(param, true));
        }
        else {
            _statement.operands.push_back(Operand(param, false));
        }

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        // Add operands to map
        for (const auto& operand : _statement.operands) {
            add_operand(operand);
        }
        curr_line++;
    }

    void create_pop_statement(std::string sz) {
        CommonStatement _statement = CommonStatement();
        _statement.type = POP_St;
        _statement.operands.push_back(Operand(sz, true));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_goto_statement(std::string label) {
        CommonStatement _statement = CommonStatement();
        _statement.type = GOTO_St;
        if (tac_labels.find(label) == tac_labels.end()) {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(label, Label(label, -1));
        }
        _statement.labels.push_back(tac_labels.at(label));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_variable_statement(VariableType type, std::string var, std::string ind) {
        VariableStatement _statement = VariableStatement();
        _statement.type = type;
        _statement.operands.push_back(Operand(ind, true));
        _statement.operands.push_back(Operand(var, false));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<VariableStatement>(_statement));

        // Add operands to map
        for (const auto& operand : _statement.operands) {
            add_operand(operand);
        }
        curr_line++;
    }

    void create_variable_statement_assign(VariableType type, std::string var, std::string rval, bool is_constant, std::string ind) {
        VariableStatement _statement = VariableStatement();
        _statement.type = type;
        _statement.operands.push_back(Operand(ind, true));
        _statement.operands.push_back(Operand(rval, is_constant));
        _statement.operands.push_back(Operand(var, false));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<VariableStatement>(_statement));

        // Add operands to map
        for (const auto& operand : _statement.operands) {
            add_operand(operand);
        }
        curr_line++;
    }

    void create_enter_statement() {
        CommonStatement _statement = CommonStatement();
        _statement.type = ENTER_St;
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_exit_statement() {
        CommonStatement _statement = CommonStatement();
        _statement.type = EXIT_St;
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void optimise_tac() {
        output_msg("Optimising TAC...");
        init_gpr_map();
        for (const auto& statement : statements) {
            statement->generate_assembly();
        }
    }

    void print_assembly() {
        output_msg("Printing assembly...");

        assembly_file << ".data\n";
        assembly_file << CodeGen::data_stream.str();

        assembly_file << "\n\n.text\n";
        assembly_file << CodeGen::asm_stream.str();
    }

    bool check_last_use(int reg, int line_number) {
        ///debug last used
        CodeGen::add_to_asm("# Last used: " + get_gpr_name(static_cast<GPR>(reg)) + " " + std::to_string(last_used[gpr_map[static_cast<GPR>(reg)].name]) + " curr line " + std::to_string(line_number), "Debug last used");
        if (last_used[gpr_map[static_cast<GPR>(reg)].name] == line_number) {
            free_gpr(static_cast<GPR>(reg));
            return 1;
        }
        return 0;
    }

}