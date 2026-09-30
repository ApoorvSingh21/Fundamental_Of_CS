o#include "TACGenerator.h"

#include <stdexcept>

TACGenerator::TACGenerator()
    : temporaryCounter(0)
{
}

std::string TACGenerator::newTemporary()
{
    ++temporaryCounter;

    return "t" + std::to_string(temporaryCounter);
}
std::string TACGenerator::generateExpression(const ASTNode* node)
{
    if (node == nullptr)
    {
        throw std::runtime_error(
            "TAC generation error: null expression."
        );
    }

    switch (node->getType())
    {
        case ASTNodeType::INTEGER_LITERAL:
        {
            const auto* literal =
                static_cast<const IntegerLiteral*>(node);

            return std::to_string(literal->getValue());
        }

        case ASTNodeType::FLOAT_LITERAL:
        {
            const auto* literal =
                static_cast<const FloatLiteral*>(node);

            return std::to_string(literal->getValue());
        }

        case ASTNodeType::CHAR_LITERAL:
        {
            const auto* literal =
                static_cast<const CharLiteral*>(node);

            std::string value;

            value += '\'';
            value += literal->getValue();
            value += '\'';

            return value;
        }

        case ASTNodeType::BOOLEAN_LITERAL:
        {
            const auto* literal =
                static_cast<const BooleanLiteral*>(node);

            return literal->getValue()
                ? "true"
                : "false";
        }

        case ASTNodeType::IDENTIFIER:
        {
            const auto* identifier =
                static_cast<const Identifier*>(node);

            return identifier->getName();
        }

        case ASTNodeType::BINARY_EXPRESSION:
        {
            const auto* binary =
                static_cast<const BinaryExpression*>(node);

            std::string left =
                generateExpression(binary->getLeft());

            std::string right =
                generateExpression(binary->getRight());

            std::string temporary =
                newTemporary();

            IROp operation;

            const std::string& op =
                binary->getOperator();

            if (op == "+")
                operation = IROp::ADD;

            else if (op == "-")
                operation = IROp::SUB;

            else if (op == "*")
                operation = IROp::MUL;

            else if (op == "/")
                operation = IROp::DIV;

            else if (op == "%")
                operation = IROp::MOD;

            else
            {
                throw std::runtime_error(
                    "Unsupported binary operator: " + op
                );
            }

            irProgram.emit(
                TACInstruction(
                    operation,
                    left,
                    right,
                    temporary
                )
            );

            return temporary;
        }

        default:
            throw std::runtime_error(
                "Unsupported AST node in expression."
            );
    }
}
void TACGenerator::generateStatement(
    const ASTNode* node
)
{
    if (node == nullptr)
    {
        return;
    }

    switch (node->getType())
    {
        case ASTNodeType::VARIABLE_DECLARATION:
        {
            const auto* declaration =
                static_cast<const VariableDeclaration*>(node);

            if (declaration->getInitializer() != nullptr)
            {
                std::string value =
                    generateExpression(
                        declaration->getInitializer()
                    );

                irProgram.emit(
                    TACInstruction(
                        IROp::ASSIGN,
                        value,
                        "",
                        declaration->getName()
                    )
                );
            }

            break;
        }

        case ASTNodeType::ASSIGNMENT:
        {
            const auto* assignment =
                static_cast<const Assignment*>(node);

            std::string value =
                generateExpression(
                    assignment->getExpression()
                );

            irProgram.emit(
                TACInstruction(
                    IROp::ASSIGN,
                    value,
                    "",
                    assignment->getName()
                )
            );

            break;
        }

        case ASTNodeType::PRINT_STATEMENT:
        {
            const auto* printStatement =
                static_cast<const PrintStatement*>(node);

            std::string value =
                generateExpression(
                    printStatement->getExpression()
                );

            irProgram.emit(
                TACInstruction(
                    IROp::PRINT,
                    value
                )
            );

            break;
        }

        default:
            throw std::runtime_error(
                "Unsupported AST statement."
            );
    }
}
void TACGenerator::generate(
    const Program* program
)
{
    if (program == nullptr)
    {
        throw std::runtime_error(
            "Cannot generate TAC from null program."
        );
    }

    for (const auto& statement :
         program->getStatements())
    {
        generateStatement(statement.get());
    }
}

const IRProgram& TACGenerator::getIRProgram() const
{
    return irProgram;
}
