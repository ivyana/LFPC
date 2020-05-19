#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Lexer.h"
#include "Parser.h"


using namespace std;

int main() {
    string input;

    cout << "Enter the name of input file: " << endl;
    ifstream inFile;
    cin >> input;
    inFile.open(input);
    Lexer l(input);
    Parser p(l.getQueue());
    return 0;
}
