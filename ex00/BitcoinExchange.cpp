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
		while (std::getline(pricesFile, line)) {
			valuesHistory.insert(pairFromLine(line));
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	pricesFile.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
}

BitcoinExchange::~BitcoinExchange() { }

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		this->valuesHistory = other.valuesHistory;
	}
	return (*this);
}

void BitcoinExchange::evaluateFile(const std::string& filename) {
	std::ifstream	dateFile(filename);

	if (!dateFile.is_open())
		throw std::runtime_error("Error opening dates file");

	try {
		std::string line;
		while (getline(dateFile, line)) {
			std::cout << evaluateLine(line) << std::endl;
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	dateFile.close();
}

std::string BitcoinExchange::evaluateLine(const std::string& line) {
	const std::vector<std::string>	lineContent = CppSplit::cppSplit(line, '|');

	if (lineContent.size() != 2)
		throw std::runtime_error("Error invalid content in file to evaluate : " + line);

	std::tm	date;
	float	amount;
	try {
		date = timeFromString(lineContent[0]);
		amount = StrictFloatToi::strictFloatToi(lineContent[1]);
	} catch (std::exception&) {
		throw std::runtime_error("Error invalid content in file to evaluate : " + line);
	}

	if (amount < 0.0f || amount > 1000.0f)
		throw std::runtime_error("Error invalid number in file to evaluate : " + line);

	if (date.tm_year < 2009)
		throw std::runtime_error("Error invalid date year in file to evaluate : " + line);

	float	valueAtDate = getValueAtDate(date);
	return (std::to_string(date.tm_year) + "-" +
				std::to_string(date.tm_mon + 1) + "-" +
				std::to_string(date.tm_mday)) + " => " +
				std::to_string(amount) + " = " +
				std::to_string(valueAtDate * amount);
}

float BitcoinExchange::getValueAtDate(const tm& tm) {
	if (valuesHistory.empty()) {
		throw std::runtime_error("No historical values available");
	}

	auto it = valuesHistory.lower_bound(tm);
	return (it->second);
}

std::pair<std::tm, float> BitcoinExchange::pairFromLine(const std::string& line) {
	const std::vector<std::string>	lineContent = CppSplit::cppSplit(line, ',');

	if (lineContent.size() != 2)
		throw std::runtime_error("Error invalid content in data file : " + line);

	std::tm	date;
	float	price;
	try {
		date = timeFromString(lineContent[0]);
		price = StrictFloatToi::strictFloatToi(lineContent[1]);
	} catch (std::exception&) {
		throw std::runtime_error("Error invalid content in data file : " + line);
	}

	if (price < 0.f)
		throw std::runtime_error("Error invalid content in data file : " + line);

	if (date.tm_year < 2009)
		throw std::runtime_error("Error invalid content in data file : " + line);

	return std::make_pair(date, price);
}

std::tm BitcoinExchange::timeFromString(const std::string& str) {
	const std::vector<std::string>	dateContent = CppSplit::cppSplit(str, '-');

	if (dateContent.size() != 3)
		throw std::invalid_argument("Not a date string");

	const int	year = StrictAtoi::strictAtoi(dateContent[0]);
	const int	month = StrictAtoi::strictAtoi(dateContent[1]);
	const int	day = StrictAtoi::strictAtoi(dateContent[2]);

	if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31)
		throw std::invalid_argument("Invalid date string");

	return (std::tm {0, 0, 0, day, month + 1, year});
}
