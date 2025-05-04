#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line))
    {
        std::string date;
        std::string valueStr;

        std::size_t commaPos = line.find(',');
        if (commaPos == std::string::npos)
            continue;

        date = line.substr(0, commaPos);
        valueStr = line.substr(commaPos + 1);

        float value = std::atof(valueStr.c_str());
        _data[date] = value;
    }
}

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr) {
    std::stringstream ss(valueStr);
    float f;
    ss >> f;
    return !ss.fail() && f >= 0.0f && f <= 1000.0f;
}

float BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, float>::const_iterator it = _data.find(date);
    if (it != _data.end())
        return it->second;
    
    it = _data.lower_bound(date);
    if (it == _data.begin())
        return 0.0f;
    --it;
    return it->second;
}

void BitcoinExchange::processInputFile(const std::string &filename)
{
    std::ifstream input(filename.c_str());
    if (!input.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(input, line); // skip header

    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string date, valueStr;
        if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        // Trim spaces
        while (!date.empty() && (date[date.size() - 1] == ' ' || date[date.size() - 1] == '\t'))
            date.erase(date.size() - 1);
        while (!valueStr.empty() && (valueStr[0] == ' ' || valueStr[0] == '\t'))
            valueStr.erase(0, 1);

        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (!isValidValue(valueStr))
        {
            std::cerr << "Error: invalid value." << std::endl;
            continue;
        }

        float value = std::atof(valueStr.c_str());
        float rate = getExchangeRate(date);
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}