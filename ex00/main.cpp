#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./btc <input_file>" << std::endl;
        return 1;
    }

    BitcoinExchange exchange;

    exchange.loadDatabase("data.csv");

    exchange.processInput(argv[1]);

    return 0;
}
