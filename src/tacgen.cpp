#include <tacgen.h>

namespace backend
{
    // Extern variables

    std::vector<std::unique_ptr<TACStatement>> statements;
    std::map<std::string, Label> tac_labels;

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
    }

    void create_triple(std::string result, bool is_const, UnaryOp op, SpecialOp special_op, std::string op1)
    {
        Triple triple;
        triple.op = op;
        triple.special_op = special_op;

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
    }

    void create_double(std::string result, std::string op1, bool is_const, bool is_str)
    {
        Double double_stmt;
        double_stmt.string_lit = is_str;
        double_stmt.str = op1;

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
    }

    void create_label_statement(std::string name, int location)
    {
        tac_labels.emplace(name, Label(name, location));
        CommonStatement _statement = CommonStatement();
        _statement.type = LABEL_St;
        _statement.labels.push_back(tac_labels.at(name));
        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void create_func_statement(std::string function_name, int location)
    {
        tac_labels.emplace(function_name, Label(function_name, location));
        CommonStatement _statement = CommonStatement();
        _statement.type = FUNC_St;
        _statement.labels.push_back(Label(function_name, location));
        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void create_if_statement(std::string op1, std::string op2, BinaryOp op, std::string label, bool left_const, bool right_const)
    {
        Quad quad;
        quad.is_conditional = true;
        quad.op = op;

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
    }

    void create_return_statement(std::string result, bool is_const)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = RETURN_St;

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
    }

    void create_call_statement(std::string function_name, std::string arg_count)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = CALL_St;
        _statement.operands.push_back(Operand(function_name, false));
        _statement.operands.push_back(Operand(arg_count, true));

        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void create_param_statement(std::string param, bool is_const)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = PARAM_St;

        if (is_const)
        {
            _statement.operands.push_back(Operand(param, true));
        }
        else
        {
            _statement.operands.push_back(Operand(param, false));
        }

        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void create_push_statement(std::string var, std::string sz, std::string index)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = PUSH_St;
        _statement.operands.push_back(Operand(var, false));
        _statement.operands.push_back(Operand(sz, true));
        _statement.operands.push_back(Operand(index, true));

        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void create_pop_statement(std::string sz)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = POP_St;
        _statement.operands.push_back(Operand(sz, true));

        statements.push_back(std::make_unique<CommonStatement>(_statement));
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

        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void create_static_statement(std::string var, std::string sz, std::string index)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = STATIC_St;
        _statement.operands.push_back(Operand(var, false));
        _statement.operands.push_back(Operand(sz, true));
        if (index != "")
            _statement.operands.push_back(Operand(index, true));

        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void create_copy_statement(std::string result, std::string op1)
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = COPY_St;
        _statement.operands.push_back(Operand(result, false));
        _statement.operands.push_back(Operand(op1, false));

        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void create_enter_statement()
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = ENTER_St;

        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void create_exit_statement()
    {
        CommonStatement _statement = CommonStatement();
        _statement.type = EXIT_St;

        statements.push_back(std::make_unique<CommonStatement>(_statement));
    }

    void optimise_tac()
    {
        // Placeholder for TAC optimisation logic
        // In a real implementation, this would contain logic to optimise the TAC statements
        // Prints the TAC statements in new file for now
    }

}