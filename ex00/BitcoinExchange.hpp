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

#include "StrictAtoi.hpp"
#include "StrictFloatToi.hpp"

class BitcoinExchange {
	private:
		std::map<time_t, float>	valuesHistory;

	public:
		BitcoinExchange(const std::string& pricesFilename);
		BitcoinExchange(const BitcoinExchange& other);
		~BitcoinExchange();

		BitcoinExchange&	operator=(const BitcoinExchange& other);

		void				evaluateFile(const std::string& filename);

	private:
		BitcoinExchange();

		void								evaluateLine(const std::string& line);
		float								getValueAtDate(std::tm& time);
		static std::pair<time_t, float>		pairFromLine(const std::string& line);
		static std::tm						timeFromString(const std::string& str);
};



#endif
