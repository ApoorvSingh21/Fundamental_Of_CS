#include "Parser.h"

#include <stdexcept>
#include <cstdlib>


Parser::Parser(
    const std::vector<Token>& tokens
)
    : tokens(tokens),
      current(0)
{
}


// ================================
// Token Helpers
// ================================

const Token& Parser::peek() const
{
    return tokens[current];
}


const Token& Parser::previous() const
{
    return tokens[current - 1];
}


bool Parser::isAtEnd() const
{
    return peek().type == TokenType::END_OF_FILE;
}


const Token& Parser::advance()
{
    if (!isAtEnd())
    {
        current++;
    }

    return previous();
}


bool Parser::check(TokenType type) const
{
    return peek().type == type;
}


bool Parser::match(TokenType type)
{
    if (!check(type))
        return false;

    advance();

    return true;
}


const Token& Parser::consume(
    TokenType type,
    const std::string& message
)
{
    if (check(type))
        return advance();

    throw std::runtime_error(
        message +
        " at line " +
        std::to_string(peek().line)
    );
}


// ================================
// Program
// ================================

std::unique_ptr<Program> Parser::parse()
{
    auto program = std::make_unique<Program>();

    while (!isAtEnd())
    {
        program->statements.push_back(
            parseStatement()
        );
    }

    return program;
}


// ================================
// Statement
// ================================

ASTNodePtr Parser::parseStatement()
{
    if (
        check(TokenType::INT) ||
        check(TokenType::FLOAT) ||
        check(TokenType::CHAR) ||
        check(TokenType::BOOL)
    )
    {
        return parseVariableDeclaration();
    }

    if (check(TokenType::IDENTIFIER))
    {
        return parseAssignment();
    }

    if (check(TokenType::PRINT))
    {
        return parsePrintStatement();
    }

    throw std::runtime_error(
        "Unexpected token '" +
        peek().lexeme +
        "' at line " +
        std::to_string(peek().line)
    );
}


// ================================
// Variable Declaration
// ================================

ASTNodePtr Parser::parseVariableDeclaration()
{
    std::string dataType;

    if (match(TokenType::INT))
    {
        dataType = "int";
    }
    else if (match(TokenType::FLOAT))
    {
        dataType = "float";
    }
    else if (match(TokenType::CHAR))
    {
        dataType = "char";
    }
    else if (match(TokenType::BOOL))
    {
        dataType = "bool";
    }

    const Token& name = consume(
        TokenType::IDENTIFIER,
        "Expected variable name"
    );

    ASTNodePtr initializer = nullptr;

    if (match(TokenType::ASSIGN))
    {
        initializer = parseExpression();
    }

    consume(
        TokenType::SEMICOLON,
        "Expected ';' after declaration"
    );

    return std::make_unique<VariableDeclaration>(
        dataType,
        name.lexeme,
        std::move(initializer)
    );
}


// ================================
// Assignment
// ================================

ASTNodePtr Parser::parseAssignment()
{
    const Token& name = consume(
        TokenType::IDENTIFIER,
        "Expected identifier"
    );

    consume(
        TokenType::ASSIGN,
        "Expected '='"
    );

    auto expression = parseExpression();

    consume(
        TokenType::SEMICOLON,
        "Expected ';' after assignment"
    );

    return std::make_unique<Assignment>(
        name.lexeme,
        std::move(expression)
    );
}


// ================================
// Print
// ================================

ASTNodePtr Parser::parsePrintStatement()
{
    consume(
        TokenType::PRINT,
        "Expected 'print'"
    );

    consume(
        TokenType::LEFT_PAREN,
        "Expected '(' after print"
    );

    auto expression = parseExpression();

    consume(
        TokenType::RIGHT_PAREN,
        "Expected ')' after expression"
    );

    consume(
        TokenType::SEMICOLON,
        "Expected ';' after print statement"
    );

    return std::make_unique<PrintStatement>(
        std::move(expression)
    );
}


// ================================
// Expression
// ================================

ASTNodePtr Parser::parseExpression()
{
    auto left = parseTerm();

    while (
        check(TokenType::PLUS) ||
        check(TokenType::MINUS)
    )
    {
        std::string op = advance().lexeme;

        auto right = parseTerm();

        left = std::make_unique<BinaryExpression>(
            op,
            std::move(left),
            std::move(right)
        );
    }

    return left;
}


// ================================
// Term
// ================================

ASTNodePtr Parser::parseTerm()
{
    auto left = parseFactor();

    while (
        check(TokenType::MULTIPLY) ||
        check(TokenType::DIVIDE) ||
        check(TokenType::MODULO)
    )
    {
        std::string op = advance().lexeme;

        auto right = parseFactor();

        left = std::make_unique<BinaryExpression>(
            op,
            std::move(left),
            std::move(right)
        );
    }

    return left;
}


// ================================
// Factor
// ================================

ASTNodePtr Parser::parseFactor()
{
    if (match(TokenType::INTEGER_LITERAL))
    {
        int value = std::stoi(
            previous().lexeme
        );

        return std::make_unique<IntegerLiteral>(
            value
        );
    }

    if (match(TokenType::FLOAT_LITERAL))
    {
        double value = std::stod(
            previous().lexeme
        );

        return std::make_unique<FloatLiteral>(
            value
        );
    }

    if (match(TokenType::CHAR_LITERAL))
    {
        char value = previous().lexeme[0];

        return std::make_unique<CharLiteral>(
            value
        );
    }

    if (match(TokenType::TRUE))
    {
        return std::make_unique<BooleanLiteral>(
            true
        );
    }

    if (match(TokenType::FALSE))
    {
        return std::make_unique<BooleanLiteral>(
            false
        );
    }

    if (match(TokenType::IDENTIFIER))
    {
        return std::make_unique<Identifier>(
            previous().lexeme
        );
    }

    if (match(TokenType::LEFT_PAREN))
    {
        auto expression = parseExpression();

        consume(
            TokenType::RIGHT_PAREN,
            "Expected ')'"
        );

        return expression;
    }

    throw std::runtime_error(
        "Expected expression at line " +
        std::to_string(peek().line)
    );
}
