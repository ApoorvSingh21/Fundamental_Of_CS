#ifndef TYPE_H
#define TYPE_H

#include <string>

enum class DataType
{
    INT,
    FLOAT,
    CHAR,
    BOOL,
    UNKNOWN
};

inline std::string dataTypeToString(DataType type)
{
    switch (type)
    {
        case DataType::INT:
            return "int";

        case DataType::FLOAT:
            return "float";

        case DataType::CHAR:
            return "char";

        case DataType::BOOL:
            return "bool";

        default:
            return "unknown";
    }
}

#endif
