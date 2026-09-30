#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    // Keywords
    INT,
    FLOAT,
    CHAR,
    BOOL,
    PRINT,
    TRUE,
    FALSE,

    // Identifiers and literals
    IDENTIFIER,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    CHAR_LITERAL,

    // Operators
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    ASSIGN,

    // Symbols
    LEFT_PAREN,
    RIGHT_PAREN,
    SEMICOLON,
    COMMA,

    // Special
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token(
        TokenType type,
        const std::string& lexeme,
        int line,
        int column
    );
};

std::string tokenTypeToString(TokenType type);

#endif
