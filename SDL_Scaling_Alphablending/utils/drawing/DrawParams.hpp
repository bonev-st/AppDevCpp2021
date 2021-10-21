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

enum class BlendMode_t : uint8_t {
	NONE  = 0, //value for SDL_BLENDMODE_NONE
	BLEND = 1, //value for SDL_BLENDMODE_BLEND
	ADD   = 2, //value for SDL_BLENDMODE_ADD
	MOD   = 4  //value for SDL_BLENDMODE_MODE
};

inline constexpr int32_t FULL_OPACITY = 255;
inline constexpr int32_t ZERO_OPACITY = 0;

struct DrawParams_t {
	int32_t m_ResrId = INVALID_RESR_ID;
	int32_t m_Opacity = FULL_OPACITY;
	Rectangle m_SrcRect = Rectangle::UNDEFINED;
	Rectangle m_DstRect = Rectangle::UNDEFINED;
};

#endif /* UTILS_DRAWING_DRAWPARAMS_HPP_ */
