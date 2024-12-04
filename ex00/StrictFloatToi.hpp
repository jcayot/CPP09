//
// Created by jules on 05/11/2024.
//

#ifndef STRICTFLOATTOI_HPP
# define STRICTFLOATTOI_HPP

#include <string>
#include <stdexcept>

class StrictFloatToi {
	private:
		StrictFloatToi();
		StrictFloatToi(const StrictFloatToi&);

		StrictFloatToi& operator=(const StrictFloatToi&);

	public:
		~StrictFloatToi();

		static float strictFloatToi(const std::string& string);
};



#endif //STRICTFLOATTOI_HPP
