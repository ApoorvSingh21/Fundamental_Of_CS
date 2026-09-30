#include "Lexer.h"

#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& source)
    : source(source),
      position(0),
      line(1),
      column(1)
{
    keywords["int"] = TokenType::INT;
    keywords["float"] = TokenType::FLOAT;
    keywords["char"] = TokenType::CHAR;
    keywords["bool"] = TokenType::BOOL;
    keywords["print"] = TokenType::PRINT;
    keywords["true"] = TokenType::TRUE;
    keywords["false"] = TokenType::FALSE;
}

char Lexer::currentChar() const
{
    if (position >= source.length())
        return '\0';

    return source[position];
}

void Lexer::advance()
{
    if (currentChar() == '\n')
    {
        line++;
        column = 1;
    }
    else
    {
        column++;
    }

    position++;
}

void Lexer::skipWhitespace()
{
    while (std::isspace(
        static_cast<unsigned char>(currentChar())))
    {
        advance();
    }
}

Token Lexer::scanIdentifierOrKeyword()
{
    int startLine = line;
    int startColumn = column;

    std::string value;

    while (
        std::isalnum(
            static_cast<unsigned char>(currentChar()))
        || currentChar() == '_'
    )
    {
        value += currentChar();
        advance();
    }

    auto it = keywords.find(value);

    if (it != keywords.end())
    {
        return Token(
            it->second,
            value,
            startLine,
            startColumn
        );
    }

    return Token(
        TokenType::IDENTIFIER,
        value,
        startLine,
        startColumn
    );
}

Token Lexer::scanNumber()
{
    int startLine = line;
    int startColumn = column;

    std::string value;
    bool hasDecimal = false;

    while (std::isdigit(
        static_cast<unsigned char>(currentChar())))
    {
        value += currentChar();
        advance();
    }

    if (currentChar() == '.')
    {
        hasDecimal = true;

        value += currentChar();
        advance();

        while (std::isdigit(
            static_cast<unsigned char>(currentChar())))
        {
            value += currentChar();
            advance();
        }
    }

    if (hasDecimal)
    {
        return Token(
            TokenType::FLOAT_LITERAL,
            value,
            startLine,
            startColumn
        );
    }

    return Token(
        TokenType::INTEGER_LITERAL,
        value,
        startLine,
        startColumn
    );
}

Token Lexer::scanChar()
{
    int startLine = line;
    int startColumn = column;

    advance(); // Skip opening '

    if (currentChar() == '\0')
    {
        throw std::runtime_error(
            "Unterminated character literal"
        );
    }

    char value = currentChar();

    advance();

    if (currentChar() != '\'')
    {
        throw std::runtime_error(
            "Character literal must contain exactly one character"
        );
    }

    advance(); // Skip closing '

    return Token(
        TokenType::CHAR_LITERAL,
        std::string(1, value),
        startLine,
        startColumn
    );
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    while (currentChar() != '\0')
    {
        skipWhitespace();

        if (currentChar() == '\0')
            break;

        int startLine = line;
        int startColumn = column;

        char ch = currentChar();

        // Identifier / keyword
        if (
            std::isalpha(
                static_cast<unsigned char>(ch))
            || ch == '_'
        )
        {
            tokens.push_back(
                scanIdentifierOrKeyword()
            );

            continue;
        }

        // Number
        if (std::isdigit(
            static_cast<unsigned char>(ch)))
        {
            tokens.push_back(scanNumber());

            continue;
        }

        // Character
        if (ch == '\'')
        {
            tokens.push_back(scanChar());

            continue;
        }

        // Single-character tokens
        switch (ch)
        {
            case '+':
                tokens.emplace_back(
                    TokenType::PLUS,
                    "+",
                    startLine,
                    startColumn
                );
                advance();
                break;

            case '-':
                tokens.emplace_back(
                    TokenType::MINUS,
                    "-",
                    startLine,
                    startColumn
                );
                advance();
                break;

            case '*':
                tokens.emplace_back(
                    TokenType::MULTIPLY,
                    "*",
                    startLine,
                    startColumn
                );
                advance();
                break;

            case '/':
                tokens.emplace_back(
                    TokenType::DIVIDE,
                    "/",
                    startLine,
                    startColumn
                );
                advance();
                break;

            case '%':
                tokens.emplace_back(
                    TokenType::MODULO,
                    "%",
                    startLine,
                    startColumn
                );
                advance();
                break;

            case '=':
                tokens.emplace_back(
                    TokenType::ASSIGN,
                    "=",
                    startLine,
                    startColumn
                );
                advance();
                break;

            case '(':
                tokens.emplace_back(
                    TokenType::LEFT_PAREN,
                    "(",
                    startLine,
                    startColumn
                );
                advance();
                break;

            case ')':
                tokens.emplace_back(
                    TokenType::RIGHT_PAREN,
                    ")",
                    startLine,
                    startColumn
                );
                advance();
                break;

            case ';':
                tokens.emplace_back(
                    TokenType::SEMICOLON,
                    ";",
                    startLine,
                    startColumn
                );
                advance();
                break;

            case ',':
                tokens.emplace_back(
                    TokenType::COMMA,
                    ",",
                    startLine,
                    startColumn
                );
                advance();
                break;

            default:
                tokens.emplace_back(
                    TokenType::UNKNOWN,
                    std::string(1, ch),
                    startLine,
                    startColumn
                );
                advance();
                break;
        }
    }

    tokens.emplace_back(
        TokenType::END_OF_FILE,
        "",
        line,
        column
    );

    return tokens;
}
