#pragma once

#include <iostream>

extern int yycolumn;
extern int yylineno;

void error_msg(std::string msg, int line_num = 0, int column = 0);
void warning_msg(std::string msg, int line_num = 0, int column = 0);
void debug_msg(std::string msg, int line_num = 0, int column = 0);
void output_msg(std::string msg);