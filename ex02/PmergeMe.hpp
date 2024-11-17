//
// Created by jules on 14/11/2024.
//

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <list>
#include <vector>
#include <sys/types.h>

class PmergeMe {
	private:
		static constexpr int ARBITRARY_VALUE = 10;

	public:
		static std::list<u_int>		mergeInsertSort(const std::list<u_int>& list);
		static std::vector<u_int>	mergeInsertSort(const std::vector<u_int>& vector);

		~PmergeMe();

	private:
		static std::list<u_int>		insertSort(const std::list<u_int>& list);
		static std::vector<u_int>	insertSort(const std::vector<u_int>& vector);
		static std::list<u_int>		mergeSort(const std::list<u_int>& v1, const std::list<u_int>& v2);
		static std::vector<u_int>	mergeSort(const std::vector<u_int>& v1, const std::vector<u_int>& v2);

		PmergeMe();
		PmergeMe(const PmergeMe &);

		PmergeMe &operator=(const PmergeMe &);
};

#endif
