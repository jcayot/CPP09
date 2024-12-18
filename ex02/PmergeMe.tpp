#ifndef PMERGEME_TPP
# define PMERGEME_TPP

# include "PmergeMe.hpp"

template<typename T>
typename T::iterator PmergeMe::getInsertionPosition(const typename T::iterator& begin, const typename T::iterator& end,
	u_int pairLen, u_int value) {
	if (begin == end)
		return (begin);

	auto searchStart = std::next(begin, pairLen - 1);
	auto searchEnd = std::prev(end);
	if (std::distance(searchStart, searchEnd) % pairLen != 0)
		throw std::runtime_error("Error");

	if (value < *searchStart)
		return (begin);
	if (value > *searchEnd)
		return (end);

	while (std::distance(searchStart, searchEnd) > pairLen)
	{
		int middleDistance = ((std::distance(searchStart, searchEnd) / 2) / pairLen) * pairLen; // NOLINT(*-narrowing-conversions)
		auto middle = std::next(searchStart, middleDistance);

		if (*middle == value)
			return (std::next(middle));
		if (*middle > value)
			searchEnd = middle;
		else
			searchStart = middle;
	}
	return (std::next(searchStart));
}

#endif