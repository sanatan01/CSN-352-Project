#include <tacgen.h>
#include <utils.h>
#include <codegen.h>

namespace backend
{
    // Extern variables
    std::map<std::string, int> last_used;
    std::vector<std::unique_ptr<TACStatement>> statements;
    std::map<std::string, Label> tac_labels;

    int curr_line = 1;

    void add_operand(Operand op)
    {
        if (op.type == CONSTANT)
        {
            return;
        }

        last_used[op.name] = curr_line;
    }

    // Enum functions

    std::string get_type_name(StatementType type)
    {
        switch (type)
        {
        case COPY_St:
            return "COPY";
        case GOTO_St:
            return "GOTO";
        case STATIC_St:
            return "STATIC";
        case POP_St:
            return "POP";
        case PUSH_St:
            return "PUSH";
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

    std::string get_type_name(TACType type)
    {
        switch (type)
        {
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
    size_t get_size_const(std::string name)
    {
        // Placeholder function to get size of a variable
        // In a real implementation, this would look up the variable's type and return its size
        return 4; // Assuming 4 bytes for simplicity
    }

    size_t get_size(std::string name)
    {
        // Placeholder function to get size of a variable
        // In a real implementation, this would look up the variable's type and return its size
        return 4; // Assuming 4 bytes for simplicity
    }

    // TODO
    Operand::Operand(std::string name, bool is_const) : name(name)
    {
        if (is_const)
        {
            type = CONSTANT;
            size = get_size_const(name);
        }
        else
        {
            type = SIGNED;         // Assuming signed for non-constant
            size = get_size(name); // These need to be assigend later
        }
    }

    // Function implementations

    void create_quad(std::string result, std::string op1, BinaryOp op, std::string op2, bool left_const, bool right_const)
    {
        Quad quad;
        quad.is_conditional = false;
        quad.op = op;
        quad.line_number = curr_line;

        if (left_const)
        {
            quad.operands.push_back(Operand(op1, true));
        }
        else
        {
            quad.operands.push_back(Operand(op1, false));
        }

        if (right_const)
        {
            quad.operands.push_back(Operand(op2, true));
        }
        else
        {
            quad.operands.push_back(Operand(op2, false));
        }

        quad.operands.push_back(Operand(result, false));
        statements.push_back(std::make_unique<Quad>(quad));

        // Add operands to map
        for (const auto &operand : quad.operands)
        {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_triple(std::string result, bool is_const, UnaryOp op, SpecialOp special_op, std::string op1)
    {
        Triple triple;
        triple.op = op;
        triple.special_op = special_op;
        triple.line_number = curr_line;

        if (is_const)
        {
            triple.operands.push_back(Operand(op1, true));
        }
        else
        {
            triple.operands.push_back(Operand(op1, false));
        }

        triple.operands.push_back(Operand(result, false));

        statements.push_back(std::make_unique<Triple>(triple));

        // Add operands to map
        for (const auto &operand : triple.operands)
        {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_double(std::string result, std::string op1, bool is_const, bool is_str)
    {
        Double double_stmt;
        double_stmt.string_lit = is_str;
        double_stmt.str = op1;
        double_stmt.line_number = curr_line;

        if (!is_str)
        {
            if (is_const)
            {
                double_stmt.operands.push_back(Operand(op1, true));
            }
            else
            {
                double_stmt.operands.push_back(Operand(op1, false));
            }
        }

        double_stmt.operands.push_back(Operand(result, false));

        statements.push_back(std::make_unique<Double>(double_stmt));

        // Add operands to map
        for (const auto &operand : double_stmt.operands)
        {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_label_statement(std::string _name)
    {
        // _name will be of the form identifier:
        // So we remove the last colon
        if (_name[_name.length() - 1] == ':')
        {
            _name = _name.substr(0, _name.length() - 1);
        }

        auto it = tac_labels.find(_name);
        if (it == tac_labels.end())
        {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(_name, Label(_name, curr_line));
        }
        else
        {
            it->second = Label(_name, curr_line);
        }

        CommonStatement _statement = CommonStatement();
        _statement.type = LABEL_St;
        _statement.labels.push_back(tac_labels.at(_name));
        _statement.line_number = curr_line;
        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_func_statement(std::string function_name)
    {
        if (function_name[function_name.length() - 1] == ':')
        {
            function_name = function_name.substr(0, function_name.length() - 1);
        }

        auto it = tac_labels.find(function_name);
        if (it == tac_labels.end())
        {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(function_name, Label(function_name, curr_line));
        }
        else
        {
            it->second = Label(function_name, curr_line);
        }
        CommonStatement _statement = CommonStatement();
        _statement.type = FUNC_St;
        _statement.labels.push_back(tac_labels.at(function_name));
        _statement.line_number = curr_line;
        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_if_statement(std::string op1, std::string op2, BinaryOp op, std::string label, bool left_const, bool right_const)
    {
        Quad quad;
        quad.is_conditional = true;
        quad.op = op;
        quad.line_number = curr_line;

        if (op < 12)
        {
            // Throw error message
            return;
        }

        if (left_const)
        {
            quad.operands.push_back(Operand(op1, true));
        }
        else
        {
            quad.operands.push_back(Operand(op1, false));
        }

        if (right_const)
        {
            quad.operands.push_back(Operand(op2, true));
        }
        else
        {
            quad.operands.push_back(Operand(op2, false));
        }

        if (tac_labels.find(label) == tac_labels.end())
        {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(label, Label(label, -1));
        }
        quad.labels.push_back(tac_labels.at(label));

        statements.push_back(std::make_unique<Quad>(quad));

        // Add operands to map
        for (const auto &operand : quad.operands)
        {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_return_statement(std::string result, bool is_const)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = RETURN_St;
        _statement.line_number = curr_line;

        if (result != "")
        {
            if (is_const)
            {
                _statement.operands.push_back(Operand(result, true));
            }
            else
            {
                _statement.operands.push_back(Operand(result, false));
            }
        }

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        // Add operands to map
        for (const auto &operand : _statement.operands)
        {
            add_operand(operand);
        }

        curr_line++;
    }

    void create_call_statement(std::string function_name, std::string arg_count)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = CALL_St;
        if (tac_labels.find(function_name) == tac_labels.end())
        {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(function_name, Label(function_name, -1));
        }
        _statement.labels.push_back(tac_labels.at(function_name));
        _statement.operands.push_back(Operand(arg_count, true));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_param_statement(std::string param, bool is_const)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = PARAM_St;
        _statement.line_number = curr_line;

        if (is_const)
        {
            _statement.operands.push_back(Operand(param, true));
        }
        else
        {
            _statement.operands.push_back(Operand(param, false));
        }

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        // Add operands to map
        for (const auto &operand : _statement.operands)
        {
            add_operand(operand);
        }
        curr_line++;
    }

    void create_push_statement(std::string var, std::string sz, std::string index)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = PUSH_St;
        _statement.operands.push_back(Operand(var, false));
        _statement.operands.push_back(Operand(sz, true));
        _statement.operands.push_back(Operand(index, true));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        // Add operands to map
        for (const auto &operand : _statement.operands)
        {
            add_operand(operand);
        }
        curr_line++;
    }

    void create_pop_statement(std::string sz)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = POP_St;
        _statement.operands.push_back(Operand(sz, true));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_goto_statement(std::string label)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = GOTO_St;
        if (tac_labels.find(label) == tac_labels.end())
        {
            // The label has not appeared yet, we will create one
            tac_labels.emplace(label, Label(label, -1));
        }
        _statement.labels.push_back(tac_labels.at(label));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_static_statement(std::string var, std::string sz, std::string index)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = STATIC_St;
        _statement.operands.push_back(Operand(var, false));
        _statement.operands.push_back(Operand(sz, true));
        _statement.line_number = curr_line;
        if (index != "")
            _statement.operands.push_back(Operand(index, true));

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        // Add operands to map
        for (const auto &operand : _statement.operands)
        {
            add_operand(operand);
        }
        curr_line++;
    }

    void create_copy_statement(std::string result, std::string op1)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = COPY_St;
        _statement.operands.push_back(Operand(result, false));
        _statement.operands.push_back(Operand(op1, false));
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        // Add operands to map
        for (const auto &operand : _statement.operands)
        {
            add_operand(operand);
        }
        curr_line++;
    }

    void create_enter_statement()
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = ENTER_St;
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void create_exit_statement()
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = EXIT_St;
        _statement.line_number = curr_line;

        statements.push_back(std::make_unique<CommonStatement>(_statement));

        curr_line++;
    }

    void optimise_tac()
    {
        output_msg("Optimising TAC...");

        // Print the map
        // for (const auto &pair : last_used)
        // {
        //     output_msg(pair.first + ": " + std::to_string(pair.second));
        // }

        // Iterate through the statements and assign registers
        for (const auto &statement : statements)
        {
            // We dont need variables for certain statements we can skip
            if (statement->get_type() == COMMON) {
                CommonStatement *common_statement = static_cast<CommonStatement *>(statement.get());
                if (common_statement->type == GOTO_St || common_statement->type == STATIC_St || common_statement->type == POP_St ||
                    common_statement->type == PUSH_St || common_statement->type == FUNC_St || common_statement->type == LABEL_St ||
                    common_statement->type == ENTER_St || common_statement->type == EXIT_St)
                {
                    continue;
                }
            }

            std::string msg = "";
            for (const auto &operand : statement->operands)
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
                        msg += "# " + operand.name + " to " + get_gpr_name(reg) + " | ";
                    }
                    else
                    {
                        msg += "Failed to assign " + operand.name + " to a register ";
                    }
                }
                else
                {
                    msg += operand.name + " to " + get_gpr_name(reg) + " | ";
                }
            }

            // Perform operations with the register

            // Free unused register
            for (const auto &operand : statement->operands)
            {
                if (operand.type == CONSTANT)
                {
                    continue;
                }

                if (last_used[operand.name] <= statement->line_number) {
                    GPR reg = get_assigned_gpr(operand.name);
                    if (reg != empty)
                    {
                        free_gpr(reg);
                        msg += "! " + operand.name + " from " + get_gpr_name(reg) + " | ";
                    }
                }
            }

            output_msg(std::to_string(statement->line_number) + ": " + msg);
        }
    }

}