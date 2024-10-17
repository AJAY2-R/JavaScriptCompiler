#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"
#include "ASTNode.h"

class Parser {
public:
	Parser(const std::vector<Token>& tokens);
	ASTNode* parse();
private:
	std::vector<Token> tokens;
	size_t currentPos;
	Token getNextToken();
	ASTNode* parseExpression();
	ASTNode* parseStatement();
	ASTNode* parseBlock();
	ASTNode* parseTerm();
	ASTNode* parseFactor();
	ASTNode* parseNumber();
	ASTNode* parseIdentifier();
	ASTNode* parseParenthesizedExpression();
	ASTNode* parseAssignmentExpression();
};
#endif // PARSER_H
