#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

bool PmergeMe::isNumber(const std::string &str)
{
    for (std::size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
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

void PmergeMe::printContainer(const std::string &label, const std::vector<int> &c)
{
    std::cout << label;
    for (std::size_t i = 0; i < c.size(); ++i)
    {
        std::cout << c[i];
        if (i != c.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printContainer(const std::string &label, const std::deque<int> &c)
{
    std::cout << label;
    for (std::size_t i = 0; i < c.size(); ++i)
    {
        std::cout << c[i];
        if (i != c.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}

template <typename T>
int binarySearchPosition(const T &container, int value) {
    int left = 0;
    int right = static_cast<int>(container.size());
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (container[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

template <typename T>
void mergeContainer(T &container, int left, int mid, int right)
{
    T leftVec(container.begin() + left, container.begin() + mid + 1);
    T rightVec(container.begin() + mid + 1, container.begin() + right + 1);

    std::size_t i = 0, j = 0;
    int k = left;

    while (i < leftVec.size() && j < rightVec.size())
    {
        if (leftVec[i] <= rightVec[j])
            container[k++] = leftVec[i++];
        else
            container[k++] = rightVec[j++];
    }
    while (i < leftVec.size())
        container[k++] = leftVec[i++];
    while (j < rightVec.size())
        container[k++] = rightVec[j++];
}

template <typename T>
void mergeSort(T &container, int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(container, left, mid);
    mergeSort(container, mid + 1, right);
    mergeContainer(container, left, mid, right);
}

template <typename T>
void    genericFordJohnsonSort(T& container)
{
    if (container.size() <= 1)
        return;
    T mainChain;
    T pending;

    for (std::size_t i = 0; i + 1 < container.size(); i += 2) {
        int a = container[i];
        int b = container[i + 1];
        if (a < b) {
            mainChain.push_back(b);
            pending.push_back(a);
        } else {
            mainChain.push_back(a);
            pending.push_back(b);
        }
    }

    if (container.size() % 2 != 0)
        pending.push_back(container[container.size() - 1]);

    mergeSort(mainChain, 0, mainChain.size() - 1);

    for (std::size_t i = 0; i < pending.size(); ++i) {
        int pos = binarySearchPosition(mainChain, pending[i]);
        mainChain.insert(mainChain.begin() + pos, pending[i]);
    }
    container = mainChain;
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


