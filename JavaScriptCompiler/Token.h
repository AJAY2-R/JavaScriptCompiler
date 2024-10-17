#ifndef TOKEN_H
#define TOKEN_H

#include<string>
#include<unordered_map>

enum class TokenType {
    NUMBER,         //  Numbers (e.g., 123, 4.56)
    IDENTIFIER,     //  Variable or function names
    KEYWORD,        //  Language keywords (e.g., if, while)
    SYMBOL,         //  Symbols (e.g., +, -, *, /, =, (, ), {, }, etc.)
    STRING,         //  String literals (e.g., "Hello, world")
    OPERATOR,       //  Operators (e.g., +, -, *, /)
    EOF_TOKEN,      //  End of file/input token
    COMMENT,        //  Comments (e.g., // or /* */)
    UNKNOWN         //  Unrecognized or invalid tokens
};

/// <summary>
/// A map to convert TokenType to its string representation (useful for debugging)
/// </summary>
static std::unordered_map<TokenType, std::string> TokenTypeToString = {
    {TokenType::NUMBER, "NUMBER"},
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::KEYWORD, "KEYWORD"},
    {TokenType::SYMBOL, "SYMBOL"},
    {TokenType::STRING, "STRING"},
    {TokenType::OPERATOR, "OPERATOR"},
    {TokenType::EOF_TOKEN, "EOF_TOKEN"},
    {TokenType::COMMENT, "COMMENT"},
    {TokenType::UNKNOWN, "UNKNOWN"}
};

/// <summary>
/// Represents a token in the lexer.
/// </summary>
struct Token {
    TokenType type;  // The type of the token
    std::string value;  // The actual value of the token (e.g., "123", "x", "+")
    int line;        // The line number where the token appears
    int column;      // The column number where the token starts

    Token(TokenType t, const std::string& v, int l, int c)
        : type(t), value(v), line(l), column(c) {}

    std::string toString() const {
        return "Token(" + TokenTypeToString[type] + ", " + value +
            ", Line: " + std::to_string(line) +
            ", Column: " + std::to_string(column) + ")";
    }
};

#endif // !TOKEN_H
