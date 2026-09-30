#ifndef TAC_GENERATOR_H
#define TAC_GENERATOR_H

#include "IR.h"
#include "../parser/AST.h"

#include <string>

class TACGenerator
{
private:
    IRProgram irProgram;

    int temporaryCounter;

    std::string newTemporary();

    std::string generateExpression(const ASTNode* node);

    void generateStatement(const ASTNode* node);

public:
    TACGenerator();

    void generate(const Program* program);

    const IRProgram& getIRProgram() const;
};

#endif
