#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange {
    private:
        std::map<std::string, float> _data;
    public:
        BitcoinExchange();
        ~BitcoinExchange();

        void loadDatabase(const std::string& filename);
        void processInputFile(const std::string& filename);
        float getExchangeRate(const std::string& date) const;

        static bool isValidDate(const std::string& date);
        static bool isValidValue(const std::string& valueStr);
};

#endif