#pragma once

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <tacgen.h>
#include <utils.h>
#include <memory>

namespace backend {

    enum GPR {
        empty = -1, // When GPR is not assigned
        r0 = 0,     // Constant 0
        at = 1,     // Reserved for assembler
        v0 = 2,     // Expression evaluation and
        v1 = 3,     // results of a function
        a0 = 4,     // Argument 1
        a1 = 5,     // Argument 2
        a2 = 6,     // Argument 3
        a3 = 7,     // Argument 4
        t0 = 8,     // Temporary (not preserved across call)
        t1 = 9,     // Temporary (not preserved across call)
        t2 = 10,    // Temporary (not preserved across call)
        t3 = 11,    // Temporary (not preserved across call)
        t4 = 12,    // Temporary (not preserved across call)
        t5 = 13,    // Temporary (not preserved across call)
        t6 = 14,    // Temporary (not preserved across call)
        t7 = 15,    // Temporary (not preserved across call)
        s0 = 16,    // Saved temporary (preserved across call)
        s1 = 17,    // Saved temporary (preserved across call)
        s2 = 18,    // Saved temporary (preserved across call)
        s3 = 19,    // Saved temporary (preserved across call)
        s4 = 20,    // Saved temporary (preserved across call)
        s5 = 21,    // Saved temporary (preserved across call)
        s6 = 22,    // Saved temporary (preserved across call)
        s7 = 23,    // Saved temporary (preserved across call)
        t8 = 24,    // Temporary (not preserved across call)
        t9 = 25,    // Temporary (not preserved across call)
        k0 = 26,    // Reserved for OS kernel
        k1 = 27,    // Reserved for OS kernel
        gp = 28,    // Pointer to global area
        sp = 29,    // Stack pointer
        fp = 30,    // Frame pointer
        ra = 31     // Return address
    };

    class Register {
    public:
        int value;
        std::string name;
        std::string reg_name;

        Register(): value(0), name(""), reg_name("") {}

        void free_reg();
        bool is_free();
    };

    extern std::map<GPR, Register> gpr_map;

    void init_gpr_map();

    std::string get_gpr_name(GPR reg);

    GPR get_free_gpr();

    void set_gpr(GPR reg, std::string name);

    void free_gpr(GPR reg);

    GPR get_assigned_gpr(std::string name);

    class Stack {
    private:
        static std::vector<Operand> stack;
        static std::map<std::string, Operand> symbol_map; // This acts as the symbol table for backend

    public:
        Stack() = delete;

        static void push(Operand op);
        static void pop(int size);
        static int get_offset(std::string name);

        static bool add_symbol(std::string name, int index);
        static bool add_symbol(std::string name, int size, OpType type);

        static int get_symbol_size(std::string name);
        static OpType get_symbol_type(std::string name);
        static bool is_symbol_present(std::string name);
    };

    class CodeGen {
    public:
        static int current_scope;

        CodeGen() = delete;

        static std::vector<GPR> get_used_gprs(const TACStatement& statement);
        static std::stringstream generate_asm(const TACStatement& statement, std::vector<GPR>& used_gprs);
        static std::stringstream generate_data(const TACStatement& statement);
    };

    std::string generate_asm_str(std::string txt, bool indent = true);
    std::string data_str(std::string name, int size, bool is_asssigned, long long val);
    std::string data_str_float(std::string name, int size, bool is_assigned, long double val);
}