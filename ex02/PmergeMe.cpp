#include "PmergeMe.hpp"
#include <sstream>
#include <cstdlib>

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

bool PmergeMe::isNumber(const std::string &str)
{
    for (std::size_t i = 0; i < str.length(); ++i)
        if (!std::isdigit(str[i]))
            return false;
    return true;
}

void PmergeMe::parseInput(int ac, char **av)
{
    for (int i = 1; i < ac; ++i)
    {
        std::string s(av[i]);
        if (!isNumber(s))
            throw std::runtime_error("Invalid number: " + s);
        int n = std::atoi(s.c_str());
        if (n < 0)
            throw std::runtime_error("Negative number not allowed.");
        _vec.push_back(n);
        _deq.push_back(n);
    }
}

void PmergeMe::sortAndMeasure()
{
    printContainer("Before: ", _vec);

    std::clock_t startVec = std::clock();
    genericFordJohnsonSort(_vec);
    std::clock_t endVec = std::clock();

    std::clock_t startDeq = std::clock();
    genericFordJohnsonSort(_deq);
    std::clock_t endDeq = std::clock();

    printContainer("After: ", _vec);

    double timeVec = 1000000.0 * (endVec - startVec) / CLOCKS_PER_SEC;
    double timeDeq = 1000000.0 * (endDeq - startDeq) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
