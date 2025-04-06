#include <helper.h>
#include <symtab.h>
#include <iostream>
#include <types.h>
#include <tac.h>

extern int yyparse();
extern FILE* yyin;
extern int yylineno;
extern int yycolumn;
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
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <input_file> <symtab_file> <3ac_file>\n", argv[0]);
        exit(1);
    }

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening input file");
        exit(1);
    }

    symbol_table_file.open(argv[2], std::ios::out);
    if (!symbol_table_file.is_open()) {
        std::cerr << "Error opening symbol table file" << std::endl;
        fclose(input_file);
        exit(1);
    }

    tac_file.open(argv[3], std::ios::out | std::ios::app);
    if (!tac_file.is_open()) {
        std::cerr << "Error opening 3AC file" << std::endl;
        fclose(input_file);
        exit(1);
    }

    formatSymbolTable(); // Format the symbol table header


    #ifdef _DEBUG_MODE
    std::cerr << "[DEBUG] Debug mode is enabled." << std::endl;
    #endif

    yylineno = 1; // Initialize line number
    yyin = input_file;
    yyparse(); // Invoke the parser

    TAC::dump_to_file(); // Initialize TAC file

    fclose(input_file);
    symbol_table_file.close();
    tac_file.close();
    return 0;
}
