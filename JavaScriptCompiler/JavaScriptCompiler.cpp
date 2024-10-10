#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum class TokenType {
	NUMBER,
	IDENTIFER,
	EOF_TOKEN,
	KEYWORD,
	SYMBOL
};

struct Token {
	TokenType type;
	string value;
};

class JavaScriptCompiler {
public:
	vector<Token> tokenize(const string& input) {
		vector<Token> tokens;
		size_t pos = 0;

		while (pos < input.size()) {
			if (isdigit(input[pos])) {
				string number;
				while (isdigit(input[pos])) number += input[pos++];
				tokens.push_back({ TokenType::NUMBER, number });
			}
			else if (isalpha(input[pos])) {
				string identifier;
				while (isalnum(input[pos])) identifier += input[pos++];
				tokens.push_back({ TokenType::IDENTIFER, identifier });
			}
			else if (isspace(input[pos])) {
				pos++;
			}
			else {
				tokens.push_back({ TokenType::SYMBOL, string(1, input[pos++]) });
			}
		}
		tokens.push_back({ TokenType::EOF_TOKEN, "" });
		return tokens;
	}

	int parseFactor(vector<Token>& tokens, size_t& pos) {
		if (tokens[pos].type == TokenType::NUMBER) {
			return stoi(tokens[pos++].value);
		}
		else if (tokens[pos].value == "(") {
			pos++; 
			int value = parseExpression(tokens, pos);
			if (tokens[pos].value == ")") {
				pos++;  
				return value;
			}
			else {
				throw runtime_error("Missing closing parenthesis");
			}
		}
		return 0;
	}

	int parseTerm(vector<Token>& tokens, size_t& pos) {
		int value = parseFactor(tokens, pos);
		while (tokens[pos].value == "*" || tokens[pos].value == "/") {
			string op = tokens[pos++].value;
			int nextTerm = parseFactor(tokens, pos);
			if (op == "*") value *= nextTerm;
			else if (op == "/") {
				if (nextTerm == 0) {
					throw runtime_error("Division by zero");
				}
				value /= nextTerm;
			}
		}
		return value;
	}

	int parseExpression(vector<Token>& tokens, size_t& pos) {
		int value = parseTerm(tokens, pos);
		while (tokens[pos].value == "+" || tokens[pos].value == "-") {
			string op = tokens[pos++].value;
			int nextTerm = parseTerm(tokens, pos);
			if (op == "+") value += nextTerm;
			else if (op == "-") value -= nextTerm;
		}
		return value;
	}
};

int main() {
	const string input = "3 * (4+5) + 5";
	JavaScriptCompiler js;
	auto tokens = js.tokenize(input);
	size_t pos = 0;
	try {
		cout << js.parseExpression(tokens, pos) << endl;
	}
	catch (const runtime_error& e) {
		cout << "Error: " << e.what() << endl;
	}
	return 0;
}
