#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int year, month, day;
    std::istringstream y(date.substr(0, 4));
    std::istringstream m(date.substr(5, 2));
    std::istringstream d(date.substr(8, 2));

    if (!(y >> year) || !(m >> month) || !(d >> day))
        return false;

    if (year < 2009 || month < 1 || month > 12)
        return false;

    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;

    return day >= 1 && day <= daysInMonth[month - 1];
}


bool BitcoinExchange::isValidValue(const std::string& value) {
    if (value.empty()) return false;
    if (value == ".") return false;

    std::size_t i = 0;
    if (value[0] == '-') i = 1;

    bool dotSeen = false;
    for (; i < value.length(); ++i) {
        if (value[i] == '.') {
            if (dotSeen)
                return false;
            dotSeen = true;
        } else if (!std::isdigit(value[i]))
            return false;
    }
    return true;
}


std::string BitcoinExchange::trim(const std::string& str) {
    std::size_t first = str.find_first_not_of(" \t");
    std::size_t last = str.find_last_not_of(" \t");
    if (first == std::string::npos || last == std::string::npos)
        return "";
    return str.substr(first, last - first + 1);
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date, value;
        if (!std::getline(iss, date, ',') || !std::getline(iss, value))
            continue;
        _rates[date] = std::atof(value.c_str());
    }

    file.close();
}

float BitcoinExchange::getRateForDate(const std::string& date) {
    std::map<std::string, float>::const_iterator it = _rates.lower_bound(date);

    if (it != _rates.end() && it->first == date)
        return it->second;

    if (it == _rates.begin())
        return -1.0f;

    --it;
    return it->second;
}

void BitcoinExchange::processInput(const std::string& filename) {
    std::ifstream input(filename.c_str());
    if (!input.is_open()) {
        std::cerr << "Error: could not open input file." << std::endl;
        return;
    }

    std::string line;
    bool header_checked = false;

    while (std::getline(input, line)) {
        if (!header_checked) {
            header_checked = true;
            if (trim(line) != "date | value") {
                std::cerr << "The input.txt format is incorrect. The first line should be: \"date | value\"" << std::endl;
                return;
            }
            continue;
        }

        std::istringstream iss(line);
        std::string date, value;

        if (!std::getline(iss, date, '|') || !std::getline(iss, value)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        date = trim(date);
        value = trim(value);

        if (!isValidDate(date)) {
            std::cerr << "Error: invalid date => " << date << std::endl;
            continue;
        }

        if (value == "." || !isValidValue(value)) {
            std::cerr << "Error: invalid value." << std::endl;
            continue;
        }

        float fValue = std::atof(value.c_str());

        if (fValue < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }

        if (fValue > 1000) {
            std::cerr << "Error: too large number." << std::endl;
            continue;
        }

        float rate = getRateForDate(date);
        if (rate < 0) {
            std::cerr << "Error: no rate found for date => " << date << std::endl;
            continue;
        }

        std::cout << date << " => " << fValue << " = " << (fValue * rate) << std::endl;
    }

    input.close();
}
