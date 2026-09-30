#include "Token.h"

Token::Token(
    TokenType type,
    const std::string& lexeme,
    int line,
    int column
)
    : type(type),
      lexeme(lexeme),
      line(line),
      column(column)
{
}

std::string tokenTypeToString(TokenType type)
{
    switch (type)
    {
        case TokenType::INT:
            return "INT";

        case TokenType::FLOAT:
            return "FLOAT";

        case TokenType::CHAR:
            return "CHAR";

        case TokenType::BOOL:
            return "BOOL";

        case TokenType::PRINT:
            return "PRINT";

        case TokenType::TRUE:
            return "TRUE";

        case TokenType::FALSE:
            return "FALSE";

        case TokenType::IDENTIFIER:
            return "IDENTIFIER";

        case TokenType::INTEGER_LITERAL:
            return "INTEGER_LITERAL";

        case TokenType::FLOAT_LITERAL:
            return "FLOAT_LITERAL";

        case TokenType::CHAR_LITERAL:
            return "CHAR_LITERAL";

        case TokenType::PLUS:
            return "PLUS";

        case TokenType::MINUS:
            return "MINUS";

        case TokenType::MULTIPLY:
            return "MULTIPLY";

        case TokenType::DIVIDE:
            return "DIVIDE";

        case TokenType::MODULO:
            return "MODULO";

        case TokenType::ASSIGN:
            return "ASSIGN";

        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";

        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";

        case TokenType::SEMICOLON:
            return "SEMICOLON";

        case TokenType::COMMA:
            return "COMMA";

        case TokenType::END_OF_FILE:
            return "END_OF_FILE";

        default:
            return "UNKNOWN";
    }
}
