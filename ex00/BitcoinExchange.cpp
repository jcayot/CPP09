//
// Created by jules on 05/11/2024.
//

#include "BitcoinExchange.hpp"

#include "SpacesClean.hpp"

BitcoinExchange::BitcoinExchange(const std::string& pricesFilename) {
	std::ifstream	pricesFile(pricesFilename);

	if (!pricesFile.is_open())
		throw std::runtime_error("Error opening prices file");

	try {
		std::string line;
		std::getline(pricesFile, line);
		while (std::getline(pricesFile, line)) {
			valuesHistory.insert(pairFromLine(line));
		}
	} catch (std::exception& e) {
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
	const std::vector<std::string>	lineContent = CppSplit::cppSplit(line, '|');

	if (lineContent.size() != 2)
		throw std::runtime_error("Error invalid line format in file to evaluate at line : " + line);

	std::tm	date = {};
	float	amount;
	try {
		date = timeFromString(SpacesClean::cleanSpaces(lineContent[0]));
		amount = StrictFloatToi::strictFloatToi(SpacesClean::cleanSpaces(lineContent[1]));
	} catch (std::exception& e) {
		throw std::runtime_error(e.what() + line);
	}

	if (amount < 0.0f || amount > 1000.0f)
		throw std::runtime_error("Error invalid amount in file to evaluate at line : " + line);

	if (date.tm_year < 2009)
		throw std::runtime_error("Error invalid date year in file to evaluate at line : " + line);

	float	valueAtDate = getValueAtDate(date);
	std::cout << lineContent[0] << amount << " = " << (valueAtDate * amount) << "\n";
}

float	BitcoinExchange::getValueAtDate(tm& time) {
	const time_t					time_seconds = std::mktime(&time);
	std::map<long, float>::iterator	it = valuesHistory.lower_bound(time_seconds);

	if (it == valuesHistory.begin())
		throw std::runtime_error("Error invalid date in file to evaluate : " + timeToString(time));
	if (it == valuesHistory.end() || it->first > time_seconds)
		--it;
	return (it->second);
}

std::pair<time_t, float> BitcoinExchange::pairFromLine(const std::string& line) {
	const std::vector<std::string>	lineContent = CppSplit::cppSplit(line, ',');

	if (lineContent.size() != 2)
		throw std::runtime_error("Error invalid content in data file at line : " + line);

	std::tm	date = {};
	float price;
	try {
		date = timeFromString(SpacesClean::cleanSpaces(lineContent[0]));
		price = StrictFloatToi::strictFloatToi(SpacesClean::cleanSpaces(lineContent[1]));
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
	const std::vector<std::string>	dateContent = CppSplit::cppSplit(str, '-');

	const int	year = StrictAtoi::strictAtoi(dateContent[0]);
	const int	month = StrictAtoi::strictAtoi(dateContent[1]);
	const int	day = StrictAtoi::strictAtoi(dateContent[2]);

	if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31)
		throw std::invalid_argument("Invalid date string");

	return (std::tm {0, 0, 0, day, month + 1, year, 0, 0, 0, 0, nullptr});
}

std::string BitcoinExchange::timeToString(const std::tm& time) {
	return (std::to_string(time.tm_year) + "-" + std::to_string(time.tm_mon + 1) + "-" + std::to_string(time.tm_mday));
}
