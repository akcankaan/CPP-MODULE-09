#include "RPN.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./RPN \"<expression>\"" << std::endl;
        return 1;
    }

    std::string expr;
    for (int i = 1; i < argc; ++i) {
        expr += argv[i];
        if (i != argc - 1)
            expr += " ";
    }

    RPN rpn;
    try {
        int result = rpn.evaluate(expr);
        std::cout << result << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
