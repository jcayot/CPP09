//
// Created by jules on 13/11/2024.
//

#include "RPN.hpp"

#include <stdexcept>

int RPN::evaluate(const std::string& expression) {
	std::stack<int>	evaluationStack;

	unsigned int i = 0;
	while (i < expression.length()) {
		if (!isspace(expression[i])) {
			std::string	data = getData(expression, i);

			if (isNum(data)) {
				evaluationStack.push(stoi(data));
			} else if (evaluationStack.size() > 1) {
				const int n1 = evaluationStack.top();
				evaluationStack.pop();
				const int n2 = evaluationStack.top();
				evaluationStack.pop();
				evaluationStack.push(calculate(n1, n2, data));
			} else
				throw std::invalid_argument("Invalid expression");
			i += data.length();
		}
		else
			i++;
	}

	if (evaluationStack.size() != 1)
		throw std::invalid_argument("Invalid expression");
	return (evaluationStack.top());
}

std::string RPN::getData(const std::string& expression, unsigned int i) {
	unsigned int end = i;

	while (end < expression.length() && !isspace(expression[end]))
		end++;

	return (expression.substr(i, end - i));
}

bool RPN::isNum(const std::string& data) {
	for (unsigned int i = 0; i < data.length(); i++) {
		if (!isdigit(data[i]))
			return (false);
	}
	return (true);
}

int RPN::calculate(const int n1, const int n2, const std::string& data) {
	if (data.length() == 1) {
		switch (data[0]) {
			case '+':
				return (n1 + n2);
			case '-':
				return (n1 - n2);
			case '*':
				return (n1 * n2);
			case '/':
				return (n1 / n2);
		}
	}
	throw std::invalid_argument("Invalid expression");
}
