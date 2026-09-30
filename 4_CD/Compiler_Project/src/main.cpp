#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "semantic/SemanticAnalyzer.h"
#include "evaluator/Evaluator.h"
#include "ir/TACGenerator.h"

int main()
{
    std::string source = R"(
        int a = 10;
        int b = 20;

        float x = 10.5;

        char grade = 'A';

        bool active = true;

        int result = a + b * 2;

        float total = x + 2.5 * 2;

        print(result);
        print(total);
        print(grade);
        print(active);
    )";

    try
    {
        // =========================
        // 1. LEXICAL ANALYSIS
        // =========================

        Lexer lexer(source);

        std::vector<Token> tokens =
            lexer.tokenize();


        // =========================
        // 2. PARSING
        // =========================

        Parser parser(tokens);

        std::unique_ptr<Program> program =
            parser.parse();


        // =========================
        // 3. SEMANTIC ANALYSIS
        // =========================

        SemanticAnalyzer semanticAnalyzer;

        semanticAnalyzer.analyze(
            program.get()
        );


        // =========================
        // 4. EVALUATION
        // =========================

        Evaluator evaluator;

        evaluator.execute(
            program.get()
        );


        // =========================
        // 5. TAC GENERATION
        // =========================

        TACGenerator tacGenerator;

        tacGenerator.generate(
            program.get()
        );

        tacGenerator
            .getIRProgram()
            .print();
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "Compiler Error: "
            << e.what()
            << '\n';

        return 1;
    }

    return 0;
}
