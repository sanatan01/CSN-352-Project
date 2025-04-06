#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "tac.h"

int label_count = 0;
int temp_count = 0;

std::vector<int> breakCase;
std::vector<int> continueCase;
std::vector<int> returnCase;
std::vector<int> gotoCase;
std::vector<int> trueCase;
std::vector<int> falseCase;

std::ostringstream tac_stream;
std::ostringstream tac_temp_stream;

void TAC::print_tac(std::string str) {
    if(str[0]=='L'){
        tac_stream << str << std::endl;
    }
    else{
        tac_stream << "\t" << str << std::endl;
    }
}

void TAC::print_tac(std::string result, std::string op1, std::string op, std::string op2) {
    tac_stream << '\t' << result << " = " << op1 << " " << op << " " << op2 << std::endl;
}

void TAC::dump_to_file() {
    tac_file << tac_stream.str();
    tac_stream.str(""); // Clear the stream
    tac_stream.clear(); // Reset the stream state
}

void TAC::dump_to_temp() {
    tac_temp_stream << tac_stream.str();
    tac_stream.str(""); // Clear the stream
    tac_stream.clear(); // Reset the stream state   
}

void TAC::get_from_temp() {
    tac_stream << tac_temp_stream.str();  // Append entire content
    tac_temp_stream.str("");              // Clear the buffer
    tac_temp_stream.clear(); 
}

void TAC::clear_stream() {
    tac_stream.str(""); // Clear the stream
    tac_stream.clear(); // Reset the stream state
}

void TAC::add_label(Case labelCase) {
    switch (labelCase)
    {
    case BREAK_C:
        breakCase.push_back(label_count++);
        std::cerr << "Break labels count: " << breakCase.size() << std::endl;
        break;
    case CONTINUE_C:
        continueCase.push_back(label_count++);
        std::cerr << "Continue labels count: " << continueCase.size() << std::endl;
        break;
    case RETURN_C:
        returnCase.push_back(label_count++);
        std::cerr << "Return labels count: " << returnCase.size() << std::endl;
        break;
    case GOTO_C:
        gotoCase.push_back(label_count++);
        std::cerr << "Goto labels count: " << gotoCase.size() << std::endl;
        break;
    case TRUE_C:
        trueCase.push_back(label_count++);
        std::cerr << "True labels count: " << trueCase.size() << std::endl;
        break;
    case FALSE_C:
        falseCase.push_back(label_count++);
        std::cerr << "False labels count: " << falseCase.size() << std::endl;
        break;
    default:
        std::cerr << "Error: Invalid label case" << std::endl;
        break;
    }
}

std::string TAC::get_label(Case caseLabel) {
    switch (caseLabel)
    {
    case BREAK_C:
        if (breakCase.empty()) {
            std::cerr << "Error: No break label found" << std::endl;
            return "ERROR";
        }
        return "L" + std::to_string(breakCase.back());
    case CONTINUE_C:
        if (continueCase.empty()) {
            std::cerr << "Error: No continue label found" << std::endl;
            return "ERROR";
        }
        return "L" + std::to_string(continueCase.back());
    case RETURN_C:
        if (returnCase.empty()) {
            std::cerr << "Error: No return label found" << std::endl;
            return "ERROR";
        }
        return "L" + std::to_string(returnCase.back());
    case GOTO_C:
        if (gotoCase.empty()) {
            std::cerr << "Error: No goto label found" << std::endl;
            return "ERROR";
        }
        return "L" + std::to_string(gotoCase.back());
    case TRUE_C:
        if (trueCase.empty()) {
            std::cerr << "Error: No true label found" << std::endl;
            return "ERROR";
        }
        return "L" + std::to_string(trueCase.back());
    case FALSE_C:
        if (falseCase.empty()) {
            std::cerr << "Error: No false label found" << std::endl;
            return "ERROR";
        }
        return "L" + std::to_string(falseCase.back());
    default:
        std::cerr << "Error: Invalid label case" << std::endl;
        return "ERROR";
    }
}

std::string TAC::get_temp() {
    return "t" + std::to_string(temp_count++);
}

void TAC::print_label(Case labelCase) {
    switch (labelCase)
    {
    case BREAK_C:
        TAC::print_tac( "L" + std::to_string(breakCase.back()) + ":" );
        break;
    case CONTINUE_C:
        TAC::print_tac( "L" + std::to_string(continueCase.back()) + ":" );
        break;
    case RETURN_C:
        TAC::print_tac( "L" + std::to_string(returnCase.back()) + ":" );
        break;
    case GOTO_C:
        TAC::print_tac( "L" + std::to_string(gotoCase.back()) + ":" );
        break;
    case TRUE_C:
        TAC::print_tac( "L" + std::to_string(trueCase.back()) + ":" );
        break;
    case FALSE_C:
        TAC::print_tac( "L" + std::to_string(falseCase.back()) + ":" );
        break;
    default:
        std::cerr << "Error: Invalid label case" << std::endl;
    }
}

void TAC::remove_break_label() {
    if (breakCase.size() == 0) {
        std::cerr << "Error: No break label found" << std::endl;
    }
    else {
        TAC::print_tac("L" + std::to_string(breakCase.back()) + ":");
        breakCase.pop_back();
    }
}

void TAC::remove_continue_label() {
    if (continueCase.size() == 0) {
        std::cerr << "Error: No continue label found" << std::endl;
    }
    else {
        continueCase.pop_back();
    }
}

void TAC::remove_return_label() {
    if (returnCase.size() == 0) {
        std::cerr << "Error: No return label found" << std::endl;
    }
    else {
        returnCase.pop_back();
    }
}

void TAC::remove_goto_label() {
    if (gotoCase.size() == 0) {
        std::cerr << "Error: No goto label found" << std::endl;
    }
    else {
        gotoCase.pop_back();
    }
}

void TAC::remove_true_label() {
    if (trueCase.size() == 0) {
        std::cerr << "Error: No true label found" << std::endl;
    }
    else {
        TAC::print_tac("L" + std::to_string(trueCase.back()) + ":");
        trueCase.pop_back();
    }
}

void TAC::remove_false_label() {
    if (falseCase.size() == 0) {
        std::cerr << "Error: No false label found" << std::endl;
    }
    else {
        TAC::print_tac("L" + std::to_string(falseCase.back()) + ":");
        falseCase.pop_back();
    }
}

void TAC::create_function_definition(std::string function_name) {
    print_tac("L_" + function_name + ":");;
}

void TAC::create_loop_statement() {
    add_label(CONTINUE_C);
    add_label(BREAK_C);
}

void TAC::create_if_statement() {
    add_label(FALSE_C);
    add_label(TRUE_C);
}

void TAC::print_goto_conditional(class Expression* expr, int _case) {

    if (expr == nullptr) {
        std::cerr << "Error: Expression is null" << std::endl;
        return;
    }

    switch (_case)
    {
    case BREAK_C:
        TAC::print_tac("if " + expr->name + " == 0 goto " + TAC::get_label(BREAK_C));
        break;
    case CONTINUE_C:
        TAC::print_tac("if " + expr->name + " == 0 goto " + TAC::get_label(CONTINUE_C));
        break;
    case RETURN_C:
        TAC::print_tac("if " + expr->name + " == 0 goto " + TAC::get_label(RETURN_C));
        break;
    case GOTO_C:
        TAC::print_tac("if " + expr->name + " == 0 goto " + TAC::get_label(GOTO_C));
        break;
    case TRUE_C:
        TAC::print_tac("if " + expr->name + " == 0 goto " + TAC::get_label(TRUE_C));
        break;
    case FALSE_C:
        TAC::print_tac("if " + expr->name + " == 0 goto " + TAC::get_label(FALSE_C));
        break;
    default:
        std::cerr << "Error: Invalid case for goto conditional" << std::endl;
        break;
    }
}
void TAC::print_goto_do_while( class Expression* expr){
    TAC::print_tac("if " + expr->name + " != 0 goto " + TAC::get_label(CONTINUE_C));
}
void TAC::print_goto(int _case, bool remove) {
    switch (_case)
    {
    case BREAK_C:
        TAC::print_tac("goto " + TAC::get_label(BREAK_C));
        if (remove) {
            TAC::remove_break_label();
        }
        break;
    case CONTINUE_C:
        TAC::print_tac("goto " + TAC::get_label(CONTINUE_C));
        if (remove) {
            TAC::remove_continue_label();
        }
        break;
    case RETURN_C:
        TAC::print_tac("goto " + TAC::get_label(RETURN_C));
        if (remove) {
            TAC::remove_return_label();
        }
        break;
    case GOTO_C:
        TAC::print_tac("goto " + TAC::get_label(GOTO_C));
        if (remove) {
            TAC::remove_goto_label();
        }
        break;
    case TRUE_C:
        TAC::print_tac("goto " + TAC::get_label(TRUE_C));
        if (remove) {
            TAC::remove_true_label();
        }
        break;
    case FALSE_C:
        TAC::print_tac("goto " + TAC::get_label(FALSE_C));
        if (remove) {
            TAC::remove_false_label();
        }
        break;
    default:
        std::cerr << "Error: Invalid case for goto" << std::endl;
        break;
    }
}