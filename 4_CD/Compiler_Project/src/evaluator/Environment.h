i#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Value.h"

#include <string>
#include <unordered_map>

class Environment
{
private:
    std::unordered_map<
        std::string,
        RuntimeValue
    > variables;

public:

    void define(
        const std::string& name,
        const RuntimeValue& value
    );

    void assign(
        const std::string& name,
        const RuntimeValue& value
    );

    RuntimeValue get(
        const std::string& name
    ) const;

    bool exists(
        const std::string& name
    ) const;
};

#endif
