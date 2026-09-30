#ifndef SYMBOL_H
#define SYMBOL_H

#include "Type.h"
#include <string>

struct Symbol
{
    std::string name;
    DataType type;

    Symbol(
        const std::string& name,
        DataType type
    )
        : name(name),
          type(type)
    {
    }
};

#endif
