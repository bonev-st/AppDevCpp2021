/*
 * DisplayMode.hpp
 *
 *  Created on: Nov 17, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_INC_SDL_UTILS_DIPLAYMODE_HPP_
#define SDL_UTILS_INC_SDL_UTILS_DIPLAYMODE_HPP_

#include <cstdint>

namespace DisplayMode {
struct Mode_t {
    uint32_t m_Format = 0;		/**< pixel format */
    int32_t m_W = 0;			/**< width, in screen coordinates */
    int32_t m_H = 0;			/**< height, in screen coordinates */
    int32_t m_RefreshRate = 0;	/**< refresh rate (or zero for unspecified) */
};
}

#endif /* SDL_UTILS_INC_SDL_UTILS_DIPLAYMODE_HPP_ */
