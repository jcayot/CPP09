//
// Created by jules on 14/11/2024.
//

#include "PmergeMe.hpp"

std::list<u_int> PmergeMe::sort(const std::list<u_int>& list)
{
	std::list<u_int> sortedList = list;

	u_int pairLen = doPairSorting(sortedList, 2);

	std::cout << "\n" << "List : ";
	for (u_int n : sortedList)
		std::cout << n << " ";
	std::cout << std::endl;

	doInsertionSorting(sortedList, pairLen / 2);

	return (sortedList);
}

std::vector<u_int> PmergeMe::sort(const std::vector<u_int>& vector)
{
	(void)vector;
	return (std::vector<u_int>());
}

u_int	PmergeMe::doPairSorting(std::list<unsigned int>& list, u_int pairLen)
{
	auto firstPairStart = list.begin();

	while (std::distance(firstPairStart, list.end()) >= pairLen)
	{
		auto firstPairEnd = firstPairStart;
		std::advance(firstPairEnd, (pairLen - 1) / 2);
		auto secondPairEnd = firstPairEnd;
		std::advance(secondPairEnd, pairLen / 2);

		if (*firstPairEnd > *secondPairEnd)
			std::swap_ranges(firstPairStart, std::next(firstPairEnd), std::next(firstPairEnd));

		firstPairStart = std::next(secondPairEnd);
	}

	if (pairLen * 2 <= list.size())
		return (doPairSorting(list, pairLen * 2));

	return (pairLen);
}

void PmergeMe::doInsertionSorting(std::list<unsigned int>& main, u_int pairLen)
{
	std::list<u_int> aux, rem;

	createAuxiliaryRemaining(main, pairLen, aux, rem);

	{
		std::cout << "Start" << std::endl;
		std::cout << "Pair length: " << pairLen << std::endl;
		std::cout << "Main : ";
		for (u_int n : main)
			std::cout << n << " ";
		std::cout << std::endl;
		std::cout << "Aux : ";
		for (u_int n : aux)
			std::cout << n << " ";
		std::cout << std::endl;
	}
	insertAuxiliary(main, pairLen, aux);
	handleRemaining(main, rem, pairLen);

	std::cout << "END " << std::endl;
	for (u_int n : main)
		std::cout << n << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	if (pairLen > 1)
		doInsertionSorting(main, pairLen / 2);
}

void PmergeMe::createAuxiliaryRemaining(std::list<unsigned int>& main, u_int pairLen, std::list<u_int>& aux, std::list<u_int>& rem)
{
	auto firstStart = std::next(main.begin(), pairLen * 2);
	while (std::distance(firstStart, main.end()) >= pairLen * 2)
	{
		auto firstEnd = std::next(firstStart, pairLen);
		aux.splice(aux.end(), main, firstStart, firstEnd);

		firstStart = std::next(firstEnd, pairLen);
	}
	rem.splice(rem.end(), main, firstStart, main.end());
}

void PmergeMe::insertAuxiliary(std::list<unsigned int>& main, u_int pairLen, std::list<u_int>& aux)
{
	u_int previousJacobsthalNumber = 1;
	u_int jacobsthalNumber = 3;

	while (aux.size() > 0)
	{
		int auxIndex = jacobsthalNumber - (previousJacobsthalNumber + 1);
		if (static_cast<u_int>(auxIndex) >= aux.size() / pairLen)
			auxIndex = (aux.size() / pairLen) - 1;

		while (auxIndex >= 0)
		{
			auto searchStart = std::next(main.begin(), pairLen - 1);
			std::list<u_int>::iterator searchEnd = main.end();

			// {
			// 	std::cout << "auxIndex: " << auxIndex << std::endl;
			// 	std::cout << "cond : " <<((jacobsthalNumber + previousJacobsthalNumber - 1) * pairLen + pairLen - 1) << std::endl;
			// 	std::cout << "main size : " << main.size() << std::endl;
			// }

			if (((jacobsthalNumber + previousJacobsthalNumber - 1) * pairLen) + pairLen - 1 < main.size())
				searchEnd = std::next(searchStart, (jacobsthalNumber + previousJacobsthalNumber - 1) * pairLen);

			// {
			// 	std::cout << "Jacobsthal number: " << jacobsthalNumber << std::endl;
			// 	if (searchEnd != main.end())
			// 		std::cout << "Search until : " << *searchEnd << std::endl;
			// 	else
			// 		std::cout << "Search until end " << std::endl;
			// }

			std::list<u_int>::iterator pairStart;
			if ((auxIndex * pairLen) < aux.size())
				pairStart = std::next(aux.begin(), auxIndex * pairLen);
			else
				pairStart = std::prev(aux.end(), pairLen);
			auto pairEnd = std::next(pairStart, pairLen);

			auto insertionPosition = getInsertionPosition(searchStart, searchEnd, pairLen, *std::prev(pairEnd));
			if (insertionPosition == searchStart)
				insertionPosition = main.begin();

			// {
			// 	std::cout << "Insertion position: " << *insertionPosition << std::endl;
			// 	std::cout << "Insertion range: ";
			// 	for (auto it = pairStart; it != pairEnd; ++it)
			// 		std::cout << *it << " ";
			// 	std::cout << std::endl;
			// }

			main.splice(insertionPosition, aux, pairStart, pairEnd);
			auxIndex--;
			std::cout << std::endl;
		}
		u_int previousPreviousJacobsthalNumber = previousJacobsthalNumber;
		previousJacobsthalNumber = jacobsthalNumber;
		jacobsthalNumber = getNextJacobsthalNumber(previousJacobsthalNumber, previousPreviousJacobsthalNumber);
	}

}

void PmergeMe::handleRemaining(std::list<unsigned int>& main, std::list<u_int>& rem, u_int pairLen)
{
	if (!rem.empty())
	{
		if (rem.size() >= pairLen)
		{
			auto pairStart = rem.begin();
			auto pairEnd = std::next(pairStart, pairLen);

			auto insertionPosition = getInsertionPosition(std::next(main.begin(), pairLen - 1), main.end(), pairLen, *std::prev(pairEnd));
			main.splice(insertionPosition, rem, pairStart, pairEnd);
		}
		if (!rem.empty())
			main.splice(main.end(), rem, rem.begin(), rem.end());
	}
}

//TODO NOT INCLUDE THE END ???
std::list<u_int>::iterator PmergeMe::getInsertionPosition(const std::list<u_int>::iterator& begin,
	const std::list<u_int>::iterator& end, u_int pairLen, u_int value)
{
	if (begin == end)
		return (begin);
	if (pairLen > std::distance(begin, end))
		throw std::invalid_argument("Invalid pair length");

	auto searchStart = begin;
	auto searchEnd = end;

	while (std::distance(searchStart, searchEnd) > pairLen) {
		int middleDistance = ((std::distance(searchStart, searchEnd) / 2) / pairLen) * pairLen;
		if (middleDistance == 0)
			break ;
		auto middle = std::next(searchStart, middleDistance);
		if (*middle == value)
			return (std::next(middle));
		else if (*middle > value)
			searchEnd = middle;
		else
			searchStart = middle;
	}
	if (searchStart == begin && value < *begin)
		return (begin);
	return (std::next(searchStart));
}

u_int PmergeMe::getNextJacobsthalNumber(u_int previous, u_int previousPrevious)
{
	return (previous + (2 * previousPrevious));
}
