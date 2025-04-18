%{
#include <backend_helper.h>
#include <y.tab.h>

void displayLexer(const char * name, const char* text);
int check_type();
void tacError(const char* message, ...);
int tac_errorCount = 0;
int tac_yycolumn = 1;
static char* line_start = NULL;

extern FILE* tac_lex_file;

%}

%option prefix="tac_"
%option yylineno

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS          (u|U|l|L|ll|LL|ul|uL|Ul|UL|lu|lU|Lu|LU|ull|uLL|Ull|ULL|llu|llU|LLu|LLU)


%%

".call"     { displayLexer("CALL", yytext);}
".return"   { displayLexer("RETURN", yytext);}
".param"    { displayLexer("PARAM", yytext);}
".push"     { displayLexer("PUSH", yytext);}
".pop"      { displayLexer("POP", yytext);}
".goto"     { displayLexer("GOTO", yytext);}
".static"   { displayLexer("STATIC", yytext);}
".copy"     { displayLexer("COPY", yytext);}
".if"       { displayLexer("IF", yytext);}
".func"     { displayLexer("FUNC", yytext);}

{L}({L}|{D})*":" { displayLexer("LABEL", yytext);}
"t"({D})*        { displayLexer("TEMP", yytext);}
{L}({L}|{D})*    { displayLexer("IDENTIFIER", yytext);}


0[xX]{H}+{IS}?                   { displayLexer("CONSTANT_LITERAL", yytext);}
0{D}+{IS}?                       { displayLexer("CONSTANT_LITERAL", yytext);}
{D}+{IS}?                        { displayLexer("CONSTANT_LITERAL", yytext);}
L?'(\\.|[^\\'])+\'               { displayLexer("CONSTANT_LITERAL", yytext);}
{D}+{E}{FS}?                     { displayLexer("CONSTANT_LITERAL", yytext);}
{D}*"."{D}+({E})?{FS}?           { displayLexer("CONSTANT_LITERAL", yytext);}
{D}+"."{D}*({E})?{FS}?           { displayLexer("CONSTANT_LITERAL", yytext);}


L?\"(\\.|[^\\"])*\"              { displayLexer("STRING_LITERAL", yytext);}


">>"        { displayLexer("RIGHT_OP", yytext); }
"<<"        { displayLexer("LEFT_OP", yytext); }
"&&"        { displayLexer("AND_OP", yytext); }
"||"        { displayLexer("OR_OP", yytext); }
"=="        { displayLexer("EQ_OP", yytext); }
"!="        { displayLexer("NE_OP", yytext); }
","         { displayLexer("COMMA", yytext); }
":"         { displayLexer("COLON", yytext); }
"="         { displayLexer("ASSIGN", yytext); }
"."         { displayLexer("DOT", yytext); }
"&"         { displayLexer("AMPERSAND", yytext); }
"!"         { displayLexer("EXCLAMATION", yytext); }
"~"         { displayLexer("TILDE", yytext); }
"-"         { displayLexer("MINUS", yytext); }
"+"         { displayLexer("PLUS", yytext); }
"*"         { displayLexer("ASTERISK", yytext); }
"/"         { displayLexer("SLASH", yytext); }
"%"         { displayLexer("PERCENT", yytext); }
"<"         { displayLexer("LESS_THAN", yytext); }
">"         { displayLexer("GREATER_THAN", yytext); }
"^"         { displayLexer("CARET", yytext); }
"|"         { displayLexer("PIPE", yytext); }

([\n]) {
    tac_yycolumn = 1;
    line_start = yytext + yyleng;
}
([ \t\v\f])* { }
. {}

%%

int yywrap(void) {
    return 1;
}

void displayLexer(const char* name, const char* text) {
    static int first_call = 1;

    if (tac_lex_file == NULL) {
        fprintf(stderr, "Error: output_file is not initialized\n");
        exit(EXIT_FAILURE);
    }

    if (first_call) {
        fprintf(tac_lex_file, "+----------------------+----------------------+\n");
        fprintf(tac_lex_file, "| %-20s | %-20s |\n", "Token", "Text");
        fprintf(tac_lex_file, "+----------------------+----------------------+\n");
        first_call = 0;
    }
    fprintf(tac_lex_file, "| %-20s | %-20s |\n", name, text);
    fflush(tac_lex_file); // Ensure the output is written to the file immediately
}

/* Add this function at the end */
void tacError(const char* message, ...) {
    va_list args;
    va_start(args, message);
    fprintf(stderr, "Lexical error at line %d: ", yylineno);
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
    va_end(args);
    tac_errorCount++;
}