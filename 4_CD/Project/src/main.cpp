#include "../include/lexer.h"

#include <iostream>
#include <string>

std::string tokenTypeName(TokenType type) {

    switch (type) {

        case TokenType::LET:
            return "LET";

        case TokenType::PRINT:
            return "PRINT";

        case TokenType::IDENTIFIER:
            return "IDENTIFIER";

        case TokenType::NUMBER:
            return "NUMBER";

        case TokenType::PLUS:
            return "PLUS";

        case TokenType::MINUS:
            return "MINUS";

        case TokenType::STAR:
            return "STAR";

        case TokenType::SLASH:
            return "SLASH";

        case TokenType::MODULO:
            return "MODULO";

        case TokenType::ASSIGN:
            return "ASSIGN";

        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";

        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";

        case TokenType::LEFT_BRACE:
            return "LEFT_BRACE";

        case TokenType::RIGHT_BRACE:
            return "RIGHT_BRACE";

        case TokenType::SEMICOLON:
            return "SEMICOLON";

        case TokenType::END_OF_FILE:
            return "EOF";

        default:
            return "UNKNOWN";
    }
}

int main() {

    std::string source =
        "let x = 10 + 20;\n"
        "print(x);";

    Lexer lexer(source);

    std::vector<Token> tokens = lexer.tokenize();

    for (const Token& token : tokens) {

        std::cout
            << tokenTypeName(token.type)
            << " -> "
            << token.lexeme
            << " (line "
            << token.line
            << ")"
            << std::endl;
    }

    return 0;
}
