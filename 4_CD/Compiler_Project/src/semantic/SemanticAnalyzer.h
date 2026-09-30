#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "../parser/AST.h"
#include "SymbolTable.h"

class SemanticAnalyzer
{
private:
    SymbolTable symbolTable;

    DataType getTypeFromString(
        const std::string& type
    ) const;

    DataType analyzeExpression(
        const ASTNode* node
    );

    void analyzeStatement(
        const ASTNode* node
    );

public:
    void analyze(
        const Program* program
    );

    const SymbolTable& getSymbolTable() const;
};

#endif
