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
	public:
		static std::list<u_int>		sort(const std::list<u_int>& list);
		static std::vector<u_int>	sort(const std::vector<u_int>& vector);

		~PmergeMe();

	private:
		static u_int	doPairSorting(std::list<unsigned int>& list, u_int pairLen);
		static u_int	doPairSorting(std::vector<unsigned int>& vector, u_int pairLen);
		static void		doInsertionSorting(std::list<unsigned int>& main, u_int pairLen);
		static void		doInsertionSorting(std::vector<unsigned int>& main, u_int pairLen);
		static void		createAuxiliaryRemaining(std::list<unsigned int>& main, u_int pairLen, std::list<u_int>& aux,
			std::list<u_int>& rem);
		static void		createAuxiliaryRemaining(std::vector<unsigned int>& main, u_int pairLen,
			std::vector<u_int>& aux, std::vector<u_int>& rem);
		static void		insertAuxiliary(std::list<unsigned int>& main, u_int pairLen, std::list<u_int>& aux);
		static void		insertAuxiliary(std::vector<unsigned int>& main, u_int pairLen, std::vector<u_int>& aux);
		static void		handleRemaining(std::list<unsigned int>& main, std::list<u_int>& rem, u_int pairLen);
		static void		handleRemaining(std::vector<unsigned int>& main, std::vector<u_int>& rem, u_int pairLen);

		template<typename T>
		static typename T::iterator	getInsertionPosition(const typename T::iterator& begin, const typename
			T::iterator& end, u_int pairLen,u_int value);
		static u_int				getNextJacobsthalNumber(u_int previous, u_int previousPrevious);

		PmergeMe();
		PmergeMe(const PmergeMe &);

		PmergeMe &operator=(const PmergeMe &);
};

#include "PmergeMe.tpp"

#endif
