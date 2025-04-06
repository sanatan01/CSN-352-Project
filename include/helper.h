#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <y.tab.h>
#include <stdarg.h>


static inline const char* getTokenName(int token) {
    switch (token) {
    case AUTO:              return "AUTO";
    case BREAK:             return "BREAK";
    case CASE:              return "CASE";
    case CHAR:              return "CHAR";
    case CONST:             return "CONST";
    case CONTINUE:          return "CONTINUE";
    case DEFAULT:           return "DEFAULT";
    case DO:                return "DO";
    case DOUBLE:            return "DOUBLE";
    case ELSE:              return "ELSE";
    case ENUM:              return "ENUM";
    case EXTERN:            return "EXTERN";
    case FLOAT:             return "FLOAT";
    case FOR:               return "FOR";
    case GOTO:              return "GOTO";
    case IF:                return "IF";
    case INT:               return "INT";
    case LONG:              return "LONG";
    case REGISTER:          return "REGISTER";
    case RETURN:            return "RETURN";
    case SHORT:             return "SHORT";
    case SIGNED:            return "SIGNED";
    case SIZEOF:            return "SIZEOF";
    case STATIC:            return "STATIC";
    case STRUCT:            return "STRUCT";
    case SWITCH:            return "SWITCH";
    case TYPEDEF:           return "TYPEDEF";
    case UNION:             return "UNION";
    case UNSIGNED:          return "UNSIGNED";
    case VOID:              return "VOID";
    case VOLATILE:          return "VOLATILE";
    case WHILE:             return "WHILE";
    case IDENTIFIER:        return "IDENTIFIER";
    case CONSTANT_LITERAL:          return "CONSTANT_LITERAL";
    case STRING_LITERAL:    return "STRING_LITERAL";
    case ELLIPSIS:          return "ELLIPSIS";
    case RIGHT_ASSIGN:      return "RIGHT_ASSIGN";
    case LEFT_ASSIGN:       return "LEFT_ASSIGN";
    case ADD_ASSIGN:        return "ADD_ASSIGN";
    case SUB_ASSIGN:        return "SUB_ASSIGN";
    case MUL_ASSIGN:        return "MUL_ASSIGN";
    case DIV_ASSIGN:        return "DIV_ASSIGN";
    case MOD_ASSIGN:        return "MOD_ASSIGN";
    case AND_ASSIGN:        return "AND_ASSIGN";
    case XOR_ASSIGN:        return "XOR_ASSIGN";
    case OR_ASSIGN:         return "OR_ASSIGN";
    case RIGHT_OP:          return "RIGHT_OP";
    case LEFT_OP:           return "LEFT_OP";
    case INC_OP:            return "INC_OP";
    case DEC_OP:            return "DEC_OP";
    case PTR_OP:            return "PTR_OP";
    case AND_OP:            return "AND_OP";
    case OR_OP:             return "OR_OP";
    case LE_OP:             return "LE_OP";
    case GE_OP:             return "GE_OP";
    case EQ_OP:             return "EQ_OP";
    case NE_OP:             return "NE_OP";
    case SEMICOLON:      return "SEMICOLON";
    case LEFT_BRACE:     return "LEFT_BRACE";
    case RIGHT_BRACE:    return "RIGHT_BRACE";
    case COMMA:          return "COMMA";
    case COLON:          return "COLON";
    case ASSIGN:         return "ASSIGN";
    case LEFT_PAREN:     return "LEFT_PAREN";
    case RIGHT_PAREN:    return "RIGHT_PAREN";
    case LEFT_BRACKET:   return "LEFT_BRACKET";
    case RIGHT_BRACKET:  return "RIGHT_BRACKET";
    case DOT:            return "DOT";
    case AMPERSAND:      return "AMPERSAND";
    case EXCLAMATION:    return "EXCLAMATION";
    case TILDE:          return "TILDE";
    case MINUS:          return "MINUS";
    case PLUS:           return "PLUS";
    case ASTERISK:       return "ASTERISK";
    case SLASH:          return "SLASH";
    case PERCENT:        return "PERCENT";
    case LESS_THAN:      return "LESS_THAN";
    case GREATER_THAN:   return "GREATER_THAN";
    case CARET:          return "CARET";
    case PIPE:           return "PIPE";
    case QUESTION:       return "QUESTION";
    case INVALID_ID:        return "INVALID_ID";
    case INVALID_CHAR:      return "INVALID_CHAR";
    case INVALID_OCT:       return "INVALID_OCT";
    case UNTERM_STRING:     return "UNTERM_STRING";
    case BOOL:              return "BOOL";
    default:                return "UNKNOWN";
    }
}


// Function declarations
void displayTables();
void comment();

// 

// Other necessary declarations
