#include "Parser.h"

Parser::Parser(deque<Token> myQ) {
	Queue = myQ;
	Token endToken;
	endToken.tokenID = 0;
	endToken.lineNumber = 0;
	endToken.tokenItem = "$";
	Queue.push_back(endToken);
	parse();
}

void Parser::parse() {
	cout << "Starting Parser..." << endl;

	// Push end symbol onto the stack.
	Symbol endSymbol;
	endSymbol.text = "$";
	Stack.push_back(endSymbol);
	printChanges();

	// Push start symbol onto the stack.
	Symbol startSymbol;
	startSymbol.text = "Pgm";
	Stack.push_back(startSymbol);
	printChanges();

	// Loop until stack is empty.
	while (!Stack.empty()) {
		Symbol currentSymbol = Stack.back();
		Token currentToken = Queue.front();

		// Check for a terminal Symbol.
		if (currentSymbol.isTerminal()) {
			if (currentSymbol.getSymbolId() == currentToken.tokenID) {
				Queue.pop_front();
				Stack.pop_back();
				printChanges();
			}
			else {
				cout << "ERROR: Terminal Symbol was found but did not match." << endl;
				printError();
				break;
			}
		}
		// Check for a non-terminal Symbol.
		else {
			vector<Symbol> expansion = expand(currentSymbol, currentToken);

			if (expansion.size() != 0) {
				Stack.pop_back();
				printChanges();

				// Push onto Stack in reverse order
				for (int i = expansion.size() - 1; i >= 0; i--) {
					if (expansion[i].text != "eps") {
						Stack.push_back(expansion[i]);
						printChanges();
					}
				}
			}
			else {
				printError();
				break;
			}
		}
	}
	if (Queue.empty() && Stack.empty()) {
		cout << "Parse successful." << endl;
	}
	else {
		cout << "ERROR: Parser did not finish correctly." << endl;
	}
}

// Expands a non-terminal symbol
vector<Symbol> Parser::expand(Symbol symbol, Token token) {
	vector<Symbol> expansion;
	string symbolLine = theMatrix[getRow(symbol)][getColumn(token)];
	istringstream stringStream(symbolLine);
	istream_iterator<string> begin(stringStream), end;
	vector<string> symbolText(begin, end);

	for (int i = 0; i < symbolText.size(); i++) {
		Symbol mySymbol;
		mySymbol.text = symbolText[i];
		expansion.push_back(mySymbol);
	}
	return expansion;
}

int Parser::getRow(Symbol symbol) {
	if (symbol.text == "Pgm") { return  0; }
	else if (symbol.text == "Slist") { return  1; }
	else if (symbol.text == "Stmt") { return  2; }
	else if (symbol.text == "Print") { return  3; }
	else if (symbol.text == "Y1") { return  4; }
	else if (symbol.text == "Elist") { return  5; }
	else if (symbol.text == "Elist2") { return  6; }
	else if (symbol.text == "E") { return  7; }
	else if (symbol.text == "X1") { return  8; }
	else if (symbol.text == "T") { return  9; }
	else if (symbol.text == "X2") { return  10; }
	else if (symbol.text == "F") { return  11; }
	else if (symbol.text == "DType") { return  12; }
	else if (symbol.text == "Opadd") { return  13; }
	else if (symbol.text == "Opmul") { return  14; }
	else { return -1; }
}

int Parser::getColumn(Token token) {
	if (token.tokenID == 10) { return 0; }
	else if (token.tokenID == 23) { return 1; }
	else if (token.tokenID == 22) { return 2; }
	else if (token.tokenID == 2) { return 3; }
	else if (token.tokenID == 3) { return 4; }
	else if (token.tokenID == 4) { return 5; }
	else if (token.tokenID == 5) { return 6; }
	else if (token.tokenID == 37) { return 7; }
	else if (token.tokenID == 38) { return 8; }
	else if (token.tokenID == 6) { return 9; }
	else if (token.tokenID == 46) { return 10; }
	else if (token.tokenID == 47) { return 11; }
	else if (token.tokenID == 41) { return 12; }
	else if (token.tokenID == 48) { return 13; }
	else if (token.tokenID == 42) { return 14; }
	else if (token.tokenID == 7) { return 15; }
	else if (token.tokenID == 33) { return 16; }
	else if (token.tokenID == 34) { return 17; }
	else if (token.tokenID == 0) { return 18; }
	else { return -1; }
}

// Prints the changes to the Stack & Queue
void Parser::printChanges() {
	for (int i = 0; i < Stack.size(); i++) {
		Symbol currentSymbol = Stack[i];
		cout << currentSymbol.getAbbreviation();
	}
	if (!Queue.empty()) {
		cout << "        ";
		Token currentToken = Queue.front();
		cout << "(Tok: id = "
			<< currentToken.tokenID
			<< " line = "
			<< currentToken.lineNumber
			<< " str = "
			<< '"'
			<< currentToken.tokenItem
			<< '"';

		if (currentToken.tokenID == 3) {
			cout << " int = " << currentToken.tokenItem;
		}
		if (currentToken.tokenID == 4) {
			cout << " float = " << currentToken.tokenItem;
		}

		cout << ")";
	}
	cout << endl;
}

string Parser::getColumnHeader(Token token) {
	if (token.tokenID == 10) { return "kwdprog"; }
	else if (token.tokenID == 23) { return "kwdprint"; }
	else if (token.tokenID == 22) { return "kwdinput"; }
	else if (token.tokenID == 2) { return "id"; }
	else if (token.tokenID == 3) { return "int"; }
	else if (token.tokenID == 4) { return "float"; }
	else if (token.tokenID == 5) { return "string"; }
	else if (token.tokenID == 37) { return "parens1"; }
	else if (token.tokenID == 38) { return "parens2"; }
	else if (token.tokenID == 6) { return "comma"; }
	else if (token.tokenID == 46) { return "minus"; }
	else if (token.tokenID == 47) { return "plus"; }
	else if (token.tokenID == 41) { return "aster"; }
	else if (token.tokenID == 48) { return "slash"; }
	else if (token.tokenID == 42) { return "caret"; }
	else if (token.tokenID == 7) { return  "semi"; }
	else if (token.tokenID == 33) { return "brace1"; }
	else if (token.tokenID == 34) { return "brace2"; }
	else if (token.tokenID == 0) { return  "$"; }
	else { return "ERROR: Unknown Token"; }
}

// Prints an error message.
void Parser::printError() {
	cout << "Token = " << getColumnHeader(Queue.front()) << endl;

	cout << "Top-of-stack Symbol = " << Stack.back().text << endl;

	if (Queue.front().lineNumber > -1) {
		cout << "Line Number = " << Queue.front().lineNumber << endl;
	}
}