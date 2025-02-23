%{
#include "helper.h"

void displayLexer(int token, const char* text);
int check_type();
%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS          (u|U|ul|Ul|uL|UL|ull|Ull|uLl|UlL|uLL|ULL)

%%
"//".* { /* Single-line comment: ignore */ }
"/*" { comment(); }

"auto" { displayLexer(AUTO, yytext); return(AUTO); }
"break" { displayLexer(BREAK, yytext); return(BREAK); }
"case" { displayLexer(CASE, yytext); return(CASE); }
"char" { displayLexer(CHAR, yytext); return(CHAR); }
"const" { displayLexer(CONST, yytext); return(CONST); }
"continue" { displayLexer(CONTINUE, yytext); return(CONTINUE); }
"default" { displayLexer(DEFAULT, yytext); return(DEFAULT); }
"do" { displayLexer(DO, yytext); return(DO); }
"double" { displayLexer(DOUBLE, yytext); return(DOUBLE); }
"else" { displayLexer(ELSE, yytext); return(ELSE); }
"enum" { displayLexer(ENUM, yytext); return(ENUM); }
"extern" { displayLexer(EXTERN, yytext); return(EXTERN); }
"float" { displayLexer(FLOAT, yytext); return(FLOAT); }
"for" { displayLexer(FOR, yytext); return(FOR); }
"goto" { displayLexer(GOTO, yytext); return(GOTO); }
"if" { displayLexer(IF, yytext); return(IF); }
"int" { displayLexer(INT, yytext); return(INT); }
"long" { displayLexer(LONG, yytext); return(LONG); }
"register" { displayLexer(REGISTER, yytext); return(REGISTER); }
"return" { displayLexer(RETURN, yytext); return(RETURN); }
"short" { displayLexer(SHORT, yytext); return(SHORT); }
"signed" { displayLexer(SIGNED, yytext); return(SIGNED); }
"sizeof" { displayLexer(SIZEOF, yytext); return(SIZEOF); }
"static" { displayLexer(STATIC, yytext); return(STATIC); }
"struct" { displayLexer(STRUCT, yytext); return(STRUCT); }
"switch" { displayLexer(SWITCH, yytext); return(SWITCH); }
"typedef" { displayLexer(TYPEDEF, yytext); return(TYPEDEF); }
"union" { displayLexer(UNION, yytext); return(UNION); }
"unsigned" { displayLexer(UNSIGNED, yytext); return(UNSIGNED); }
"void" { displayLexer(VOID, yytext); return(VOID); }
"volatile" { displayLexer(VOLATILE, yytext); return(VOLATILE); }
"while" { displayLexer(WHILE, yytext); return(WHILE); }

{L}({L}|{D})* {
    displayLexer(IDENTIFIER, yytext);
    return check_type();
}

0[xX]{H}+{IS}? { displayLexer(CONSTANT, yytext); return(CONSTANT); }
0{D}+{IS}? { displayLexer(CONSTANT, yytext); return(CONSTANT); }
{D}+{IS}? { displayLexer(CONSTANT, yytext); return(CONSTANT); }
L?'(\\.|[^\\'])+' { displayLexer(CONSTANT, yytext); return(CONSTANT); }

{D}+{E}{FS}? { displayLexer(CONSTANT, yytext); return(CONSTANT); }
{D}*"."{D}+({E})?{FS}? { displayLexer(CONSTANT, yytext); return(CONSTANT); }
{D}+"."{D}*({E})?{FS}? { displayLexer(CONSTANT, yytext); return(CONSTANT); }

L?\"(\\.|[^\\"])*\" { displayLexer(STRING_LITERAL, yytext); return(STRING_LITERAL); }

"..." { displayLexer(ELLIPSIS, yytext); return(ELLIPSIS); }
">>=" { displayLexer(RIGHT_ASSIGN, yytext); return(RIGHT_ASSIGN); }
"<<=" { displayLexer(LEFT_ASSIGN, yytext); return(LEFT_ASSIGN); }
"+=" { displayLexer(ADD_ASSIGN, yytext); return(ADD_ASSIGN); }
"-=" { displayLexer(SUB_ASSIGN, yytext); return(SUB_ASSIGN); }
"*=" { displayLexer(MUL_ASSIGN, yytext); return(MUL_ASSIGN); }
"/=" { displayLexer(DIV_ASSIGN, yytext); return(DIV_ASSIGN); }
"%=" { displayLexer(MOD_ASSIGN, yytext); return(MOD_ASSIGN); }
"&=" { displayLexer(AND_ASSIGN, yytext); return(AND_ASSIGN); }
"^=" { displayLexer(XOR_ASSIGN, yytext); return(XOR_ASSIGN); }
"|=" { displayLexer(OR_ASSIGN, yytext); return(OR_ASSIGN); }
">>" { displayLexer(RIGHT_OP, yytext); return(RIGHT_OP); }
"<<" { displayLexer(LEFT_OP, yytext); return(LEFT_OP); }
"++" { displayLexer(INC_OP, yytext); return(INC_OP); }
"--" { displayLexer(DEC_OP, yytext); return(DEC_OP); }
"->" { displayLexer(PTR_OP, yytext); return(PTR_OP); }
"&&" { displayLexer(AND_OP, yytext); return(AND_OP); }
"||" { displayLexer(OR_OP, yytext); return(OR_OP); }
"<=" { displayLexer(LE_OP, yytext); return(LE_OP); }
">=" { displayLexer(GE_OP, yytext); return(GE_OP); }
"==" { displayLexer(EQ_OP, yytext); return(EQ_OP); }
"!=" { displayLexer(NE_OP, yytext); return(NE_OP); }
";"          { displayLexer(';', yytext); return (';'); }
("{"|"<%")   { displayLexer('{', yytext); return ('{'); }
("}"|"%>")   { displayLexer('}', yytext); return ('}'); }
","          { displayLexer(',', yytext); return (','); }
":"          { displayLexer(':', yytext); return (':'); }
"="          { displayLexer('=', yytext); return ('='); }
"("          { displayLexer('(', yytext); return ('('); }
")"          { displayLexer(')', yytext); return (')'); }
("["|"<:")   { displayLexer('[', yytext); return ('['); }
("]"|":>")   { displayLexer(']', yytext); return (']'); }
"."          { displayLexer('.', yytext); return ('.'); }
"&"          { displayLexer('&', yytext); return ('&'); }
"!"          { displayLexer('!', yytext); return ('!'); }
"~"          { displayLexer('~', yytext); return ('~'); }
"-"          { displayLexer('-', yytext); return ('-'); }
"+"          { displayLexer('+', yytext); return ('+'); }
"*"          { displayLexer('*', yytext); return ('*'); }
"/"          { displayLexer('/', yytext); return ('/'); }
"%"          { displayLexer('%', yytext); return ('%'); }
"<"          { displayLexer('<', yytext); return ('<'); }
">"          { displayLexer('>', yytext); return ('>'); }
"^"          { displayLexer('^', yytext); return ('^'); }
"|"          { displayLexer('|', yytext); return ('|'); }
"?"          { displayLexer('?', yytext); return ('?'); }

[ \t\v\n\f] { }
. {  }

%%

int yywrap(void) {
    return 1;
}

void comment() {
    char c, c1;

    while (1) {
        while ((c = input()) != '*' && c != 0) {
            if (c == '\n') {
                // Handle new lines if needed
            }
            putchar(c);
        }

        if (c == 0) {
            // End of file within comment
            break;
        }

        c1 = input();
        if (c1 == '/') {
            putchar(c1);
            break;
        } else if (c1 == 0) {
            // End of file
            break;
        } else {
            unput(c1);
            putchar(c); // put the '*' back.
        }
    }
}

void displayLexer(int token, const char* text) {
    printf("Token: %s, Text: %s\n", getTokenName(token), text);
}

int column = 0;

int check_type() {
    return(IDENTIFIER);
}