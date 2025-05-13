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

void PmergeMe::sortAndMeasure()
{
    printContainer("Before: ", _vec);

    std::clock_t startVec = std::clock();
    fordJohnsonSortVector(_vec);
    std::clock_t endVec = std::clock();

    std::clock_t startDeq = std::clock();
    fordJohnsonSortDeque(_deq);
    std::clock_t endDeq = std::clock();

    printContainer("After: ", _vec);

    double timeVec = 1000000.0 * (endVec - startVec) / CLOCKS_PER_SEC;
    double timeDeq = 1000000.0 * (endDeq - startDeq) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}

void PmergeMe::mergeVector(std::vector<int> &vec, int left, int mid, int right)
{
    std::vector<int> leftVec(vec.begin() + left, vec.begin() + mid + 1);
    std::vector<int> rightVec(vec.begin() + mid + 1, vec.begin() + right + 1);

    std::size_t i = 0, j = 0;
    int k = left;

    while (i < leftVec.size() && j < rightVec.size())
    {
        if (leftVec[i] <= rightVec[j])
            vec[k++] = leftVec[i++];
        else
            vec[k++] = rightVec[j++];
    }
    while (i < leftVec.size())
        vec[k++] = leftVec[i++];
    while (j < rightVec.size())
        vec[k++] = rightVec[j++];
}

void PmergeMe::mergeSortVector(std::vector<int> &vec, int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSortVector(vec, left, mid);
    mergeSortVector(vec, mid + 1, right);
    mergeVector(vec, left, mid, right);
}

void PmergeMe::mergeDeque(std::deque<int> &deq, int left, int mid, int right)
{
    std::deque<int> leftDeq, rightDeq;

    for (int i = left; i <= mid; ++i)
        leftDeq.push_back(deq[i]);
    for (int i = mid + 1; i <= right; ++i)
        rightDeq.push_back(deq[i]);

    unsigned int i = 0;
    unsigned int j = 0;
    int k = left;

    while (i < leftDeq.size() && j < rightDeq.size())
    {
        if (leftDeq[i] <= rightDeq[j])
            deq[k++] = leftDeq[i++];
        else
            deq[k++] = rightDeq[j++];
    }

    while (i < leftDeq.size())
        deq[k++] = leftDeq[i++];
    while (j < rightDeq.size())
        deq[k++] = rightDeq[j++];
}

void PmergeMe::mergeSortDeque(std::deque<int> &deq, int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSortDeque(deq, left, mid);
    mergeSortDeque(deq, mid + 1, right);
    mergeDeque(deq, left, mid, right);
}

int PmergeMe::binarySearchPosition(const std::vector<int>& vec, int value) {
    int left = 0;
    int right = vec.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (vec[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void PmergeMe::fordJohnsonSortVector(std::vector<int>& input) {
    if (input.size() <= 1)
        return;
    std::vector<int> mainChain;
    std::vector<int> pending;

    for (std::size_t i = 0; i + 1 < input.size(); i += 2) {
        int a = input[i];
        int b = input[i + 1];
        if (a < b) {
            mainChain.push_back(b);
            pending.push_back(a);
        } else {
            mainChain.push_back(a);
            pending.push_back(b);
        }
    }

    if (input.size() % 2 != 0)
        pending.push_back(input[input.size() - 1]);
    
    mergeSortVector(mainChain, 0, mainChain.size() - 1);

    for (std::size_t i = 0; i < pending.size(); ++i) {
        int pos = binarySearchPosition(mainChain, pending[i]);
        mainChain.insert(mainChain.begin() + pos, pending[i]);
    }
    input = mainChain;
}

void PmergeMe::fordJohnsonSortDeque(std::deque<int> &input)
{
    if (input.size() <= 1)
        return;

    std::deque<int> mainChain;
    std::deque<int> pending;

    for (std::size_t i = 0; i + 1 < input.size(); i += 2)
    {
        int a = input[i];
        int b = input[i + 1];
        if (a < b)
        {
            mainChain.push_back(b);
            pending.push_back(a);
        }
        else
        {
            mainChain.push_back(a);
            pending.push_back(b);
        }
    }

    if (input.size() % 2 != 0)
        pending.push_back(input[input.size() - 1]);

    // normal merge sort
    mergeSortDeque(mainChain, 0, mainChain.size() - 1);

    for (std::size_t i = 0; i < pending.size(); ++i)
    {
        int value = pending[i];
        std::size_t pos = 0;
        while (pos < mainChain.size() && mainChain[pos] < value)
            ++pos;
        mainChain.insert(mainChain.begin() + pos, value);
    }

    input = mainChain;
}
