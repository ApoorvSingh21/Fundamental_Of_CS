#ifndef PARSER_H
#define PARSER_H

#include "../lexer/Token.h"
#include "AST.h"

#include <vector>
#include <memory>

class Parser
{
private:
    const std::vector<Token>& tokens;

    size_t current;

    const Token& peek() const;

    const Token& previous() const;

    bool isAtEnd() const;

    const Token& advance();

    bool check(TokenType type) const;

    bool match(TokenType type);

    const Token& consume(
        TokenType type,
        const std::string& message
    );

    ASTNodePtr parseStatement();

    ASTNodePtr parseVariableDeclaration();

    ASTNodePtr parseAssignment();

    ASTNodePtr parsePrintStatement();

    ASTNodePtr parseExpression();

    ASTNodePtr parseTerm();

    ASTNodePtr parseFactor();

public:
    explicit Parser(
        const std::vector<Token>& tokens
    );

    std::unique_ptr<Program> parse();
};

#endif
