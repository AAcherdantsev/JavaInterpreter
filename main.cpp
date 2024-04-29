#include <iostream>
#include "Diagram.h"

int main(int argc, char *argv[])
{
    string fileName = "input.dat";

    auto *scanner = new Scanner(fileName);
    auto *diagram = new Diagram(scanner);

    diagram->program();

    Lexeme lexeme;

    int type = scanner->scan(lexeme);

    if (type == TYPE_END)
    {
        cout << "No syntax errors were found." << endl;
    }
    else
        scanner->printError("Additional text found at the end of the program", "");

    return 0;
}