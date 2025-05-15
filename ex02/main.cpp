#include "PmergeMe.hpp"
#include <iostream>

int main(int ac, char** av) {
    if (ac < 2) {
        std::cerr << "Usage: ./PmergeMe <positive integers>" << std::endl;
        return 1;
    }

    try {
        PmergeMe sorter;
        sorter.parseInput(ac, av);
        sorter.sortAndMeasure();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
