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
                    op.type = GlobalType(*typ);
                    op.name = operands.back().name;
                    op.is_constant = false;
                    op.size = typ->getSize();
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
                MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
            }
            break;
            default:
                break;

            }
        }



    }

    void Quad::generate_asm() const {
        return;
    };


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
                        MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    }
                    else {
                        Operand op = Operand();
                        op.name = operands.back().name;
                        op.is_constant = false;
                        op.type = *(create_pointer_type(&old_op.type));
                        operands.back() = Operand(op);
                        MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    }
                }
                case ASTERISK_SP: {
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
                        MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
                    }
                    else {
                        error_msg("Invalid TAC, cannot dereference a non-pointer type");
                    }
                }
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
        return;
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
                MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
            }

        }
    }

    void Double::generate_asm() const {
        return;
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

            error_msg("Invalid TAC code, because lval should be declared before being used");
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
            case GLOBAL_St:
            case STATIC_St:
            {
                MMU::add_symbol(operands.back().name, std::stoi(operands[0].name));
                Operand op = MMU::get_symbol(operands.back().name);
                operands.back() = Operand(op);
                operands.back().is_constant = false;
                MMU::add_symbol(operands.back().name, operands.back().size, operands.back().type);
            }
            case DATA_St: {
                //Nothing to do here, sed
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
                CodeGen::add_to_asm("addi $sp, $sp, -" + std::to_string((operands.back()).size) + '\n');
            }
            else if (operands.size() == 3) {

                MMU::push(operands.back());
                CodeGen::add_to_asm("addi $sp, $sp, -" + std::to_string((operands.back()).size) + '\n');

                GPR reg = get_gpr(operands.back().name);

                if (operands[1].is_constant) {
                    if (is_float(operands[1].type)) {
                        GPR float_reg = get_gpr(operands[1]);
                        if(operands[1].size==4){
                            auto [hi, lo] = floatToIEEEHex(operands[1].name, false);
                            CodeGen::add_to_asm("li " + get_gpr_name(reg) + ", " + hi + '\n');
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(reg) + ", " + get_gpr_name(float_reg) + '\n');
                            CodeGen::add_to_asm("s.s " + get_gpr_name(float_reg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)\n");
                            gpr_map[float_reg].name = operands.back().name;  
                        }
                        else{
                            auto [hi, lo] = floatToIEEEHex(operands[1].name, true);
                            CodeGen::add_to_asm("li " + get_gpr_name(reg) + ", " + hi + '\n');
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(reg) + ", " + get_gpr_name(float_reg) + '\n');
                            CodeGen::add_to_asm("li " + get_gpr_name(reg) + ", " + lo + '\n');
                            CodeGen::add_to_asm("mtc1 " + get_gpr_name(reg) + ", " + get_gpr_name(static_cast<GPR>((int)float_reg+1)) + '\n');
                            CodeGen::add_to_asm("s.d " + get_gpr_name(float_reg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)\n"); 
                            gpr_map[float_reg].name = operands.back().name;
                            gpr_map[static_cast<GPR>((int)float_reg+1)].name = operands.back().name;
                        }
                        free_gpr(reg);
                    }
                    else {
                        if (operands[1].size <= 4) {
                            CodeGen::add_to_asm("li " + get_gpr_name(reg) + ", " + operands[1].name + '\n');
                            CodeGen::add_to_asm("sw " + get_gpr_name(reg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)\n");
                        }
                        else {
                            auto [hi, lo] = getHighLowBytes(operands[1].name);
                            CodeGen::add_to_asm("li " + get_gpr_name(reg) + ", " + hi + '\n');
                            CodeGen::add_to_asm("sw " + get_gpr_name(reg) + ", " + std::to_string(MMU::get_offset(operands.back().name) + 4) + "($sp)\n");
                            CodeGen::add_to_asm("li " + get_gpr_name(reg) + ", " + lo + '\n');
                            CodeGen::add_to_asm("sw " + get_gpr_name(reg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)\n");
                            free_gpr(reg);
                        }
                    }

                }
                else {
                    if(operands[1].type.type_tag == STANDARD_TYPE && operands.back().type.type_tag == STANDARD_TYPE) {
                        if (operands[1].type.standard_type->name == operands.back().type.standard_type->name) {
                            if (operands[1].size <= 4) {
                                
                                CodeGen::add_to_asm("sw " + get_gpr_name(reg) + ", " + std::to_string(MMU::get_offset(operands.back().name)) + "($sp)\n");
                            }
                        }
                        else {
                            output_msg("Need to handle type conversion");
                        }
                    }
                }
            }
            else {
                error_msg("Invalid number of operands for LOCAL statement");
                return;
            }
            break;
        }
        break;
        case GLOBAL_St:
        case STATIC_St:
        case DATA_St:
        {
            
        }
        break;
        default: {
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

    void create_func_statement(std::string function_name) {
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

        for (const auto& statement : statements) {

            statement->generate_assembly();
            // // Get the registers being used
            // statement->operands = CodeGen::set_operands(*statement);
            // std::vector<GPR> used_gprs = CodeGen::get_used_gprs(*statement);
            // statement->asm_stream = CodeGen::generate_asm(*statement, used_gprs);
            // statement->data_stream = CodeGen::generate_data(*statement);

            // // Free unused register
            // for (const auto& operand : statement->operands) {
            //     if (operand.is_constant) {
            //         continue;
            //     }

            //     if (last_used[operand.name] <= statement->line_number) {
            //         GPR reg = get_assigned_gpr(operand.name);
            //         if (reg != empty) {
            //             free_gpr(reg);
            //             output_msg("Freed " + operand.name + " from " + get_gpr_name(reg));
            //         }
            //     }
            // }
        }
    }

    void print_assembly() {
        output_msg("Printing assembly...");

        assembly_file << ".data\n";
        for (const auto& statement : statements) {
            assembly_file << CodeGen::data_stream.str();
        }

        assembly_file << "\n\n.text\n";
        for (const auto& statement : statements) {
            assembly_file << CodeGen::asm_stream.str();
        }
    }

}