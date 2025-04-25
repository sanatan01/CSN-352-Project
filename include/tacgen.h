#pragma once

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include <fstream>
#include <types.h>
#include <codegen.h>

extern std::fstream assembly_file;

namespace backend {

    extern std::map<std::string, int> last_used;

    class Label {
    public:
        std::string name;
        int location;

        Label(std::string name, int location)
            : name(name), location(location) {}

        // copy constructor
        Label(const Label& other)
            : name(other.name), location(other.location) {}
    };

    enum StorageLoc {
        TEMP,
        STACK,
        DATA,
    };

    class Operand {
    public:
        std::string name;
        size_t size;
        GlobalType type;
        bool is_constant;
        StorageLoc storage_loc;

        Operand() = default;
        Operand(std::string name, bool is_const);
        Operand(const Operand& other)
            : name(other.name), size(other.size), type(other.type),
            is_constant(other.is_constant), storage_loc(other.storage_loc) {}
    };

    enum TACType {
        QUAD,
        TRIPLE,
        DOUBLE,
        COMMON,
        VARIABLE
    };

    class TACStatement {
    public:
        std::vector<Operand> operands;
        std::vector<Label> labels;
        int line_number;

        // Explicitly define a copy constructor
        TACStatement(const TACStatement& other)
            : operands(other.operands), labels(other.labels), line_number(other.line_number) {}

        // Default constructor
        TACStatement() = default;

        // Default destructor
        virtual ~TACStatement() = default;

        // Virtual functions to be implemented by derived classes
        virtual TACType get_type() const = 0;

        virtual void set_operands() = 0;
        virtual void generate_asm() const = 0;

        virtual void generate_assembly() {
            set_operands();
            generate_asm();
        }


    };

    enum BinaryOp {
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

    enum SpecialOp {
        NONE_SP,
        AMPERSAND_SP,
        ASTERISK_SP,
    };

    enum UnaryOp {
        NOP,
        REF_OP,
        DEREF_OP,
        EXCLAMATION_OP,
        TILDE_OP,
        POS_OP,
        NEG_OP,
    };

    class Quad: public TACStatement { // This also includes conditional statements
    public:
        bool is_conditional;
        BinaryOp op;

        // Explicitly define a copy constructor
        Quad(const Quad& other): TACStatement(other), is_conditional(other.is_conditional), op(other.op) {}

        // Default constructor
        Quad(): is_conditional(false), op() {}

        // Override get_type to return QUAD
        TACType get_type() const override {
            return QUAD;
        }

        void set_operands() override;
        void generate_asm() const override;
    };

    class Triple: public TACStatement {
    public:
        UnaryOp op;
        SpecialOp special_op;

        // Explicitly define a copy constructor
        Triple(const Triple& other)
            : TACStatement(other), op(other.op), special_op(other.special_op) {}

        // Default constructor
        Triple(): op(), special_op() {}

        // Override get_type to return TRIPLE
        TACType get_type() const override {
            return TRIPLE;
        }

        void set_operands() override;
        void generate_asm() const override;
    };

    class Double: public TACStatement {
    public:
        bool string_lit;
        std::string str;

        // Explicitly define a copy constructor
        Double(const Double& other)
            : TACStatement(other), string_lit(other.string_lit), str(other.str) {}

        // Default constructor
        Double(): string_lit(false), str() {}

        // Override get_type to return DOUBLE
        TACType get_type() const override {
            return DOUBLE;
        }

        void set_operands() override;
        void generate_asm() const override;
    };

    enum StatementType {
        GOTO_St, // No register
        POP_St,  // No register
        PARAM_St,
        CALL_St,
        RETURN_St,
        FUNC_St,  // No Register
        LABEL_St, // No Register
        ENTER_St, // No Register
        EXIT_St,  // No Register
    };

    std::string get_type_name(StatementType type);

    std::string get_type_name(TACType type);

    class CommonStatement: public TACStatement {
    public:
        StatementType type;

        // Explicitly define a copy constructor
        CommonStatement(const CommonStatement& other): TACStatement(other), type(other.type) {}

        // Default constructor
        CommonStatement(): type() {}

        // Override get_type to return COMMON
        TACType get_type() const override {
            return COMMON;
        }

        void set_operands() override;
        void generate_asm() const override;
    };

    enum VariableType {
        GLOBAL_St,
        STATIC_St,
        LOCAL_St,
        DATA_St,
    };

    class VariableStatement: public TACStatement {
    public:
        VariableType type;

        VariableStatement(const VariableStatement& other): TACStatement(other), type(other.type) {}

        VariableStatement(): type() {}

        TACType get_type() const override {
            return VARIABLE;
        }

        void set_operands() override;
        void generate_asm() const override;
    };

    extern std::vector<std::unique_ptr<TACStatement>>
        statements;
    extern std::map<std::string, Label> tac_labels;

    // Function declarations
    void create_quad(std::string result, std::string op1, BinaryOp op, std::string op2, bool left_const, bool right_const);

    void create_triple(std::string result, bool is_const, UnaryOp op, SpecialOp special_op, std::string op1);

    void create_double(std::string result, std::string op1, bool is_const, bool is_str);

    void create_label_statement(std::string label);

    void create_func_statement(std::string function_name);

    void create_if_statement(std::string op1, std::string op2, BinaryOp op, std::string label, bool left_const, bool right_const);

    void create_return_statement(std::string result, bool is_const);

    void create_call_statement(std::string function_name, std::string arg_count);

    void create_param_statement(std::string param, bool is_const);

    void create_pop_statement(std::string sz);

    void create_goto_statement(std::string label);

    void create_variable_statement(VariableType type, std::string var, std::string ind);

    void create_variable_statement_assign(VariableType type, std::string var, std::string rval, bool is_constant, std::string ind);

    void create_enter_statement();

    void create_exit_statement();

    // Main function to make all changes to TAC

    void optimise_tac();

    void print_assembly();
}