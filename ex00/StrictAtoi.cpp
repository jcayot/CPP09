//
// Created by jules on 05/11/2024.
//

#include "StrictAtoi.hpp"

StrictAtoi::~StrictAtoi() { }

int StrictAtoi::strictAtoi(const std::string& string) {

	if (string.empty())
		throw std::invalid_argument("Input string is empty");

	for (const char c: string) {
		if (!std::isdigit(c))
			throw std::invalid_argument("Input string contains non-numeric characters");
	}
	return std::atoi(string.c_str());
}
