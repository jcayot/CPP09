//
// Created by jules on 05/11/2024.
//

#ifndef STRICTATOI_HPP
# define STRICTATOI_HPP

#include <string>
#include <stdexcept>

class StrictAtoi {
	private:
		StrictAtoi();
		StrictAtoi(const StrictAtoi &);

		StrictAtoi &operator=(const StrictAtoi &);

	public:
		~StrictAtoi();

		static int strictAtoi(const std::string& string);
};

#endif //STRICTATOI_HPP
