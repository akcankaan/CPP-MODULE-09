#include "RPN.hpp"
#include <cstdlib> // std::atoi
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>

RPN::RPN() {}

RPN::~RPN() {}

int RPN::isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    else if (c >= '0' && c <= '9')
        return 2;
    return 0;
}

int RPN::applyOperation(int a, int b, char op)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
    {
        if (b == 0)
            throw std::runtime_error("Division by zero");
        return a / b;
    }
    throw std::runtime_error("Invalid operator");
}

int RPN::evaluate(const std::string &expression)
{
    std::stack<int> stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        int tokenType = isOperator(token[0]);

        if (tokenType == 0)
        {
            throw std::runtime_error("Invalid expression");
        }

        if (tokenType == 1)
        {
            if (stack.size() < 2)
            {
                throw std::runtime_error("Invalid expression");
            }
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            int result = applyOperation(a, b, token[0]);
            stack.push(result);
        }
        else if (tokenType == 2)
        {
            int number = std::atoi(token.c_str());
            if (number < 0 || number > 9)
            {
                throw std::runtime_error("Number out of range");
            }
            stack.push(number);
        }
    }

    if (stack.size() != 1)
    {
        throw std::runtime_error("Invalid expression");
    }

    return stack.top();
}
