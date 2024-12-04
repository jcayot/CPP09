//
// Created by jules on 14/11/2024.
//

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <list>
#include <vector>
#include <sys/types.h>
#include <iostream>

class PmergeMe {
	private:
		static constexpr int ARBITRARY_VALUE = 10;

	public:
		template <typename T>
		static T	mergeInsertSort(const T& container);

	~PmergeMe();

	private:
		template <typename T>
		static T		insertSort(const T& container);

		template <typename T>
		static T		mergeSort(const T& container1, const T& container2);

		PmergeMe();
		PmergeMe(const PmergeMe &);

		PmergeMe &operator=(const PmergeMe &);
};

#include "PmergeMe.tpp"

#endif
