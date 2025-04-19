#include <helper.h>
#include <backend_helper.h>
#include <symtab.h>
#include <iostream>
#include <types.h>
#include <tac.h>
#include <codegen.h>
extern int yyparse();
extern int tac_parse();
extern FILE* yyin;
extern int yylineno;
extern int yycolumn;
FILE* output_file = NULL;
FILE* tac_lex_file = NULL;
std::fstream symbol_table_file;
std::ofstream tac_file;

void formatSymbolTable(){
    symbol_table_file << std::left << std::setw(15) << "Symbol:" << '|'
                      << std::left << std::setw(15) << "Scope:" << '|'
                      << std::left << std::setw(15) << "Line:" << '|'
                      << std::left << std::setw(15) << "Column:" << '|'
                      << std::left << std::setw(15) << "Return Type:" << '\n';
    symbol_table_file << "---------------------------------------------------------------------\n";
}

int main(int argc, char** argv) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <input_file> <lexer_file> <symtab_file> <3ac_file> <3ac_lex>\n", argv[0]);
        exit(1);
    }

    // ---------------- FRONTEND ------------------------

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening input file");
        exit(1);
    }

    output_file = fopen(argv[2], "w");
    if (!output_file) {
        std::cerr << "Error opening lexer output file" << std::endl;
        fclose(input_file);
        exit(1);
    }

    symbol_table_file.open(argv[3], std::ios::out);
    if (!symbol_table_file.is_open()) {
        std::cerr << "Error opening symbol table file" << std::endl;
        fclose(input_file);
        exit(1);
    }

    tac_file.open(argv[4], std::ios::out | std::ios::app);
    if (!tac_file.is_open()) {
        std::cerr << "Error opening 3AC file" << std::endl;
        fclose(input_file);
        exit(1);
    }

    formatSymbolTable(); // Format the symbol table header

    // Initialize built-in functions
    SymbolTable::initialize_built_ins();

    #ifdef _DEBUG_MODE
    std::cerr << "[  DEBUG  ] Debug mode is enabled." << std::endl;
    #endif

    yylineno = 1; // Initialize line number
    yyin = input_file;
    yyparse(); // Invoke the parser

    TAC::dump_to_file(); // Initialize TAC file
    TAC::check_labels();

    fclose(input_file);
    symbol_table_file.close();
    tac_file.close();
    fclose(output_file);

    // ---------------- BACKEND ------------------------

    // Open the 3AC file for reading
    FILE * tac_input_file = fopen(argv[4], "r");
    if (!tac_input_file) {
        std::cerr << "Error opening 3AC file" << std::endl;
        exit(1);
    }

    // Open the output file for writing
    tac_lex_file = fopen(argv[5], "w");
    if (!tac_lex_file) {
        std::cerr << "Error opening lexer output file" << std::endl;
        fclose(tac_input_file);
        exit(1);
    }

    tac_in = tac_input_file;
    tac_lineno = 1; // Initialize line number

    tac_parse();

    // Print the contents of tac_instructions to verify elements are being pushed into it
    std::cerr << "\n----- TAC Instructions -----\n";
    print_tac_instructions();
    std::cerr << "----- End of TAC Instructions -----\n";
    fclose(tac_input_file);
    fclose(tac_lex_file);

    return 0;
}
