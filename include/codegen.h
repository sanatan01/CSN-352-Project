#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "symtab.h"
enum GPR {
    r0 = 0, // Constant 0
    at = 1, // Reserved for assembler
    v0 = 2, // Expression evaluation and
    v1 = 3, // results of a function
    a0 = 4, // Argument 1
    a1 = 5, // Argument 2
    a2 = 6, // Argument 3
    a3 = 7, // Argument 4
    t0 = 8, // Temporary (not preserved across call)
    t1 = 9, // Temporary (not preserved across call)
    t2 = 10, // Temporary (not preserved across call)
    t3 = 11, // Temporary (not preserved across call)
    t4 = 12, // Temporary (not preserved across call)
    t5 = 13, // Temporary (not preserved across call)
    t6 = 14, // Temporary (not preserved across call)
    t7 = 15, // Temporary (not preserved across call)
    s0 = 16, // Saved temporary (preserved across call)
    s1 = 17, // Saved temporary (preserved across call)
    s2 = 18, // Saved temporary (preserved across call)
    s3 = 19, // Saved temporary (preserved across call)
    s4 = 20, // Saved temporary (preserved across call)
    s5 = 21, // Saved temporary (preserved across call)
    s6 = 22, // Saved temporary (preserved across call)
    s7 = 23, // Saved temporary (preserved across call)
    t8 = 24, // Temporary (not preserved across call)
    t9 = 25, // Temporary (not preserved across call)
    k0 = 26, // Reserved for OS kernel
    k1 = 27, // Reserved for OS kernel
    gp = 28, // Pointer to global area
    sp = 29, // Stack pointer
    fp = 30, // Frame pointer
    ra = 31  // Return address
};

class Register {
public:
    int value;
    std::string name;
    std::string reg_name;

    Register() : value(0), name(""), reg_name("") {}
    void free_reg() {
        value = 0;
        name = "";
    }
};

extern std::map<GPR, Register> gpr_map;
void init_gpr_map();
std::string get_gpr_name(GPR reg);

class TACInstruction {
public:
    unsigned int line_number;
    
    TACInstruction() : line_number(0) {}
    TACInstruction(unsigned int line_number) : line_number(line_number) {}
    // Virtual print function that will be overridden by derived classes
    virtual void print() const {
        std::cerr <<line_number << "| " << std::endl;
    }
    
    // Virtual destructor for proper cleanup
    virtual ~TACInstruction() {}
};

class Quad: public TACInstruction {
public:
    std::string result;
    std::string op1;
    std::string op;
    std::string op2;
    
    Quad() : result(""), op1(""), op(""), op2("") {}
    Quad(const std::string& res, const std::string& op1, const std::string& op, const std::string& op2) : result(res), op1(op1), op(op), op2(op2) {}
    
    void print() const override {

        std::cerr <<line_number << "| " << result << " = " << op1 << " " << op << " " << op2 << std::endl;
    }
};

class Triplet: public TACInstruction {
public:
    std::string result;
    std::string op;
    std::string op1;

    Triplet() : result(""), op(""), op1("") {}
    Triplet(const std::string& res, const std::string& op, const std::string& op1) : result(res), op(op), op1(op1) {}
    
    void print() const override {
        std::cerr <<line_number << "| " << result << " = " << op << " " << op1 << std::endl;
    }
};

class Double: public TACInstruction {
public:
    std::string result;
    std::string op1;
    
    Double() : result(""), op1("") {}
    Double(const std::string& res, const std::string& op1) : result(res), op1(op1) {}
    
    void print() const override {
        std::cerr <<line_number << "| " << result << " = " << op1 << std::endl;
    }
};

class Label: public TACInstruction {
public:
    std::string label;
    
    Label() : label("") {}
    Label(const std::string& lbl) : label(lbl) {}
    
    void print() const override {
        std::cerr <<line_number << "| " << label << std::endl;
    }
};

class Goto: public TACInstruction {
public:
    Label goto_label;
    
    Goto() : goto_label("") {}
    Goto(const std::string& lbl) : goto_label(lbl) {}
    void print() const override {
        std::cerr <<line_number << "| " << ".goto " << goto_label.label << std::endl;
    }
};

class ConditionalGoto: public TACInstruction {
public:
    std::string op1;
    std::string op;
    std::string op2;
    Goto label;
    
    ConditionalGoto() : op1(""), op(""), op2(""), label("") {}
    ConditionalGoto(const std::string& op1, const std::string& op, const std::string& op2, const std::string& lbl) : op1(op1), op(op), op2(op2), label(lbl) {}
    
    void print() const override {
        std::cerr <<line_number << "| " << ".if " << op1 << " " << op << " " << op2 << " ";
        label.print();
    }
};

class Call: public TACInstruction {
public:
    std::string function_name;
    int num_args;
    
    Call() : function_name(""), num_args(0) {}
    Call(const std::string& fn, int args) : function_name(fn), num_args(args) {}
    void print() const override {
        std::cerr <<line_number << "| " << ".call " << function_name << " , " << num_args << std::endl;
    }
};

class Arg: public TACInstruction {
public:
    std::string arg_name;

    Arg() : arg_name("") {}
    Arg(const std::string& arg) : arg_name(arg) {}
    void print() const override {
        std::cerr <<line_number << "| " << ".param " << arg_name << std::endl;
    }
};

class Return: public TACInstruction {
public:
    std::string return_value; // change it to return value's address?
    
    Return() : return_value("") {}
    Return(const std::string& val) : return_value(val) {}
    void print() const override {
        if (!return_value.empty()) {
            std::cerr <<line_number << "| " << ".return " << return_value << std::endl;
        } else {
            std::cerr <<line_number << "| " << ".return" << std::endl;
        }
    }
};

class Push: public TACInstruction {
public:
    std::string variable; // do we need an enum for temp vs identifier?
    std::string size;
    int index;
    
    Push() : variable(""), size(""), index(0) {}
    Push(const std::string& var, const std::string& size, int idx) : variable(var), size(size), index(idx) {}
    void print() const override {
        std::cerr <<line_number << "| " << ".push " << variable << " " << size << " .index " << index << std::endl;
    }
};

class Pop: public TACInstruction {
public:
    std::string size;

    Pop() : size("") {}
    Pop(const std::string& size) : size(size) {}
    void print() const override {
        std::cerr <<line_number << "| " << ".pop " << size << std::endl;
    }
};

class Static: public TACInstruction {
public:
    std::string variable;
    std::string size;
    int index;
    
    Static(std::string variable, std::string size, int index) : variable(variable), size(size), index(index) {}
    Static(std::string variable, std::string name) : variable(variable), size(name), index(-1) {}
    
    void print() const override {
        if (index != -1) {
            std::cerr <<line_number << "| " << ".static " << variable << " " << size << " .index " << index << std::endl;
        } else {
            std::cerr <<line_number << "| " << ".static " << variable << " " << size << std::endl;
        }
    }
};

class Copy: public TACInstruction {
public:
    std::string op1;
    std::string op2;
    
    Copy() : op1(""), op2("") {}
    Copy(const std::string& op1, const std::string& op2) : op1(op1), op2(op2) {}
    void print() const override {
        std::cerr <<line_number << "| " << ".copy " << op1 << ", " << op2 << std::endl;
    }
};

extern std::vector<TACInstruction*> tac_instructions;
void print_tac_instructions();

// modify
extern std::map<Symbol*,unsigned int> live_map; // map of symbol to its line number in tac
void live_analysis();

