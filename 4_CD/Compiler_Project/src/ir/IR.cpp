#include "IR.h"

#include <iostream>

TACInstruction::TACInstruction(
    IROp op,
    const std::string& arg1,
    const std::string& arg2,
    const std::string& result
)
    : op(op),
      arg1(arg1),
      arg2(arg2),
      result(result)
{
}

std::string irOpToString(IROp op)
{
    switch (op)
    {
        case IROp::ADD:
            return "+";

        case IROp::SUB:
            return "-";

        case IROp::MUL:
            return "*";

        case IROp::DIV:
            return "/";

        case IROp::MOD:
            return "%";

        case IROp::ASSIGN:
            return "=";

        case IROp::PRINT:
            return "PRINT";
    }

    return "UNKNOWN";
}

void IRProgram::emit(const TACInstruction& instruction)
{
    instructions.push_back(instruction);
}

const std::vector<TACInstruction>& IRProgram::getInstructions() const
{
    return instructions;
}

void IRProgram::print() const
{
    std::cout << "\n===== THREE ADDRESS CODE =====\n";

    for (const auto& instruction : instructions)
    {
        switch (instruction.op)
        {
            case IROp::ADD:
            case IROp::SUB:
            case IROp::MUL:
            case IROp::DIV:
            case IROp::MOD:

                std::cout
                    << instruction.result
                    << " = "
                    << instruction.arg1
                    << " "
                    << irOpToString(instruction.op)
                    << " "
                    << instruction.arg2
                    << '\n';

                break;

            case IROp::ASSIGN:

                std::cout
                    << instruction.result
                    << " = "
                    << instruction.arg1
                    << '\n';

                break;

            case IROp::PRINT:

                std::cout
                    << "PRINT "
                    << instruction.arg1
                    << '\n';

                break;
        }
    }

    std::cout << "==============================\n";
}
