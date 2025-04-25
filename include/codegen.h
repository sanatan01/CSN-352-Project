#pragma once

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <tacgen.h>
#include <utils.h>
#include <memory>
#include <fstream>
#include <iomanip> // For std::hex

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
        sp = 29,    // MMU pointer
        fp = 30,    // Frame pointer
        ra = 31,     // Return address
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

    std::string get_gpr_name(GPR reg) {
        switch (reg) {
        case r0:
            return "$zero";
        case at:
            return "$at";
        case v0:
            return "$v0";
        case v1:
            return "$v1";
        case a0:
            return "$a0";
        case a1:
            return "$a1";
        case a2:
            return "$a2";
        case a3:
            return "$a3";
        case t0:
            return "$t0";
        case t1:
            return "$t1";
        case t2:
            return "$t2";
        case t3:
            return "$t3";
        case t4:
            return "$t4";
        case t5:
            return "$t5";
        case t6:
            return "$t6";
        case t7:
            return "$t7";
        case s0:
            return "$s0";
        case s1:
            return "$s1";
        case s2:
            return "$s2";
        case s3:
            return "$s3";
        case s4:
            return "$s4";
        case s5:
            return "$s5";
        case s6:
            return "$s6";
        case s7:
            return "$s7";
        case t8:
            return "$t8";
        case t9:
            return "$t9";
        case k0:
            return "$k0";
        case k1:
            return "$k1";
        case gp:
            return "$gp";
        case sp:
            return "$sp";
        case fp:
            return "$fp";
        case ra:
            return "$ra";
        case f0:
            return "$f0";
        case f1:
            return "$f1";
        case f2:
            return "$f2";
        case f3:
            return "$f3";
        case f4:
            return "$f4";
        case f5:
            return "$f5";
        case f6:
            return "$f6";
        case f7:
            return "$f7";
        case f8:
            return "$f8";
        case f9:
            return "$f9";
        case f10:
            return "$f10";
        case f11:
            return "$f11";
        case f12:
            return "$f12";
        case f13:
            return "$f13";
        case f14:
            return "$f14";
        case f15:
            return "$f15";
        case f16:
            return "$f16";
        case f17:
            return "$f17";
        case f18:
            return "$f18";
        case f19:
            return "$f19";
        case f20:
            return "$f20";
        case f21:
            return "$f21";
        case f22:
            return "$f22";
        case f23:
            return "$f23";
        case f24:
            return "$f24";
        case f25:
            return "$f25";
        case f26:
            return "$f26";
        case f27:
            return "$f27";
        case f28:
            return "$f28";
        case f29:
            return "$f29";
        case f30:
            return "$f30";
        case f31:
            return "$f31";
        default:
            return "empty";
        }
    }


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

    GPR get_free_gpr(Operand op);

    void set_gpr(GPR reg, std::string name);

    void free_gpr(GPR reg);
    void store_gpr(GPR reg, std::string name);

    GPR get_assigned_gpr(std::string name);
    GPR get_gpr(Operand op);

    class MMU {
    private:
        static std::vector<Operand> stack;
        static std::map<std::string, Operand> symbol_map; // This acts as the symbol table for backend

    public:
        MMU() = delete;

        static void push(Operand op);
        static void pop(int size);
        static int get_offset(std::string name);

        static bool add_symbol(std::string name, int index);
        static bool add_symbol(std::string name, int size, GlobalType type);

        static int get_symbol_size(std::string name);
        static Operand get_symbol(std::string name);
        static GlobalType* get_symbol_type(std::string name);
        static bool is_symbol_present(std::string name);
    };

    class CodeGen {
    public:
        static int current_scope;

        static std::stringstream asm_stream;
        static std::stringstream data_stream;

        CodeGen() = delete;

        static std::string convert_to_valid(std::string str);

        static void add_to_asm(std::string txt, bool indent = true);
        static void add_to_data(std::string txt, bool indent = true);
        static std::stringstream& get_asm_stream();
        static std::stringstream& get_data_stream();

        static std::vector<Operand> set_operands(const TACStatement& statement);
        static std::vector<GPR> get_used_gprs(const TACStatement& statement);
        static std::stringstream generate_asm(const TACStatement& statement, std::vector<GPR>& used_gprs);
        static std::stringstream generate_data(const TACStatement& statement);
    };

    std::string generate_asm_str(std::string txt, bool indent = true);
    std::string data_str(std::string name, int size, bool is_asssigned, long long val);
    std::string data_str_float(std::string name, int size, bool is_assigned, long double val);
    bool is_float(GlobalType typ);
    std::pair<std::string, std::string> getHighLowBytes(const std::string &decimalStr);
    std::pair<std::string, std::string> floatToIEEEHex(const std::string &inputStr, bool isDouble);
}