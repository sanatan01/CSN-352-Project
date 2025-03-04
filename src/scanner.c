#include "helper.h"
extern FILE* yyin;
extern int yyparse();

// Symbol table implementation
SymbolEntry symbolTable[1000];
int symbolCount = 0;

// Constant table implementation
ConstantEntry constantTable[1000];
int constantCount = 0;


void insertSymbol(char* name, char* type, char* return_type) {
    symbolTable[symbolCount].name = strdup(name);
    symbolTable[symbolCount].type = strdup(type);
    symbolTable[symbolCount].return_type = strdup(return_type);
    symbolCount++;
}

void insertConstant(char* value, char* type) {
    constantTable[constantCount].value = strdup(value);
    constantTable[constantCount].type = strdup(type);
    constantCount++;
}


void displayTables() {
    // Symbol table display
    printf("\nSYMBOL TABLE:\n");
    printf("+-----------------+-----------------+-----------------+\n");
    printf("| %-15s | %-15s | %-15s |\n", "Name", "Type", "Return Type");
    printf("+-----------------+-----------------+-----------------+\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("| %-15s | %-15s | %-15s |\n",
               symbolTable[i].name,
               symbolTable[i].type,
               symbolTable[i].return_type);
    }
    printf("+-----------------+-----------------+-----------------+\n");
    
    // Constant table display
    // printf("\nCONSTANT TABLE:\n");
    // printf("+-----------------+-----------------+\n");
    // printf("| %-15s | %-15s |\n", "Value", "Type");
    // printf("+-----------------+-----------------+\n");
    // for (int i = 0; i < constantCount; i++) {
    //     printf("| %-15s | %-15s |\n",
    //            constantTable[i].value,
    //            constantTable[i].type);
    // }
    // printf("+-----------------+-----------------+\n");
}

extern int yylineno; // Add this at the top with other extern declarations

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

    displayTables(); // Display the symbol table

    return 0;
}
