//
// Created by jules on 13/11/2024.
//

#include <iostream>
#include "RPN.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error\n";
	} else {
		try {
			const int result = RPN::evaluate(argv[1]);
			std::cout << result << std::endl;
			return (0);
		} catch (std::exception &e) {
			std::cerr << "Error\n";
		}
	}
	return (1);
}