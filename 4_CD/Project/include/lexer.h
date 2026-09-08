#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <vector>

class Lexer {
private:
    std::string source;
    std::vector<Token> tokens;

    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd();
    char advance();
    char peek();
    char peekNext();

    void scanToken();

    void identifier();
    void number();

    void addToken(TokenType type);
    void addToken(TokenType type, const std::string& text);

public:
    Lexer(const std::string& source);

    std::vector<Token> tokenize();
};

#endif

