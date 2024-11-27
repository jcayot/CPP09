//
// Created by jules on 14/11/2024.
//

#include "PmergeMe.hpp"

#include <iostream>

std::list<u_int> PmergeMe::mergeInsertSort(const std::list<u_int>& list) {
	const size_t size = list.size();
	if (size < ARBITRARY_VALUE)
		return (insertSort(list));

	auto it = list.begin();
	std::advance(it, size / 2);
	std::list<u_int> list1(list.begin(), it);
	std::list<u_int> list2(it, list.end());
	list1 = mergeInsertSort(list1);
	list2 = mergeInsertSort(list2);
	return (mergeSort(list1, list2));
}

std::vector<u_int> PmergeMe::mergeInsertSort(const std::vector<u_int>& vector) {
	const size_t vectorSize = vector.size();
	if (vectorSize < ARBITRARY_VALUE)
		return (insertSort(vector));

	std::vector<u_int> vector1(vector.begin(), vector.begin() + (vectorSize / 2));
	std::vector<u_int> vector2(vector.begin() + (vectorSize / 2), vector.end());
	vector1 = mergeInsertSort(vector1);
	vector2 = mergeInsertSort(vector2);

	return (mergeSort(vector1, vector2));
}

PmergeMe::~PmergeMe() { }


std::list<u_int> PmergeMe::insertSort(const std::list<u_int>& list) {
	std::list<u_int> result = list;

	for (auto it = ++result.begin(); it != result.end(); ++it) {
		u_int temp = *it;
		auto j = it;

		while (j != result.begin()) {
			auto prev = std::prev(j);
			if (*prev > temp) {
				*j = *prev;
				j = prev;
			} else
				break;
		}
		*j = temp;
	}
	return (result);
}

std::vector<u_int> PmergeMe::insertSort(const std::vector<u_int>& vector) {
	std::vector<u_int> result = vector;

	for (int i = 1; i < result.size(); i++) {
		u_int	temp = result[i];
		int j = i - 1;
		while (j >= 0 && result[j] > temp) {
			result[j + 1] = result[j];
			j--;
		}
		result[j + 1] = temp;
	}
	return (result);
}

std::list<u_int> PmergeMe::mergeSort(const std::list<u_int>& v1, const std::list<u_int>& v2) {
	std::list<u_int> result;

	auto	it1 = v1.begin();
	auto	it2 = v2.begin();
	while (it1 != v1.end() && it2 != v2.end()) {
		if (*it1 < *it2)
			result.push_back(*(it1++));
		else
			result.push_back(*(it2++));
	}
	while (it1 != v1.end()) {
		result.push_back(*it1);
		++it1;
	}
	while (it2 != v2.end()) {
		result.push_back(*it2);
		++it2;
	}
	return (result);
}

std::vector<u_int> PmergeMe::mergeSort(const std::vector<u_int>& v1, const std::vector<u_int>& v2) {
	std::vector<u_int> result;

	unsigned int i = 0, j = 0;
	while (i < v1.size() || j < v2.size()) {
		if (i >= v1.size() || (j < v2.size() && v1[i] > v2[j]) )
			result.push_back(v2[j++]);
		else
			result.push_back(v1[i++]);
	}
	return (result);
}
