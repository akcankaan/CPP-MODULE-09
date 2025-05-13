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

        void mergeSortVector(std::vector<int>& vec, int left, int right);
        void mergeVector(std::vector<int>& vec, int left, int mid, int right);

        void mergeSortDeque(std::deque<int>& deq, int left, int right);
        void mergeDeque(std::deque<int>& deq, int left, int mid, int right);

        void fordJohnsonSortVector(std::vector<int> &vec);
        int binarySearchPosition(const std::vector<int> &vec, int value);
        void fordJohnsonSortDeque(std::deque<int> &deq);
};

#endif