%{
#include <backend_helper.h>
#include <tac.tab.h>

void displayLexer(const char * name, const char* text);
int check_type();
void tacError(const char* message, ...);
int tac_errorCount = 0;
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

".call"     { displayLexer("CALL", yytext); tac_lval.string = strdup("CALL"); return CALL; }
".return"   { displayLexer("RETURN", yytext); tac_lval.string = strdup("RETURN"); return RETURN; }
".param"    { displayLexer("PARAM", yytext); tac_lval.string = strdup("PARAM"); return PARAM; }
".push"     { displayLexer("PUSH", yytext); tac_lval.string = strdup("PUSH"); return PUSH; }
".pop"      { displayLexer("POP", yytext); tac_lval.string = strdup("POP"); return POP; }
".goto"     { displayLexer("GOTO", yytext); tac_lval.string = strdup("GOTO"); return GOTO; }
".static"   { displayLexer("STATIC", yytext); tac_lval.string = strdup("STATIC"); return STATIC; }
".copy"     { displayLexer("COPY", yytext); tac_lval.string = strdup("COPY"); return COPY; }
".if"       { displayLexer("IF", yytext); tac_lval.string = strdup("IF"); return IF; }
".func"     { displayLexer("FUNC", yytext); tac_lval.string = strdup("FUNC"); return FUNC; }
".enter"    { displayLexer("ENTER", yytext); tac_lval.string = strdup("ENTER"); return ENTER; }
".exit"     { displayLexer("EXIT", yytext); tac_lval.string = strdup("EXIT"); return EXIT; }
".global"   { displayLexer("GLOBAL", yytext); tac_lval.string = strdup("GLOBAL"); return GLOBAL; }
".addr"     { displayLexer("REFERENCE", yytext); tac_lval.string = strdup("REFERENCE"); return REFERENCE; }
".data"     { displayLexer("DATA", yytext); tac_lval.string = strdup("DATA"); return DATA; }
".t"({D})*        { displayLexer("TEMP", yytext); tac_lval.string = strdup(yytext); return TEMP; }
{L}({L}|{D})*":" { displayLexer("LABEL", yytext); tac_lval.string = strdup(yytext); return LABEL; }
{L}({L}|{D})*"."{D}+    { displayLexer("IDENTIFIER", yytext); tac_lval.string = strdup(yytext); return IDENTIFIER; }
{L}({L}|{D})*    { displayLexer("IDENTIFIER", yytext); tac_lval.string = strdup(yytext); return IDENTIFIER; }



0[xX]{H}+{IS}?                   { displayLexer("CONSTANT_LITERAL", yytext); tac_lval.string = strdup(yytext); return CONSTANT_LITERAL; }
0{D}+{IS}?                       { displayLexer("CONSTANT_LITERAL", yytext); tac_lval.string = strdup(yytext); return CONSTANT_LITERAL; }
{D}+{IS}?                        { displayLexer("CONSTANT_LITERAL", yytext); tac_lval.string = strdup(yytext); return CONSTANT_LITERAL; }
L?'(\\.|[^\\'])+\'               { displayLexer("CONSTANT_LITERAL", yytext); tac_lval.string = strdup(yytext); return CONSTANT_LITERAL; }
{D}+{E}{FS}?                     { displayLexer("CONSTANT_LITERAL", yytext); tac_lval.string = strdup(yytext); return CONSTANT_LITERAL; }
{D}*"."{D}+({E})?{FS}?           { displayLexer("CONSTANT_LITERAL", yytext); tac_lval.string = strdup(yytext); return CONSTANT_LITERAL; }
{D}+"."{D}*({E})?{FS}?           { displayLexer("CONSTANT_LITERAL", yytext); tac_lval.string = strdup(yytext); return CONSTANT_LITERAL; }


L?\"(\\.|[^\\"])*\"              { displayLexer("STRING_LITERAL", yytext); tac_lval.string = strdup(yytext); return STRING_LITERAL; }

"("         { displayLexer("LPAREN", yytext); tac_lval.string = strdup(yytext); return LPAREN; }
")"         { displayLexer("RPAREN", yytext); tac_lval.string = strdup(yytext); return RPAREN; }
">>"        { displayLexer("RIGHT_OP", yytext); tac_lval.string = strdup(yytext); return RIGHT_OP; }
"<<"        { displayLexer("LEFT_OP", yytext); tac_lval.string = strdup(yytext); return LEFT_OP; }
"&&"        { displayLexer("AND_OP", yytext); tac_lval.string = strdup(yytext); return AND_OP; }
"||"        { displayLexer("OR_OP", yytext); tac_lval.string = strdup(yytext); return OR_OP; }
"=="        { displayLexer("EQ_OP", yytext); tac_lval.string = strdup(yytext); return EQ_OP; }
"!="        { displayLexer("NE_OP", yytext); tac_lval.string = strdup(yytext); return NE_OP; }
"<="        { displayLexer("LE_OP", yytext); tac_lval.string = strdup(yytext); return LE_OP; }
">="        { displayLexer("GE_OP", yytext); tac_lval.string = strdup(yytext); return GE_OP; }
","         { displayLexer("COMMA", yytext); tac_lval.string = strdup(yytext); return COMMA; }
"="         { displayLexer("ASSIGN", yytext); tac_lval.string = strdup(yytext); return ASSIGN; }
"."         { displayLexer("DOT", yytext); tac_lval.string = strdup(yytext); return DOT; }
"&"         { displayLexer("AMPERSAND", yytext); tac_lval.string = strdup(yytext); return AMPERSAND; }
"!"         { displayLexer("EXCLAMATION", yytext); tac_lval.string = strdup(yytext); return EXCLAMATION; }
"~"         { displayLexer("TILDE", yytext); tac_lval.string = strdup(yytext); return TILDE; }
"-"         { displayLexer("MINUS", yytext); tac_lval.string = strdup(yytext); return MINUS; }
"+"         { displayLexer("PLUS", yytext); tac_lval.string = strdup(yytext); return PLUS; }
"*"         { displayLexer("ASTERISK", yytext); tac_lval.string = strdup(yytext); return ASTERISK; }
"/"         { displayLexer("SLASH", yytext); tac_lval.string = strdup(yytext); return SLASH; }
"%"         { displayLexer("PERCENT", yytext); tac_lval.string = strdup(yytext); return PERCENT; }
"<"         { displayLexer("LESS_THAN", yytext); tac_lval.string = strdup(yytext); return LESS_THAN; }
">"         { displayLexer("GREATER_THAN", yytext); tac_lval.string = strdup(yytext); return GREATER_THAN; }
"^"         { displayLexer("CARET", yytext); tac_lval.string = strdup(yytext); return CARET; }
"|"         { displayLexer("PIPE", yytext); tac_lval.string = strdup(yytext); return PIPE; }

([\n]) {
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