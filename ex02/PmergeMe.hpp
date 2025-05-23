#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <stdexcept>
#include <ctime>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int> _deq;

public:
    PmergeMe();
    ~PmergeMe();

    void parseInput(int ac, char** av);
    void sortAndMeasure();

    bool isNumber(const std::string& str);

    template <typename Container>
    void printContainer(const std::string& label, const Container &c) {
        std::cout << label;
        for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it) {
            std::cout << *it;
            if (it + 1 != c.end())
                std::cout << " ";
        }
        std::cout << std::endl;
    }
};

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
void insertionSort(T &container) {
    for (std::size_t i = 1; i < container.size(); ++i) {
        int key = container[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && container[j] > key) {
            container[j + 1] = container[j];
            --j;
        }
        container[j + 1] = key;
    }
}

template <typename T>
void genericFordJohnsonSort(T &container) {
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
        pending.push_back(container.back());

    insertionSort(mainChain);

    for (std::size_t i = 0; i < pending.size(); ++i) {
        int pos = binarySearchPosition(mainChain, pending[i]);
        mainChain.insert(mainChain.begin() + pos, pending[i]);
    }

    container = mainChain;
}

#endif
