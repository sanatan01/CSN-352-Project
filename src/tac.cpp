#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <tac.h>
#include <utils.h>

int label_count = 0;
int temp_count = 0;
std::vector<int> breakCase;
std::vector<int> continueCase;
std::vector<int> returnCase;
std::vector<int> gotoCase;
std::vector<int> trueCase;
std::vector<int> falseCase;
std::map<std::string, bool> labels;

std::ostringstream tac_stream;
std::ostringstream tac_temp_stream;
std::ostringstream tac_postfix_temp;

void TAC::dump_to_postfix() {
    tac_postfix_temp << tac_stream.str();
    tac_stream.str(""); // Clear the stream
    tac_stream.clear(); // Reset the stream state
}

void TAC::get_from_postfix() {
    tac_stream << tac_postfix_temp.str(); // Append entire content
    tac_postfix_temp.str("");             // Clear the buffer
    tac_postfix_temp.clear();
}

void TAC::transfer_from_postfix() {
    tac_stream << tac_postfix_temp.str();
    tac_postfix_temp.str(""); // Clear the buffer
    tac_postfix_temp.clear();
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
    tac_stream << tac_temp_stream.str(); // Append entire content
    tac_temp_stream.str("");             // Clear the buffer
    tac_temp_stream.clear();
}

void TAC::clear_stream() {
    tac_stream.str(""); // Clear the stream
    tac_stream.clear(); // Reset the stream state
}

void TAC::print_tac(std::string str) {
    if (str.length() >=5 && (str[1] == 'f' && str[2] == 'u' && str[3] == 'n' && str[4] == 'c')) {
        tac_stream << '\n' << '\n' << str << " #" << std::endl;
    }
    else if (str[0] == 'L') {
        tac_stream << "\n\t" << str << " #" << std::endl;
    }
    else {
        tac_stream << "\t\t" << str << " #" << std::endl;
    }
}

void TAC::print_tac(std::string result, std::string op1, std::string op, std::string op2) {
    print_tac(result + " = " + op1 + " " + op + " " + op2);
}

void TAC::add_label(Case labelCase) {
    switch (labelCase) {
    case BREAK_C:
        breakCase.push_back(label_count++);
        debug_msg("Break labels count: " + std::to_string(breakCase.size()));
        break;
    case CONTINUE_C:
        continueCase.push_back(label_count++);
        debug_msg("Continue labels count: " + std::to_string(continueCase.size()));
        break;
    case RETURN_C:
        returnCase.push_back(label_count++);
        debug_msg("Return labels count: " + std::to_string(returnCase.size()));
        break;
    case GOTO_C:
        gotoCase.push_back(label_count++);
        debug_msg("Goto labels count: " + std::to_string(gotoCase.size()));
        break;
    case TRUE_C:
        trueCase.push_back(label_count++);
        debug_msg("True labels count: " + std::to_string(trueCase.size()));
        break;
    case FALSE_C:
        falseCase.push_back(label_count++);
        debug_msg("False labels count: " + std::to_string(falseCase.size()));
        break;
    case LOOP_C:
        gotoCase.push_back(label_count++);
        debug_msg("Loop labels count: " + std::to_string(gotoCase.size()));
        break;
    default:
        debug_msg("Invalid label case");
        break;
    }
}

std::string TAC::get_label(Case caseLabel) {
    switch (caseLabel) {
    case BREAK_C:
        if (breakCase.empty()) {
            error_msg("No break label found");
            return "ERROR";
        }
        return "L" + std::to_string(breakCase.back());
    case CONTINUE_C:
        if (continueCase.empty()) {
            error_msg("No continue label found");
            return "ERROR";
        }
        return "L" + std::to_string(continueCase.back());
    case RETURN_C:
        if (returnCase.empty()) {
            error_msg("No return label found");
            return "ERROR";
        }
        return "L" + std::to_string(returnCase.back());
    case GOTO_C:
        if (gotoCase.empty()) {
            error_msg("No goto label found");
            return "ERROR";
        }
        return "L" + std::to_string(gotoCase.back());
    case TRUE_C:
        if (trueCase.empty()) {
            error_msg("No true label found");
            return "ERROR";
        }
        return "L" + std::to_string(trueCase.back());
    case FALSE_C:
        if (falseCase.empty()) {
            error_msg("No false label found");
            return "ERROR";
        }
        return "L" + std::to_string(falseCase.back());
    case LOOP_C:
        if (gotoCase.empty()) {
            error_msg("No loop label found");
            return "ERROR";
        }
        return "L" + std::to_string(gotoCase.back());
    default:
        error_msg("Invalid label case");
        return "ERROR";
    }
}

std::string TAC::get_temp() {
    return ".t" + std::to_string(temp_count++);
}

void TAC::enter_scope() {
    TAC::print_tac(".enter");
}

void TAC::exit_scope() {
    TAC::print_tac(".exit");
}

void TAC::print_label(Case labelCase) {
    switch (labelCase) {
    case BREAK_C:
        TAC::print_tac("L" + std::to_string(breakCase.back()) + ":");
        break;
    case CONTINUE_C:
        TAC::print_tac("L" + std::to_string(continueCase.back()) + ":");
        break;
    case RETURN_C:
        TAC::print_tac("L" + std::to_string(returnCase.back()) + ":");
        break;
    case GOTO_C:
        TAC::print_tac("L" + std::to_string(gotoCase.back()) + ":");
        break;
    case TRUE_C:
        TAC::print_tac("L" + std::to_string(trueCase.back()) + ":");
        break;
    case FALSE_C:
        TAC::print_tac("L" + std::to_string(falseCase.back()) + ":");
        break;
    case LOOP_C:
        TAC::print_tac("L" + std::to_string(gotoCase.back()) + ":");
        break;
    default:
        error_msg("Invalid label case");
    }
}

void TAC::remove_break_label() {
    if (breakCase.size() == 0) {
        error_msg("No break label found");
    }
    else {
        TAC::print_tac("L" + std::to_string(breakCase.back()) + ":");
        breakCase.pop_back();
    }
}

void TAC::remove_continue_label() {
    if (continueCase.size() == 0) {
        error_msg("No continue label found");
    }
    else {
        continueCase.pop_back();
    }
}

void TAC::remove_return_label() {
    if (returnCase.size() == 0) {
        error_msg("No return label found");
    }
    else {
        returnCase.pop_back();
    }
}

void TAC::remove_goto_label() {
    if (gotoCase.size() == 0) {
        error_msg("No goto label found");
    }
    else {
        gotoCase.pop_back();
    }
}

void TAC::remove_true_label() {
    if (trueCase.size() == 0) {
        error_msg("No true label found");
    }
    else {
        TAC::print_tac("L" + std::to_string(trueCase.back()) + ":");
        trueCase.pop_back();
    }
}

void TAC::remove_false_label() {
    if (falseCase.size() == 0) {
        error_msg("No false label found");
    }
    else {
        TAC::print_tac("L" + std::to_string(falseCase.back()) + ":");
        falseCase.pop_back();
    }
}

void TAC::create_function_definition(std::string function_name) {
    print_tac(".func " + function_name + ": " + std::to_string(SymbolTable::all_symbols.size() - 1));
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
        error_msg("Expression is null");
        return;
    }

    if(expr->name == "empty"){
        expr->name = "1";
    }

    switch (_case) {
    case BREAK_C:
        TAC::print_tac(".if " + expr->name + " == 0 .goto " + TAC::get_label(BREAK_C));
        break;
    case CONTINUE_C:
        TAC::print_tac(".if " + expr->name + " == 0 .goto " + TAC::get_label(CONTINUE_C));
        break;
    case RETURN_C:
        TAC::print_tac(".if " + expr->name + " == 0 .goto " + TAC::get_label(RETURN_C));
        break;
    case GOTO_C:
        TAC::print_tac(".if " + expr->name + " == 0 .goto " + TAC::get_label(GOTO_C));
        break;
    case TRUE_C:
        TAC::print_tac(".if " + expr->name + " == 0 .goto " + TAC::get_label(TRUE_C));
        break;
    case FALSE_C:
        TAC::print_tac(".if " + expr->name + " == 0 .goto " + TAC::get_label(FALSE_C));
        break;
    default:
        error_msg("Invalid case for goto conditional");
        break;
    }
}
void TAC::print_goto_do_while(class Expression* expr) {
    std::string new_temp = TAC::get_temp();
    TAC::print_tac(new_temp + " = !" + expr->name);
    TAC::print_tac(".if " + new_temp + " == 0 .goto " + TAC::get_label(CONTINUE_C));
}
void TAC::print_goto(int _case, bool remove) {
    switch (_case) {
    case BREAK_C:
        TAC::print_tac(".goto " + TAC::get_label(BREAK_C));
        if (remove) {
            TAC::remove_break_label();
        }
        break;
    case CONTINUE_C:
        TAC::print_tac(".goto " + TAC::get_label(CONTINUE_C));
        if (remove) {
            TAC::remove_continue_label();
        }
        break;
    case RETURN_C:
        TAC::print_tac(".goto " + TAC::get_label(RETURN_C));
        if (remove) {
            TAC::remove_return_label();
        }
        break;
    case GOTO_C:
        TAC::print_tac(".goto " + TAC::get_label(GOTO_C));
        if (remove) {
            TAC::remove_goto_label();
        }
        break;
    case TRUE_C:
        TAC::print_tac(".goto " + TAC::get_label(TRUE_C));
        if (remove) {
            TAC::remove_true_label();
        }
        break;
    case FALSE_C:
        TAC::print_tac(".goto " + TAC::get_label(FALSE_C));
        if (remove) {
            TAC::remove_false_label();
        }
        break;
    case LOOP_C:
        TAC::print_tac(".goto " + TAC::get_label(LOOP_C));
        if (remove) {
            TAC::remove_goto_label();
        }
        break;
    default:
        error_msg("Invalid case for goto");
        break;
    }
}

void TAC::add_jump_label(std::string name) {
    if(labels[name] == true) {
        error_msg("Same label defined twice");
    }
    labels[name] = true;
    TAC::print_tac(name + ":");
}

void TAC::print_goto_label(std::string name) {
    if(labels.count(name) == 0) {
        labels[name] = 0;
    }
    TAC::print_tac(".goto " + name);
}

void TAC::check_labels() {
    for(auto it : labels) {
        if(it.second == false) {
            error_msg("Label " + it.first + "was not found");
        }
    }
    labels.clear();
}