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
        bool isOperator(const std::string &token);
        int applyOperation(int a, int b, const std::string &op);
        bool isNumber(const std::string &token);
};

#endif
