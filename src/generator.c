#include<stdio.h>
#include "generator.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

int main() {
    int ntoken, vtoken;
    ntoken = yylex();
    while (ntoken) {
        printf("Token: %d\n", ntoken);
        ntoken = yylex();
    }
    return 0;
}