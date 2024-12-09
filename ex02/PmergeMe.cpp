//
// Created by jules on 14/11/2024.
//

#include "PmergeMe.hpp"

std::list<u_int> PmergeMe::mergeInsertSort(const std::list<u_int>& list) {
	const size_t size = list.size();
	if (size < ARBITRARY_VALUE)
		return (insertSort(list));

	auto it = list.begin();
	u_int	splitPoint = getUnderJacobsthalNumber(size);
	std::advance(it, splitPoint);
	std::list<u_int> list1(list.begin(), it);
	std::list<u_int> list2(it, list.end());

	list1 = mergeInsertSort(list1);
	list2 = mergeInsertSort(list2);

	return (mergeSort(list1, list2));
}

std::vector<u_int> PmergeMe::mergeInsertSort(const std::vector<u_int>& vector) {
	const size_t size = vector.size();
	if (size < ARBITRARY_VALUE)
		return (insertSort(vector));

	u_int	splitPoint = getUnderJacobsthalNumber(size);
	std::vector<u_int> vector1(vector.begin(), vector.begin() + splitPoint);
	std::vector<u_int> vector2(vector.begin() + splitPoint, vector.end());
	vector1 = mergeInsertSort(vector1);
	vector2 = mergeInsertSort(vector2);

	return (mergeSort(vector1, vector2));
}

PmergeMe::~PmergeMe() { }


std::list<u_int> PmergeMe::insertSort(const std::list<u_int>& list) {
	std::list<u_int> result;

	for (const u_int& n : list) {
		auto it = std::lower_bound(result.begin(), result.end(), n);
		result.insert(it, n);
	}
	return (result);
}

std::vector<u_int> PmergeMe::insertSort(const std::vector<u_int>& vector) {
	std::vector<u_int> result;
	result.reserve(vector.size());

	for (const u_int& n : vector) {
		auto it = std::lower_bound(result.begin(), result.end(), n);
		result.insert(it, n);
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

u_int PmergeMe::getUnderJacobsthalNumber(u_int number) {
	if (number == 0)
		return (0);

	u_int previousMinus2 = 0;
	u_int previousMinus1 = 1;
	u_int next = 1;
	while (next < number) {
		next = previousMinus1 + (2 * previousMinus2);
		previousMinus2 = previousMinus1;
		previousMinus1 = next;
	}
	return (previousMinus2);
}
