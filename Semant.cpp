#include <string>
#include <iostream>
#include "Semant.h"

#define TYPE_EMPTY (-1)

Tree::Tree(Tree *left, Tree *right, Tree *parent, Node *data)
{
    node = new Node();
    this->parent = parent;
    this->left = left;
    this->right = right;
    memcpy(node, data, sizeof(Node));
    node->data.valueOfData.dataForLong = 0;
}

Tree::Tree()
{
    node = new Node();

    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;

    memcpy(node, &("-root-"), sizeof(Node));

    node->data.valueOfData.dataForLong = 0;
}

void Tree::setScanner(Scanner *scan)
{
    scanner = scan;
}

Tree* Tree::getFirstParamOfFunc(Tree *func)
{
    return func->right->left;
}

int Tree::getDataTypeParam(Tree *firstParam)
{
    return firstParam->node->data.typeOfData;
}

Tree *Tree::getLeft(Tree *elem)
{
    return elem->left;
}

Tree* Tree::getLeft()
{
    return this->left;
}

Tree* Tree::getRight(Tree* elem)
{
    return elem->right;
}

Tree* Tree::getRight()
{
    return this->right;
}

Lexeme* Tree::getFuncName(Tree * func)
{
    return &(func->node->id);
}

void Tree::setLeft(Node *data)
{
    Tree *newLeft = new Tree(nullptr, nullptr, this, data);
    this->left = newLeft;
}

void Tree::setRight(Node *data)
{
    Tree *newRight = new Tree(nullptr, nullptr, this, data);
    this->right = newRight;
}

void Tree::deleteVariables(Tree* tree)
{
    if (!flagInter) return;

    if (tree == nullptr) return;

    if (strcmp(tree->node->id, "-root-") == 0)
    {
        destroyLocalTree(tree->right);
        destroyLocalTree(tree->left);
    }
    else
    {
        int amountVarForFunc = tree->node->amountVarForFunc;
        if (amountVarForFunc == 0)
        {
            destroyLocalTree(tree->right);
            tree->right = nullptr;
        }
        else
        {
            tree = tree->right;
            for (int i = 0; i < amountVarForFunc; i++)
                tree = tree->left;
            destroyLocalTree(tree->left);
        }
    }
}

void Tree::destroyLocalTree(Tree* tree)
{
    if (tree != nullptr)
    {
        if (tree->left != nullptr)
            destroyLocalTree(tree->left);

        if (tree->right != nullptr)
            destroyLocalTree(tree->right);

        if (tree->parent != nullptr)
        {
            tree->parent->left = nullptr;
            tree->parent->right = nullptr;
        }

        free(tree);
    }
}

Tree *Tree::findUp(Tree *fromNode, Lexeme ID)
{
    Tree *result = fromNode;

    while ((result != nullptr) &&
           (strcmp(ID, result->node->id) != 0))
        result = result->parent;

    return result;
}

Tree *Tree::findUpInsideOneArea(Tree *from, Lexeme id)
{
    Tree *result = from;

    while ((result != nullptr) && (result->parent != nullptr) && (result->parent->right != result)) {
        if (memcmp(id, result->node->id,
                   max(strlen(id), strlen(result->node->id))) == 0)
            return result;
        result = result->parent;
    }
    return nullptr;
}

Tree *Tree::findUp(Lexeme id)
{
    return findUp(this, id);
}


void Tree::showAllDataFromTree(Tree *tree)
{
    if (tree != nullptr)
    {
        if (strcmp(tree->node->id, "-empty-") != 0)
        {
            if (tree->node->data.typeOfData == TYPE_LONG_INT)
                cout << tree->node->id << " = " << tree->node->data.valueOfData.dataForLong << ";   ";
            else if (tree->node->data.typeOfData == TYPE_SHORT_INT)
                cout << tree->node->id << " = " << tree->node->data.valueOfData.dataForShort << ";   ";
            else
                cout << tree->node->id << " = " << tree->node->data.valueOfData.dataForLong << ";   ";/////////
        }
        showAllDataFromTree(tree->left);
        showAllDataFromTree(tree->right);
    }
}

void Tree::print()
{
    cout << "NODE: ";
    cout << node->id;
    cout << " =====> ";

    if (left != nullptr)
    {
        cout << " LEFT: ";
        cout << left->node->id;
    }
    if (right != nullptr)
    {
        cout << " RIGHT: ";
        cout << right->node->id;
    }
    cout << endl;
    if (left != nullptr)
        left->print();
    if (right != nullptr)
        right->print();
}

void Tree::setCurrent(Tree *elem)
{
    current = elem;
}

Tree*Tree::getCurrent()
{
    return current;
}

Tree *Tree::includeVar(Lexeme id, DataType type)
{
    if (controlId(current, id))
        scanner->printError("A function / variable with this name already exists", id);

    Node *tempElement = new Node();
    memcpy(tempElement->id, id, strlen(id) + 1);

    tempElement->data.typeOfData  = type;
    tempElement->objectType = TYPE_VARIABLE;

    if (type == TYPE_SHORT_INT)
        tempElement->data.valueOfData.dataForShort = 0;
    if (type == TYPE_LONG_INT)
        tempElement->data.valueOfData.dataForLong = 0;

    current->setLeft(tempElement);
    current = current->left;
    return current;
}

Tree *Tree::includeFunc(Lexeme id, DataType type)
{
    if (controlId(current, id))
        scanner->printError("A function / variable with this name already exists", id);

    Node *tempElement = new Node();
    memcpy(tempElement->id, id, strlen(id) + 1);
    tempElement->data.typeOfData = type;
    tempElement->objectType = TYPE_FUNCTION;

    if (type == TYPE_SHORT_INT)
        tempElement->data.valueOfData.dataForShort = 0;
    if (type == TYPE_LONG_INT)
        tempElement->data.valueOfData.dataForLong = 0;

    tempElement->amountVarForFunc = 0;
    current->setLeft(tempElement);
    current = current->left;
    Tree *result = current;
    Node *empty = new Node();
    memcpy(empty->id, &"-empty-", strlen("-empty-") + 1);
    empty->data.typeOfData = TYPE_UNKNOWN;
    empty->objectType = TYPE_EMPTY;
    empty->data.valueOfData.dataForLong = NULL;
    current->setRight(empty);
    current = current->right;
    return result;
}

Tree *Tree::makeScope()
{
    Node *emptyNode = new Node();
    memcpy(emptyNode->id, &"-empty-", strlen("-empty-") + 1);
    emptyNode->data.typeOfData = TYPE_UNKNOWN;
    emptyNode->objectType = TYPE_EMPTY;
    emptyNode->data.valueOfData.dataForLong = NULL;
    current->setLeft(emptyNode);
    current = current->left;
    Tree *pointer = current;
    current->setRight(emptyNode);
    current = current->right;
    return pointer;
}

bool Tree::controlId(Tree *elem, Lexeme id) {
    if (findUpInsideOneArea(elem, id) == nullptr)
        return false;
    return true;
}

DataType Tree::getConstType(Lexeme constLexeme)
{
    if (strcmp(constLexeme, "true") == 0 || strcmp(constLexeme, "false") == 0)
        return TYPE_BOOLEAN;
    long long number = stoll(constLexeme, nullptr, 10);
    if (number > -32768 && number < 32767)
        return TYPE_SHORT_INT;
    if (number > -2147483647 && number < 2147483647)
        return TYPE_LONG_INT;
}

int Tree::getVarType(Lexeme id)
{
    Tree *result = this->findUp(this->getCurrent(), id);

    if (result == nullptr)
        scanner->printError("Identifier was not declared", id);

    if (result->node->objectType == TYPE_FUNCTION)
        scanner->printError("Identifier is declared as a function", id);

    return result->node->data.typeOfData;
}

Data Tree::getVarData(Lexeme id)
{
    Tree* result = this->findUp(this->getCurrent(), id);

    if (result == nullptr)
        scanner->printError("Identifier was not declared", id);

    if (result->node->objectType == TYPE_FUNCTION)
        scanner->printError("Identifier is declared as a function", id);

    return result->node->data;
}

Data Tree::getFuncData(Lexeme id)
{
    Tree* result = this->findUp(this->getCurrent(), id);

    if (result == nullptr)
        scanner->printError("Identifier was not declared", id);

    if (result->node->objectType == TYPE_VARIABLE)
        scanner->printError("Identifier is declared as a variable", id);

    return result->node->data;
}

Data* Tree::getVar(Lexeme id)
{
    Tree* result = this->findUp(this->getCurrent(), id);

    if (result == nullptr)
        scanner->printError("Identifier was not declared", id);

    if (result->node->objectType == TYPE_FUNCTION)
        scanner->printError("Identifier is declared as a function", id);

    return &result->node->data;
}

Node* Tree::getObjectFromTree(Lexeme id)
{
    Tree* result = this->findUp(this->getCurrent(), id);
    return result->node;
}

DataValue Tree::getVarValue(Lexeme id)
{
    Tree* result = this->findUp(this->getCurrent(), id);

    if (result == nullptr)
        scanner->printError("Identifier was not declared", id);

    if (result->node->objectType == TYPE_FUNCTION)
        scanner->printError("Identifier is declared as a function", id);

    return result->node->data.valueOfData;
}

void Tree::setVarValueAndType(Data newData, Lexeme id)
{
    Tree* result = this->findUp(this->getCurrent(), id);

    if (result == nullptr)
        scanner->printError("Identifier was not declared", id);

    if (result->node->objectType == TYPE_FUNCTION)
        scanner->printError("Identifier is declared as a function", id);

    result->node->data.typeOfData = newData.typeOfData;
    if (newData.typeOfData == TYPE_SHORT_INT)
        result->node->data.valueOfData.dataForShort = newData.valueOfData.dataForShort;

    if (newData.typeOfData == TYPE_LONG_INT)
        result->node->data.valueOfData.dataForLong = newData.valueOfData.dataForLong;
}

void Tree::setVarValue(Data newData, Lexeme id)
{
    Tree* result = this->findUp(this->getCurrent(), id);

    if (result == nullptr)
        scanner->printError("Identifier was not declared", id);

    if (result->node->objectType == TYPE_FUNCTION)
        scanner->printError("Identifier is declared as a function", id);

    if (result->node->data.typeOfData == TYPE_SHORT_INT)
    {
        result->node->data.valueOfData.dataForShort = newData.valueOfData.dataForShort;
        result->node->data.valueOfData.dataForShort = newData.valueOfData.dataForLong;

    }

    if (result->node->data.typeOfData == TYPE_LONG_INT)
    {
        result->node->data.valueOfData.dataForLong = newData.valueOfData.dataForLong;
        result->node->data.valueOfData.dataForLong = newData.valueOfData.dataForShort;

    }
}

int Tree::getFunType(Lexeme id) {
    Tree *result = this->findUp(this->getCurrent(), id);
    if (result == nullptr)
        scanner->printError("Identifier was not declared", id);

    if (result->node->objectType == TYPE_VARIABLE)
        scanner->printError("Identifier is declared as a variable", id);

    return result->node->data.typeOfData;
}

Data Tree::getExpressionType(Data firstType, Data secondType)
{

    if (firstType.typeOfData == TYPE_BOOLEAN && secondType.typeOfData == TYPE_BOOLEAN)
    {
        firstType.typeOfData = TYPE_BOOLEAN;
        return firstType;
    }
    if (secondType.typeOfData == TYPE_UNKNOWN)
    {
        return firstType;
    }
    else
    {
        if (firstType.typeOfData == secondType.typeOfData)
        {
            return firstType;
        }
        if (firstType.typeOfData != TYPE_LONG_INT)
        {
            firstType.typeOfData = TYPE_LONG_INT;
            firstType.valueOfData.dataForLong = firstType.valueOfData.dataForShort;
        }
        return firstType;
    }
}

void Tree::showVarInfo(DataType dataType, Lexeme lexeme)
{
    if (!flagInter) return;
    cout << "Initialization variable: ";
    if (dataType == TYPE_SHORT_INT)
        cout << " (short) ";
    if (dataType == TYPE_LONG_INT)
        cout << " (long)  ";
    if (dataType == TYPE_BOOLEAN)
        cout << " (boolean) ";
    if (dataType == TYPE_UNKNOWN)
        cout << " (unknown)  ";
    cout << lexeme << endl;
}


void Tree::assignValueToVariable(Data expressionData, Lexeme variableId)
{
    if (!flagInter) return;

    DataType variableType = (DataType) getVarType(variableId);
    assigmentControl(variableType, expressionData.typeOfData);
    setVarValueAndType(getTypeByCastTable(getVarData(variableId), expressionData), variableId);
    variableType = (DataType) getVarType(variableId);
    setVarValue(expressionData, variableId);

    cout << "Assignment variable: ";
    if (variableType == TYPE_SHORT_INT)
        cout << " (short) ";
    if (variableType == TYPE_LONG_INT)
        cout << " (long)  ";
    if (variableType == TYPE_BOOLEAN)
        cout << " (boolean) ";
    if (variableType == TYPE_UNKNOWN)
        cout << " (unknown)  ";
    cout << variableId << " = ";
    if (variableType == TYPE_SHORT_INT)
        cout << getVarValue(variableId).dataForShort << endl;
    if (variableType == TYPE_LONG_INT)
        cout << getVarValue(variableId).dataForLong << endl;
}

void Tree::showFuncInfo(Lexeme lexeme)
{
    DataType dataType = getObjectFromTree(lexeme)->data.typeOfData;
    cout << "Added function: ";
    if (dataType == TYPE_SHORT_INT)
        cout << " (short) " << lexeme << " = " << getFuncData(lexeme).valueOfData.dataForShort << endl;
    if (dataType == TYPE_LONG_INT)
        cout << " (long)  " << lexeme << " = " << getFuncData(lexeme).valueOfData.dataForLong << endl;
    if (dataType == TYPE_BOOLEAN)
        cout << " (boolean) " << endl;
    if (dataType == TYPE_UNKNOWN)
        cout << " (unknown)  " << endl;
}

Node* Tree::getNode()
{
    return this->node;
}

Data Tree::getTypeByCastTable(Data firstType, Data secondType)
{

    if (firstType.typeOfData == TYPE_BOOLEAN && secondType.typeOfData == TYPE_BOOLEAN)
    {
        firstType.typeOfData = TYPE_BOOLEAN;
        return firstType;
    }
    else if
            (
            (firstType.typeOfData == TYPE_SHORT_INT && secondType.typeOfData == TYPE_SHORT_INT) ||
            (firstType.typeOfData == TYPE_SHORT_INT && secondType.typeOfData == TYPE_LONG_INT) ||
            (firstType.typeOfData == TYPE_LONG_INT && secondType.typeOfData == TYPE_SHORT_INT) ||
            (firstType.typeOfData == TYPE_LONG_INT && secondType.typeOfData == TYPE_LONG_INT)
            )
    {
        if (firstType.typeOfData == secondType.typeOfData)
        {
            return firstType;
        }
        if (firstType.typeOfData != TYPE_LONG_INT)
        {
            firstType.typeOfData = TYPE_LONG_INT;
            firstType.valueOfData.dataForLong = firstType.valueOfData.dataForShort;
        }
        return firstType;
    }
    Tree::scanner->printError("Boolean cast error", "");
}

bool Tree::assigmentControl(DataType IDType, DataType expressionType)
{
    if (IDType == TYPE_BOOLEAN && expressionType == TYPE_BOOLEAN)
        return true;
    else if (
            (IDType == TYPE_SHORT_INT && expressionType == TYPE_SHORT_INT) ||
            (IDType == TYPE_SHORT_INT && expressionType == TYPE_LONG_INT) ||
            (IDType == TYPE_LONG_INT && expressionType == TYPE_SHORT_INT) ||
            (IDType == TYPE_LONG_INT && expressionType == TYPE_LONG_INT)
            )
        return true;
    Tree::scanner->printError("Typecast error", "");
    return false;
}

void Tree::SemSetParam(Tree* addr, int num)
{
    addr->node->amountVarForFunc = num;
}

void Tree::SemControlParam(Tree *addr, int num)
{
    if (!flagInter) return;
    if (num != addr->node->amountVarForFunc)
        Tree::scanner->printError("Invalid number of parameters for the function ", addr->node->id);
}

Tree * Tree::semGetFunc(Lexeme lexeme)
{
    Tree * v = findUp(current, lexeme);

    if (v == nullptr)
        Tree::scanner->printError("Missing function description ", lexeme);

    if (v->node->objectType != TYPE_FUNCTION)
        Tree::scanner->printError("ID is not a function ", lexeme);
    return v;
}

Tree::~Tree() = default;
Tree* Tree::current = nullptr;
Scanner* Tree::scanner = nullptr;
bool Tree::flagInter = true;