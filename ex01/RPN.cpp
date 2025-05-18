#include "RPN.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cctype>

RPN::RPN() {}

RPN::~RPN() {}

bool RPN::isOperator(const std::string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool RPN::isNumber(const std::string &token)
{
    if (token.empty())
        return false;

    if (token == "-")
        return false;

    std::size_t i = 0;
    if (token[0] == '-')
        i = 1;

    for (; i < token.length(); ++i)
    {
        if (!std::isdigit(token[i]))
            return false;
    }

    return true;
}

int RPN::applyOperation(int a, int b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0)
            throw std::runtime_error("Error: division by zero");
        return a / b;
    }
    throw std::runtime_error("Error: invalid operator");
}

int RPN::evaluate(const std::string &expression) {
    std::stack<int> stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isNumber(token)) {
            int number = std::atoi(token.c_str());
            stack.push(number);
        }
        else if (isOperator(token)) {
            if (stack.size() < 2)
                throw std::runtime_error("Error: insufficient operands");
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            int result = applyOperation(a, b, token);
            stack.push(result);
        }
        else {
            throw std::runtime_error("Error: invalid token '" + token + "'");
        }
    }

    if (stack.size() != 1)
        throw std::runtime_error("Error: invalid expression");

    return stack.top();
}