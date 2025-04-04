%{
#include <helper.h>
#include <y.tab.h>

void displayLexer(int token, const char* text);
int check_type();
void lexicalError(const char* message, ...);
int errorCount = 0;

%}

%option yylineno

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS          (u|U|l|L|ll|LL|ul|uL|Ul|UL|lu|lU|Lu|LU|ull|uLL|Ull|ULL|llu|llU|LLu|LLU)

/* Add error patterns */
INVALID_IDENTIFIER      {D}+{L}+({L}|{D})*
INVALID_CHARACTER    [$@`]
INVALID_OCT_NUM     0[0-7]*[89][0-7]*
UNTERMINATED_STRING   L?\"([^"\\\n]|\\.)*$

%%
"//".* { /* Single-line comment: ignore */ }
"/*" { comment(); }


{INVALID_IDENTIFIER} {
    lexicalError("Invalid identifier '%s' - cannot start with digit", yytext);
    displayLexer(INVALID_ID, yytext);
    yylval.nice = strdup(yytext);
    return ERROR;
}

{INVALID_CHARACTER} {
    lexicalError("Invalid character '%s' in input", yytext);
    displayLexer(INVALID_CHAR, yytext);
    yylval.nice = strdup("INVALID CHARACTER");
    return ERROR;
}

"auto"      { displayLexer(AUTO, yytext);      yylval.nice = strdup(getTokenName(AUTO));      return AUTO; }
"break"     { displayLexer(BREAK, yytext);     yylval.nice = strdup(getTokenName(BREAK));     return BREAK; }
"case"      { displayLexer(CASE, yytext);      yylval.nice = strdup(getTokenName(CASE));      return CASE; }
"char"      { displayLexer(CHAR, yytext);      yylval.nice = strdup(getTokenName(CHAR));      return CHAR; }
"const"     { displayLexer(CONST, yytext);     yylval.nice = strdup(getTokenName(CONST));     return CONST; }
"continue"  { displayLexer(CONTINUE, yytext);  yylval.nice = strdup(getTokenName(CONTINUE));  return CONTINUE; }
"default"   { displayLexer(DEFAULT, yytext);   yylval.nice = strdup(getTokenName(DEFAULT));   return DEFAULT; }
"do"        { displayLexer(DO, yytext);        yylval.nice = strdup(getTokenName(DO));        return DO; }
"double"    { displayLexer(DOUBLE, yytext);    yylval.nice = strdup(getTokenName(DOUBLE));    return DOUBLE; }
"else"      { displayLexer(ELSE, yytext);      yylval.nice = strdup(getTokenName(ELSE));      return ELSE; }
"enum"      { displayLexer(ENUM, yytext);      yylval.nice = strdup(getTokenName(ENUM));      return ENUM; }
"extern"    { displayLexer(EXTERN, yytext);    yylval.nice = strdup(getTokenName(EXTERN));    return EXTERN; }
"float"     { displayLexer(FLOAT, yytext);     yylval.nice = strdup(getTokenName(FLOAT));     return FLOAT; }
"for"       { displayLexer(FOR, yytext);       yylval.nice = strdup(getTokenName(FOR));       return FOR; }
"goto"      { displayLexer(GOTO, yytext);      yylval.nice = strdup(getTokenName(GOTO));      return GOTO; }
"if"        { displayLexer(IF, yytext);        yylval.nice = strdup(getTokenName(IF));        return IF; }
"int"       { displayLexer(INT, yytext);       yylval.nice = strdup(getTokenName(INT));       return INT; }
"long"      { displayLexer(LONG, yytext);      yylval.nice = strdup(getTokenName(LONG));      return LONG; }
"register"  { displayLexer(REGISTER, yytext);  yylval.nice = strdup(getTokenName(REGISTER));  return REGISTER; }
"return"    { displayLexer(RETURN, yytext);    yylval.nice = strdup(getTokenName(RETURN));    return RETURN; }
"short"     { displayLexer(SHORT, yytext);     yylval.nice = strdup(getTokenName(SHORT));     return SHORT; }
"signed"    { displayLexer(SIGNED, yytext);    yylval.nice = strdup(getTokenName(SIGNED));    return SIGNED; }
"sizeof"    { displayLexer(SIZEOF, yytext);    yylval.nice = strdup(getTokenName(SIZEOF));    return SIZEOF; }
"static"    { displayLexer(STATIC, yytext);    yylval.nice = strdup(getTokenName(STATIC));    return STATIC; }
"struct"    { displayLexer(STRUCT, yytext);    yylval.nice = strdup(getTokenName(STRUCT));    return STRUCT; }
"switch"    { displayLexer(SWITCH, yytext);    yylval.nice = strdup(getTokenName(SWITCH));    return SWITCH; }
"typedef"   { displayLexer(TYPEDEF, yytext);   yylval.nice = strdup(getTokenName(TYPEDEF));   return TYPEDEF; }
"union"     { displayLexer(UNION, yytext);     yylval.nice = strdup(getTokenName(UNION));     return UNION; }
"unsigned"  { displayLexer(UNSIGNED, yytext);  yylval.nice = strdup(getTokenName(UNSIGNED));  return UNSIGNED; }
"void"      { displayLexer(VOID, yytext);      yylval.nice = strdup(getTokenName(VOID));      return VOID; }
"volatile"  { displayLexer(VOLATILE, yytext);  yylval.nice = strdup(getTokenName(VOLATILE));  return VOLATILE; }
"while"     { displayLexer(WHILE, yytext);     yylval.nice = strdup(getTokenName(WHILE));     return WHILE; }


{L}({L}|{D})* {
    displayLexer(IDENTIFIER, yytext);
    yylval.nice = strdup(yytext);
    return IDENTIFIER;
}


0[xX]{H}+{IS}?                   { displayLexer(CONSTANT_LITERAL, yytext); yylval.nice = strdup(yytext); return CONSTANT_LITERAL; }
0{D}+{IS}?                       { displayLexer(CONSTANT_LITERAL, yytext); yylval.nice = strdup(yytext); return CONSTANT_LITERAL; }
{D}+{IS}?                        { displayLexer(CONSTANT_LITERAL, yytext); yylval.nice = strdup(yytext); return CONSTANT_LITERAL; }
L?'(\\.|[^\\'])+\'               { displayLexer(CONSTANT_LITERAL, yytext); yylval.nice = strdup(yytext); return CONSTANT_LITERAL; }
{D}+{E}{FS}?                     { displayLexer(CONSTANT_LITERAL, yytext); yylval.nice = strdup(yytext); return CONSTANT_LITERAL; }
{D}*"."{D}+({E})?{FS}?           { displayLexer(CONSTANT_LITERAL, yytext); yylval.nice = strdup(yytext); return CONSTANT_LITERAL; }
{D}+"."{D}*({E})?{FS}?           { displayLexer(CONSTANT_LITERAL, yytext); yylval.nice = strdup(yytext); return CONSTANT_LITERAL; }


{INVALID_OCT_NUM} {
    lexicalError("Invalid octal constant '%s'", yytext);
    displayLexer(INVALID_OCT, yytext);
    yylval.nice = strdup("INVALID OCTAL");
    return ERROR;
}


L?\"(\\.|[^\\"])*\"              { displayLexer(STRING_LITERAL, yytext); yylval.nice = strdup(getTokenName(STRING_LITERAL)); return STRING_LITERAL; }


{UNTERMINATED_STRING} {
    lexicalError("Unterminated string literal '%s'", yytext);
    displayLexer(UNTERM_STRING, yytext);
    yylval.nice = strdup("UNTERMINATED STRING");
    return ERROR;
}


"..."       { displayLexer(ELLIPSIS, yytext);    yylval.nice = strdup(getTokenName(ELLIPSIS));    return ELLIPSIS; }
">>="       { displayLexer(RIGHT_ASSIGN, yytext); yylval.nice = strdup(getTokenName(RIGHT_ASSIGN)); return RIGHT_ASSIGN; }
"<<="       { displayLexer(LEFT_ASSIGN, yytext);  yylval.nice = strdup(getTokenName(LEFT_ASSIGN));  return LEFT_ASSIGN; }
"+="        { displayLexer(ADD_ASSIGN, yytext);   yylval.nice = strdup(getTokenName(ADD_ASSIGN));   return ADD_ASSIGN; }
"-="        { displayLexer(SUB_ASSIGN, yytext);   yylval.nice = strdup(getTokenName(SUB_ASSIGN));   return SUB_ASSIGN; }
"*="        { displayLexer(MUL_ASSIGN, yytext);   yylval.nice = strdup(getTokenName(MUL_ASSIGN));   return MUL_ASSIGN; }
"/="        { displayLexer(DIV_ASSIGN, yytext);   yylval.nice = strdup(getTokenName(DIV_ASSIGN));   return DIV_ASSIGN; }
"%="        { displayLexer(MOD_ASSIGN, yytext);   yylval.nice = strdup(getTokenName(MOD_ASSIGN));   return MOD_ASSIGN; }
"&="        { displayLexer(AND_ASSIGN, yytext);   yylval.nice = strdup(getTokenName(AND_ASSIGN));   return AND_ASSIGN; }
"^="        { displayLexer(XOR_ASSIGN, yytext);   yylval.nice = strdup(getTokenName(XOR_ASSIGN));   return XOR_ASSIGN; }
"|="        { displayLexer(OR_ASSIGN, yytext);    yylval.nice = strdup(getTokenName(OR_ASSIGN));    return OR_ASSIGN; }
">>"        { displayLexer(RIGHT_OP, yytext);     yylval.nice = strdup(getTokenName(RIGHT_OP));     return RIGHT_OP; }
"<<"        { displayLexer(LEFT_OP, yytext);      yylval.nice = strdup(getTokenName(LEFT_OP));      return LEFT_OP; }
"++"        { displayLexer(INC_OP, yytext);       yylval.nice = strdup(getTokenName(INC_OP));       return INC_OP; }
"--"        { displayLexer(DEC_OP, yytext);       yylval.nice = strdup(getTokenName(DEC_OP));       return DEC_OP; }
"->"        { displayLexer(PTR_OP, yytext);       yylval.nice = strdup(getTokenName(PTR_OP));       return PTR_OP; }
"&&"        { displayLexer(AND_OP, yytext);       yylval.nice = strdup(getTokenName(AND_OP));       return AND_OP; }
"||"        { displayLexer(OR_OP, yytext);        yylval.nice = strdup(getTokenName(OR_OP));        return OR_OP; }
"<="        { displayLexer(LE_OP, yytext);        yylval.nice = strdup(getTokenName(LE_OP));        return LE_OP; }
">="        { displayLexer(GE_OP, yytext);        yylval.nice = strdup(getTokenName(GE_OP));        return GE_OP; }
"=="        { displayLexer(EQ_OP, yytext);        yylval.nice = strdup(getTokenName(EQ_OP));        return EQ_OP; }
"!="        { displayLexer(NE_OP, yytext);        yylval.nice = strdup(getTokenName(NE_OP));        return NE_OP; }


";"         { displayLexer(SEMICOLON, yytext);    yylval.nice = strdup(getTokenName(SEMICOLON));    return SEMICOLON; }
("{"|"<%")  { displayLexer(LEFT_BRACE, yytext);   yylval.nice = strdup(getTokenName(LEFT_BRACE));   return LEFT_BRACE; }
("}"|"%>")  { displayLexer(RIGHT_BRACE, yytext);  yylval.nice = strdup(getTokenName(RIGHT_BRACE));  return RIGHT_BRACE; }
","         { displayLexer(COMMA, yytext);        yylval.nice = strdup(getTokenName(COMMA));        return COMMA; }
":"         { displayLexer(COLON, yytext);        yylval.nice = strdup(getTokenName(COLON));        return COLON; }
"="         { displayLexer(ASSIGN, yytext);       yylval.nice = strdup(getTokenName(ASSIGN));       return ASSIGN; }
"("         { displayLexer(LEFT_PAREN, yytext);   yylval.nice = strdup(getTokenName(LEFT_PAREN));   return LEFT_PAREN; }
")"         { displayLexer(RIGHT_PAREN, yytext);  yylval.nice = strdup(getTokenName(RIGHT_PAREN));  return RIGHT_PAREN; }
("["|"<:")  { displayLexer(LEFT_BRACKET, yytext); yylval.nice = strdup(getTokenName(LEFT_BRACKET)); return LEFT_BRACKET; }
("]"|":>")  { displayLexer(RIGHT_BRACKET, yytext);yylval.nice = strdup(getTokenName(RIGHT_BRACKET));return RIGHT_BRACKET; }
"."         { displayLexer(DOT, yytext);          yylval.nice = strdup(getTokenName(DOT));          return DOT; }
"&"         { displayLexer(AMPERSAND, yytext);    yylval.nice = strdup(getTokenName(AMPERSAND));    return AMPERSAND; }
"!"         { displayLexer(EXCLAMATION, yytext);  yylval.nice = strdup(getTokenName(EXCLAMATION));  return EXCLAMATION; }
"~"         { displayLexer(TILDE, yytext);        yylval.nice = strdup(getTokenName(TILDE));        return TILDE; }
"-"         { displayLexer(MINUS, yytext);        yylval.nice = strdup(getTokenName(MINUS));        return MINUS; }
"+"         { displayLexer(PLUS, yytext);         yylval.nice = strdup(getTokenName(PLUS));         return PLUS; }
"*"         { displayLexer(ASTERISK, yytext);     yylval.nice = strdup(getTokenName(ASTERISK));     return ASTERISK; }
"/"         { displayLexer(SLASH, yytext);        yylval.nice = strdup(getTokenName(SLASH));        return SLASH; }
"%"         { displayLexer(PERCENT, yytext);      yylval.nice = strdup(getTokenName(PERCENT));      return PERCENT; }
"<"         { displayLexer(LESS_THAN, yytext);    yylval.nice = strdup(getTokenName(LESS_THAN));    return LESS_THAN; }
">"         { displayLexer(GREATER_THAN, yytext); yylval.nice = strdup(getTokenName(GREATER_THAN)); return GREATER_THAN; }
"^"         { displayLexer(CARET, yytext);        yylval.nice = strdup(getTokenName(CARET));        return CARET; }
"|"         { displayLexer(PIPE, yytext);         yylval.nice = strdup(getTokenName(PIPE));         return PIPE; }
"?"         { displayLexer(QUESTION, yytext);     yylval.nice = strdup(getTokenName(QUESTION));     return QUESTION; }

([ \t\v\n\f])* { }
. {}

%%

int yywrap(void) {
    return 1;
}

void comment() {
    // char c, c1;

    // while (1) {
    //     while ((c = input()) != '*' && c != 0) {
    //         if (c == '\n') {
    //             // Handle new lines if needed
    //         }
    //         putchar(c);
    //     }

    //     if (c == 0) {
    //         // End of file within comment
    //         break;
    //     }

    //     c1 = input();
    //     if (c1 == '/') {
    //         putchar(c1);
    //         break;
    //     } else if (c1 == 0) {
    //         // End of file
    //         break;
    //     } else {
    //         unput(c1);
    //         putchar(c); // put the '*' back.
    //     }
    // }
}

void displayLexer(int token, const char* text) {
    static int first_call = 1;
    if (first_call) {
        printf("+----------------------+----------------------+\n");
        printf("| %-20s | %-20s |\n", "Token", "Text");
        printf("+----------------------+----------------------+\n");
        first_call = 0;
    }
    printf("| %-20s | %-20s |\n", getTokenName(token), text);
}

/* Add this function at the end */
void lexicalError(const char* message, ...) {
    va_list args;
    va_start(args, message);
    fprintf(stderr, "Lexical error at line %d: ", yylineno);
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
    va_end(args);
    errorCount++;
}