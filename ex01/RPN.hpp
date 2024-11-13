//
// Created by jules on 13/11/2024.
//

#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <string>

class RPN {
	public:
		~RPN();

		static int	evaluate(const std::string& expression);

	private:
		static std::string	getData(const std::string& expression, unsigned int i);
		static bool			isNum(const std::string& data);
		static int			calculate(int n1, int n2, const std::string& data);

		RPN();
		RPN(const RPN&);
		RPN& operator=(const RPN&);
};

#endif
