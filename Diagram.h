//
// Created by Aleksandr Cherdantsev on 29.04.2024.
//

#ifndef JAVAINTERPRETER_DIAGRAM_H
#define JAVAINTERPRETER_DIAGRAM_H

#include "Scanner.h"
#include "Semant.h"

class Diagram
{
private:
    Scanner *scanner;
    void setAll(int pointer, int line, int column);
    void getAll(int *pointer, int *line, int *column);

    void classMain();
    void classContent();
    void description();
    void data();
    void variablesList(DataType dataType);
    void variables(DataType dataType);
    Data function(bool needToInterpActions);
    int  varForFunc(Tree * treeFunc);
    Data compositeOperator();
    Data operatorsAndDescription();
    Data operatorD();
    void assigment();
    Data functionCall();
    int  listOfExpression(Tree *func);
    Data loop();

    Data expression();
    Data logAnd();
    Data excOr();
    Data equality();
    Data comparison();
    Data addend(bool minusWasHere);
    Data multiplier();
    Data elementaryExpression();

public:
    void program();
    Tree *root;
    explicit Diagram(Scanner *scanner);
    ~Diagram();
};

#endif //JAVAINTERPRETER_DIAGRAM_H
