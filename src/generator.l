D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS          (u|U|ul|Ul|uL|UL|ull|Ull|uLl|UlL|uLL|ULL)

%{
#include <stdio.h>
#include "y.tab.h"
#include "generator.h"
%}

%%
"//".* { /* Single-line comment: ignore */ }
"/*"			{ comment(); }

"auto"			{  return(AUTO); }
"break"			{  return(BREAK); }
"case"			{  return(CASE); }
"char"			{  return(CHAR); }
"const"			{  return(CONST); }
"continue"		{  return(CONTINUE); }
"default"		{  return(DEFAULT); }
"do"			{  return(DO); }
"double"		{  return(DOUBLE); }
"else"			{  return(ELSE); }
"enum"			{  return(ENUM); }
"extern"		{  return(EXTERN); }
"float"			{  return(FLOAT); }
"for"			{  return(FOR); }
"goto"			{  return(GOTO); }
"if"			{  return(IF); }
"int"			{  return(INT); }
"long"			{  return(LONG); }
"register"		{  return(REGISTER); }
"return"		{  return(RETURN); }
"short"			{  return(SHORT); }
"signed"		{  return(SIGNED); }
"sizeof"		{  return(SIZEOF); }
"static"		{  return(STATIC); }
"struct"		{  return(STRUCT); }
"switch"		{  return(SWITCH); }
"typedef"		{  return(TYPEDEF); }
"union"			{  return(UNION); }
"unsigned"		{  return(UNSIGNED); }
"void"			{  return(VOID); }
"volatile"		{  return(VOLATILE); }
"while"			{  return(WHILE); }

{L}({L}|{D})*		    {  return(check_type()); }

0[xX]{H}+{IS}?		    {  return(CONSTANT); }
0{D}+{IS}?		        {  return(CONSTANT); }
{D}+{IS}?		        {  return(CONSTANT); }
L?'(\\.|[^\\'])+'	    {  return(CONSTANT); }

{D}+{E}{FS}?		    {  return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{  return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{  return(CONSTANT); }

L?\"(\\.|[^\\"])*\"	    {  return(STRING_LITERAL); }

"..."			{  return(ELLIPSIS); }
">>="			{  return(RIGHT_ASSIGN); }
"<<="			{  return(LEFT_ASSIGN); }
"+="			{  return(ADD_ASSIGN); }
"-="			{  return(SUB_ASSIGN); }
"*="			{  return(MUL_ASSIGN); }
"/="			{  return(DIV_ASSIGN); }
"%="			{  return(MOD_ASSIGN); }
"&="			{  return(AND_ASSIGN); }
"^="			{  return(XOR_ASSIGN); }
"|="			{  return(OR_ASSIGN); }
">>"			{  return(RIGHT_OP); }
"<<"			{  return(LEFT_OP); }
"++"			{  return(INC_OP); }
"--"			{  return(DEC_OP); }
"->"			{  return(PTR_OP); }
"&&"			{  return(AND_OP); }
"||"			{  return(OR_OP); }
"<="			{  return(LE_OP); }
">="			{  return(GE_OP); }
"=="			{  return(EQ_OP); }
"!="			{  return(NE_OP); }
";"			{  return(';'); }
("{"|"<%")		{  return('{'); }
("}"|"%>")		{  return('}'); }
","			{  return(','); }
":"			{  return(':'); }
"="			{  return('='); }
"("			{  return('('); }
")"			{  return(')'); }
("["|"<:")		{  return('['); }
("]"|":>")		{  return(']'); }
"."			{  return('.'); }
"&"			{  return('&'); }
"!"			{  return('!'); }
"~"			{  return('~'); }
"-"			{  return('-'); }
"+"			{  return('+'); }
"*"			{  return('*'); }
"/"			{  return('/'); }
"%"			{  return('%'); }
"<"			{  return('<'); }
">"			{  return('>'); }
"^"			{  return('^'); }
"|"			{  return('|'); }
"?"			{  return('?'); }

[ \t\v\n\f]		{  }
.			{ return(INVALID_CHARACTER); }

%%

int yywrap(void) {
    return 1;
}



void comment() {
    char c, c1;

    while (1) {
        while ((c = input()) != '*' && c != 0) {
            if (c == '\n') {
                //Handle new lines if needed
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
        } else if (c1 == 0){
            //End of file
            break;
        } else {
            unput(c1);
            putchar(c); //put the '*' back.
        }
    }
}

int column = 0;


int check_type()
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return(TYPE_NAME);
*
*	return(IDENTIFIER);
*/

/*
*	it actually will only return IDENTIFIER
*/

	return(IDENTIFIER);
}