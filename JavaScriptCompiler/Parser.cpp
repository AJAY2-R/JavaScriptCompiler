#include "Parser.h"
#include "ASTNode.h"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), currentPos(0) {}

Token Parser::getNextToken() {
	if (currentPos < tokens.size()) {
		return tokens[currentPos++];
	}
	return Token(TokenType::EOF_TOKEN, "", 0, 0);
}

ASTNode* Parser::parseExpression() {
	Token token = getNextToken();
	if (token.type == TokenType::NUMBER) {
		return new ExpressionNode(token.value);
	}
	else if (token.type == TokenType::IDENTIFIER) {
		return new ExpressionNode(token.value);
	}
	else if (token.type == TokenType::SYMBOL && token.value == "(") {
		ASTNode* left = parseExpression();
		Token op = getNextToken();
		ASTNode* right = parseExpression();
		Token closeParen = getNextToken();
		if (op.type == TokenType::OPERATOR && closeParen.type == TokenType::SYMBOL && closeParen.value == ")") {
			return new BinaryOperatorNode(op.value, left, right);
		}
	}
}

ASTNode* Parser::parseStatement() {
	Token token = getNextToken();
	if (token.type == TokenType::KEYWORD && token.value == "if") {
		ASTNode* condition = parseParenthesizedExpression();
		ASTNode* ifBlock = parseBlock();
		ASTNode* elseBlock = nullptr;
		Token elseToken = getNextToken();
		if (elseToken.type == TokenType::KEYWORD && elseToken.value == "else") {
			elseBlock = parseBlock();
		}
		return new IfStatementNode(condition, ifBlock, elseBlock);
	}
	else if (token.type == TokenType::KEYWORD && token.value == "while") {
		ASTNode* condition = parseParenthesizedExpression();
		ASTNode* whileBlock = parseBlock();
		return new WhileStatementNode(condition, whileBlock);
	}
	else if (token.type == TokenType::IDENTIFIER) {
		Token nextToken = getNextToken();
		if (nextToken.type == TokenType::OPERATOR && nextToken.value == "=") {
			ASTNode* value = parseExpression();
			return new AssignmentNode(token.value, value);
		}
	}
}

ASTNode* Parser::parseTerm() {
	ASTNode* left = parseFactor();
	Token op = getNextToken();
	if (op.type == TokenType::OPERATOR && (op.value == "*" || op.value == "/")) {
		ASTNode* right = parseTerm();
		return new BinaryOperatorNode(op.value, left, right);
	}
	return left;
}

ASTNode* Parser::parseFactor() {
	Token token = getNextToken();
	if (token.type == TokenType::NUMBER) {
		return new ExpressionNode(token.value);
	}
	else if (token.type == TokenType::IDENTIFIER) {
		return new ExpressionNode(token.value);
	}
	else if (token.type == TokenType::SYMBOL && token.value == "(") {
		ASTNode* expression = parseExpression();
		Token closeParen = getNextToken();
		if (closeParen.type == TokenType::SYMBOL && closeParen.value == ")") {
			return expression;
		}
	}
}

ASTNode* Parser::parseNumber() {
	Token token = getNextToken();
	if (token.type == TokenType::NUMBER) {
		return new ExpressionNode(token.value);
	}
}

ASTNode* Parser::parseIdentifier() {
	Token token = getNextToken();
	if (token.type == TokenType::IDENTIFIER) {
		return new ExpressionNode(token.value);
	}
}

ASTNode* Parser::parseParenthesizedExpression() {
	Token openParen = getNextToken();
	if (openParen.type == TokenType::SYMBOL && openParen.value == "(") {
		ASTNode* expression = parseExpression();
		Token closeParen = getNextToken();
		if (closeParen.type == TokenType::SYMBOL && closeParen.value == ")") {
			return expression;
		}
	}
}

ASTNode* Parser::parseBlock() {
	std::vector<ASTNode*> statements;
	Token openBrace = getNextToken();
	if (openBrace.type == TokenType::SYMBOL && openBrace.value == "{") {
		ASTNode* statement = parseStatement();
		while (statement != nullptr) {
			statements.push_back(statement);
			statement = parseStatement();
		}
		Token closeBrace = getNextToken();
		if (closeBrace.type == TokenType::SYMBOL && closeBrace.value == "}") {
			return new BlockNode(statements);
		}
	}
}

ASTNode* Parser::parseAssignmentExpression() {
	ASTNode* left = parseIdentifier();
	Token op = getNextToken();
	if (op.type == TokenType::OPERATOR && op.value == "=") {
		ASTNode* right = parseExpression();
		return new AssignmentNode(left->toString(), right);
	}
}
