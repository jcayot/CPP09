//
// Created by jules on 05/11/2024.
//

#include "BitcoinExchange.hpp"

int	main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " [file to evaluate]" << std::endl;
		return (1);
	}
	try {
		BitcoinExchange bitcoinExchange("data.csv");
		bitcoinExchange.evaluateFile(argv[1]);
	} catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
