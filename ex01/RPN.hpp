#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN
{
public:
    RPN();
    ~RPN();

    int evaluate(const std::string &expression);

private:
    int isOperator(char c);
    int applyOperation(int a, int b, char op);
};

#endif
