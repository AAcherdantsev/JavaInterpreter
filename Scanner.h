//
// Created by Aleksandr Cherdantsev on 29.04.2024.
//

#ifndef JAVAINTERPRETER_SCANNER_H
#define JAVAINTERPRETER_SCANNER_H

#include "defs.h"

class Scanner
{
private:
    Text text;
    int pointer;
    int currentLine = 1;
    int currentColumn = 1;
    void countLineAndColumn();
public:
    void setPointer(int index);
    int getPointer();

    int getCurrentLine() const;
    void setCurrentLine(int line);

    int getCurrentColumn() const;
    void setCurrentColumn(int column);

    void printError(string, string);
    void readText(string);
    int scan(Lexeme lexeme);

    Scanner(string);
    ~Scanner() = default;
};

#endif //JAVAINTERPRETER_SCANNER_H
