/*
 * Dimention.hpp
 *
 *  Created on: Oct 23, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_DRAWING_DIMENTION_HPP_
#define UTILS_INC_UTILS_DRAWING_DIMENTION_HPP_

#include <cstdint>
struct Dimention;

struct Dimentions {
	static const Dimention ZERO;
	static const Dimention UNDEFINED;
};

struct Dimention {
	Dimention()  = default;

	Dimention(std::int32_t w, std::int32_t h);

	std::int32_t m_W = 0;
	std::int32_t m_H = 0;
};



#endif /* UTILS_INC_UTILS_DRAWING_DIMENTION_HPP_ */
