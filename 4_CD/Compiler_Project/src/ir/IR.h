#ifndef IR_H
#define IR_H

#include <string>
#include <vector>

enum class IROp
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    ASSIGN,

    PRINT
};

struct TACInstruction
{
    IROp op;

    std::string arg1;
    std::string arg2;
    std::string result;

    TACInstruction(
        IROp op,
        const std::string& arg1 = "",
        const std::string& arg2 = "",
        const std::string& result = ""
    );
};

std::string irOpToString(IROp op);

class IRProgram
{
private:
    std::vector<TACInstruction> instructions;

public:
    void emit(const TACInstruction& instruction);

    const std::vector<TACInstruction>& getInstructions() const;

    void print() const;
};

#endif
