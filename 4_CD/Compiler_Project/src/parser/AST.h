#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <vector>

enum class ASTNodeType
{
    PROGRAM,

    VARIABLE_DECLARATION,
    ASSIGNMENT,
    PRINT_STATEMENT,

    BINARY_EXPRESSION,

    INTEGER_LITERAL,
    FLOAT_LITERAL,
    CHAR_LITERAL,
    BOOLEAN_LITERAL,

    IDENTIFIER
};

class ASTNode
{
public:
    ASTNodeType type;

    explicit ASTNode(ASTNodeType type);

    virtual ~ASTNode() = default;

    virtual void print(int indent = 0) const = 0;
};

using ASTNodePtr = std::unique_ptr<ASTNode>;


// ================================
// Literal Nodes
// ================================

class IntegerLiteral : public ASTNode
{
public:
    int value;

    explicit IntegerLiteral(int value);

    void print(int indent = 0) const override;
};


class FloatLiteral : public ASTNode
{
public:
    double value;

    explicit FloatLiteral(double value);

    void print(int indent = 0) const override;
};


class CharLiteral : public ASTNode
{
public:
    char value;

    explicit CharLiteral(char value);

    void print(int indent = 0) const override;
};


class BooleanLiteral : public ASTNode
{
public:
    bool value;

    explicit BooleanLiteral(bool value);

    void print(int indent = 0) const override;
};


// ================================
// Identifier
// ================================

class Identifier : public ASTNode
{
public:
    std::string name;

    explicit Identifier(const std::string& name);

    void print(int indent = 0) const override;
};


// ================================
// Binary Expression
// ================================

class BinaryExpression : public ASTNode
{
public:
    std::string op;

    ASTNodePtr left;
    ASTNodePtr right;

    BinaryExpression(
        const std::string& op,
        ASTNodePtr left,
        ASTNodePtr right
    );

    void print(int indent = 0) const override;
};


// ================================
// Variable Declaration
// ================================

class VariableDeclaration : public ASTNode
{
public:
    std::string dataType;
    std::string name;

    ASTNodePtr initializer;

    VariableDeclaration(
        const std::string& dataType,
        const std::string& name,
        ASTNodePtr initializer
    );

    void print(int indent = 0) const override;
};


// ================================
// Assignment
// ================================

class Assignment : public ASTNode
{
public:
    std::string name;

    ASTNodePtr expression;

    Assignment(
        const std::string& name,
        ASTNodePtr expression
    );

    void print(int indent = 0) const override;
};


// ================================
// Print Statement
// ================================

class PrintStatement : public ASTNode
{
public:
    ASTNodePtr expression;

    explicit PrintStatement(ASTNodePtr expression);

    void print(int indent = 0) const override;
};


// ================================
// Program
// ================================

class Program : public ASTNode
{
public:
    std::vector<ASTNodePtr> statements;

    Program();

    void print(int indent = 0) const override;
};

#endif
