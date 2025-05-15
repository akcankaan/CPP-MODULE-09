#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
    private:
        std::vector<int> _vec;
        std::deque<int> _deq;
    public:
        PmergeMe();
        ~PmergeMe();

        void parseInput(int ac, char** av);
        void sortAndMeasure();

    private:
        bool isNumber(const std::string& str);
        void printContainer(const std::string& label, const std::vector<int>& c);
        void printContainer(const std::string& label, const std::deque<int>& c);

        int binarySearchPosition(const std::vector<int> &vec, int value);
    };

#endif
