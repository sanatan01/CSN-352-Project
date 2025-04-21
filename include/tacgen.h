#pragma once

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <memory>

class Label
{
public:
    std::string name;
    int location;

    Label(std::string name, int location)
        : name(name), location(location) {}

    // copy constructor
    Label(const Label &other)
        : name(other.name), location(other.location) {}
};

enum OpType
{
    SIGNED,
    FLOAT,
    UNSIGNED,
    STRUCT,
    UNION,
    POINTER,
    CONSTANT,
};

class Operand
{
public:
    std::string name;
    size_t size;
    OpType type;

    Operand(std::string name, bool is_const);
};

enum TACType
{
    QUAD,
    TRIPLE,
    DOUBLE,
    COMMON
};

class TACStatement
{
public:
    std::vector<Operand> operands;
    std::vector<Label> labels;
    std::stringstream asm_stream;

    // Explicitly define a copy constructor
    TACStatement(const TACStatement &other)
        : operands(other.operands), labels(other.labels)
    {
        asm_stream << other.asm_stream.str();
    }

    // Default constructor
    TACStatement() = default;

    // Default destructor
    virtual ~TACStatement() = default;

    virtual TACType get_type() const = 0;
};

enum BinaryOp
{
    ADD,         // PLUS
    SUB,         // MINUS
    MUL,         // ASTERISK
    DIV,         // SLASH
    MOD,         // PERCENT
    BITWISE_AND, // AMPERSAND
    BITWISE_XOR, // CARET
    BITWISE_OR,  // PIPE
    LOGICAL_AND, // AND_OP
    LOGICAL_OR,  // OR_OP
    SHL,         // LEFT_OP
    SHR,         // RIGHT_OP
    EQ,          // EQ_OP
    NE,          // NE_OP
    LT,          // LESS_THAN
    GT,          // GREATER_THAN
    GE,          // GE_OP
    LE           // LE_OP
};

enum SpecialOp
{
    NONE,
    AMPERSAND_SP,
    ASTERISK_SP,
};

enum UnaryOp
{
    NOP,
    REF_OP,
    DEREF_OP,
    EXCLAMATION_OP,
    TILDE_OP,
};

class Quad : public TACStatement
{ // This also includes conditional statements
public:
    bool is_conditional;
    BinaryOp op;

    // Explicitly define a copy constructor
    Quad(const Quad &other) : TACStatement(other), is_conditional(other.is_conditional), op(other.op) {}

    // Default constructor
    Quad() : is_conditional(false), op() {}

    // Override get_type to return QUAD
    TACType get_type() const override
    {
        return QUAD;
    }
};

class Triple : public TACStatement
{
public:
    UnaryOp op;
    SpecialOp special_op;

    // Explicitly define a copy constructor
    Triple(const Triple &other)
        : TACStatement(other), op(other.op), special_op(other.special_op) {}

    // Default constructor
    Triple() : op(), special_op() {}

    // Override get_type to return TRIPLE
    TACType get_type() const override
    {
        return TRIPLE;
    }
};

class Double : public TACStatement
{
public:
    bool string_lit;
    std::string str;

    // Explicitly define a copy constructor
    Double(const Double &other)
        : TACStatement(other), string_lit(other.string_lit), str(other.str) {}

    // Default constructor
    Double() : string_lit(false), str() {}

    // Override get_type to return DOUBLE
    TACType get_type() const override
    {
        return DOUBLE;
    }
};

enum StatementType
{
    COPY_St,
    GOTO_St,
    STATIC_St,
    POP_St,
    PUSH_St,
    PARAM_St,
    CALL_St,
    RETURN_St,
    FUNC_St,
    LABEL_St,
    ENTER_St,
    EXIT_St,
};

class CommonStatement : public TACStatement
{
public:
    StatementType type;

    // Explicitly define a copy constructor
    CommonStatement(const CommonStatement &other) : TACStatement(other), type(other.type) {}

    // Default constructor
    CommonStatement() : type() {}

    // Override get_type to return COMMON
    TACType get_type() const override
    {
        return COMMON;
    }
};

extern std::vector<std::unique_ptr<TACStatement>> statements;
extern std::map<std::string, Label> tac_labels;

// Function declarations
void create_quad(std::string result, std::string op1, BinaryOp op, std::string op2, bool left_const, bool right_const);

void create_triple(std::string result, bool is_const, UnaryOp op, SpecialOp special_op, std::string op1);

void create_double(std::string result, std::string op1, bool is_const, bool is_str);

void create_label_statement(std::string label, int location);

void create_func_statement(std::string function_name, int location);

void create_if_statement(std::string op1, std::string op2, BinaryOp op, std::string label, bool left_const, bool right_const);

void create_return_statement(std::string result, bool is_const);

void create_call_statement(std::string function_name, std::string arg_count);

void create_param_statement(std::string param, bool is_const);

void create_push_statement(std::string var, std::string sz, std::string index);

void create_pop_statement(std::string sz);

void create_goto_statement(std::string label);

void create_static_statement(std::string var, std::string sz, std::string index = "");

void create_copy_statement(std::string result, std::string op1);

void create_enter_statement();

void create_exit_statement();

// Main function to make all changes to TAC

void optimise_tac();
