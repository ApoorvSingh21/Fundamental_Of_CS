#include "SemanticAnalyzer.h"

#include <stdexcept>


DataType SemanticAnalyzer::getTypeFromString(
    const std::string& type
) const
{
    if (type == "int")
        return DataType::INT;

    if (type == "float")
        return DataType::FLOAT;

    if (type == "char")
        return DataType::CHAR;

    if (type == "bool")
        return DataType::BOOL;

    return DataType::UNKNOWN;
}


DataType SemanticAnalyzer::analyzeExpression(
    const ASTNode* node
)
{
    if (!node)
    {
        return DataType::UNKNOWN;
    }


    // Integer
    if (node->type ==
        ASTNodeType::INTEGER_LITERAL)
    {
        return DataType::INT;
    }


    // Float
    if (node->type ==
        ASTNodeType::FLOAT_LITERAL)
    {
        return DataType::FLOAT;
    }


    // Char
    if (node->type ==
        ASTNodeType::CHAR_LITERAL)
    {
        return DataType::CHAR;
    }


    // Boolean
    if (node->type ==
        ASTNodeType::BOOLEAN_LITERAL)
    {
        return DataType::BOOL;
    }


    // Identifier
    if (node->type ==
        ASTNodeType::IDENTIFIER)
    {
        const auto* identifier =
            static_cast<
                const Identifier*
            >(node);

        const Symbol* symbol =
            symbolTable.lookup(
                identifier->name
            );

        if (!symbol)
        {
            throw std::runtime_error(
                "Variable '" +
                identifier->name +
                "' is not declared"
            );
        }

        return symbol->type;
    }


    // Binary expression
    if (node->type ==
        ASTNodeType::BINARY_EXPRESSION)
    {
        const auto* binary =
            static_cast<
                const BinaryExpression*
            >(node);

        DataType leftType =
            analyzeExpression(
                binary->left.get()
            );

        DataType rightType =
            analyzeExpression(
                binary->right.get()
            );

        // int + int → int
        if (
            leftType == DataType::INT &&
            rightType == DataType::INT
        )
        {
            return DataType::INT;
        }

        // float operations
        if (
            (leftType == DataType::FLOAT &&
             rightType == DataType::FLOAT)
        )
        {
            return DataType::FLOAT;
        }

        // int + float → float
        if (
            (leftType == DataType::INT &&
             rightType == DataType::FLOAT)
            ||
            (leftType == DataType::FLOAT &&
             rightType == DataType::INT)
        )
        {
            return DataType::FLOAT;
        }

        throw std::runtime_error(
            "Invalid operands for operator '" +
            binary->op +
            "': " +
            dataTypeToString(leftType) +
            " and " +
            dataTypeToString(rightType)
        );
    }


    return DataType::UNKNOWN;
}


void SemanticAnalyzer::analyzeStatement(
    const ASTNode* node
)
{
    // Variable declaration
    if (
        node->type ==
        ASTNodeType::VARIABLE_DECLARATION
    )
    {
        const auto* declaration =
            static_cast<
                const VariableDeclaration*
            >(node);

        DataType declaredType =
            getTypeFromString(
                declaration->dataType
            );

        if (
            !symbolTable.declare(
                declaration->name,
                declaredType
            )
        )
        {
            throw std::runtime_error(
                "Variable '" +
                declaration->name +
                "' already declared"
            );
        }

        if (declaration->initializer)
        {
            DataType expressionType =
                analyzeExpression(
                    declaration->initializer.get()
                );

            // Exact match
            if (expressionType == declaredType)
            {
                return;
            }

            // int → float allowed
            if (
                declaredType == DataType::FLOAT &&
                expressionType == DataType::INT
            )
            {
                return;
            }

            throw std::runtime_error(
                "Cannot initialize variable '" +
                declaration->name +
                "' of type " +
                dataTypeToString(declaredType) +
                " with expression of type " +
                dataTypeToString(expressionType)
            );
        }

        return;
    }


    // Assignment
    if (
        node->type ==
        ASTNodeType::ASSIGNMENT
    )
    {
        const auto* assignment =
            static_cast<
                const Assignment*
            >(node);

        const Symbol* symbol =
            symbolTable.lookup(
                assignment->name
            );

        if (!symbol)
        {
            throw std::runtime_error(
                "Variable '" +
                assignment->name +
                "' is not declared"
            );
        }

        DataType expressionType =
            analyzeExpression(
                assignment->expression.get()
            );

        if (
            expressionType == symbol->type
        )
        {
            return;
        }

        if (
            symbol->type == DataType::FLOAT &&
            expressionType == DataType::INT
        )
        {
            return;
        }

        throw std::runtime_error(
            "Cannot assign " +
            dataTypeToString(expressionType) +
            " to " +
            dataTypeToString(symbol->type) +
            " variable '" +
            assignment->name +
            "'"
        );
    }


    // Print
    if (
        node->type ==
        ASTNodeType::PRINT_STATEMENT
    )
    {
        const auto* print =
            static_cast<
                const PrintStatement*
            >(node);

        analyzeExpression(
            print->expression.get()
        );

        return;
    }
}


void SemanticAnalyzer::analyze(
    const Program* program
)
{
    for (const auto& statement :
         program->statements)
    {
        analyzeStatement(
            statement.get()
        );
    }
}


const SymbolTable&
SemanticAnalyzer::getSymbolTable() const
{
    return symbolTable;
}
