/*
 * DiplayMode.hpp
 *
 *  Created on: Nov 17, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_INC_SDL_UTILS_DIPLAYMODE_HPP_
#define SDL_UTILS_INC_SDL_UTILS_DIPLAYMODE_HPP_

#include <cstdint>

namespace DiplayMode {

struct Mode_t {
    uint32_t format = 0;            /**< pixel format */
    int w = 0;                      /**< width, in screen coordinates */
    int h = 0;                      /**< height, in screen coordinates */
    int refresh_rate = 0;           /**< refresh rate (or zero for unspecified) */
};
}

#endif /* SDL_UTILS_INC_SDL_UTILS_DIPLAYMODE_HPP_ */
