/*
 * DrawParams.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DRAWING_DRAWPARAMS_HPP_
#define UTILS_DRAWING_DRAWPARAMS_HPP_

#include <cstdint>
#include "Rectangle.hpp"

inline constexpr auto INVALID_RESR_ID = -1;

struct DrawingParams_t {
	int32_t m_ResrId = INVALID_RESR_ID;
	Rectangle m_SrcRect = Rectangle::UNDEFINED;
	Rectangle m_DstRect = Rectangle::UNDEFINED;
};

#endif /* UTILS_DRAWING_DRAWPARAMS_HPP_ */
