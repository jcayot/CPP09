//
// Created by jules on 05/11/2024.
//

#include "StrictFloatToi.hpp"

#include <stdexcept>

StrictFloatToi::~StrictFloatToi() { }

float StrictFloatToi::strictFloatToi(const std::string& string) {
	try {
		size_t pos;
		const float result = std::stof(string, &pos);

		if (pos == string.size())
			return (result);

		throw std::invalid_argument("Invalid input, string contains non-float characters");
	} catch (const std::exception&) {
		throw std::invalid_argument("Invalid input, unable to convert string to float");
	}
}
