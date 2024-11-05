//
// Created by jules on 05/11/2024.
//

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

#include "CppSplit.hpp"
#include "StrictAtoi.hpp"
#include "StrictFloatToi.hpp"

class BitcoinExchange {
	private:
		std::map<std::tm, float>	valuesHistory;

	public:
		BitcoinExchange(const std::string& pricesFilename);
		BitcoinExchange(const BitcoinExchange& other);
		~BitcoinExchange();

		BitcoinExchange&	operator=(const BitcoinExchange& other);

		void		evaluateFile(const std::string& filename);
		std::string	evaluateLine(const std::string& line);
		float		getValueAtDate(const tm& tm);

	private:
		BitcoinExchange();

		std::pair<std::tm, float>	pairFromLine(const std::string& line);
		std::tm						timeFromString(const std::string& str);
};



#endif
