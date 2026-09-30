#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string>
#include <vector>
#include <unordered_map>

class Lexer
{
private:
    std::string source;

    size_t position;
    int line;
    int column;

    std::unordered_map<std::string, TokenType> keywords;

    char currentChar() const;

    void advance();

    void skipWhitespace();

    Token scanIdentifierOrKeyword();

    Token scanNumber();

    Token scanChar();

public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();
};

#endif
