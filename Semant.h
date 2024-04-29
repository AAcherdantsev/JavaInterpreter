#ifndef JAVAINTERPRETER_SEMANT_H
#define JAVAINTERPRETER_SEMANT_H

#include "defs.h"
#include "Scanner.h"
#include <algorithm>

enum DataType
{
    TYPE_SHORT_INT = 0,
    TYPE_LONG_INT = 1,
    TYPE_BOOLEAN = 2,
    TYPE_UNKNOWN = 3
};

union DataValue
{
    short int dataForShort;
    long long int dataForLong;
};

enum ObjectType
{
    TYPE_FUNCTION,
    TYPE_VARIABLE
};

struct Data
{
    DataType typeOfData;
    DataValue valueOfData;
};

struct Node
{
    Lexeme ID;
    Data data;

    int objectType;
    int amountVarForFunc;
    int pointerForFunc;
};

class Tree
{
    Node *node;
    Tree *parent;
    Tree *left;
    Tree *right;
    static Scanner *scanner;
public:
    static bool flagInter;
    static Tree *current;

    Tree   *findUp(Tree *from, Lexeme ID);
    Tree   *findUpInsideOneArea(Tree *from, Lexeme ID);
    Tree   *findUp(Lexeme ID);
    void   showAllDataFromTree(Tree* tree);
    Tree   *getFirstParamOfFunc(Tree *func);
    Tree   *getLeft(Tree *elem);
    Tree* getLeft();
    Tree* getRight(Tree* elem);
    Tree* getRight();
    Lexeme *getFuncName(Tree * func);
    void   setLeft(Node *data);
    void   setRight(Node *data);
    void   deleteVariables(Tree* finish);
    void   destroyLocalTree(Tree* tree);
    int    getDataTypeParam(Tree *firstParam);
    void   print();

    Tree   *getCurrent();
    Tree   *includeVar(Lexeme ID, DataType type);
    Tree   *includeFunc(Lexeme ID, DataType type);
    Tree   *makeScope();
    DataType getConstType(Lexeme constLexeme);
    Data   getExpressionType(Data firstType, Data secondType);
    void showVarInfo(DataType datatype, Lexeme lexeme);
    void assignValueToVariable(Data expressionData, Lexeme variableID);
    void showFuncInfo(Lexeme lexeme);
    Node* getNode();
    Data   getTypeByCastTable(Data firstType, Data  secondType);
    Tree   *SemGetFunct(Lexeme a);
    bool   IDcontrol(Tree *elem, Lexeme ID);
    void   setCurrent(Tree *elem);
    int    getVarType(Lexeme ID);
    Data   getVarData(Lexeme ID);
    Data   getFuncData(Lexeme ID);
    Data   *getVar(Lexeme ID);
    Node* getObjectFromTree(Lexeme ID);
    DataValue getVarValue(Lexeme ID);
    void   setVarValueAndType(Data newData, Lexeme ID);
    void   setVarValue(Data newData, Lexeme ID);
    int    getFunType(Lexeme ID);
    void   SemSetParam(Tree* Addr, int num);
    void   SemControlParam(Tree *Addr, int num);
    bool   assigmentControl(DataType IDType, DataType expressionType);
    static void setScanner(Scanner *scanner);
    Tree(Tree *left, Tree *right, Tree *parent, Node *data);
    Tree();
    ~Tree();
};

#endif //JAVAINTERPRETER_SEMANT_H