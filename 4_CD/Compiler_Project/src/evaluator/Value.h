#ifndef VALUE_H
#define VALUE_H

#include <variant>
#include <string>
#include <iostream>

using RuntimeValue = std::variant<
    int,
    double,
    char,
    bool
>;

enum class RuntimeType
{
    INT,
    FLOAT,
    CHAR,
    BOOL
};

inline RuntimeType getRuntimeType(
    const RuntimeValue& value
)
{
    if (std::holds_alternative<int>(value))
        return RuntimeType::INT;

    if (std::holds_alternative<double>(value))
        return RuntimeType::FLOAT;

    if (std::holds_alternative<char>(value))
        return RuntimeType::CHAR;

    return RuntimeType::BOOL;
}

inline std::string runtimeTypeToString(
    RuntimeType type
)
{
    switch (type)
    {
        case RuntimeType::INT:
            return "int";

        case RuntimeType::FLOAT:
            return "float";

        case RuntimeType::CHAR:
            return "char";

        case RuntimeType::BOOL:
            return "bool";
    }

    return "unknown";
}

/*inline void printRuntimeValue(
    const RuntimeValue& value
)
{
    std::visit(
        [](const auto& v)
        {
            std::cout << v;
        },
        value
    );
}*/
inline void printRuntimeValue(
    const RuntimeValue& value
)
{
    if (std::holds_alternative<int>(value))
    {
        std::cout
            << std::get<int>(value);

        return;
    }

    if (std::holds_alternative<double>(value))
    {
        std::cout
            << std::get<double>(value);

        return;
    }

    if (std::holds_alternative<char>(value))
    {
        std::cout
            << std::get<char>(value);

        return;
    }

    if (std::holds_alternative<bool>(value))
    {
        std::cout
            << (
                std::get<bool>(value)
                    ? "true"
                    : "false"
            );

        return;
    }
}

#endif
