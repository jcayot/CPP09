//
// Created by jules on 14/11/2024.
//

#include "PmergeMe.hpp"

std::list<u_int> PmergeMe::sort(const std::list<u_int>& list)
{
	std::list<u_int> sortedList = list;

	u_int pairLen = doPairSorting(sortedList, 2);
	doInsertionSorting(sortedList, pairLen / 2);

	return (sortedList);
}

std::vector<u_int> PmergeMe::sort(const std::vector<u_int>& vector)
{
	std::vector<u_int> sortedVector = vector;

	u_int pairLen = doPairSorting(sortedVector, 2);
	doInsertionSorting(sortedVector, pairLen / 2);

	return (sortedVector);
}

u_int	PmergeMe::doPairSorting(std::list<unsigned int>& list, const u_int pairLen) // NOLINT(*-no-recursion)
{
	auto firstPairStart = list.begin();

	// ReSharper disable once CppDFALoopConditionNotUpdated
	while (std::distance(firstPairStart, list.end()) >= pairLen)
	{
		auto firstPairEnd = firstPairStart;
		std::advance(firstPairEnd, (pairLen / 2) - 1);
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

u_int PmergeMe::doPairSorting(std::vector<unsigned int>& vector, const u_int pairLen) // NOLINT(*-no-recursion)
{
	u_int pairStart = 0;

	while (vector.size() - pairStart >= pairLen)
	{
		if (vector[pairStart + (pairLen / 2) - 1] > vector[pairStart + pairLen - 1])
		{
			for (size_t i = 0; i < (pairLen / 2); i++)
				std::swap(vector[pairStart + i], vector[pairStart + (pairLen / 2) + i]);
		}
		pairStart += pairLen;
	}
	if (pairLen * 2 <= vector.size())
		return (doPairSorting(vector, pairLen * 2));
	return (pairLen);
}

void PmergeMe::doInsertionSorting(std::list<unsigned int>& main, const u_int pairLen) // NOLINT(*-no-recursion)
{
	std::list<u_int> aux, rem;

	createAuxiliaryRemaining(main, pairLen, aux, rem);
	insertAuxiliary(main, pairLen, aux);
	handleRemaining(main, rem, pairLen);

	if (pairLen > 1)
		doInsertionSorting(main, pairLen / 2);
}

void PmergeMe::doInsertionSorting(std::vector<unsigned int>& main, const u_int pairLen) // NOLINT(*-no-recursion)
{
	std::vector<u_int> aux, rem;

	createAuxiliaryRemaining(main, pairLen, aux, rem);
	// std::cout << main.size() << std::endl;
	// for (u_int n : main)
	// 	std::cout << n << " ";
	// std::cout << std::endl;
	// std::cout << aux.size() << std::endl;
	// for (u_int n : aux)
	// 	std::cout << n << " ";
	// std::cout << std::endl;
	// std::cout << rem.size() << std::endl;
	// for (u_int n : rem)
	// 	std::cout << n << " ";
	// std::cout << std::endl;
	insertAuxiliary(main, pairLen, aux);
	handleRemaining(main, rem, pairLen);

	if (pairLen > 1)
		doInsertionSorting(main, pairLen / 2);
}

void PmergeMe::createAuxiliaryRemaining(std::list<unsigned int>& main, const u_int pairLen, std::list<u_int>& aux,
	std::list<u_int>& rem)
{
	auto firstStart = std::next(main.begin(), pairLen * 2);

	// ReSharper disable once CppDFALoopConditionNotUpdated
	while (std::distance(firstStart, main.end()) >= pairLen * 2)
	{
		auto firstEnd = std::next(firstStart, pairLen);
		aux.splice(aux.end(), main, firstStart, firstEnd);

		firstStart = std::next(firstEnd, pairLen);
	}
	rem.splice(rem.end(), main, firstStart, main.end());
}

void PmergeMe::createAuxiliaryRemaining(std::vector<unsigned int>& main, u_int pairLen, std::vector<u_int>& aux,
	std::vector<u_int>& rem)
{
	u_int start = pairLen * 2;

	while (main.size() - start >= pairLen * 2)
	{
		aux.insert(aux.end(), main.begin() + start, main.begin() + start + pairLen);
		main.erase(main.begin() + start, main.begin() + start + pairLen);
		start += pairLen;
	}
	rem.insert(rem.end(), main.begin() + start, main.end());
	main.erase(main.begin() + start, main.end());
}

void PmergeMe::insertAuxiliary(std::list<unsigned int>& main, const u_int pairLen, std::list<u_int>& aux)
{
	u_int previousJacobsthalNumber = 1;
	u_int jacobsthalNumber = 3;

	while (!aux.empty())
	{
		int auxIndex = jacobsthalNumber - (previousJacobsthalNumber + 1); // NOLINT(*-narrowing-conversions)
		if (static_cast<u_int>(auxIndex) >= aux.size() / pairLen)
			auxIndex = (aux.size() / pairLen) - 1; // NOLINT(*-narrowing-conversions)

		while (auxIndex >= 0)
		{
			auto searchStart = main.begin();
			auto searchEnd = main.end();
			if (((jacobsthalNumber + previousJacobsthalNumber - 1) * pairLen) + pairLen - 1 < main.size())
				searchEnd = std::next(searchStart, ((jacobsthalNumber + previousJacobsthalNumber - 1) * pairLen));

			std::list<u_int>::iterator pairStart;
			if ((auxIndex * pairLen) < aux.size())
				pairStart = std::next(aux.begin(), auxIndex * pairLen);
			else
				pairStart = std::prev(aux.end(), pairLen);
			auto pairEnd = std::next(pairStart, pairLen);

			auto insertionPosition = getInsertionPosition<std::list<u_int>>(searchStart, searchEnd, pairLen,
				*std::prev(pairEnd));

			main.splice(insertionPosition, aux, pairStart, pairEnd);
			auxIndex--;
		}
		u_int previousPreviousJacobsthalNumber = previousJacobsthalNumber;
		previousJacobsthalNumber = jacobsthalNumber;
		jacobsthalNumber = getNextJacobsthalNumber(previousJacobsthalNumber, previousPreviousJacobsthalNumber);
	}

}

void PmergeMe::insertAuxiliary(std::vector<unsigned int>& main, u_int pairLen, std::vector<u_int>& aux)
{
	u_int previousJacobsthalNumber = 1;
	u_int jacobsthalNumber = 3;

	while (!aux.empty())
	{
		int auxIndex = jacobsthalNumber - (previousJacobsthalNumber + 1); // NOLINT(*-narrowing-conversions)
		if (static_cast<u_int>(auxIndex) >= aux.size() / pairLen)
			auxIndex = (aux.size() / pairLen) - 1; // NOLINT(*-narrowing-conversions)

		while (auxIndex >= 0)
		{
			auto searchStart = main.begin();
			auto searchEnd = main.end();
			if (((jacobsthalNumber + previousJacobsthalNumber - 1) * pairLen) + pairLen - 1 < main.size())
				searchEnd = searchStart + ((jacobsthalNumber + previousJacobsthalNumber - 1) * pairLen);

			u_int pairStart;
			if ((auxIndex * pairLen) < aux.size())
				pairStart = auxIndex * pairLen;
			else
				pairStart = aux.size() - pairLen;
			u_int pairEnd = pairStart + pairLen;
			auto insertionPosition = getInsertionPosition<std::vector<u_int>>(searchStart, searchEnd, pairLen,
				aux[pairEnd - 1]);
			main.insert(insertionPosition, aux.begin() + pairStart, aux.begin() + pairEnd);
			aux.erase(aux.begin() + pairStart, aux.begin() + pairEnd);
			auxIndex--;
		}
		u_int previousPreviousJacobsthalNumber = previousJacobsthalNumber;
		previousJacobsthalNumber = jacobsthalNumber;
		jacobsthalNumber = getNextJacobsthalNumber(previousJacobsthalNumber, previousPreviousJacobsthalNumber);
	}
}

void PmergeMe::handleRemaining(std::list<unsigned int>& main, std::list<u_int>& rem, const u_int pairLen)
{
	if (!rem.empty())
	{
		if (rem.size() >= pairLen)
		{
			auto pairStart = rem.begin();
			auto pairEnd = std::next(pairStart, pairLen);

			auto insertionPosition = getInsertionPosition<std::list<u_int>>(main.begin(), main.end(), pairLen,
				*std::prev(pairEnd));
			main.splice(insertionPosition, rem, pairStart, pairEnd);
		}
		if (!rem.empty())
			main.splice(main.end(), rem, rem.begin(), rem.end());
	}
}

void PmergeMe::handleRemaining(std::vector<unsigned int>& main, std::vector<u_int>& rem, u_int pairLen)
{
	if (!rem.empty())
	{
		if (rem.size() >= pairLen)
		{
			u_int pairStart = 0;
			u_int pairEnd = pairLen;
			auto insertionPosition = getInsertionPosition<std::vector<u_int>>(main.begin(), main.end(), pairLen,
				rem[pairEnd - 1]);
			main.insert(insertionPosition, rem.begin() + pairStart, rem.begin() + pairEnd);
			rem.erase(rem.begin() + pairStart, rem.begin() + pairEnd);
		}
		if (!rem.empty())
		{
			main.insert(main.end(), rem.begin(), rem.end());
			rem.clear();
		}
	}
}

u_int PmergeMe::getNextJacobsthalNumber(const u_int previous, const u_int previousPrevious)
{
	return (previous + (2 * previousPrevious));
}
