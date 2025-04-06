#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <expression.h>

extern int label_count;
extern int temp_count;

extern std::ofstream tac_file;

extern std::vector<int> breakCase;
extern std::vector<int> continueCase;
extern std::vector<int> returnCase;
extern std::vector<int> gotoCase;
extern std::vector<int> trueCase;
extern std::vector<int> falseCase;

enum Case {
    BREAK_C,
    CONTINUE_C,
    RETURN_C,
    GOTO_C,
    TRUE_C,
    FALSE_C
};

class TAC {
public:
    TAC() = delete;
    static void dump_to_postfix();
    static void get_from_postfix();
    static void transfer_to_file();
    static void transfer_from_postfix();
    static void dump_to_file();
    static void dump_to_temp();
    static void get_from_temp();
    static void clear_stream();
    static void print_tac(std::string str);
    static void print_tac(std::string result, std::string op1, std::string op, std::string op2);
    

    static void add_label(Case labelCase);

    static std::string get_temp();

    static std::string get_label(Case labelCase);

    static void print_label(Case labelCase);

    static void remove_break_label();
    static void remove_continue_label();
    static void remove_return_label();
    static void remove_goto_label();
    static void remove_true_label();
    static void remove_false_label();

    static void create_function_definition(std::string function_name);
    static void create_loop_statement();

    static void create_if_statement();
    static void print_goto_conditional(class Expression* expr, int _case);
    static void print_goto_do_while(class Expression* expr);
    static void print_goto(int _case, bool remove);
};
