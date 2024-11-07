//
// Created by jules on 05/11/2024.
//

#include "CppSplit.hpp"

CppSplit::~CppSplit() { }

std::vector<std::string> CppSplit::cppSplit(const std::string& string, const char delim) {
	std::vector<std::string> result;
	std::stringstream stream(string);
	std::string item;

	while (std::getline(stream, item, delim)) {
		if (!item.empty())
			result.push_back(item);
	}
	return (result);
}
