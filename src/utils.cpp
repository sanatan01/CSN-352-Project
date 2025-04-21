#include <utils.h>

void error_msg(std::string msg, int line_num, int column) {
    std::cerr << "[  ERROR  ] " << msg << " at line " << yylineno << ", column " << yycolumn << std::endl;
}

void warning_msg(std::string msg, int line_num, int column) {
    std::cerr << "[ WARNING ] " << msg << " at line " << yylineno << ", column " << yycolumn << std::endl;
}

void debug_msg(std::string msg, int line_num, int column) {
#ifdef _DEBUG_MODE

    std::cerr << "[  DEBUG  ] " << msg << " at line " << yylineno << ", column " << yycolumn << std::endl;

#endif
}

void output_msg(std::string msg) {
#ifdef _DEBUG_MODE
    std::cout << "[   ASM   ] " << msg << std::endl;
#endif
}