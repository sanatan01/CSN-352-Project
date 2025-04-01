#include <helper.h>
#include <symtab.h>
#include <iostream>
#include <types.h>

extern int yyparse();
extern FILE* yyin;
extern int yylineno;
std::fstream symbol_table_file;

void formatSymbolTable(){
    symbol_table_file << std::left << std::setw(15) << "Symbol:" << '|'
                      << std::left << std::setw(15) << "Scope:" << '|'
                      << std::left << std::setw(15) << "Line:" << '|'
                      << std::left << std::setw(15) << "Column:" << '|'
                      << std::left << std::setw(15) << "Return Type:" << '\n';
    symbol_table_file << "---------------------------------------------------------------------\n";
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_file> <symtab_file>\n", argv[0]);
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

    formatSymbolTable(); // Format the symbol table header

    yylineno = 1; // Initialize line number counter
    yyin = input_file;
    yyparse(); // Invoke the parser
    fclose(input_file);
    symbol_table_file.close();
    return 0;
}
