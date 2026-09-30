#include "Evaluator.h"

#include <stdexcept>


// =====================================
// Binary Operator
// =====================================

RuntimeValue Evaluator::applyBinaryOperator(
    const std::string& op,
    const RuntimeValue& left,
    const RuntimeValue& right
)
{
    // =================================
    // INT + INT
    // =================================

    if (
        std::holds_alternative<int>(left) &&
        std::holds_alternative<int>(right)
    )
    {
        int l = std::get<int>(left);
        int r = std::get<int>(right);

        if (op == "+")
            return l + r;

        if (op == "-")
            return l - r;

        if (op == "*")
            return l * r;

        if (op == "/")
        {
            if (r == 0)
                throw std::runtime_error(
                    "Division by zero"
                );

            return l / r;
        }

        if (op == "%")
        {
            if (r == 0)
                throw std::runtime_error(
                    "Modulo by zero"
                );

            return l % r;
        }
    }


    // =================================
    // FLOAT + FLOAT
    // =================================

    if (
        std::holds_alternative<double>(left) &&
        std::holds_alternative<double>(right)
    )
    {
        double l =
            std::get<double>(left);

        double r =
            std::get<double>(right);

        if (op == "+")
            return l + r;

        if (op == "-")
            return l - r;

        if (op == "*")
            return l * r;

        if (op == "/")
        {
            if (r == 0.0)
                throw std::runtime_error(
                    "Division by zero"
                );

            return l / r;
        }
    }


    // =================================
    // INT + FLOAT
    // =================================

    if (
        std::holds_alternative<int>(left) &&
        std::holds_alternative<double>(right)
    )
    {
        double l =
            static_cast<double>(
                std::get<int>(left)
            );

        double r =
            std::get<double>(right);

        if (op == "+")
            return l + r;

        if (op == "-")
            return l - r;

        if (op == "*")
            return l * r;

        if (op == "/")
        {
            if (r == 0.0)
                throw std::runtime_error(
                    "Division by zero"
                );

            return l / r;
        }
    }


    // =================================
    // FLOAT + INT
    // =================================

    if (
        std::holds_alternative<double>(left) &&
        std::holds_alternative<int>(right)
    )
    {
        double l =
            std::get<double>(left);

        double r =
            static_cast<double>(
                std::get<int>(right)
            );

        if (op == "+")
            return l + r;

        if (op == "-")
            return l - r;

        if (op == "*")
            return l * r;

        if (op == "/")
        {
            if (r == 0.0)
                throw std::runtime_error(
                    "Division by zero"
                );

            return l / r;
        }
    }


    throw std::runtime_error(
        "Invalid operation: " +
        op
    );
}


// =====================================
// Expression Evaluation
// =====================================

RuntimeValue Evaluator::evaluateExpression(
    const ASTNode* node
)
{
    // =================================
    // Integer
    // =================================

    if (
        node->type ==
        ASTNodeType::INTEGER_LITERAL
    )
    {
        const auto* literal =
            static_cast<
                const IntegerLiteral*
            >(node);

        return literal->value;
    }


    // =================================
    // Float
    // =================================

    if (
        node->type ==
        ASTNodeType::FLOAT_LITERAL
    )
    {
        const auto* literal =
            static_cast<
                const FloatLiteral*
            >(node);

        return literal->value;
    }


    // =================================
    // Character
    // =================================

    if (
        node->type ==
        ASTNodeType::CHAR_LITERAL
    )
    {
        const auto* literal =
            static_cast<
                const CharLiteral*
            >(node);

        return literal->value;
    }


    // =================================
    // Boolean
    // =================================

    if (
        node->type ==
        ASTNodeType::BOOLEAN_LITERAL
    )
    {
        const auto* literal =
            static_cast<
                const BooleanLiteral*
            >(node);

        return literal->value;
    }


    // =================================
    // Identifier
    // =================================

    if (
        node->type ==
        ASTNodeType::IDENTIFIER
    )
    {
        const auto* identifier =
            static_cast<
                const Identifier*
            >(node);

        return environment.get(
            identifier->name
        );
    }


    // =================================
    // Binary Expression
    // =================================

    if (
        node->type ==
        ASTNodeType::BINARY_EXPRESSION
    )
    {
        const auto* binary =
            static_cast<
                const BinaryExpression*
            >(node);

        RuntimeValue left =
            evaluateExpression(
                binary->left.get()
            );

        RuntimeValue right =
            evaluateExpression(
                binary->right.get()
            );

        return applyBinaryOperator(
            binary->op,
            left,
            right
        );
    }


    throw std::runtime_error(
        "Unknown expression"
    );
}


// =====================================
// Statement Execution
// =====================================

void Evaluator::executeStatement(
    const ASTNode* node
)
{
    // =================================
    // Variable Declaration
    // =================================

    if (
        node->type ==
        ASTNodeType::VARIABLE_DECLARATION
    )
    {
        const auto* declaration =
            static_cast<
                const VariableDeclaration*
            >(node);

        RuntimeValue value;

        if (declaration->initializer)
        {
            value =
                evaluateExpression(
                    declaration->initializer.get()
                );
        }
        else
        {
            // Default initialization
            if (declaration->dataType == "int")
                value = 0;

            else if (
                declaration->dataType == "float"
            )
                value = 0.0;

            else if (
                declaration->dataType == "char"
            )
                value = '\0';

            else if (
                declaration->dataType == "bool"
            )
                value = false;
        }

        environment.define(
            declaration->name,
            value
        );

        return;
    }


    // =================================
    // Assignment
    // =================================

    if (
        node->type ==
        ASTNodeType::ASSIGNMENT
    )
    {
        const auto* assignment =
            static_cast<
                const Assignment*
            >(node);

        RuntimeValue value =
            evaluateExpression(
                assignment->expression.get()
            );

        environment.assign(
            assignment->name,
            value
        );

        return;
    }


    // =================================
    // Print
    // =================================

    if (
        node->type ==
        ASTNodeType::PRINT_STATEMENT
    )
    {
        const auto* print =
            static_cast<
                const PrintStatement*
            >(node);

        RuntimeValue value =
            evaluateExpression(
                print->expression.get()
            );

        printRuntimeValue(value);

        std::cout << '\n';

        return;
    }
}


// =====================================
// Execute Program
// =====================================

void Evaluator::execute(
    const Program* program
)
{
    for (
        const auto& statement :
        program->statements
    )
    {
        executeStatement(
            statement.get()
        );
    }
}
