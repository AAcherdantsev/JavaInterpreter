#ifndef JAVAINTERPRETER_DEFS_H
#define JAVAINTERPRETER_DEFS_H

#define MAX_TEXT_SIZE 10000
#define MAX_LEXEME_SIZE 100
#define MAX_KEYWORDS 11

#include "iostream"
#include <fstream>
#include <cstring>

typedef char Lexeme[MAX_LEXEME_SIZE];
typedef char Text[MAX_TEXT_SIZE];

using namespace std;

enum type
{
    TYPE_CLASS = 1,
    TYPE_MAIN = 2,
    TYPE_DO = 3,
    TYPE_WHILE = 4,
    TYPE_SHORT = 5,
    TYPE_LONG = 6,
    TYPE_BOOL = 7,
    TYPE_TRUE = 8,
    TYPE_FALSE = 9,
    TYPE_RETURN = 10,
    TYPE_MAIN_FUNC = 11,

    TYPE_IDENTIFIER = 20,

    TYPE_CONST_DECIMAL = 31,
    TYPE_CONST_HEX = 32,

    TYPE_COMMA = 40,
    TYPE_SEMICOLON = 41,
    TYPE_OPEN_PARENTHESES = 42,
    TYPE_CLOSED_PARENTHESES = 43,
    TYPE_OPEN_BRACES = 44,
    TYPE_CLOSED_BRACES = 45,

    TYPE_LESS = 50,
    TYPE_LESS_EQUAL = 51,
    TYPE_MORE = 52,
    TYPE_MORE_EQUAL = 53,
    TYPE_EQUAL = 54,
    TYPE_NOT_EQUAL = 55,
    TYPE_PLUS = 56,
    TYPE_MINUS = 57,
    TYPE_MULTIPLICATION = 58,
    TYPE_DIVISION = 59,
    TYPE_SAVE = 60,

    TYPE_LOG_OR = 61,
    TYPE_LOG_AND = 62,
    TYPE_EXC_OR = 63,
    TYPE_DIV_REM = 64,
    TYPE_LOG_NOT = 65,

    TYPE_END = 100,
    TYPE_ERROR = 200
};


#define ERROR_DATA ""


#endif //JAVAINTERPRETER_DEFS_H