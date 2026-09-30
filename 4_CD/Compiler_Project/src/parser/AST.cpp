#include "AST.h"

#include <iostream>

static void printIndent(int indent)
{
    for (int i = 0; i < indent; ++i)
    {
        std::cout << "  ";
    }
}


// ================================
// ASTNode
// ================================

ASTNode::ASTNode(ASTNodeType type)
    : type(type)
{
}


// ================================
// Integer
// ================================

IntegerLiteral::IntegerLiteral(int value)
    : ASTNode(ASTNodeType::INTEGER_LITERAL),
      value(value)
{
}

void IntegerLiteral::print(int indent) const
{
    printIndent(indent);

    std::cout << "IntegerLiteral: "
              << value
              << '\n';
}


// ================================
// Float
// ================================

FloatLiteral::FloatLiteral(double value)
    : ASTNode(ASTNodeType::FLOAT_LITERAL),
      value(value)
{
}

void FloatLiteral::print(int indent) const
{
    printIndent(indent);

    std::cout << "FloatLiteral: "
              << value
              << '\n';
}


// ================================
// Char
// ================================

CharLiteral::CharLiteral(char value)
    : ASTNode(ASTNodeType::CHAR_LITERAL),
      value(value)
{
}

void CharLiteral::print(int indent) const
{
    printIndent(indent);

    std::cout << "CharLiteral: '"
              << value
              << "'\n";
}


// ================================
// Boolean
// ================================

BooleanLiteral::BooleanLiteral(bool value)
    : ASTNode(ASTNodeType::BOOLEAN_LITERAL),
      value(value)
{
}

void BooleanLiteral::print(int indent) const
{
    printIndent(indent);

    std::cout << "BooleanLiteral: "
              << (value ? "true" : "false")
              << '\n';
}


// ================================
// Identifier
// ================================

Identifier::Identifier(const std::string& name)
    : ASTNode(ASTNodeType::IDENTIFIER),
      name(name)
{
}

void Identifier::print(int indent) const
{
    printIndent(indent);

    std::cout << "Identifier: "
              << name
              << '\n';
}


// ================================
// Binary Expression
// ================================

BinaryExpression::BinaryExpression(
    const std::string& op,
    ASTNodePtr left,
    ASTNodePtr right
)
    : ASTNode(ASTNodeType::BINARY_EXPRESSION),
      op(op),
      left(std::move(left)),
      right(std::move(right))
{
}

void BinaryExpression::print(int indent) const
{
    printIndent(indent);

    std::cout << "BinaryExpression: "
              << op
              << '\n';

    left->print(indent + 1);
    right->print(indent + 1);
}


// ================================
// Variable Declaration
// ================================

VariableDeclaration::VariableDeclaration(
    const std::string& dataType,
    const std::string& name,
    ASTNodePtr initializer
)
    : ASTNode(ASTNodeType::VARIABLE_DECLARATION),
      dataType(dataType),
      name(name),
      initializer(std::move(initializer))
{
}

void VariableDeclaration::print(int indent) const
{
    printIndent(indent);

    std::cout << "VariableDeclaration: "
              << dataType
              << " "
              << name
              << '\n';

    if (initializer)
    {
        initializer->print(indent + 1);
    }
}


// ================================
// Assignment
// ================================

Assignment::Assignment(
    const std::string& name,
    ASTNodePtr expression
)
    : ASTNode(ASTNodeType::ASSIGNMENT),
      name(name),
      expression(std::move(expression))
{
}

void Assignment::print(int indent) const
{
    printIndent(indent);

    std::cout << "Assignment: "
              << name
              << '\n';

    expression->print(indent + 1);
}


// ================================
// Print
// ================================

PrintStatement::PrintStatement(ASTNodePtr expression)
    : ASTNode(ASTNodeType::PRINT_STATEMENT),
      expression(std::move(expression))
{
}

void PrintStatement::print(int indent) const
{
    printIndent(indent);

    std::cout << "PrintStatement\n";

    expression->print(indent + 1);
}


// ================================
// Program
// ================================

Program::Program()
    : ASTNode(ASTNodeType::PROGRAM)
{
}

void Program::print(int indent) const
{
    printIndent(indent);

    std::cout << "Program\n";

    for (const auto& statement : statements)
    {
        statement->print(indent + 1);
    }
}
