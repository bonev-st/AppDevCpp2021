/*
 * BlendMode.hpp
 *
 *  Created on: Nov 3, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_DRAWING_BLENDMODE_HPP_
#define UTILS_INC_UTILS_DRAWING_BLENDMODE_HPP_

#include <cstdint>

enum class BlendMode_t : uint8_t {
	NONE  = 0, //value for SDL_BLENDMODE_NONE
	BLEND = 1, //value for SDL_BLENDMODE_BLEND
	ADD   = 2, //value for SDL_BLENDMODE_ADD
	MOD   = 4  //value for SDL_BLENDMODE_MODE
};

inline constexpr int32_t FULL_OPACITY = 255;
inline constexpr int32_t ZERO_OPACITY = 0;

#endif /* UTILS_INC_UTILS_DRAWING_BLENDMODE_HPP_ */
