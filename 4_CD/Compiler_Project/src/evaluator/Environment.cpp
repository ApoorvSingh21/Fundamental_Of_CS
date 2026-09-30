#include "Environment.h"

#include <stdexcept>

void Environment::define(
    const std::string& name,
    const RuntimeValue& value
)
{
    if (exists(name))
    {
        throw std::runtime_error(
            "Runtime error: variable '" +
            name +
            "' already exists"
        );
    }

    variables[name] = value;
}


void Environment::assign(
    const std::string& name,
    const RuntimeValue& value
)
{
    auto it = variables.find(name);

    if (it == variables.end())
    {
        throw std::runtime_error(
            "Runtime error: variable '" +
            name +
            "' does not exist"
        );
    }

    it->second = value;
}


RuntimeValue Environment::get(
    const std::string& name
) const
{
    auto it = variables.find(name);

    if (it == variables.end())
    {
        throw std::runtime_error(
            "Runtime error: variable '" +
            name +
            "' does not exist"
        );
    }

    return it->second;
}


bool Environment::exists(
    const std::string& name
) const
{
    return variables.find(name)
        != variables.end();
}
