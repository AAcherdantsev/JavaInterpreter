#include "Diagram.h"
#include <string>

Data operator /(Data v1, Data v2)
{
    Data result;
    result.typeOfData = v1.typeOfData;

    if (v1.typeOfData == TYPE_SHORT_INT)
        result.valueOfData.dataForShort = v1.valueOfData.dataForShort / v2.valueOfData.dataForShort;

    if (v1.typeOfData == TYPE_LONG_INT)
        result.valueOfData.dataForLong = v1.valueOfData.dataForLong / v2.valueOfData.dataForLong;

    return result;
}

Data operator *(Data v1, Data v2)
{
    Data result;
    result.typeOfData = v1.typeOfData;

    if (v1.typeOfData == TYPE_SHORT_INT)
        result.valueOfData.dataForShort = v1.valueOfData.dataForShort * v2.valueOfData.dataForShort;

    if (v1.typeOfData == TYPE_LONG_INT)
        result.valueOfData.dataForLong = v1.valueOfData.dataForLong * v2.valueOfData.dataForLong;

    return result;
}

Data operator -(Data v1, Data v2)
{
    Data result;
    result.typeOfData = v1.typeOfData;

    if (v1.typeOfData == TYPE_SHORT_INT)
        result.valueOfData.dataForShort = v1.valueOfData.dataForShort - v2.valueOfData.dataForShort;

    if (v1.typeOfData == TYPE_LONG_INT)
        result.valueOfData.dataForLong = v1.valueOfData.dataForLong - v2.valueOfData.dataForLong;
    return result;
}

Data operator +(Data v1, Data v2)
{
    Data result;
    result.typeOfData = v1.typeOfData;

    if (v1.typeOfData == TYPE_SHORT_INT)
        result.valueOfData.dataForShort = v1.valueOfData.dataForShort + v2.valueOfData.dataForShort;

    if (v1.typeOfData == TYPE_LONG_INT)
        result.valueOfData.dataForLong = v1.valueOfData.dataForLong + v2.valueOfData.dataForLong;

    return result;
}

Data operator -(Data v1)
{
    Data result;
    result.typeOfData = v1.typeOfData;
    if (v1.typeOfData == TYPE_SHORT_INT)
    {
        result.valueOfData.dataForShort = -v1.valueOfData.dataForShort;
    }
    if (v1.typeOfData == TYPE_LONG_INT)
    {
        result.valueOfData.dataForLong = -v1.valueOfData.dataForLong;
    }
    return result;
}

bool operator ==(Data v1, Data v2)
{
    if (v1.typeOfData == v2.typeOfData)
    {
        if (v1.typeOfData == TYPE_LONG_INT)
        {
            return v1.valueOfData.dataForLong == v2.valueOfData.dataForLong;
        }
        else
        {
            return v1.valueOfData.dataForShort == v2.valueOfData.dataForShort;
        }
    }
    else
    {
        if (v1.typeOfData == TYPE_LONG_INT)
        {
            return v1.valueOfData.dataForLong == v2.valueOfData.dataForShort;
        }
        else
        {
            return v1.valueOfData.dataForShort == v2.valueOfData.dataForLong;
        }
    }
}

bool operator >(Data v1, Data v2)
{
    if (v1.typeOfData == v2.typeOfData)
    {
        if (v1.typeOfData == TYPE_LONG_INT)
        {
            return v1.valueOfData.dataForLong > v2.valueOfData.dataForLong;
        }
        else
        {
            return v1.valueOfData.dataForShort > v2.valueOfData.dataForShort;
        }
    }
    else
    {
        if (v1.typeOfData == TYPE_LONG_INT)
        {
            return v1.valueOfData.dataForLong > v2.valueOfData.dataForShort;
        }
        else
        {
            return v1.valueOfData.dataForShort > v2.valueOfData.dataForLong;
        }
    }
}

bool operator <(Data v1, Data v2)
{
    if (v1.typeOfData == v2.typeOfData)
    {
        if (v1.typeOfData == TYPE_LONG_INT)
        {
            return v1.valueOfData.dataForLong < v2.valueOfData.dataForLong;
        }
        else
        {
            return v1.valueOfData.dataForShort < v2.valueOfData.dataForShort;
        }
    }
    else
    {
        if (v1.typeOfData == TYPE_LONG_INT)
        {
            return v1.valueOfData.dataForLong < v2.valueOfData.dataForShort;
        }
        else
        {
            return v1.valueOfData.dataForShort < v2.valueOfData.dataForLong;
        }
    }
}

bool operator !=(Data v1, int v2)
{
    if (v1.typeOfData == TYPE_SHORT_INT)
    {
        return v1.valueOfData.dataForShort != v2;
    }
    if (v1.typeOfData == TYPE_LONG_INT)
    {
        return v1.valueOfData.dataForLong != v2;
    }
}

void Diagram::setAll(int pointer, int line, int column)
{
    scanner->setPointer(pointer);
    scanner->setCurrentLine(line);
    scanner->setCurrentColumn(column);
}

void Diagram::getAll(int* pointer, int* line, int* column)
{
    *pointer = scanner->getPointer();
    *line = scanner->getCurrentLine();
    *column = scanner->getCurrentLine();
}

void Diagram::program()
{
    Lexeme lexeme;
    int pointer, line, column, type;

    getAll(&pointer, &line, &column);
    type = scanner->scan(lexeme);

    if (type == TYPE_CLASS)
        classMain();

    root->deleteVariables(root);
}

void Diagram::classMain()
{
    Lexeme lexeme;
    int pointer, line, column, type;

    getAll(&pointer, &line, &column);

    type = scanner->scan(lexeme);
    if (type == TYPE_MAIN)
    {
        type = scanner->scan(lexeme);
        if (type == TYPE_OPEN_BRACES)
        {
            getAll(&pointer, &line, &column);
            type = scanner->scan(lexeme);
            if (type != TYPE_CLOSED_BRACES)
            {
                setAll(pointer, line, column);
                classContent();
                type = scanner->scan(lexeme);
            }
            if (type == TYPE_CLOSED_BRACES)
            {
                type = scanner->scan(lexeme);
                if (type != TYPE_SEMICOLON)
                    scanner->printError("Symbol ';' was expected", lexeme);
            }
            else
                scanner->printError("Symbol '}' was expected", lexeme);
        }
        else
            scanner->printError("Symbol '{' was expected", lexeme);
    }
    else
        scanner->printError("Lexeme 'Main' was expected", lexeme);
}

void Diagram::classContent()
{
    Lexeme lexeme;
    int pointer, line, column, type;
    getAll(&pointer, &line, &column);
    type = scanner->scan(lexeme);
    do
    {
        setAll(pointer, line, column);
        description();
        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
        setAll(pointer, line, column);

    } while (type == TYPE_LONG || type == TYPE_SHORT || type == TYPE_BOOL);
}

void Diagram::description()
{
    Lexeme lexeme;
    int pointer, line, column, type;

    getAll(&pointer, &line, &column);
    type = scanner->scan(lexeme);

    if (type == TYPE_LONG || type == TYPE_SHORT || type == TYPE_BOOL)
    {
        type = scanner->scan(lexeme);
        if (type == TYPE_IDENTIFIER || type == TYPE_MAIN_FUNC)
        {
            type = scanner->scan(lexeme);
            if (type == TYPE_OPEN_PARENTHESES)
            {
                setAll(pointer, line, column);
                function(false);
            }
            else if (type == TYPE_SEMICOLON || type == TYPE_COMMA || type == TYPE_SAVE)
            {
                setAll(pointer, line, column);
                data();
            }
            else
                scanner->printError("A variable(s) or function declaration was expected.", lexeme);
        }
        else
            scanner->printError("Identifier was expected", lexeme);
    }
    else
        scanner->printError("Data type was expected", lexeme);
}

void Diagram::data()
{
    DataType dataType;
    Lexeme lexeme;
    int type = scanner->scan(lexeme);
    if (type == TYPE_LONG || type == TYPE_SHORT || type == TYPE_BOOL)
    {
        if (type == TYPE_LONG)
            dataType = TYPE_LONG_INT;
        else if (type == TYPE_SHORT)
            dataType = TYPE_SHORT_INT;
        else
            dataType = TYPE_BOOLEAN;

        variablesList(dataType);
        type = scanner->scan(lexeme);
        if (type != TYPE_SEMICOLON)
            scanner->printError("Symbol ';' was expected", lexeme);
    }
    else
        scanner->printError("Data type was expected", lexeme);
}

void Diagram::variablesList(DataType dataType)
{
    Lexeme lexeme;
    int pointer, line, column, type;

    do
    {
        variables(dataType);
        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);

    } while (type == TYPE_COMMA);

    setAll(pointer, line, column);
}

void Diagram::variables(DataType dataType)
{
    Lexeme lexeme;
    int pointer, line, column, type;
    type = scanner->scan(lexeme);

    if (type == TYPE_IDENTIFIER)
    {
        root->includeVar(lexeme, dataType);
        root->showVarInfo(dataType, lexeme);

        Lexeme variableID;  strcpy(variableID, lexeme);

        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);

        if (type == TYPE_SAVE)
        {
            Data expressionData = expression();
            root->assignValueToVariable(expressionData, variableID);
        }
        else
            setAll(pointer, line, column);
    }
    else
        scanner->printError("Identifier was expected", lexeme);
}

Data Diagram::function(bool needToInterpActions)
{
    Lexeme lexeme;
    DataType dataType;
    int pointerI, line, column, type;
    bool mainWasHere = false;
    bool localFlag;
    int amountVar = 0;
    Tree* pointer = nullptr;

    if (needToInterpActions)
        goto beginToInterpretFunction;

    localFlag = root->flagInter;
    root->flagInter = true;
    type = scanner->scan(lexeme);

    if (type == TYPE_LONG || type == TYPE_SHORT || type == TYPE_BOOL)
    {
        if (type == TYPE_LONG)
            dataType = TYPE_LONG_INT;
        else if (type == TYPE_SHORT)
            dataType = TYPE_SHORT_INT;
        else
            dataType = TYPE_BOOLEAN;
        type = scanner->scan(lexeme);
        Lexeme funcID;
        strcpy(funcID, lexeme);
        if (type == TYPE_IDENTIFIER || type == TYPE_MAIN_FUNC)
        {
            if (type == TYPE_MAIN_FUNC)
                mainWasHere = true;

            pointer = root->includeFunc(lexeme, dataType);

            type = scanner->scan(lexeme);
            if (type == TYPE_OPEN_PARENTHESES)
            {
                root->showFuncInfo(funcID);
                amountVar = varForFunc(pointer);
                root->SemSetParam(pointer, amountVar);

                if (mainWasHere)
                    root->flagInter = true;
                else
                    root->flagInter = false;

                type = scanner->scan(lexeme);
                if (type == TYPE_CLOSED_PARENTHESES)
                {
                    getAll(&pointerI, &line, &column);
                    root->getObjectFromTree(funcID)->pointerForFunc = pointerI;

                    beginToInterpretFunction:

                    Data data = compositeOperator();
                    root->deleteVariables(pointer);
                    root->setCurrent(pointer);

                    return data;
                }
                else
                    scanner->printError("Symbol ')' was expected", lexeme);
            }
            else
                scanner->printError("Symbol '(' was expected", lexeme);
        }
        else
            scanner->printError("Identifier was expected", lexeme);
    }
    else
        scanner->printError("Data type was expected", lexeme);
}

int Diagram::varForFunc(Tree* treeFunc)
{
    Lexeme lexeme;
    int pointer, line, column, type;
    getAll(&pointer, &line, &column);
    int amountVar = 0;
    do
    {
        type = scanner->scan(lexeme);
        if (type == TYPE_LONG || type == TYPE_SHORT || type == TYPE_BOOL)
        {
            DataType dataType;
            if (type == TYPE_LONG)
                dataType = TYPE_LONG_INT;
            if (type == TYPE_SHORT)
                dataType = TYPE_SHORT_INT;
            if (type == TYPE_BOOL)
                dataType = TYPE_BOOLEAN;
            type = scanner->scan(lexeme);
            amountVar++;
            if (type != TYPE_IDENTIFIER)
                scanner->printError("Identifier was expected", lexeme);

            treeFunc->includeVar(lexeme, dataType);
        }
        else if (type == TYPE_CLOSED_PARENTHESES)
        {
            setAll(pointer, line, column);
        }
        else
            scanner->printError("Data type was expected", lexeme);
        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
    } while (type == TYPE_COMMA);
    setAll(pointer, line, column);
    return amountVar;
}

Data Diagram::compositeOperator()
{
    Lexeme lexeme;
    int type = scanner->scan(lexeme);
    if (type == TYPE_OPEN_BRACES)
    {
        Tree* lastCurr = root->current;
        Tree* pointer = root->makeScope();
        Data data = operatorsAndDescription();
        type = scanner->scan(lexeme);
        if (type != TYPE_CLOSED_BRACES)
            scanner->printError("Symbol '}' was expected", lexeme);

        root->deleteVariables(pointer);
        root->setCurrent(pointer);

        if (data.typeOfData != TYPE_UNKNOWN)
            return data;
    }
    else
        scanner->printError("Symbol '{' was expected", lexeme);
    Data data;
    data.typeOfData = TYPE_UNKNOWN;
    return data;
}

Data Diagram::operatorsAndDescription()
{
    Lexeme lexeme;
    int pointer, line, column, type;
    getAll(&pointer, &line, &column);
    type = scanner->scan(lexeme);
    do
    {
        if (type == TYPE_OPEN_BRACES)
        {
            setAll(pointer, line, column);
            Data data = compositeOperator();
            if (data.typeOfData != TYPE_UNKNOWN)
                return data;
        }
        else if (type == TYPE_LONG ||
                 type == TYPE_SHORT ||
                 type == TYPE_BOOL)
        {
            setAll(pointer, line, column);
            data();
        }
        else if (type == TYPE_RETURN ||
                 type == TYPE_DO ||
                 type == TYPE_IDENTIFIER)
        {
            setAll(pointer, line, column);
            Data data = operatorD();
            if (data.typeOfData != TYPE_UNKNOWN)
                return data;
        }
        else if (type == TYPE_CLOSED_BRACES)
        {
            setAll(pointer, line, column);
        }

        else if (type == TYPE_SEMICOLON)
        {
            setAll(pointer, line, column);
            Data data = operatorD();
            if (data.typeOfData != TYPE_UNKNOWN)
                return data;
        }
        else
            scanner->printError("Data or operator was expected", lexeme);
        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
        setAll(pointer, line, column);
    } while (
            type == TYPE_LONG ||
            type == TYPE_SHORT ||
            type == TYPE_BOOL ||
            type == TYPE_RETURN ||
            type == TYPE_DO ||
            type == TYPE_OPEN_BRACES ||
            type == TYPE_IDENTIFIER ||
            type == TYPE_SEMICOLON);
    Data data;
    data.typeOfData = TYPE_UNKNOWN;
    return data;
}

Data Diagram::operatorD()
{
    Lexeme lexeme;
    int pointer, line, column, type;
    getAll(&pointer, &line, &column);
    type = scanner->scan(lexeme);
    if (type == TYPE_RETURN)
    {
        Data data = expression();
        type = scanner->scan(lexeme);
        if (type != TYPE_SEMICOLON)
            scanner->printError("Symbol ';' was expected", lexeme);
        if (data.typeOfData != TYPE_UNKNOWN)
            return data;
    }
    else if (type == TYPE_DO)
    {
        setAll(pointer, line, column);
        loop();
        type = scanner->scan(lexeme);
        if (type != TYPE_SEMICOLON)
            scanner->printError("Symbol ';' was expected", lexeme);
    }
    else if (type == TYPE_OPEN_BRACES)
    {
        setAll(pointer, line, column);
        Data  data = compositeOperator();
        type = scanner->scan(lexeme);
        if (type != TYPE_SEMICOLON)
            scanner->printError("Symbol ';' was expected", lexeme);
        if (data.typeOfData != TYPE_UNKNOWN)
            return data;
    }
    else if (type == TYPE_IDENTIFIER)
    {
        type = scanner->scan(lexeme);
        if (type == TYPE_SAVE)
        {
            setAll(pointer, line, column);
            assigment();
            type = scanner->scan(lexeme);
            if (type != TYPE_SEMICOLON)
                scanner->printError("Symbol ';' was expected", lexeme);
        }
        else if (type == TYPE_OPEN_PARENTHESES)
        {
            setAll(pointer, line, column);
            functionCall();
            type = scanner->scan(lexeme);
            if (type != TYPE_SEMICOLON)
                scanner->printError("Symbol ';' was expected", lexeme);
        }
        else
            scanner->printError("Assigment or call Of function was expected", lexeme);
    }
    Data data;
    data.typeOfData = TYPE_UNKNOWN;
    return data;
}

void Diagram::assigment()
{
    Lexeme lexeme;
    int type = scanner->scan(lexeme);
    if (type == TYPE_IDENTIFIER)
    {
        Lexeme variableID;
        strcpy(variableID, lexeme);
        type = scanner->scan(lexeme);
        if (type == TYPE_SAVE)
        {
            Data expressionData = expression();
            root->assignValueToVariable(expressionData, variableID);
        }
        else
            scanner->printError("Symbol '=' was expected", lexeme);
    }
    else
        scanner->printError("Identifier was expected", lexeme);
}

Data Diagram::functionCall()
{
    Lexeme lexeme;
    int pointer, line, column, type;
    getAll(&pointer, &line, &column);
    type = scanner->scan(lexeme);
    Data functionData;
    Tree* currentForFuncCall;
    int pointerForFuncCall;
    currentForFuncCall = root->current;

    functionData.typeOfData = (DataType)root->getFunType(lexeme);

    if (type == TYPE_IDENTIFIER)
    {
        Lexeme identifier;
        strcpy(identifier, lexeme);
        Tree* func = root->SemGetFunct(identifier);
        type = scanner->scan(lexeme);
        if (type == TYPE_OPEN_PARENTHESES)
        {
            getAll(&pointer, &line, &column);
            type = scanner->scan(lexeme);
            if (type != TYPE_CLOSED_PARENTHESES)
            {
                setAll(pointer, line, column);
                int amountVar = listOfExpression(func);
                root->SemControlParam(func, amountVar);
                type = scanner->scan(lexeme);
            }
            else
            {
                root->SemControlParam(func, 0);
            }

            pointerForFuncCall = scanner->getPointer();
            scanner->setPointer(root->getObjectFromTree(identifier)->pointerForFunc);

            int amountParam = root->SemGetFunct(identifier)->getNode()->amountVarForFunc;
            Tree* param = nullptr;
            if (amountParam == 0)
            {
                param = root->SemGetFunct(identifier);
            }
            else
            {
                param = root->SemGetFunct(identifier)->getRight();
                for (int i = 0; i < amountParam; i++)
                    param = param->getLeft();
            }

            root->setCurrent(param);

            functionData = compositeOperator();
            if (functionData.typeOfData != root->getFuncData(identifier).typeOfData)
            {
                if (root->getFuncData(identifier).typeOfData == TYPE_LONG_INT)
                {
                    functionData.typeOfData = TYPE_LONG_INT;
                    functionData.valueOfData.dataForLong = functionData.valueOfData.dataForShort;
                }
                if (root->getFuncData(identifier).typeOfData == TYPE_SHORT_INT)
                {
                    functionData.typeOfData = TYPE_SHORT_INT;
                    functionData.valueOfData.dataForShort = functionData.valueOfData.dataForLong;
                }
            }

            if (type != TYPE_CLOSED_PARENTHESES)
                scanner->printError("Symbol ')' was expected", lexeme);

            root->setCurrent(currentForFuncCall);
            scanner->setPointer(pointerForFuncCall);
            return functionData;
        }
        else
            scanner->printError("Symbol '(' was expected", lexeme);
    }
    else
        scanner->printError("Identifier was expected", lexeme);
}
int Diagram::listOfExpression(Tree* func)
{
    Lexeme lexeme;
    int pointer, line, column, type, amountVar = 0;
    Tree* currVarInTree = func->getFirstParamOfFunc(func);
    do
    {
        int paramType = func->getDataTypeParam(currVarInTree);
        amountVar++;
        Data dataFunc = expression();
        if (!(
                (dataFunc.typeOfData == TYPE_BOOLEAN && paramType == TYPE_BOOLEAN) ||
                (dataFunc.typeOfData == TYPE_SHORT_INT && paramType == TYPE_SHORT_INT) ||
                (dataFunc.typeOfData == TYPE_SHORT_INT && paramType == TYPE_LONG_INT) ||
                (dataFunc.typeOfData == TYPE_LONG_INT && paramType == TYPE_SHORT_INT) ||
                (dataFunc.typeOfData == TYPE_LONG_INT && paramType == TYPE_LONG_INT)
        ))
        {
            string st = "The function "
                        + string(*(func->getFuncName(func)))
                        + string(" was called with the ")
                        + to_string(amountVar)
                        + string("st(rd) invalid parameter (data type error) ");
            scanner->printError(st, "");
        }
        currVarInTree->getNode()->data = root->getTypeByCastTable(dataFunc, currVarInTree->getNode()->data);
        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
        currVarInTree = currVarInTree->getLeft(currVarInTree);

    } while (type == TYPE_COMMA);

    setAll(pointer, line, column);
    return amountVar;
}

Data Diagram::loop()
{
    Lexeme lexeme;
    int pointer, column, line;
    int type = scanner->scan(lexeme);
    bool localFlagInterp = root->flagInter;
    if (type == TYPE_DO)
    {
        comebackToLoop:
        getAll(&pointer, &line, &column);
        Data data = compositeOperator();
        if (data.typeOfData != TYPE_UNKNOWN)
            return data;
        type = scanner->scan(lexeme);
        if (type == TYPE_WHILE)
        {
            type = scanner->scan(lexeme);
            if (type == TYPE_OPEN_PARENTHESES)
            {
                Data data = expression();
                type = scanner->scan(lexeme);
                if (type != TYPE_CLOSED_PARENTHESES)
                    scanner->printError("Symbol ')' was expected", lexeme);
                if (root->flagInter && data != 0)
                {
                    setAll(pointer, line, column);
                    goto comebackToLoop;
                }
                else
                {
                    root->flagInter = localFlagInterp;
                }
            }
            else
                scanner->printError("Symbol '(' was expected", lexeme);
        }
        else
            scanner->printError("Lexeme 'while' was expected", lexeme);
    }
    else
        scanner->printError("Lexeme 'do' was expected", lexeme);
    Data data;
    data.typeOfData = TYPE_UNKNOWN;
    return data;
}

Data Diagram::expression()
{

    Data firstData = logAnd();
    Data secondData;
    Lexeme lexeme;
    int pointer, line, column;
    getAll(&pointer, &line, &column);
    int type = scanner->scan(lexeme);
    while (type == TYPE_LOG_OR)
    {
        secondData = logAnd();
        firstData = root->getExpressionType(firstData, secondData);

        int result = 0;

        if (firstData != 0 || secondData != 0)
            result = 1;
        else
            result = 0;

        if (firstData.typeOfData == TYPE_LONG_INT)
            firstData.valueOfData.dataForLong = result;

        if (firstData.typeOfData == TYPE_SHORT_INT)
            firstData.valueOfData.dataForShort = result;

        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
    }
    setAll(pointer, line, column);
    return firstData;
}

Data Diagram::logAnd()
{
    Data firstData = excOr();
    Data secondData;
    Lexeme lexeme;
    int pointer, line, column;
    getAll(&pointer, &line, &column);
    int type = scanner->scan(lexeme);
    while (type == TYPE_LOG_AND)
    {
        secondData = excOr();
        firstData = root->getExpressionType(firstData, secondData);

        int result = 0;
        if (firstData != 0 && secondData != 0)
            result = 1;
        else
            result = 0;
        if (firstData.typeOfData == TYPE_LONG_INT)
            firstData.valueOfData.dataForLong = result;
        if (firstData.typeOfData == TYPE_SHORT_INT)
            firstData.valueOfData.dataForShort = result;

        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
    }
    setAll(pointer, line, column);
    return firstData;
}

Data Diagram::excOr()
{
    Data firstData = equality();
    Data secondData;
    Lexeme lexeme;

    int pointer, line, column;
    getAll(&pointer, &line, &column);

    int type = scanner->scan(lexeme);
    while (type == TYPE_EXC_OR)
    {
        secondData = equality();
        firstData = root->getExpressionType(firstData, secondData);

        int result = 0;
        if ((firstData != 0 && secondData != 0) || (!(firstData != 0) && (!(secondData != 0))))
            result = 0;
        else
            result = 1;
        if (firstData.typeOfData == TYPE_LONG_INT)
            firstData.valueOfData.dataForLong = result;
        if (firstData.typeOfData == TYPE_SHORT_INT)
            firstData.valueOfData.dataForShort = result;

        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
    }
    setAll(pointer, line, column);
    return firstData;
}

Data Diagram::equality()
{
    Data firstData = comparison();
    Data secondData;
    Lexeme lexeme;
    int pointer, line, column;
    getAll(&pointer, &line, &column);
    int type = scanner->scan(lexeme);
    while (type == TYPE_EQUAL || type == TYPE_NOT_EQUAL)
    {
        secondData = comparison();
        firstData = root->getExpressionType(firstData, secondData);
        int result = 0;
        if (firstData == secondData)
        {
            if (type == TYPE_EQUAL)
                result = 1;
            else
                result = 0;
        }
        else
        {
            if (type == TYPE_EQUAL)
                result = 0;
            else
                result = 1;
        }
        if (firstData.typeOfData == TYPE_LONG_INT)
            firstData.valueOfData.dataForLong = result;
        if (firstData.typeOfData == TYPE_SHORT_INT)
            firstData.valueOfData.dataForShort = result;

        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
    }
    setAll(pointer, line, column);
    return firstData;
}

Data Diagram::comparison()
{
    Lexeme lexeme;
    bool minusWasHere = false;
    bool plusWasHere = false;
    int pointer, line, column;
    getAll(&pointer, &line, &column);
    int type = scanner->scan(lexeme);
    if (type != TYPE_PLUS && type != TYPE_MINUS)
        setAll(pointer, line, column);
    else
    {
        if (type == TYPE_PLUS)
            plusWasHere = true;
        else
            minusWasHere = true;
    }
    Data firstData = addend(minusWasHere);
    Data secondData;
    getAll(&pointer, &line, &column);
    type = scanner->scan(lexeme);
    while (type >= TYPE_LESS && type <= TYPE_MORE_EQUAL)
    {
        secondData = addend(minusWasHere);
        firstData = root->getExpressionType(firstData, secondData);
        int result = 0;
        if (type == TYPE_LESS)
        {
            if (firstData < secondData)
                result = 1;
            else
                result = 0;
        }
        if (type == TYPE_LESS_EQUAL)
        {
            if ((firstData < secondData) || (firstData == secondData))
                result = 1;
            else
                result = 0;
        }
        if (type == TYPE_MORE)
        {
            if (firstData > secondData)
                result = 1;
            else
                result = 0;
        }
        if (type == TYPE_MORE_EQUAL)
        {
            if ((firstData > secondData) || (firstData == secondData))
                result = 1;
            else
                result = 0;
        }

        if (firstData.typeOfData == TYPE_LONG_INT)
            firstData.valueOfData.dataForLong = result;
        if (firstData.typeOfData == TYPE_SHORT_INT)
            firstData.valueOfData.dataForShort = result;

        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
    }
    setAll(pointer, line, column);
    return firstData;
}

Data Diagram::addend(bool minusWasHere)
{
    Data firstData = multiplier();
    if (minusWasHere)
        firstData = -firstData;
    Data secondData;
    Lexeme lexeme;
    int pointer, line, column;
    getAll(&pointer, &line, &column);
    int type = scanner->scan(lexeme);
    while (type == TYPE_PLUS || type == TYPE_MINUS)
    {
        secondData = multiplier();

        if (firstData.typeOfData == TYPE_BOOLEAN || secondData.typeOfData == TYPE_BOOLEAN)
            scanner->printError("Illegal operation. Arithmetic  operation for boolean", "");

        if (type == TYPE_PLUS)
            firstData = firstData + secondData;
        else
            firstData = firstData - secondData;

        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
    }
    setAll(pointer, line, column);
    return firstData;
}
Data Diagram::multiplier()
{
    bool LogNotWasHere = false;
    Lexeme lexeme;
    int pointer, line, column;
    getAll(&pointer, &line, &column);
    int type = scanner->scan(lexeme);
    if (type != TYPE_LOG_NOT)
        setAll(pointer, line, column);
    else
        LogNotWasHere = true;
    Data firstData = elementaryExpression();
    if (LogNotWasHere)
    {
        if (firstData != 0)
        {
            if (firstData.typeOfData == TYPE_SHORT_INT)
                firstData.valueOfData.dataForShort = 0;
            else
                firstData.valueOfData.dataForLong = 0;
        }
        else
        {
            if (firstData.typeOfData == TYPE_SHORT_INT)
                firstData.valueOfData.dataForShort = 1;
            else
                firstData.valueOfData.dataForLong = 1;
        }
    }
    Data secondData;
    getAll(&pointer, &line, &column);
    type = scanner->scan(lexeme);
    while (type == TYPE_DIVISION || type == TYPE_MULTIPLICATION)
    {
        secondData = elementaryExpression();
        if (firstData.typeOfData == TYPE_BOOLEAN || secondData.typeOfData == TYPE_BOOLEAN)
            scanner->printError("Illegal operation. Arithmetic  operation for boolean", "");

        firstData = root->getTypeByCastTable(firstData, secondData);
        if (type == TYPE_DIVISION)
            firstData = firstData / secondData;
        else
            firstData = firstData * secondData;
        getAll(&pointer, &line, &column);
        type = scanner->scan(lexeme);
    }
    setAll(pointer, line, column);
    return firstData;
}

Data Diagram::elementaryExpression()
{
    Lexeme lexeme;
    int startPointer, startLine, startColumn;
    getAll(&startPointer, &startLine, &startColumn);
    int type = scanner->scan(lexeme);
    if (type == TYPE_CONST_DECIMAL || type == TYPE_CONST_HEX || type == TYPE_TRUE || type == TYPE_FALSE)
    {
        Data result;
        result.typeOfData = root->getConstType(lexeme);
        if (type == TYPE_CONST_HEX)
        {
            if (result.typeOfData == TYPE_SHORT_INT)
                result.valueOfData.dataForShort = static_cast<const int>(strtol(lexeme, NULL, 16));
            if (result.typeOfData == TYPE_LONG_INT)
                result.valueOfData.dataForLong = static_cast<const int>(strtol(lexeme, NULL, 16));
        }
        else if (type == TYPE_CONST_DECIMAL)
        {
            if (result.typeOfData == TYPE_SHORT_INT)
                result.valueOfData.dataForShort = atoi(lexeme);
            if (result.typeOfData == TYPE_LONG_INT)
                result.valueOfData.dataForLong = atoi(lexeme);
        }
        return result;
    }

    if (type == TYPE_OPEN_PARENTHESES)
    {
        Data expressionData = expression();
        type = scanner->scan(lexeme);
        if (type != TYPE_CLOSED_PARENTHESES)
            scanner->printError("Symbol ')' was expected", lexeme);
        return expressionData;
    }
    if (type == TYPE_IDENTIFIER)
    {
        Lexeme identifier;
        memcpy(identifier, lexeme, strlen(lexeme) + 1);
        int secondReadPointer, secondReadLine, secondReadColumn;
        getAll(&secondReadPointer, &secondReadLine, &secondReadColumn);
        type = scanner->scan(lexeme);
        if (type == TYPE_OPEN_PARENTHESES)
        {
            setAll(startPointer, startLine, startColumn);
            return functionCall();
        }
        else
            setAll(secondReadPointer, secondReadLine, secondReadColumn);

        Data result;
        result.typeOfData = (DataType)root->getVarType(identifier);
        result.valueOfData = root->getVarValue(identifier);
        return result;
    }
    scanner->printError("Expression was expected", lexeme);
}

Diagram::Diagram(Scanner* scanner)
{
    this->scanner = scanner;
    this->root = new Tree();
    Tree::setScanner(scanner);
    root->setCurrent(root);
}