#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

class Lexer {
public:
	Lexer(const std::string& input);
	Token getNextToken();
	std::vector<Token> tokenize();
private:
	std::string sourceCode;
	size_t currentPos;
	char getNextChar();
	void skipWhiteSpace();
};

#endif // !1
