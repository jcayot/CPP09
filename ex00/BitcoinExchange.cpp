//
// Created by jules on 05/11/2024.
//

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string& pricesFilename) {
	std::ifstream	pricesFile(pricesFilename);

	if (!pricesFile.is_open())
		throw std::runtime_error("Error opening prices file");

	try {
		std::string line;
		std::getline(pricesFile, line);
		if (line != "date,exchange_rate")
			throw std::runtime_error("Invalid prices file");
		while (std::getline(pricesFile, line)) {
			valuesHistory.insert(pairFromLine(line));
		}
	} catch (std::exception&) {
		pricesFile.close();
		throw;
	}
	pricesFile.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
}

BitcoinExchange::~BitcoinExchange() { }

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		this->valuesHistory = other.valuesHistory;
	return (*this);
}

void BitcoinExchange::evaluateFile(const std::string& filename) {
	std::ifstream	dateFile(filename);

	if (!dateFile.is_open())
		throw std::runtime_error("Error opening dates file");

	std::string line;
	getline(dateFile, line);
	if (line != "date | value")
		throw std::runtime_error("Invalid values file");
	while (getline(dateFile, line)) {
		try {
			evaluateLine(line);
		} catch (std::runtime_error& e) {
			std::cout << e.what() << std::endl;
		}
	}
	dateFile.close();
}

void BitcoinExchange::evaluateLine(const std::string& line) {
	const size_t separatorPos = line.find('|');
	if (separatorPos == std::string::npos || separatorPos != line.find_last_of('|')
		|| separatorPos == 0 || separatorPos == line.size() - 1
		|| line[separatorPos - 1] != ' ' || line[separatorPos + 1] != ' ')
		throw std::runtime_error("Error invalid line format in file to evaluate at line : " + line);

	const std::string timeString = line.substr(0, separatorPos - 1);
	const std::string amountString = line.substr(separatorPos + 1);

	std::tm	date = {};
	float	amount;
	try {
		date = timeFromString(timeString);
		amount = StrictFloatToi::strictFloatToi(amountString);
	} catch (std::exception& e) {
		throw std::runtime_error(e.what() + line);
	}

	if (amount < 0.0f || amount > 1000.0f)
		throw std::runtime_error("Error invalid amount in file to evaluate at line : " + line);

	if (date.tm_year < 2009)
		throw std::runtime_error("Error invalid date year in file to evaluate at line : " + line);

	try {
		const float	valueAtDate = getValueAtDate(date);
		std::cout << timeString << " => " << amount << " = " << (valueAtDate * amount) << "\n";
	} catch (std::exception& e) {
		throw std::runtime_error(e.what() + line);
	}
}

float	BitcoinExchange::getValueAtDate(tm& time) {
	const time_t					time_seconds = std::mktime(&time);
	std::map<long, float>::iterator	it = valuesHistory.lower_bound(time_seconds);

	if (it == valuesHistory.begin())
		throw std::runtime_error("Error invalid date in file to evaluate : ");
	if (it == valuesHistory.end() || it->first > time_seconds)
		--it;
	return (it->second);
}

std::pair<time_t, float> BitcoinExchange::pairFromLine(const std::string& line) {
	const size_t separatorPos = line.find(',');
	if (separatorPos == std::string::npos || separatorPos != line.find_last_of(','))
		throw std::runtime_error("Error invalid line format in file to evaluate at line : " + line);

	const std::string timeString = line.substr(0, separatorPos);
	const std::string amountString = line.substr(separatorPos + 1);

	std::tm	date = {};
	float price;
	try {
		date = timeFromString(timeString);
		price = StrictFloatToi::strictFloatToi(amountString);

	} catch (std::exception&) {
		throw std::runtime_error("Error invalid content in data file at line : " + line);
	}

	if (price < 0.f)
		throw std::runtime_error("Error invalid content in data file at line : " + line);

	if (date.tm_year < 2009)
		throw std::runtime_error("Error invalid content in data file at line : " + line);

	return std::make_pair(std::mktime(&date), price);
}

std::tm BitcoinExchange::timeFromString(const std::string& str) {
	const size_t	firstSeparatorPos = str.find('-');
	if (firstSeparatorPos == std::string::npos)
		throw std::runtime_error("Invalid date string");
	const size_t	secondSeparatorPos = str.find('-', firstSeparatorPos + 1);
	if (secondSeparatorPos == std::string::npos || secondSeparatorPos != str.find_last_of('-'))
		throw std::runtime_error("Invalid date string");

	const std::string yearString = str.substr(0, firstSeparatorPos);
	const std::string monthString = str.substr(firstSeparatorPos + 1, secondSeparatorPos - (firstSeparatorPos + 1));
	const std::string dayString = str.substr(secondSeparatorPos + 1);

	if (yearString.length() != 4 || monthString.length() != 2 || dayString.length() != 2)
		throw std::runtime_error("Invalid date string");
	const int	year = StrictAtoi::strictAtoi(yearString);
	const int	month = StrictAtoi::strictAtoi(monthString);
	const int	day = StrictAtoi::strictAtoi(dayString);

	if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31)
		throw std::invalid_argument("Invalid date string");

	return (std::tm {0, 0, 0, day, month + 1, year, 0, 0, 0, 0, nullptr});
}
