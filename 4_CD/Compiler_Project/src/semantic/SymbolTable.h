#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "Symbol.h"

#include <string>
#include <unordered_map>

class SymbolTable
{
private:
    std::unordered_map<std::string, Symbol> symbols;

public:

    bool declare(
        const std::string& name,
        DataType type
    );

    bool exists(
        const std::string& name
    ) const;

    const Symbol* lookup(
        const std::string& name
    ) const;

    void print() const;
};

#endif
