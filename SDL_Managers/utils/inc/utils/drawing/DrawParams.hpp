/*
 * DrawParams.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DRAWING_DRAWPARAMS_HPP_
#define UTILS_DRAWING_DRAWPARAMS_HPP_

#include <cstdint>
#include "utils/drawing/Rectangle.hpp"

inline constexpr std::size_t INVALID_RESR_ID = -1;

enum class BlendMode_t : uint8_t {
	NONE  = 0, //value for SDL_BLENDMODE_NONE
	BLEND = 1, //value for SDL_BLENDMODE_BLEND
	ADD   = 2, //value for SDL_BLENDMODE_ADD
	MOD   = 4  //value for SDL_BLENDMODE_MODE
};

enum class WidgetType_t : uint8_t {
	IMAGE,
	TEXT,
	UNKNOWN
};

inline constexpr int32_t FULL_OPACITY = 255;
inline constexpr int32_t ZERO_OPACITY = 0;

struct DrawParams_t {
	std::size_t m_ResrId = INVALID_RESR_ID;
	int32_t m_Opacity = FULL_OPACITY;
	BlendMode_t m_BlendMode = BlendMode_t::NONE;
	Rectangle m_SrcRect = Rectangle::UNDEFINED;
	Rectangle m_DstRect = Rectangle::UNDEFINED;
	WidgetType_t m_WidgetType = WidgetType_t::UNKNOWN;
};

#endif /* UTILS_DRAWING_DRAWPARAMS_HPP_ */
