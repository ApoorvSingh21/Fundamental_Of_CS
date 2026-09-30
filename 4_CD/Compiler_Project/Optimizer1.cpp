#include "Optimizer.h"

#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <stdexcept>

bool Optimizer::isIntegerConstant(
    const std::string& value
) const
{
    if (value.empty())
        return false;

    std::size_t start = 0;

    if (value[0] == '-' || value[0] == '+')
        start = 1;

    if (start == value.size())
        return false;

    for (std::size_t i = start;
         i < value.size();
         ++i)
    {
        if (!std::isdigit(
                static_cast<unsigned char>(value[i])))
        {
            return false;
        }
    }

    return true;
}

bool Optimizer::isFloatConstant(
    const std::string& value
) const
{
    if (value.empty())
        return false;

    char* end = nullptr;

    std::strtod(
        value.c_str(),
        &end
    );

    return end != value.c_str()
        && *end == '\0'
        && value.find('.') != std::string::npos;
}

bool Optimizer::isNumericConstant(
    const std::string& value
) const
{
    return isIntegerConstant(value)
        || isFloatConstant(value);
}

std::string Optimizer::getConstantValue(
    const std::string& value
) const
{
    auto it = constants.find(value);

    if (it != constants.end())
        return it->second;

    return value;
}


bool Optimizer::isKnownConstant(
    const std::string& value
) const
{
    return isNumericConstant(value)
        || constants.find(value)
           != constants.end();
}

std::string Optimizer::getConstantValue(
    const std::string& value
) const
{
    auto it = constants.find(value);

    if (it != constants.end())
        return it->second;

    return value;
}


