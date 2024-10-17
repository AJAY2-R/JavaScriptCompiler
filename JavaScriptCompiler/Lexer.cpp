#include "Lexer.h"
#include "Token.h"
#include <cctype>

Lexer::Lexer(const std::string& source) :sourceCode(source), currentPos(0) {}

char Lexer::getNextChar() {
	if (currentPos < sourceCode.size()) {
		return sourceCode[currentPos++];
	}
	return '\0';
}

void Lexer::skipWhiteSpace() {
	while (std::isspace(sourceCode[currentPos])) {
		currentPos++;
	}
}

Token Lexer::getNextToken() {
	skipWhiteSpace();
	char currentChar = getNextChar();
	int line = 1;
	int column = 1;
	while (currentChar != '\0') {
		if (std::isdigit(currentChar)) {
			std::string number(1, currentChar);
			while (std::isdigit(sourceCode[currentPos])) {
				number += sourceCode[currentPos++];
			}
			return Token(TokenType::NUMBER, number, line, column);
		}
		else if (std::isalpha(currentChar) || currentChar == '_') {
			std::string identifier(1, currentChar);
			while (std::isalnum(sourceCode[currentPos]) || sourceCode[currentPos] == '_') {
				identifier += sourceCode[currentPos++];
			}
			return Token(TokenType::IDENTIFIER, identifier, line, column);
		}
		else if (currentChar == '"') {
			std::string str;
			while (sourceCode[currentPos] != '"') {
				str += sourceCode[currentPos++];
			}
			currentPos++;
			return Token(TokenType::STRING, str, line, column);
		}
		else if (currentChar == '+') {
			return Token(TokenType::OPERATOR, "+", line, column);
		}
		else if (currentChar == '-') {
			return Token(TokenType::OPERATOR, "-", line, column);
		}
		else if (currentChar == '*') {
			return Token(TokenType::OPERATOR, "*", line, column);
		}
		else if (currentChar == '/') {
			return Token(TokenType::OPERATOR, "/", line, column);
		}
		else if (currentChar == '=') {
			return Token(TokenType::OPERATOR, "=", line, column);
		}
		else if (currentChar == '(') {
			return Token(TokenType::SYMBOL, "(", line, column);
		}
		else if (currentChar == ')') {
			return Token(TokenType::SYMBOL, ")", line, column);
		}
		else if (currentChar == '{') {
			return Token(TokenType::SYMBOL, "{", line, column);
		}
		else if (currentChar == '}') {
			return Token(TokenType::SYMBOL, "}", line, column);
		}
		else if (currentChar == ';') {
			return Token(TokenType::SYMBOL, ";", line, column);
		}
		else if (currentChar == ',') {
			return Token(TokenType::SYMBOL, ",", line, column);
		}
		else if (currentChar == '<') {
			if (sourceCode[currentPos] == '=') {
				currentPos++;
				return Token(TokenType::OPERATOR, "<=", line, column);
			}
			return Token(TokenType::OPERATOR, "<", line, column);
		}
		else if (currentChar == '>') {
			if (sourceCode[currentPos] == '=') {
				currentPos++;
				return Token(TokenType::OPERATOR, ">=", line, column);
			}
			return Token(TokenType::OPERATOR, ">", line, column);
		}
		else if (currentChar == '!') {
			if (sourceCode[currentPos] == '=') {
				currentPos++;
				return Token(TokenType::OPERATOR, "!=", line, column);
			}
			return Token(TokenType::OPERATOR, "!", line, column);
		}
		else if (currentChar == '&') {
			if (sourceCode[currentPos] == '&') {
				currentPos++;
				return Token(TokenType::OPERATOR, "&&", line, column);
			}
			return Token(TokenType::OPERATOR, "&", line, column);
		}
		else if (currentChar == '|') {
			if (sourceCode[currentPos] == '|') {
				currentPos++;
				return Token(TokenType::OPERATOR, "||", line, column);
			}
			return Token(TokenType::OPERATOR, "|", line, column);
		}
		else if (currentChar == '/') {
			if (sourceCode[currentPos] == '/') {
				while (sourceCode[currentPos] != '\n') {
					currentPos++;
				}
				currentPos++;
				line++;
				column = 1;
				continue;
			}
			else if (sourceCode[currentPos] == '*') {
				currentPos++;
				while (sourceCode[currentPos] != '*' && sourceCode[currentPos + 1] != '/') {
					if (sourceCode[currentPos] == '\n') {
						line++;
						column = 1;
					}
					currentPos++;
				}
				currentPos += 2;
				continue;
			}
			return Token(TokenType::OPERATOR, "/", line, column);
		}
		else if (currentChar == '\n') {
			line++;
			column = 1;
		}
		else {
			return Token(TokenType::UNKNOWN, std::string(1, currentChar), line, column);
		}
		currentChar = getNextChar();
		column++;
	}
	return Token(TokenType::EOF_TOKEN, "", line, column);
}

std::vector<Token> Lexer::tokenize() {
	std::vector<Token> tokens;
	Token token = getNextToken();
	while (token.type != TokenType::EOF_TOKEN) {
		tokens.push_back(token);
		token = getNextToken();
	}
	return tokens;
}