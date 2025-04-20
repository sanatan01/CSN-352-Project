#include <tacgen.h>

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

void create_label_statement(std::string name, int location) {
    tac_labels.emplace(name, Label(name, location));
    CommonStatement _statement = CommonStatement();
    _statement.type = LABEL_St;
    _statement.labels.push_back(tac_labels.at(name));
    statements.push_back(std::make_unique<CommonStatement>(_statement));
}



