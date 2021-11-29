/*
 * DisplayMode.hpp
 *
 *  Created on: Nov 17, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_INC_SDL_UTILS_DISPLAYMODE_HPP_
#define SDL_UTILS_INC_SDL_UTILS_DISPLAYMODE_HPP_

#include <cstdint>

namespace DisplayMode {
struct Mode_t {
    int32_t m_W = 0;			/**< width, in screen coordinates */
    int32_t m_H = 0;			/**< height, in screen coordinates */
    int32_t m_DefW = 0;			/**< width, in screen coordinates */
    int32_t m_DefH = 0;			/**< height, in screen coordinates */
};
}

#endif /* SDL_UTILS_INC_SDL_UTILS_DIPLAYMODE_HPP_ */
