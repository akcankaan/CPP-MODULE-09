#include "PmergeMe.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./PmergeMe <positive integers>" << std::endl;
        return 1;
    }

    try
    {
        PmergeMe sorter;
        sorter.parseInput(argc, argv);
        sorter.sortAndMeasure();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
