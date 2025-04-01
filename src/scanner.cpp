#include <helper.h>
#include <symtab.h>
#include <iostream>
#include <types.h>

extern int yyparse();
extern FILE* yyin;
extern int yylineno;


int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(1);
    }

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening input file");
        exit(1);
    }

    yylineno = 1; // Initialize line number counter
    yyin = input_file;
    yyparse(); // Invoke the parser
    fclose(input_file);

    return 0;
}
