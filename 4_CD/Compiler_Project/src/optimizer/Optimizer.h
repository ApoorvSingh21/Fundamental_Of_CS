#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "../ir/IR.h"

#include <string>
#include <unordered_map>

class Optimizer
{
private:
    std::unordered_map<std::string, std::string>
        constants;

    bool isIntegerConstant(
        const std::string& value
    ) const;

    bool isFloatConstant(
        const std::string& value
    ) const;

    bool isNumericConstant(
        const std::string& value
    ) const;

    bool isKnownConstant(
        const std::string& value
    ) const;

    std::string getConstantValue(
        const std::string& value
    ) const;

    std::string evaluateConstantExpression(
        IROp op,
        const std::string& left,
        const std::string& right
    ) const;

public:
    IRProgram optimize(
        const IRProgram& input
    );
};

#endif
