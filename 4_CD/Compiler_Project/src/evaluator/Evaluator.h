#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Environment.h"
#include "../parser/AST.h"

class Evaluator
{
private:

    Environment environment;

    RuntimeValue evaluateExpression(
        const ASTNode* node
    );

    void executeStatement(
        const ASTNode* node
    );

    RuntimeValue applyBinaryOperator(
        const std::string& op,
        const RuntimeValue& left,
        const RuntimeValue& right
    );

public:

    void execute(
        const Program* program
    );
};

#endif
