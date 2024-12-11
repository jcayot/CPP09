//
// Created by jules on 17/11/2024.
//

#include <algorithm>
#include <cstring>
#include <iostream>
#include <climits>
#include <ostream>
#include <chrono>

#include "PmergeMe.hpp"

int	main(int argc, char *argv[]) {
	if (argc < 2)
		return (1);
	if (argc > 1000000)
		return (1);
	std::list<u_int>	list;
	std::vector<u_int>	vec;

	for (int i = 1; i < argc; i++) {
		try {
			size_t idx;
			const unsigned long num = std::stoul(argv[i], &idx, 10);
			if (idx != strlen(argv[i]) || num > UINT_MAX || (argv[i][0] < '0' || argv[i][0] > '9'))
				throw std::invalid_argument("Invalid argument");
			list.push_back(static_cast<u_int>(num));
			vec.push_back(static_cast<u_int>(num));
		} catch (...) {
			std::cerr << "Error " << std::endl;
			return (1);
		}
	}

	std::cout << "Before: " << std::endl;
	for (const unsigned int & it : list) {
		std::cout << it << " ";
	}
	std::cout << std::endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;

	start = std::chrono::high_resolution_clock::now();
	list = PmergeMe::mergeInsertSort(list);
	end = std::chrono::high_resolution_clock::now();
	if (std::is_sorted(list.begin(), list.end()) == false)
		throw std::runtime_error("List is not sorted");
	const unsigned long listTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	start = std::chrono::high_resolution_clock::now();
	vec = PmergeMe::mergeInsertSort(vec);
	end = std::chrono::high_resolution_clock::now();
	if (std::is_sorted(vec.begin(), vec.end()) == false)
		throw std::runtime_error("Vector is not sorted");
	const unsigned long vecTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	std::cout << "After: " << std::endl;
	for (const unsigned int& it : list) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << argc - 1 << " elements with list: " << listTime << " microseconds"
		<< std::endl;
	std::cout << "Time to process a range of " << argc - 1 << " elements with vec: " << vecTime << " microseconds"
		<< std::endl;
	return (0);
}