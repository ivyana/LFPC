#ifndef Lexer_h
#define Lexer_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <deque>

using namespace std;

struct Token {
    int lineNumber;
    int tokenID;
    string tokenItem;
};

class Lexer {
public:
    Lexer();
    // empty constructor for standard input
    
    Lexer(string);
    // constructor opens file taking string of file name
    
    void printOutput();

    void saveInfo();
    // saves lineNumber, tokenID, and token string into Token struct & push to queue
    
    void setTokenID();
    
    void resetFields();
    
    bool isComment(char c1, char c2);
    // if current character and next character are '/' and '/', return true
    
    bool isSpace(char);
    // if character is a space, returns true
    
    bool isUnpairedDelimiter(char c);
    // if character is an unpaired delimter, returns true
    
    bool isOperator(char);
    // if character is a separator, returns true
    
    bool isUnpairedDelimeter(char);
    // if character is an operator, returns true
    
    bool isMultiOperator(char c1, char c2);
    
    bool isKeyword(string);
    // if string is a keyword, returns true
    
    bool atEndOfFile();
    // if at end of file, returns true
    
    void closeFile();
    // close file
    
    void endingProcess();
    // ending print and close file
    
    deque<Token> getQueue();
    // returns the Queue containing Token structs
    
private:
    ifstream inFile; // input stream
    
    int idNumber; // token ID number
    
    int lineCount = 1; // current line count in file
    string line; // string line read from input
    string token; // current string token
    string tempstr;
    string type;
    
    deque<Token> Queue;
};

#endif /* Lexer_h */
