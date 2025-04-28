#include <tacgen.h>
#include <utils.h>
#include <codegen.h>
#include <climits>

namespace backend {
    // Extern variables
    std::map<std::string, int> last_used;
    std::vector<std::unique_ptr<TACStatement>> statements;
    std::map<std::string, Label> tac_labels;

    std::vector<Operand> params;
    std::map<std::string, int> typeMask = {
        {"int", 1},
        {"unsigned int", 1},
        {"unsigned char", 1},
        {"unsigned short", 1},
        {"unsigned long", 1},
        {"char", 1},
        {"long", 1},
        {"short",1},
        {"unsigned short", 1},
        {"unsigned long long", 2},
        {"long long", 2},
        {"float", 3},
        {"double", 4},
    };

    std::map<std::string, PrimitiveTypes> cast_map = {
        {"int", INT_T},
        {"short", SHORT_T},
        {"long", INT_T},
        {"char", CHAR_T},
        {"float", FLOAT_T},
        {"double", DOUBLE_T},
        {"unsignedint", INT_T},
        {"unsignedshort", SHORT_T},
        {"unsignedlong", INT_T},
        {"unsignedchar", CHAR_T},
        {"unsignedlonglong", LLONG_T},
        {"longlong", LLONG_T},
        {"longdouble", DOUBLE_T},
        {"unsignedlongdouble", DOUBLE_T},
        {"bool", CHAR_T},
    };

    int curr_line = 1;

    void add_operand(Operand op) {
        if (op.is_constant) {
            return;
        }

        last_used[op.name] = curr_line;
    }

    std::string binaryOpToName(BinaryOp op) {
        switch (op) {
        case ADD:
            return "add";
        case SUB:
            return "sub";
        case MUL:
            return "mul";
        case DIV:
            return "div";
        case MOD:
            return "mod";
        case SHL:
            return "shl";
        case SHR:
            return "shr";
        case BITWISE_AND:
            return "and";
        case BITWISE_OR:
            return "or";
        case BITWISE_XOR:
            return "xor";
        case LOGICAL_AND:
            return "LOGICAL_AND";
        case LOGICAL_OR:
            return "LOGICAL_OR";
        case EQ:
            return "seq";
        case NE:
            return "sne";
        case LT:
            return "slt";
        case GT:
            return "sgt";
        case LE:
            return "sle";
        case GE:
            return "sge";
        default:
            return "operator unknown";
        }
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

    void Quad::calculate_def_use() {
        if (is_conditional) {
            if (!operands[0].is_constant) use.insert(operands[0].name);
            if (!operands[1].is_constant) use.insert(operands[1].name);
        }
        else {
            if (!operands[0].is_constant) use.insert(operands[0].name);
            if (!operands[1].is_constant) use.insert(operands[1].name);
            if (!operands[2].is_constant)def.insert(operands[2].name);
        }
    }


    void Quad::build_successors() {
        if (is_conditional) {
            successors.insert(line_number + 1);
            auto it = tac_labels.find(labels.back().name);
            if (it != tac_labels.end()) {
                successors.insert(it->second.location);
            }
            else {
                error_msg("Label not found in Quad");
            }

        }
        else {
            TACStatement::build_successors();
        }
    }

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

            if (is_conditional) {
                CodeGen::add_to_asm("", "Undeclared variable found in if statement");
                error_msg("Undeclared variable found in if statement");
                continue;
            }

            switch (op) {
            case ADD:
            {
                Operand old_op = Operand(operands[0]);
                if (old_op.type.type_tag == STRUCT_TYPE) {
                    Operand op = Operand();
                    GlobalType* typ = old_op.type.struct_type->get_member(std::stoi(operands[1].name));
                    if (typ->type_tag == POINTER_TYPE) {
                        op.type = *(create_pointer_type(typ->pointer_type->return_type, typ->pointer_type->ptr_level + 1, typ->getSpecifiers()));

                    }
                    else {
                        op.type = *(create_pointer_type(typ));
                    }
                    op.name = operands.back().name;
                    op.is_constant = false;
                    op.size = typ->getSize();
                    operands.back() = Operand(op);
                    operands.back().storage_loc = TEMP;
                    MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    break;
                }
            }
            case MUL:
            case MOD:
            case BITWISE_AND:
            case BITWISE_OR:
            case BITWISE_XOR:
            {
                Operand firstOp = Operand(operands[0]);
                Operand secondOp = Operand(operands[1]);
                if (firstOp.is_constant) {
                    operands[0] = Operand(secondOp);
                    operands[1] = Operand(firstOp);
                }
            }
            case DIV:
            case SUB:
            {
                if (!operands[0].is_constant) {
                    std::string name = operands.back().name;
                    operands.back() = Operand(operands[0]);
                    operands.back().name = name;
                    operands.back().is_constant = false;
                    operands.back().storage_loc = TEMP;
                    MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                }
                else {
                    std::string name = operands.back().name;
                    operands.back() = Operand(operands[1]);
                    operands.back().name = name;
                    operands.back().is_constant = false;
                    operands.back().storage_loc = TEMP;
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
                Operand firstOp = Operand(operands[0]);
                Operand secondOp = Operand(operands[1]);
                if (firstOp.is_constant) {
                    operands[0] = Operand(secondOp);
                    operands[1] = Operand(firstOp);
                    if (op == LT) {
                        op = GE;
                    }
                    else if (op == LE) {
                        op = GT;
                    }
                    else if (op == GE) {
                        op = LT;
                    }
                    else if (op == GT) {
                        op = LE;
                    }
                }
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
        if (is_conditional) {
            GPR lvalue = get_gpr(operands[0]);
            GPR rvalue = get_gpr(operands.back());
            if (operands[0].is_constant) {
                if (is_float(operands[0].type)) {
                    if (operands[0].size == 4) {
                        auto [hi, lo] = floatToIEEEHex(operands[0].name, false);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for float Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(lvalue), "Transferring constant to float Quad");
                        // Store 0 in another register
                        CodeGen::add_to_asm("mtc1 $zero, " + get_gpr_name(rvalue), "Transferring 0 to float Quad");
                    }
                    else {
                        auto [hi, lo] = floatToIEEEHex(operands[0].name, true);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(lvalue), "Transferring constant to double Quad");
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + lo, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(static_cast<GPR>(int(lvalue) + 1)), "Transferring constant to double Quad");
                        //Store 0 in another register
                        CodeGen::add_to_asm("mtc1 $zero, " + get_gpr_name(rvalue), "Transferring 0 to double Quad");
                        CodeGen::add_to_asm("mtc1 $zero, " + get_gpr_name(static_cast<GPR>(int(rvalue) + 1)), "Transferring 0 to double Quad");

                    }
                }
                else {
                    if (operands.back().size <= 4) {
                        CodeGen::add_to_asm("li " + get_gpr_name(lvalue) + ", " + operands[0].name, "Loading constant for Quad");
                    }
                    else {
                        ///TODO: long long to be handled
                    }
                }
            }
            if (is_float(operands[0].type)) {
                if (operands[0].size == 4) {
                    CodeGen::add_to_asm("c.eq.s " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue), "Conditional statement");
                }
                else {
                    CodeGen::add_to_asm("c.eq.d " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue), "Conditional statement");
                }

                CodeGen::add_to_asm("bc1t " + labels.back().name, "Conditional statement");

            }
            else {
                CodeGen::add_to_asm("beq " + get_gpr_name(lvalue) + ", $zero, " + labels.back().name, "Conditional statement");
            }
            check_last_use(lvalue, line_number);
            check_last_use(rvalue, line_number);
            return;
        }
        switch (op) {
        case ADD:
        {
            GPR lvalue = get_gpr(operands[2]);
            GPR rvalue1 = get_gpr(operands[0]);
            GPR rvalue2 = get_gpr(operands[1]);
            output_msg("Name of operand 2 is : " + operands[2].name + " Storage location is : " + std::to_string(operands[2].storage_loc));
            output_msg("Name of lvalue is : " + gpr_map[lvalue].name);

            if (operands[1].is_constant) {
                if (is_float(operands.back().type)) {
                    if (operands.back().size == 4) {
                        auto [hi, lo] = floatToIEEEHex(operands[1].name, false);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for float Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue2), "Transferring constant to float Quad");
                        CodeGen::add_to_asm("add.s " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Addition operation in Quad float constant");
                    }
                    else {
                        auto [hi, lo] = floatToIEEEHex(operands[1].name, true);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue2), "Transferring constant to double Quad");
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + lo, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(static_cast<GPR>(int(rvalue2) + 1)), "Transferring constant to double Quad");
                        CodeGen::add_to_asm("add.d " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Addition operation in Quad double constant");
                    }
                }
                else {
                    if (operands.back().size <= 4) {
                        CodeGen::add_to_asm("addi " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + operands[1].name, "Addition operation in Quad constant size<=4");
                    }
                    else {
                        // TODO: long long to be handled
                        //  CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                    }
                }
            }
            else {
                if (is_float(operands.back().type)) {
                    if (operands.back().size == 4) {
                        CodeGen::add_to_asm("add.s " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Addition operation in Quad float variable");
                    }
                    else {
                        CodeGen::add_to_asm("add.d " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Addition operation in Quad double variable");
                    }
                }
                else {
                    if (operands.back().size <= 4) {
                        CodeGen::add_to_asm("add " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Addition operation in Quad size<=4 for variabls:" + gpr_map[lvalue].name + ", " + gpr_map[rvalue1].name + ", " + gpr_map[rvalue2].name);
                    }
                    else {
                        // TODO: long long to be handled
                    }
                }
            }
            check_last_use(rvalue1, line_number);
            check_last_use(rvalue2, line_number);
            check_last_use(lvalue, line_number);
            CodeGen::add_to_asm("", "The registers lvalue, rvalue1,and rvalue2 are associated with names : " + gpr_map[lvalue].name + ", " + gpr_map[rvalue1].name + ", " + gpr_map[rvalue2].name);

        }
        break;
        case SUB:
        case DIV:
        {
            if (operands[0].is_constant) {
                GPR rvalue1 = get_gpr(operands[0]);
                GPR rvalue2 = get_gpr(operands[1]);
                GPR lvalue = get_gpr(operands[2]);

                if (is_float(operands.back().type)) {
                    if (operands.back().size == 4) {
                        auto [hi, lo] = floatToIEEEHex(operands[0].name, false);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for float Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue1), "Transferring constant to float Quad");
                        CodeGen::add_to_asm(binaryOpToName(op) + ".s " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad float constant");
                    }
                    else {
                        auto [hi, lo] = floatToIEEEHex(operands[0].name, true);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue1), "Transferring constant to double Quad");
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + lo, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(static_cast<GPR>(int(rvalue2) + 1)), "Transferring constant to double Quad");
                        CodeGen::add_to_asm(binaryOpToName(op) + ".d " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad double constant");
                    }
                }
                else {
                    if (operands.back().size <= 4) {
                        CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                        CodeGen::add_to_asm(binaryOpToName(op) + " " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad constant size<=4 for operands:" + gpr_map[lvalue].name + ", " + gpr_map[rvalue1].name + ", " + gpr_map[rvalue2].name);
                    }
                    else {
                        // TODO: long long to be handled
                        //  CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                    }
                }
                break;
            }
        }
        case MUL:
        {
            GPR lvalue = get_gpr(operands[2]);
            GPR rvalue1 = get_gpr(operands[0]);
            GPR rvalue2 = get_gpr(operands[1]);

            if (operands[1].is_constant) {
                if (is_float(operands.back().type)) {
                    if (operands.back().size == 4) {
                        auto [hi, lo] = floatToIEEEHex(operands[1].name, false);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for float Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue2), "Transferring constant to float Quad");
                        CodeGen::add_to_asm(binaryOpToName(op) + ".s " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad float constant");
                    }
                    else {
                        auto [hi, lo] = floatToIEEEHex(operands[1].name, true);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue2), "Transferring constant to double Quad");
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + lo, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(static_cast<GPR>(int(rvalue2) + 1)), "Transferring constant to double Quad");
                        CodeGen::add_to_asm(binaryOpToName(op) + ".d " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad double constant");
                    }
                }
                else {
                    if (operands.back().size <= 4) {
                        CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                        CodeGen::add_to_asm(binaryOpToName(op) + " " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad constant size<=4 for operands:" + gpr_map[lvalue].name + ", " + gpr_map[rvalue1].name + ", " + gpr_map[rvalue2].name);
                    }
                    else {
                        // TODO: long long to be handled
                        //  CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                    }
                }
            }
            else {
                if (is_float(operands.back().type)) {
                    if (operands.back().size == 4) {
                        CodeGen::add_to_asm(binaryOpToName(op) + ".s " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad float variable");
                    }
                    else {
                        CodeGen::add_to_asm(binaryOpToName(op) + ".d " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad double variable");
                    }
                }
                else {
                    if (operands.back().size <= 4) {
                        CodeGen::add_to_asm(binaryOpToName(op) + " " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad size<=4 for variables:" + gpr_map[lvalue].name + ", " + gpr_map[rvalue1].name + ", " + gpr_map[rvalue2].name);
                    }
                    else {
                        // TODO: long long to be handled
                    }
                }
            }
            check_last_use(rvalue1, line_number);
            check_last_use(rvalue2, line_number);
            check_last_use(lvalue, line_number);
        }

        break;
        case EQ:
        case NE:
        case LT:
        case GT:
        case GE:
        case LE:
        {
            GPR lvalue = get_gpr(operands[2]);
            GPR rvalue1 = get_gpr(operands[0]);
            GPR rvalue2 = get_gpr(operands[1]);

            if (operands[1].is_constant) {
                if (is_float(operands.back().type)) {
                    if (operands.back().size == 4) {
                        auto [hi, lo] = floatToIEEEHex(operands[1].name, false);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for float Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue2), "Transferring constant to float Quad");
                        CodeGen::add_to_asm(binaryOpToName(op) + ".s " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Mult/Sub/Div operation in Quad float constant");
                    }
                    else {
                        auto [hi, lo] = floatToIEEEHex(operands[1].name, true);
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue2), "Transferring constant to double Quad");
                        CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + lo, "Loading constant for double Quad");
                        CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(static_cast<GPR>(int(rvalue2) + 1)), "Transferring constant to double Quad");
                        CodeGen::add_to_asm(binaryOpToName(op) + ".d " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Relational operation in Quad double constant");
                    }
                }
                else {
                    if (operands.back().size <= 4) {
                        CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                        CodeGen::add_to_asm(binaryOpToName(op) + " " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Relational operation in Quad constant size<=4");
                    }
                    else {
                        //TODO: long long to be handled
                        CodeGen::add_to_asm("", "Long long is not handled in relational operation");
                        // CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                    }
                }
            }
            else {
                if (operands[0].is_constant) {
                    if (is_float(operands.back().type)) {
                        if (operands.back().size == 4) {
                            auto [hi, lo] = floatToIEEEHex(operands[0].name, false);
                            CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for float Quad");
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue1), "Transferring constant to float Quad");
                        }
                        else {
                            auto [hi, lo] = floatToIEEEHex(operands[0].name, true);
                            CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading constant for double Quad");
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(rvalue1), "Transferring constant to double Quad");
                            CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + lo, "Loading constant for double Quad");
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(static_cast<GPR>(int(rvalue1) + 1)), "Transferring constant to double Quad");
                        }
                    }
                    else {
                        if (operands.back().size <= 4) {
                            CodeGen::add_to_asm("li " + get_gpr_name(rvalue1) + ", " + operands[0].name, "Loading constant for Quad");
                        }
                        else {
                            //TODO: long long to be handled
                        }
                    }
                }
                if (is_float(operands.back().type)) {
                    if (operands.back().size == 4) {
                        CodeGen::add_to_asm(binaryOpToName(op) + ".s " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Relational operation in Quad float variable");
                    }
                    else {
                        CodeGen::add_to_asm(binaryOpToName(op) + ".d " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Relational operation in Quad double variable");
                    }
                }
                else {
                    if (operands.back().size <= 4) {
                        CodeGen::add_to_asm(binaryOpToName(op) + " " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "Relational operation in Quad size<=4 variable");
                    }
                    else {
                        // TODO: long long to be handled
                    }
                }
            }
            check_last_use(rvalue1, line_number);
            check_last_use(rvalue2, line_number);
            check_last_use(lvalue, line_number);
        }
        break;
        case MOD:
        {
            GPR lvalue = get_gpr(operands[2]);
            GPR rvalue1 = get_gpr(operands[0]);
            GPR rvalue2 = get_gpr(operands[1]);

            if (is_float(operands.back().type)) {
                error_msg("Modulus operation not supported for float found in codegen ");
                break;
            }

            if (operands[1].is_constant) {

                if (operands.back().size <= 4) {
                    CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                }
                else {
                    // TODO: long long to be handled
                    //  CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                }
            }

            if (operands.back().size <= 4) {
                CodeGen::add_to_asm("div " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "division for modulus operation in Quad constant size<=4");
                CodeGen::add_to_asm("mfhi " + get_gpr_name(lvalue), "Moving remainder for Modulus operation in Quad variable size<=4");
            }
            else {
                // TODO: long long to be handled
            }

            check_last_use(rvalue1, line_number);
            check_last_use(rvalue2, line_number);
            check_last_use(lvalue, line_number);
        }
        break;
        case BITWISE_AND:
        case BITWISE_OR:
        case BITWISE_XOR:
        {
            GPR lvalue = get_gpr(operands[2]);
            GPR rvalue1 = get_gpr(operands[0]);
            GPR rvalue2 = get_gpr(operands[1]);

            if (is_float(operands.back().type)) {
                error_msg("Modulus operation not supported for float found in codegen ");
                break;
            }

            if (operands[1].is_constant) {
                if (operands.back().size <= 4) {
                    CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                }
                else {
                    //TODO: long long to be handled
                    // CodeGen::add_to_asm("li " + get_gpr_name(rvalue2) + ", " + operands[1].name, "Loading constant for Quad");
                }
            }
            if (operands[0].is_constant) {
                if (operands.back().size <= 4) {
                    CodeGen::add_to_asm("li " + get_gpr_name(rvalue1) + ", " + operands[0].name, "Loading constant for Quad");
                }
                else {
                    //TODO: long long to be handled
                    // CodeGen::add_to_asm("li " + get_gpr_name(rvalue1) + ", " + operands[0].name, "Loading constant for Quad");
                }
            }

            if (operands.back().size <= 4) {
                CodeGen::add_to_asm(binaryOpToName(op) + " " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue1) + ", " + get_gpr_name(rvalue2), "bitwise operation in Quad constant size<=4");
                switch (operands.back().size) {
                case 1:
                    CodeGen::add_to_asm("andi " + get_gpr_name(lvalue) + ", " + get_gpr_name(lvalue) + ", 0xFF", "char bitwise op in Quad constant size<=4");
                    break;
                case 2:
                    CodeGen::add_to_asm("andi " + get_gpr_name(lvalue) + ", " + get_gpr_name(lvalue) + ", 0xFFFF", "short bitwise op operation in Quad constant size<=4");
                    break;
                default:
                    break;
                }
            }
            else {
                //TODO: long long to be handled
            }

            check_last_use(rvalue1, line_number);
            check_last_use(rvalue2, line_number);
            check_last_use(lvalue, line_number);
        }
        break;
        case LOGICAL_AND:
        case LOGICAL_OR:
        {
        }
        break;
        default:
        {
            error_msg("Reached default case in Quad generation");
        }
        break;
        };
    }

    // =================== Triple Functions ===================

    void Triple::calculate_def_use() {
        if (special_op == NONE_SP) {
            switch (op) {
            case TILDE_OP:
            case EXCLAMATION_OP:
            case POS_OP:
            case NEG_OP:
            case REF_OP:
                if (!operands[0].is_constant) use.insert(operands[0].name);
                if (!operands.back().is_constant) def.insert(operands.back().name);
                break;
            case DEREF_OP:
                if (!operands.back().is_constant) def.insert(operands.back().name);
            case NOP: // it should not reach here
            default:
                break;
            }
        }
        else if (special_op == ASTERISK_SP) {
            switch (op) {
            case NOP:
                if (!operands[0].is_constant) use.insert(operands[0].name);
                if (!operands[1].is_constant) use.insert(operands[1].name);
                // NOTE: we are taking the risky case and ignoring where * refers to
                break;
                // It shoule not reach here
            case TILDE_OP:
            case EXCLAMATION_OP:
            case POS_OP:
            case NEG_OP:
            case REF_OP:
            case DEREF_OP:
            default:
                break;
            }
        }
        else {
            // It should not reach here
        }
    }


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
                        op.size = 4;
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
                        op.size = 4;
                        operands.back() = Operand(op);
                        operands.back().storage_loc = TEMP;
                        MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    }
                    else {
                        Operand op = Operand();
                        op.name = operands.back().name;
                        op.is_constant = false;
                        op.type = *(create_pointer_type(&old_op.type));
                        op.size = 4;
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
                            op.size = op.type.getSize();
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
                            // error_msg("Dereferencing array type");
                            op.size = op.type.getSize();
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
                    CodeGen::add_to_asm("addi " + get_gpr_name(lvalue) + ", $sp, " + std::to_string(MMU::get_offset(operands[0].name)), "Loading address of " + operands[0].name);
                    // CodeGen::add_to_asm("lw " + get_gpr_name(lvalue) + ", " + std::to_string(MMU::get_offset(operands[0].name)) + "($sp)", "Loading address of " + operands[0].name);
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
                //TODO: add for float using c.eq.s and branching
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
                if (is_float(operands.back().type)) {
                    if (operands.back().size == 4) {
                        CodeGen::add_to_asm("mov.s " + get_gpr_name(rvalue) + get_gpr_name(lvalue), "Loading value of " + operands[0].name);
                    }
                    else {
                        CodeGen::add_to_asm("mov.d " + get_gpr_name(rvalue) + get_gpr_name(lvalue), "Loading value of " + operands[0].name);
                    }
                }
                else {
                    CodeGen::add_to_asm("move " + get_gpr_name(rvalue) + ", " + get_gpr_name(lvalue), "Loading value of " + operands[0].name);
                }
                check_last_use(rvalue, line_number);
            }
            break;
            case NEG_OP:
            {
                GPR rvalue = get_gpr(operands[0]);
                if (is_float(operands.back().type)) {
                    if (operands.back().size == 4) {
                        CodeGen::add_to_asm("neg.s " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue), "Loading value of " + operands[0].name);
                    }
                    else {
                        CodeGen::add_to_asm("neg.d " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue), "Loading value of " + operands[0].name);
                    }
                }
                else {
                    CodeGen::add_to_asm("neg " + get_gpr_name(lvalue) + ", " + get_gpr_name(rvalue), "Loading value of " + operands[0].name);
                }
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
            GPR address = s0;
            if (operands.back().storage_loc == DATA) {
                CodeGen::add_to_asm("la " + get_gpr_name(address) + ", " + CodeGen::convert_to_valid(operands.back().name), "Loading address of " + operands[0].name);
                CodeGen::add_to_asm("sw " + get_gpr_name(rvalue) + ", 0(" + get_gpr_name(address) + ")", "Storing value of " + operands[0].name);
            }
            else {
                CodeGen::add_to_asm("addi " + get_gpr_name(address) + ", $sp, " + std::to_string(MMU::get_offset(operands.back().name)), "Loading address of " + operands.back().name);
                CodeGen::add_to_asm("sw " + get_gpr_name(rvalue) + ", 0(" + get_gpr_name(address) + ")", "Storing value of " + operands[0].name);
            }

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
        default:
        {
            error_msg("Incorrect special op, not found of  any type");
        }
        }
        check_last_use(lvalue, line_number);
    };

    // =================== Double Functions ===================

    void Double::calculate_def_use() {
        if (!operands.back().is_constant)def.insert(operands.back().name);
        if (!operands[0].is_constant) use.insert(operands[0].name);
    }

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
            std::string name = operands.back().name;
            operands.back() = Operand(operands[0]);
            operands.back().name = name;
            operands.back().is_constant = false;
            operands.back().storage_loc = TEMP;
            MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);

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
                    // TODO: No need
                    //  CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing int constant");
                }
                else {
                    // TODO: handle  long long
                    CodeGen::add_to_asm("", "Got operands 0f size >= 4: as" + std::to_string(operands.back().size) + " with name " + operands.back().name);
                    // auto [hi, lo] = getHighLowBytes(operands[0].name);
                    // CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + hi, "Loading high part of long long");
                    // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name) + 4) + "($sp)", "Storing high part of long long");
                    // CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + lo, "Loading low part of long long");
                    // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing low part of long long");
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
                if (typeMask[operands[1].type.standard_type->name] == typeMask[operands.back().type.standard_type->name]) {

                    // get rvalue register
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
                            // TODO: handle  long long
                            //  CodeGen::add_to_asm("move "+ get_gpr_name(resultReg)+ ", "+ get_gpr_name(secondReg) );
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


    void CommonStatement::calculate_def_use() {
        switch (type) {
        case GOTO_St:
        case POP_St:
        case FUNC_St:
        case LABEL_St:
        case ENTER_St:
        case EXIT_St:
            break;
        case RETURN_St:
        case PARAM_St:
            if (!operands[0].is_constant) use.insert(operands[0].name);
            break;
        case CALL_St:
            if (!operands.back().is_constant) def.insert(operands.back().name);
            break;
        default:
            break;
        }
    }

    void CommonStatement::build_successors() {

        if (type == GOTO_St) {
            auto it = tac_labels.find(labels[0].name);
            if (it == tac_labels.end()) {
                error_msg("Label " + labels[0].name + " not found");
                return;
            }
            successors.insert(it->second.location);
        }
        else {
            TACStatement::build_successors();
        }
    }

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
                operands.back().type = GlobalType(*MMU::function_map[labels[0].name].function_type->return_type);
                operands.back().storage_loc = TEMP;
                if (operands.back().type.type_tag == STRUCT_TYPE || operands.back().type.type_tag == UNION_TYPE) {
                    operands.back().type = *(create_pointer_type(&operands.back().type));
                    operands.back().storage_loc = STACK;
                }
                operands.back().storage_loc = TEMP;
                operands.back().size = operands.back().type.getSize();
                operands.back().is_constant = false;
                MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
            }
            else {

                error_msg("Invalid TAC code, because lval should be declared before being used");
            }
        }

        if (type == CALL_St) {
            output_msg("Operand " + operands.back().name + " is in " + std::to_string(operands.back().size) + " bytes , with type " + operands.back().type.getType());
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

            if (CodeGen::current_scope == 1) {
                GPR arg_regs[] = { a0, a1, a2, a3, f0, f1 };
                for (auto reg : arg_regs) {
                    free_gpr(reg);
                }

                // Stack se pop

            }

            // Fetch the operands
            int sz = std::stoi(operands[0].name);
            CodeGen::add_to_asm("addi $sp, $sp, " + std::to_string(sz), "Pop " + std::to_string(sz) + " bytes from stack");
            MMU::pop(sz);
        }
        break;
        case FUNC_St:
        {
            CodeGen::current_func = labels[0].name;
            if (CodeGen::current_scope == 0) {
                CodeGen::add_to_asm("\n.globl " + labels[0].name, "", false);
            }

            // Function prologue
            CodeGen::add_to_asm(labels[0].name + ":", "", false);
            CodeGen::add_to_asm("# Function prologue", "");
            CodeGen::add_to_asm("addi $sp, $sp, -16", "Allocate stack space for function");
            CodeGen::add_to_asm("sw $ra, 12($sp)", "Store return address");
            CodeGen::add_to_asm("sw $fp, 8($sp)", "Store frame pointer");
            CodeGen::add_to_asm("addi $fp, $sp, 16", "Set frame pointer");
            CodeGen::add_to_asm("# Finished Function prologue", "");
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
            CodeGen::add_to_asm("j " + label, "Jump to label " + label);
        }
        break;
        case RETURN_St:
        {
            if (operands.size() == 1) {

                // Set return values
                GlobalType ret = GlobalType(*MMU::function_map[CodeGen::current_func].function_type->return_type);


                if (operands[0].is_constant) {
                    if (is_float(ret)) {

                        if (operands.back().size == 4) {
                            auto [hi, lo] = floatToIEEEHex(operands[1].name, false);
                            CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading float constant");
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(f0), "Moving float constant");
                        }
                        else {
                            auto [hi, lo] = floatToIEEEHex(operands[1].name, true);
                            CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + hi, "Loading double constant high");
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(f0), "Moving double constant high");
                            CodeGen::add_to_asm("li " + get_gpr_name(s0) + ", " + lo, "Loading double constant low");
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(s0) + ", " + get_gpr_name(static_cast<GPR>((int)f0 + 1)), "Moving double constant low");

                        }
                    }
                    else {

                        if (operands[0].size <= 4) {
                            CodeGen::add_to_asm("li " + get_gpr_name(v0) + ", " + operands[0].name, "Loading constant for return value");
                        }
                        else {
                            auto [hi, lo] = getHighLowBytes(operands[0].name);
                            CodeGen::add_to_asm("li " + get_gpr_name(v0) + ", " + hi, "Loading high part of long long");
                            CodeGen::add_to_asm("li " + get_gpr_name(v1) + ", " + lo, "Loading low part of long long");
                        }
                    }
                }
                else {
                    if (is_float(ret)) {
                        GPR ret_gpr = get_gpr(operands[0]);
                        if (operands[0].size == 4) {
                            CodeGen::add_to_asm("mov.s " + get_gpr_name(f0) + ", " + get_gpr_name(ret_gpr), "Loading float return value");
                        }
                        else {
                            CodeGen::add_to_asm("mov.d " + get_gpr_name(f0) + ", " + get_gpr_name(ret_gpr), "Loading double return value");
                        }
                        check_last_use(ret_gpr, line_number);
                    }
                    else if (ret.type_tag == STRUCT_TYPE || ret.type_tag == UNION_TYPE) {
                        GPR temp = get_assigned_gpr(operands[0].name);
                        if (temp != empty) {
                            store_gpr(temp, operands[0].name);
                        }

                        // Pushing to stack if no free registers
                        if (operands[0].storage_loc == DATA) {
                            // use s1 register to store address of data location
                            load_gpr(s1, operands[0], false);
                            set_gpr(s1, operands[0].name);
                        }
                        for (int j = 0; j < operands[0].size; j += 4) {
                            switch (operands[0].storage_loc) {
                            case STACK:
                                CodeGen::add_to_asm("sw " + get_gpr_name(s0) + ", " + std::to_string(MMU::get_offset(operands[0].name) + j) + "($sp)", "Getting return type from stack");
                                break;
                            case DATA:
                                CodeGen::add_to_asm("sw " + get_gpr_name(s0) + ", " + std::to_string(j) + "(" + get_gpr_name(s1) + ")", "Getting return type from data section");
                                break;
                            default:
                                error_msg("Invalid storage location for argument");
                                break;
                            }
                            CodeGen::add_to_asm("sw " + get_gpr_name(s0) + ", " + std::to_string(j) + "($a0)", "Setting return type on stack");
                        }
                        free_gpr(s1);
                        free_gpr(s0);
                    }
                    else {
                        GPR ret_gpr = get_gpr(operands[0]);
                        CodeGen::add_to_asm("move " + get_gpr_name(v0) + ", " + get_gpr_name(ret_gpr), "Loading int return value");
                        check_last_use(ret_gpr, line_number);
                    }
                }
            }
            // Function Epilogue
            CodeGen::add_to_asm("# Function epilogue", "");
            CodeGen::add_to_asm("move $sp, $fp", "Restore stack pointer");
            CodeGen::add_to_asm("lw $ra, -4($fp)", "Restore return address");
            CodeGen::add_to_asm("lw $fp, -8($fp)", "Restore frame pointer");
            CodeGen::add_to_asm("jr $ra", "Return to caller");
            CodeGen::add_to_asm("# Finished Function epilogue", "");
        }
        break;
        case CALL_St:
        {

            output_msg("Calling function " + labels[0].name + " with return type " + operands.back().type.getType() + " and size " + std::to_string(operands.back().size));

            // Stpre all args
            GPR arg_regs[] = { a0, a1, a2, a3};
            std::vector<Register> para;
            CodeGen::add_to_asm("addi, $sp, $sp, -16", "Pushing stack for args params");
            int j = 0;
            for (GPR reg : arg_regs) {
                CodeGen::add_to_asm("sw " + get_gpr_name(reg) + ", " + std::to_string(12 - (j * 4)) + "($sp)", "Pushing arg reg to stack");
                para.push_back(gpr_map[reg]);
                free_gpr(reg);
                j++;
            }

            CodeGen::arg_map.push_back(para);

            get_free_arg_gpr(params, operands.back());
            free_all_regs();
            CodeGen::add_to_asm("jal " + labels[0].name, "Jump to function");
            // Clear the stack pushed by params
            if (CodeGen::stack_pushed != 0) {
                MMU::pop(CodeGen::stack_pushed);
                CodeGen::add_to_asm("addi $sp, $sp, " + std::to_string(CodeGen::stack_pushed), "Clearing stack pushed params");
                CodeGen::stack_pushed = 0;
            }

            restore_all_regs();

            CodeGen::add_to_asm("addi $sp, $sp, 16", "Popping stack for args params");
            int i = 0;
            for (GPR reg : arg_regs) {
                gpr_map[reg] = CodeGen::arg_map.back()[i];
                CodeGen::add_to_asm("lw " + get_gpr_name(reg) + ", " + std::to_string(12 - (i * 4)) + "($sp)", "Pushing arg reg to stack");
                i++;
            }
            CodeGen::arg_map.pop_back();
            params.clear();

            // Set return values
            GlobalType ret = GlobalType(*MMU::function_map[CodeGen::current_func].function_type->return_type);



            if (is_float(ret)) {
                GPR ret_gpr = get_gpr(operands.back());
                if (operands.back().size == 4) {
                    CodeGen::add_to_asm("mov.s " + get_gpr_name(ret_gpr) + ", " + get_gpr_name(f0), "Loading float return value");
                }
                else {
                    CodeGen::add_to_asm("mov.d " + get_gpr_name(ret_gpr) + ", " + get_gpr_name(f0), "Loading double return value");
                }
                check_last_use(ret_gpr, line_number);
                check_last_use(f0, line_number);
            }
            else if (ret.type_tag == STRUCT_TYPE || ret.type_tag == UNION_TYPE) {
                GPR temp = get_assigned_gpr(operands.back().name);
                if (temp != empty) {
                    store_gpr(temp, operands.back().name);
                }

                // Pushing to stack if no free registers
                if (operands.back().storage_loc == DATA) {
                    // use s1 register to store address of data location
                    load_gpr(s1, operands.back(), false);
                    set_gpr(s1, operands.back().name);
                }
                for (int j = 0; j < operands.back().size; j += 4) {
                    switch (operands.back().storage_loc) {
                    case STACK:
                        CodeGen::add_to_asm("sw " + get_gpr_name(s0) + ", " + std::to_string(MMU::get_offset(operands.back().name) + j) + "($sp)", "Getting return type from stack");
                        break;
                    case DATA:
                        CodeGen::add_to_asm("sw " + get_gpr_name(s0) + ", " + std::to_string(j) + "(" + get_gpr_name(s1) + ")", "Getting return type from data section");
                        break;
                    default:
                        error_msg("Invalid storage location for argument");
                        break;
                    }
                    CodeGen::add_to_asm("sw " + get_gpr_name(s0) + ", " + std::to_string(j) + "($a0)", "Setting return type on stack");
                }
                free_gpr(s1);
                free_gpr(s0);
            }
            else {
                GPR ret_gpr = get_gpr(operands.back());
                CodeGen::add_to_asm("move " + get_gpr_name(ret_gpr) + ", " + get_gpr_name(v0), "Loading int return value");
                check_last_use(ret_gpr, line_number);
                check_last_use(v0, line_number);
            }

            output_msg("Calling function " + labels[0].name + " with return type " + operands.back().type.getType() + " and size " + std::to_string(operands.back().size));

        }
        break;
        case PARAM_St:
            params.push_back(operands[0]);
            break;
        default:
            break;
        }
    }

    // ================ Variable Functions ======================

    void VariableStatement::calculate_def_use() {
        if (operands.size() != 3) return; // No defs or uses
        if (!operands.back().is_constant) def.insert(operands.back().name);
        if (!operands[1].is_constant)use.insert(operands[1].name);
    }

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
                Operand op = Operand(operands.back());
                op.type = *(create_pointer_type(create_primitive_type(CHAR_T)));
                op.is_constant = false;
                op.storage_loc = DATA;
                operands.back() = Operand(op);
                MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type, static_cast<int>(DATA));
            }
            case ARG_St:
            {
                operands.back().is_constant = false;
                operands.back().type = GlobalType(*MMU::get_symbol_type(operands[0].name));
                operands.back().size = operands.back().type.getSize();
                output_msg("Setting arg type to " + operands.back().type.getType());
            }
            break;
            }
        }
    }

    void VariableStatement::update_arg_count() {
        if (type == ARG_St) {
            operands.back().storage_loc = static_cast<StorageLoc>(set_arg_type(operands.back()));
        }
        else {
            TACStatement::update_arg_count();
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
                            // TODO: No need
                            //  CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing int constant");
                        }
                        else {
                            // TODO: handle  long long
                            // auto [hi, lo] = getHighLowBytes(operands[1].name);
                            // CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + hi, "Loading high part of long long");
                            // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name) + 4) + "($sp)", "Storing high part of long long");
                            // CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + lo, "Loading low part of long long");
                            // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing low part of long long");
                        }
                    }
                }
                else {
                    if ((operands[1].type.type_tag != operands.back().type.type_tag) || operands[1].type.type_tag == FUNCTION_TYPE) {
                        error_msg("Incompatible types for variable assignment, the  types are " + operands[1].type.getType() + " and " + operands.back().type.getType() + " and names of operands are: " + operands[1].name + " and " + operands.back().name);
                        return;
                    }
                    if (operands[1].type.type_tag == STANDARD_TYPE) {

                        if (typeMask[operands[1].type.standard_type->name] == typeMask[operands.back().type.standard_type->name]) {
                            // get rvalue register
                            GPR secondReg = get_gpr(operands[1]);

                            if (operands.back().size <= 4) {
                                if (!is_float(operands[1].type)) {
                                    CodeGen::add_to_asm("", "Registers associated with result and second are: " + gpr_map[resultReg].name + " " + gpr_map[secondReg].name);
                                    CodeGen::add_to_asm("move " + get_gpr_name(resultReg) + ", " + get_gpr_name(secondReg), "Loading int constant");
                                    // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)");
                                }
                                else {
                                    CodeGen::add_to_asm("mov.s " + get_gpr_name(resultReg) + ", " + get_gpr_name(secondReg), "Loading float constant");
                                }
                            }
                            else {
                                if (!is_float(operands.back().type)) {
                                    // TODO: handle  long long
                                    //  CodeGen::add_to_asm("move "+ get_gpr_name(resultReg)+ ", "+ get_gpr_name(secondReg) );
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

    // ================ Cast Functions ======================

    void CastStatement::calculate_def_use() {
        if (!operands.back().is_constant) def.insert(operands.back().name);
        if (!operands[0].is_constant) use.insert(operands[0].name);
    }

    void CastStatement::set_operands() {
        // Set the operands for the CastStatement
        for (auto& operand : operands) {
            if (operand.is_constant) {
                continue;
            }

            if (MMU::is_symbol_present(operand.name)) {
                operand = Operand(MMU::get_symbol(operand.name));
                operand.type = *(create_primitive_type(cast_type));
                continue;
            }
            switch (cast_type) {
            case CHAR_T:
            case INT_T:
            case LLONG_T:
            case FLOAT_T:
            case DOUBLE_T:
            case SHORT_T:
            {
                operand.type = *(create_primitive_type(cast_type));
                operand.size = operand.type.getSize();
                operand.storage_loc = TEMP;
                operand.is_constant = false;
                MMU::add_symbol(operand.name, operand.size, operand.type);
            }
            break;
            default:
            {
                error_msg("Invalid cast type reached default");
                return;
            }

            }



        }
    }

    void CastStatement::generate_asm() const {
        // Generate assembly code for the CastStatement
        if (operands.size() != 2) {
            error_msg("Invalid number of operands for CAST statement");
            return;
        }

        GPR resultReg = get_gpr(operands.back(), true);

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
                    // TODO: No need
                    //  CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing int constant");
                }
                else {
                    // TODO: handle  long long
                    CodeGen::add_to_asm("", "Got operands 0f size >= 4: as" + std::to_string(operands.back().size) + " with name " + operands.back().name);
                    // auto [hi, lo] = getHighLowBytes(operands[0].name);
                    // CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + hi, "Loading high part of long long");
                    // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name) + 4) + "($sp)", "Storing high part of long long");
                    // CodeGen::add_to_asm("li " + get_gpr_name(resultReg) + ", " + lo, "Loading low part of long long");
                    // CodeGen::add_to_asm("sw " + get_gpr_name(resultReg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)", "Storing low part of long long");
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

                if (typeMask[operands[1].type.standard_type->name] == typeMask[operands.back().type.standard_type->name]) {

                    // get rvalue register
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
                            // TODO: handle  long long
                            //  CodeGen::add_to_asm("move "+ get_gpr_name(resultReg)+ ", "+ get_gpr_name(secondReg) );
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

    void create_double(std::string result, std::string op1, bool is_const) {
        Double double_stmt;
        double_stmt.line_number = curr_line;


        if (is_const) {
            double_stmt.operands.push_back(Operand(op1, true));
        }
        else {
            double_stmt.operands.push_back(Operand(op1, false));
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

    void create_cast_statement(std::string result, std::string cast_type1, std::string op1, bool is_constant) {
        CastStatement _statement = CastStatement();
        if (cast_map.find(cast_type1) == cast_map.end()) {
            error_msg("cast type: currently not supported" + cast_type1);
            return;
        }
        _statement.cast_type = cast_map[cast_type1];
        _statement.operands.push_back(Operand(op1, is_constant));
        _statement.operands.push_back(Operand(result, false));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CastStatement>(_statement));

        // Add operands to map
        for (const auto& operand : _statement.operands) {
            add_operand(operand);
        }
        curr_line++;
    }


    void build_successors() {
        output_msg("Building succesors...");

        for (auto& statement : statements) {
            statement->build_successors();
            std::string succ_all = "";
            for (const auto& succ : statement->successors) {
                succ_all += std::to_string(succ) + " ";
            }
            output_msg(" Successors for statement: " + std::to_string(statement->line_number) + " are: " + succ_all);
        }
    }

    void calculate_def_use() {
        output_msg("Calculating def-use...");

        for (auto& statement : statements) {
            statement->calculate_def_use();
            std::string def_all = "";
            for (const auto& def : statement->def) {
                def_all += def + " ";
            }
            std::string use_all = "";
            for (const auto& use : statement->use) {
                use_all += use + " ";
            }
            output_msg(" Defs for statement: " + std::to_string(statement->line_number) + " are: " + def_all);
            output_msg(" Uses for statement: " + std::to_string(statement->line_number) + " are: " + use_all);
        }
    }

    void liveness_analysis() {
        output_msg("Performing liveness analysis...");

        bool changed = true;
        while (changed) {
            changed = false;
            // iterate backwards for clarity, though order doesn’t actually matter
            for (int i = statements.size() - 1; i >= 0; --i) {
                auto& S = *statements[i];
                // live_out = ∪ live_in of all successors
                std::set<std::string> new_out;
                for (int j : S.successors) {
                    if (j > 0 && j <= statements.size()) {
                        new_out.insert(statements[j - 1]->live_in.begin(),
                                       statements[j - 1]->live_in.end());
                    }
                }

                // live_in = use ∪ (live_out - def)
                std::set<std::string> new_in = S.use;
                for (auto& v : new_out) {
                    if (!S.def.count(v))
                        new_in.insert(v);
                }

                // check for changes
                if (new_out != S.live_out || new_in != S.live_in) {
                    changed = true;
                    S.live_out.swap(new_out);
                    S.live_in.swap(new_in);
                }

            }
        }

        output_msg("Completed liveness analysis...");

        for (auto& statement : statements) {
            std::string live_in_all = "";
            for (const auto& live : statement->live_in) {
                live_in_all += live + " ";
            }
            std::string live_out_all = "";
            for (const auto& live : statement->live_out) {
                live_out_all += live + " ";
            }
            output_msg(" Live in for statement: " + std::to_string(statement->line_number) + " are: " + live_in_all);
            output_msg(" Live out for statement: " + std::to_string(statement->line_number) + " are: " + live_out_all);
        }

        // Set last_used according to liveness analysis
        for (auto& statement : statements) {
            for (const auto& live : statement->live_in) {
                last_used[live] = (statement->line_number + 1);
            }
        }

        for (auto& it : last_used) {
            output_msg("Last used: " + it.first + " " + std::to_string(it.second));
        }
    }

    void optimise_tac() {
        output_msg("Optimising TAC...");

        build_successors();
        calculate_def_use();

        statements.back()->successors = std::set<int>();

        liveness_analysis();

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
        /// debug last used
        CodeGen::add_to_asm("# Last used: " + get_gpr_name(static_cast<GPR>(reg)) + " " + std::to_string(last_used[gpr_map[static_cast<GPR>(reg)].name]) + " curr line " + std::to_string(line_number), "Debug last used");
        if (last_used[gpr_map[static_cast<GPR>(reg)].name] <= line_number) {
            free_gpr(static_cast<GPR>(reg));
            return 1;
        }
        return 0;
    }

}