%option c++ noyywrap
%{
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>

// Global vector to store lexeme-Identifier pairs
std::vector<std::pair<std::string, std::string>> lexemeTable;

// Function to add a lexeme-Identifier pair to the table
void add_to_table(const char* lexeme, const char* identifier) {
    lexemeTable.emplace_back(std::string(lexeme), std::string(identifier));
}
%}

D           [0-9]
L           [a-zA-Z_]
H           [a-fA-F0-9]
E           [Ee][+-]?{D}+
FS          (f|F|l|L)
IS          ((u|U)(l|L)?)|((l|L)(u|U)?) 

%%

"auto"              { add_to_table(yytext, "KEYWORD"); }
"break"             { add_to_table(yytext, "KEYWORD"); }
"case"              { add_to_table(yytext, "KEYWORD"); }
"char"              { add_to_table(yytext, "KEYWORD"); }
"const"             { add_to_table(yytext, "KEYWORD"); }
"continue"          { add_to_table(yytext, "KEYWORD"); }
"default"           { add_to_table(yytext, "KEYWORD"); }
"do"                { add_to_table(yytext, "KEYWORD"); }
"double"            { add_to_table(yytext, "KEYWORD"); }
"else"              { add_to_table(yytext, "KEYWORD"); }
"enum"              { add_to_table(yytext, "KEYWORD"); }
"extern"            { add_to_table(yytext, "KEYWORD"); }
"float"             { add_to_table(yytext, "KEYWORD"); }
"for"               { add_to_table(yytext, "KEYWORD"); }
"goto"              { add_to_table(yytext, "KEYWORD"); }
"if"                { add_to_table(yytext, "KEYWORD"); }
"int"               { add_to_table(yytext, "KEYWORD"); }
"long"              { add_to_table(yytext, "KEYWORD"); }
"register"          { add_to_table(yytext, "KEYWORD"); }
"return"            { add_to_table(yytext, "KEYWORD"); }
"short"             { add_to_table(yytext, "KEYWORD"); }
"signed"            { add_to_table(yytext, "KEYWORD"); }
"sizeof"            { add_to_table(yytext, "KEYWORD"); }
"static"            { add_to_table(yytext, "KEYWORD"); }
"struct"            { add_to_table(yytext, "KEYWORD"); }
"switch"            { add_to_table(yytext, "KEYWORD"); }
"typedef"           { add_to_table(yytext, "KEYWORD"); }
"union"             { add_to_table(yytext, "KEYWORD"); }
"unsigned"          { add_to_table(yytext, "KEYWORD"); }
"void"              { add_to_table(yytext, "KEYWORD"); }
"volatile"          { add_to_table(yytext, "KEYWORD"); }
"while"             { add_to_table(yytext, "KEYWORD"); }

{L}({L}|{D})*       { add_to_table(yytext, "IDENTIFIER"); }

0[xX]{H}+{IS}?      { add_to_table(yytext, "CONSTANT"); }
0{D}+{IS}?          { add_to_table(yytext, "CONSTANT"); }
{D}+{IS}?           { add_to_table(yytext, "CONSTANT"); }

0[xX]{H}+[a-zA-Z_]+ { add_to_table(yytext, "ERROR_INVALID_CONSTANT"); }
0{D}+[a-zA-Z_]+     { add_to_table(yytext, "ERROR_INVALID_CONSTANT"); }
{D}+[a-zA-Z_]+      { add_to_table(yytext, "ERROR_INVALID_CONSTANT"); }

L?'(\\.|[^\\'])+'   { add_to_table(yytext, "CONSTANT"); }
{D}+{E}{FS}?        { add_to_table(yytext, "CONSTANT"); }
{D}*"."{D}+({E})?{FS}? { add_to_table(yytext, "CONSTANT"); }
{D}+"."{D}*({E})?{FS}? { add_to_table(yytext, "CONSTANT"); }

L?\"(\\.|[^\\"])*\" { add_to_table(yytext, "STRING_LITERAL"); }

L?\"(\\.|[^\\"])*   { add_to_table(yytext, "ERROR_UNTERMINATED_STRING"); }



">>="               { add_to_table(yytext, "OPERATOR"); }
"<<="               { add_to_table(yytext, "OPERATOR"); }
"+="                { add_to_table(yytext, "OPERATOR"); }
"-="                { add_to_table(yytext, "OPERATOR"); }
"*="                { add_to_table(yytext, "OPERATOR"); }
"/="                { add_to_table(yytext, "OPERATOR"); }
"%="                { add_to_table(yytext, "OPERATOR"); }
"&="                { add_to_table(yytext, "OPERATOR"); }
"^="                { add_to_table(yytext, "OPERATOR"); }
"|="                { add_to_table(yytext, "OPERATOR"); }
">>"                { add_to_table(yytext, "OPERATOR"); }
"<<"                { add_to_table(yytext, "OPERATOR"); }
"++"                { add_to_table(yytext, "OPERATOR"); }
"--"                { add_to_table(yytext, "OPERATOR"); }
"->"                { add_to_table(yytext, "OPERATOR"); }
"&&"                { add_to_table(yytext, "OPERATOR"); }
"||"                { add_to_table(yytext, "OPERATOR"); }
"<="                { add_to_table(yytext, "OPERATOR"); }
">="                { add_to_table(yytext, "OPERATOR"); }
"=="                { add_to_table(yytext, "OPERATOR"); }
"!="                { add_to_table(yytext, "OPERATOR"); }
";"                 { add_to_table(yytext, "OPERATOR"); }
("{"|"<%")          { add_to_table(yytext, "OPERATOR"); }
("}"|"%>")          { add_to_table(yytext, "OPERATOR"); }
","                 { add_to_table(yytext, "OPERATOR"); }
":"                 { add_to_table(yytext, "OPERATOR"); }
"="                 { add_to_table(yytext, "OPERATOR"); }
"("                 { add_to_table(yytext, "OPERATOR"); }
")"                 { add_to_table(yytext, "OPERATOR"); }
("["|"<:")          { add_to_table(yytext, "OPERATOR"); }
("]"|":>")          { add_to_table(yytext, "OPERATOR"); }
"."                 { add_to_table(yytext, "OPERATOR"); }
"&"                 { add_to_table(yytext, "OPERATOR"); }
"!"                 { add_to_table(yytext, "OPERATOR"); }
"~"                 { add_to_table(yytext, "OPERATOR"); }
"-"                 { add_to_table(yytext, "OPERATOR"); }
"+"                 { add_to_table(yytext, "OPERATOR"); }
"*"                 { add_to_table(yytext, "OPERATOR"); }
"/"                 { add_to_table(yytext, "OPERATOR"); }
"%"                 { add_to_table(yytext, "OPERATOR"); }
"<"                 { add_to_table(yytext, "OPERATOR"); }
">"                 { add_to_table(yytext, "OPERATOR"); }
"^"                 { add_to_table(yytext, "OPERATOR"); }
"|"                 { add_to_table(yytext, "OPERATOR"); }
"?"                 { add_to_table(yytext, "OPERATOR"); }

[ \t\v\n\f]         { /* Ignore whitespace */ }
.                   { /* Ignore bad characters */ }

%%

int main(int argc, char** argv) {
    // Check if a file name is provided as an argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.c>\n";
        return 1;
    }

    // Open the input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file '" << argv[1] << "'\n";
        return 1;
    }

    // Redirect the lexer's input to the file
    yyFlexLexer lexer(&inputFile, &std::cout);

    // Call the lexer's yylex method
    lexer.yylex();

    // Close the file
    inputFile.close();

    // Output the lexeme-Identifier table
    std::cout << "\nLexeme-Identifier Table:\n";
    std::cout << "--------------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(69) << "Lexeme" << "|    " << "Identifier\n";
    std::cout << "--------------------------------------------------------------------------------------------\n";
    for (const auto& pair : lexemeTable) {
        std::cout << std::left << std::setw(69) << pair.first << "|    " << pair.second << "\n";
    }
	std::cout << "--------------------------------------------------------------------------------------------\n";
    return 0;
}