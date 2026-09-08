#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    LET,
    PRINT,

    IDENTIFIER,
    NUMBER,

    PLUS,
    MINUS,
    STAR,
    SLASH,
    MODULO,

    ASSIGN,

    LEFT_PAREN,
    RIGHT_PAREN,

    LEFT_BRACE,
    RIGHT_BRACE,

    SEMICOLON,

    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

#endif
