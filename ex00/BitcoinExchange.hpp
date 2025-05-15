#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, float> _rates;

public:
    BitcoinExchange();
    ~BitcoinExchange();

    void loadDatabase(const std::string& filename);
    void processInput(const std::string& filename);

private:
    bool isValidDate(const std::string& date);
    bool isValidValue(const std::string& value);
    std::string trim(const std::string& str);
    float getRateForDate(const std::string& date);
};

#endif
