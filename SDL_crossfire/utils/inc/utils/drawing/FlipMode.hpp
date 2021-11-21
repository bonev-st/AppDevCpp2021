/*
 * FlipMode.hpp
 *
 *  Created on: Nov 3, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_DRAWING_FLIPMODE_HPP_
#define UTILS_INC_UTILS_DRAWING_FLIPMODE_HPP_

#include <cstdint>

enum class FlipMode_t : uint8_t {
    NONE,
    HORIZONTAL,
    VERTICAL,
    HORIZONTAL_AND_VERTICAL
};

#endif /* UTILS_INC_UTILS_DRAWING_FLIPMODE_HPP_ */
