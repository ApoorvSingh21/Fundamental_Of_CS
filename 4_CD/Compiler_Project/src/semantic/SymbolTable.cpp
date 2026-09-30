#include "SymbolTable.h"

#include <iostream>

bool SymbolTable::declare(
    const std::string& name,
    DataType type
)
{
    if (exists(name))
    {
        return false;
    }

    symbols.emplace(
        name,
        Symbol(name, type)
    );

    return true;
}


bool SymbolTable::exists(
    const std::string& name
) const
{
    return symbols.find(name)
        != symbols.end();
}


const Symbol* SymbolTable::lookup(
    const std::string& name
) const
{
    auto it = symbols.find(name);

    if (it == symbols.end())
    {
        return nullptr;
    }

    return &it->second;
}


void SymbolTable::print() const
{
    std::cout << "\n=== Symbol Table ===\n";

    for (const auto& pair : symbols)
    {
        std::cout
            << pair.second.name
            << " : "
            << dataTypeToString(pair.second.type)
            << '\n';
    }
}
