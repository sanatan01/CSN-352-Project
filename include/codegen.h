#pragma once

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <tacgen.h>
#include <utils.h>
#include <memory>
#include <fstream>
#include <iomanip>

namespace backend
{

    class TACStatement;
    class Operand;

    enum GPR
    {
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
        sp = 29,    // MMU pointer
        fp = 30,    // Frame pointer
        ra = 31,    // Return address
        f0 = 32,
        f1 = 33,
        f2 = 34,
        f3 = 35,
        f4 = 36,
        f5 = 37,
        f6 = 38,
        f7 = 39,
        f8 = 40,
        f9 = 41,
        f10 = 42,
        f11 = 43,
        f12 = 44,
        f13 = 45,
        f14 = 46,
        f15 = 47,
        f16 = 48,
        f17 = 49,
        f18 = 50,
        f19 = 51,
        f20 = 52,
        f21 = 53,
        f22 = 54,
        f23 = 55,
        f24 = 56,
        f25 = 57,
        f26 = 58,
        f27 = 59,
        f28 = 60,
        f29 = 61,
        f30 = 62,
        f31 = 63
    };

    std::string get_gpr_name(GPR reg);

    class Register
    {
    public:
        int value;
        std::string name;
        std::string reg_name;

        Register() : value(0), name(""), reg_name("") {}

        void free_reg();
        bool is_free();
    };

    extern std::map<GPR, Register> gpr_map;

    void init_gpr_map();

    GPR get_free_gpr(Operand op, bool load);
    void get_free_arg_gpr(std::vector<Operand> args, Operand ret);

    void set_gpr(GPR reg, std::string name);

    void free_gpr(GPR reg);
    void free_arg_gprs();
    void store_gpr(GPR reg, std::string name);

    void dump_all_regs();
    void free_all_regs();
    void restore_all_regs();

    GPR get_assigned_gpr(std::string name);
    GPR get_gpr(Operand op, bool load = true);

    class MMU
    {
    private:
        static std::vector<Operand> stack;
        static std::map<std::string, Operand> symbol_map; // This acts as the symbol table for backend

    public:
        static std::map<std::string, GlobalType> function_map;
        MMU() = delete;

        static void push(Operand op);
        static void pop(int size);
        static int get_offset(std::string name);

        static bool add_symbol(std::string name, int index, int loc);
        static bool add_symbol(std::string name, int size, GlobalType type, int loc = 0);

        static int get_symbol_size(std::string name);
        static Operand get_symbol(std::string name);
        static GlobalType *get_symbol_type(std::string name);
        static bool is_symbol_present(std::string name);
        static void add_to_func_map(std::string name, std::string index);
    };

    class CodeGen
    {
    public:
        static int current_scope;
        static int stack_pushed;
        static bool first_param;

        // Making things work
        static std::vector<std::vector<Register>> dump_map;

        static std::stringstream asm_stream;
        static std::stringstream data_stream;

        CodeGen() = delete;

        static std::string convert_to_valid(std::string str);

        static void add_to_asm(std::string txt, std::string comment, bool indent = true);
        static void add_to_data(std::string name, int size, std::string val, int type);
    };

    bool is_float(GlobalType typ);
    std::pair<std::string, std::string> getHighLowBytes(const std::string &decimalStr);
    std::pair<std::string, std::string> floatToIEEEHex(const std::string &inputStr, bool isDouble);
}