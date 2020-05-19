#include "Lexer.h"

Lexer::Lexer(string file_name) {
    inFile.open(file_name);
    
    if (inFile.is_open()) {
        cout << "Starting Lexer..." << endl;
    }
    if (!inFile.is_open()) {
        cout << "Error: File won't open." << endl;
    }
    
    // loop through file to get input
    while(!atEndOfFile()) {
        if (inFile.eof()) break; 
        getline(inFile, line);
        
        // iterate through each char in string line
        for (std::string::size_type i = 0; i < line.size(); ++i) {
            char c = line[i];
            char c2 = line[i + 1];
            
            if (isSpace(c)) {
                continue;
            }
            
            // string
            if (c == '"') {
                ++i;
                c = line[i];
                c2 = line[i + 1];
                while (!(c == '"')) {
                    c = line[i];
                    c2 = line[i + 1];
                    if (c == '"') continue;
                    tempstr += c;
                    ++i;
                }
                token = tempstr;
                type = "string";
                setTokenID();
                saveInfo();
                printOutput();
                resetFields();
            }
            
            // unpaired delimiter
            if (isUnpairedDelimiter(c)) {
                token = c;
                type = "unpaired delimiter";
                setTokenID();
                saveInfo();
                printOutput();
                resetFields();
                continue;
            }
            // multi-operator
            if (isMultiOperator(c, c2)) {
                token = c;
                token += c2;
                type = "multioperator";
                setTokenID();
                saveInfo();
                printOutput();
                ++i;
                resetFields();
            }
            // operator
            else if (isOperator(c)) {
                if (isComment(c, c2)) {
                    break;
                }
                else {
                    if (c2 == ' ') {
                        token = c;
                        type = "operator";
                        setTokenID();
                        saveInfo();
                        printOutput();
                    }
                    resetFields();
                }
            }
            // unpaired delimiter
            else if (isUnpairedDelimeter(c)) {
                token = c;
                type = "paired delimiter";
                setTokenID();
                saveInfo();
                printOutput();
                resetFields();
            }
            // integer
            else if (isdigit(c)) {
                tempstr += c;
                type = "integer";
                while (isdigit(c2)) {
                    ++i;
                    c = line[i];
                    c2 = line[i + 1];
                    tempstr += c;
                }
                // float
                if (c2 == '.') {
                    ++i;
                    c = line[i];
                    c2 = line[i + 1];
                    tempstr += c;
                    type = "float";
                    while (isdigit(c2)) {
                        ++i;
                        c = line[i];
                        c2 = line[i + 1];
                        tempstr += c;
                    }
                }
                token = tempstr;
                setTokenID();
                saveInfo();
                printOutput();
                resetFields();
            }
            // keyword/identifier
            else if (isalpha(c)) {
                tempstr += c;
                while (isalpha(c2) || isdigit(c2)) {
                    i++;
                    c = line[i];
                    c2 = line[i + 1];
                    tempstr += c;
                }
                if (isKeyword(tempstr)) {
                    token = tempstr;
                    type = "keyword";
                    setTokenID();
                    saveInfo();
                    printOutput();
                    resetFields();
                }
                else {
                    type = "identifier";
                    token = tempstr;
                    setTokenID();
                    saveInfo();
                    printOutput();
                    resetFields();
                }
            }
        }
        lineCount += 1;
    }
    endingProcess();
}

void Lexer::printOutput() {
    cout << "(Tok: id= "
    << idNumber
    << " line= "
    << lineCount
    << " str= "
    << '"'
    << token
    << '"';
    
    if (type == "integer") {
        cout << " int= " << token;
    }
    if (type == "float") {
        cout << " float= " << token;
    }
    
    cout << ")"
    << endl;
}

void Lexer::saveInfo() {
    Token myToken;
    myToken.lineNumber = lineCount;
    myToken.tokenID = idNumber;
    myToken.tokenItem = token;
    Queue.push_back(myToken);
}

void Lexer::setTokenID() {
    
    if (type == "identifier") {
        idNumber = 2;
        return;
    }

    if (type == "integer") {
        idNumber = 3;
    }
    
    if (type == "float") {
        idNumber = 4;
    }
    
    if (type == "string") {
        idNumber = 5;
    }

    if (token == ",") {
        idNumber = 6;
    }
    if (token == ";") {
        idNumber = 7;
    }
  
    if (token == "prog") {
        idNumber = 10;
    }
    if (token == "main") {
        idNumber = 11;
    }
    if (token == "fnc") {
        idNumber = 12;
    }
    if (token == "class") {
        idNumber = 13;
    }
    if (token == "float") {
        idNumber = 15;
    }
    if (token == "int") {
        idNumber = 16;
    }
    if (token == "string") {
        idNumber = 17;
    }
    if (token == "if") {
        idNumber = 18;
    }
    if (token == "elseif") {
        idNumber = 19;
    }
    if (token == "else") {
        idNumber = 20;
    }
    if (token == "while") {
        idNumber = 21;
    }
    if (token == "input") {
        idNumber = 22;
    }
    if (token == "print") {
        idNumber = 23;
    }
    if (token == "new") {
        idNumber = 24;
    }
    if (token == "return") {
        idNumber = 25;
    }
    
    if (token == "<") {
        idNumber = 31;
    }
    if (token == ">") {
        idNumber = 32;
    }
    if (token == "{") {
        idNumber = 33;
    }
    if (token == "}") {
        idNumber = 34;
    }
    if (token == "[") {
        idNumber = 35;
    }
    if (token == "]") {
        idNumber = 36;
    }
    if (token == "(") {
        idNumber = 37;
    }
    if (token == ")") {
        idNumber = 38;
    }
    
    if (token == "*") {
        idNumber = 41;
    }
    if (token == "^") {
        idNumber = 42;
    }
    if (token == ":") {
        idNumber = 43;
    }
    if (token == ".") {
        idNumber = 44;
    }
    if (token == "=") {
        idNumber = 45;
    }
    if (token == "-") {
        idNumber = 46;
    }
    if (token == "+") {
        idNumber = 47;
    }
    if (token == "/") {
        idNumber = 48;
    }
    
    if (token == "->") {
        idNumber = 51;
    }
    if (token == "==") {
        idNumber = 52;
    }
    if (token == "!=") {
        idNumber = 53;
    }
    if (token == "<=") {
        idNumber = 54;
    }
    if (token == ">=") {
        idNumber = 55;
    }
    if (token == "<<") {
        idNumber = 56;
    }
    if (token == ">>") {
        idNumber = 57;
    }

    if (type == "error") {
        idNumber = 99;
    }
}

void Lexer::resetFields() {
    idNumber = 0;
    token = "";
    tempstr = "";
    type = "";
}

bool Lexer::isComment(char c1, char c2) {
    return ((c1 == '/') && (c2 == '/'));
}

bool Lexer::isSpace(char c) {
    return (c == ' ');
}

bool Lexer::isUnpairedDelimiter(char c) {
    return (c == ',' || c == ';');
}

bool Lexer::isOperator(char c) {
    return (
            c == '*'
            || c == '^'
            || c == ':'
            || c == '.'
            || c == '='
            || c == '-'
            || c == '+'
            || c == '/'
            );
}

bool Lexer::isUnpairedDelimeter(char c) {
    return (
            c == '<'
            || c == '>'
            || c == '{'
            || c == '}'
            || c == '['
            || c == ']'
            || c == '('
            || c == ')'
            );
}

bool Lexer::isMultiOperator(char c1, char c2) {
    return (
            (c1 == '-' && c2 == '>')
            || (c1 == '=' && c2 == '=')
            || (c1 == '!' && c2 == '=')
            || (c1 == '<' && c2 == '=')
            || (c1 == '>' && c2 == '=')
            || (c1 == '<' && c2 == '<')
            || (c1 == '>' && c2 == '>')
            );
}

bool Lexer::isKeyword(string word) {
    return (
            word == "prog"
            || word == "main"
            || word == "fnc"
            || word == "class"
            || word == "float"
            || word == "int"
            || word == "string"
            || word == "if"
            || word == "elseif"
            || word == "else"
            || word == "while"
            || word == "input"
            || word == "print");
}

bool Lexer::atEndOfFile() {
    if (!inFile) {
        closeFile();
        return true;
    } else {
        return false;
    }
}

void Lexer::closeFile() {
    inFile.close();
}

void Lexer::endingProcess() {
    idNumber = 0;
    lineCount -= 2;
    printOutput();
}

deque<Token> Lexer::getQueue() {
    return Queue;
}
