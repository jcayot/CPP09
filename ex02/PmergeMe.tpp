#ifndef PMERGEME_TPP
# define PMERGEME_TPP

# include "PmergeMe.hpp"

template<typename T>
T PmergeMe::mergeInsertSort(const T& container) {
	const size_t size = container.size();
	if (size < ARBITRARY_VALUE)
		return (insertSort(container));

	auto it = container.begin();
	std::advance(it, size / 2);
	T subContainer1(container.begin(), it);
	T subContainer2(it, container.end());
	subContainer1 = mergeInsertSort(subContainer1);
	subContainer2 = mergeInsertSort(subContainer2);
	return (mergeSort<T>(subContainer1, subContainer2));
}

template<typename T>
T PmergeMe::insertSort(const T& container) {
	T result = container;

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

template<typename T>
T PmergeMe::mergeSort(const T& container1, const T& container2) {
	T result;

	auto	it1 = container1.begin();
	auto	it2 = container2.begin();
	while (it1 != container1.end() && it2 != container2.end()) {
		if (*it1 < *it2)
			result.push_back(*(it1++));
		else
			result.push_back(*(it2++));
	}
	while (it1 != container1.end()) {
		result.push_back(*it1);
		++it1;
	}
	while (it2 != container2.end()) {
		result.push_back(*it2);
		++it2;
	}
	return (result);
}

#endif
