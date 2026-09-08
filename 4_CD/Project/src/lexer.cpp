#include "../include/lexer.h"

#include <cctype>
#include <unordered_map>

Lexer::Lexer(const std::string& source)
    : source(source) {
}

bool Lexer::isAtEnd() {
    return current >= static_cast<int>(source.length());
}

char Lexer::advance() {
    return source[current++];
}

char Lexer::peek() {
    if (isAtEnd())
        return '\0';

    return source[current];
}

char Lexer::peekNext() {
    if (current + 1 >= static_cast<int>(source.length()))
        return '\0';

    return source[current + 1];
}

void Lexer::addToken(TokenType type) {
    std::string text = source.substr(start, current - start);
    addToken(type, text);
}

void Lexer::addToken(TokenType type, const std::string& text) {
    tokens.push_back({type, text, line});
}

void Lexer::number() {

    while (std::isdigit(peek())) {
        advance();
    }

    addToken(TokenType::NUMBER);
}

void Lexer::identifier() {

    while (std::isalnum(peek()) || peek() == '_') {
        advance();
    }

    std::string text = source.substr(start, current - start);

    if (text == "let") {
        addToken(TokenType::LET);
    }
    else if (text == "print") {
        addToken(TokenType::PRINT);
    }
    else {
        addToken(TokenType::IDENTIFIER);
    }
}

void Lexer::scanToken() {

    char c = advance();

    switch (c) {

        case '+':
            addToken(TokenType::PLUS);
            break;

        case '-':
            addToken(TokenType::MINUS);
            break;

        case '*':
            addToken(TokenType::STAR);
            break;

        case '/':
            addToken(TokenType::SLASH);
            break;

        case '%':
            addToken(TokenType::MODULO);
            break;

        case '=':
            addToken(TokenType::ASSIGN);
            break;

        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;

        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;

        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;

        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;

        case ';':
            addToken(TokenType::SEMICOLON);
            break;

        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;

        default:

            if (std::isdigit(c)) {
                number();
            }
            else if (std::isalpha(c) || c == '_') {
                identifier();
            }
            else {
                addToken(TokenType::UNKNOWN);
            }

            break;
    }
}

std::vector<Token> Lexer::tokenize() {

    while (!isAtEnd()) {

        start = current;

        scanToken();
    }

    tokens.push_back({
        TokenType::END_OF_FILE,
        "",
        line
    });

    return tokens;
}
