#include "Optimizer.h"

#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <stdexcept>

std::string Optimizer::evaluateConstantExpression(
    IROp op,
    const std::string& left,
    const std::string& right
) const
{
    bool floating =
        isFloatConstant(left)
        || isFloatConstant(right);

    if (floating)
    {
        double a =
            std::stod(left);

        double b =
            std::stod(right);

        double result = 0.0;

        switch (op)
        {
            case IROp::ADD:
                result = a + b;
                break;

            case IROp::SUB:
                result = a - b;
                break;

            case IROp::MUL:
                result = a * b;
                break;

            case IROp::DIV:

                if (b == 0.0)
                    throw std::runtime_error(
                        "Division by zero during optimization."
                    );

                result = a / b;
                break;

            default:
                throw std::runtime_error(
                    "Unsupported floating-point operation."
                );
        }

        std::ostringstream output;

        output << std::setprecision(15)
               << result;

        return output.str();
    }

    long long a =
        std::stoll(left);

    long long b =
        std::stoll(right);

    long long result = 0;

    switch (op)
    {
        case IROp::ADD:
            result = a + b;
            break;

        case IROp::SUB:
            result = a - b;
            break;

        case IROp::MUL:
            result = a * b;
            break;

        case IROp::DIV:

            if (b == 0)
                throw std::runtime_error(
                    "Division by zero during optimization."
                );

            result = a / b;
            break;

        case IROp::MOD:

            if (b == 0)
                throw std::runtime_error(
                    "Modulo by zero during optimization."
                );

            result = a % b;
            break;

        default:
            throw std::runtime_error(
                "Unsupported integer operation."
            );
    }

    return std::to_string(result);
}
