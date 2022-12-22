/*
 * SDLHelper.h
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_SDLHELPER_HPP_
#define SDL_UTILS_SDLHELPER_HPP_

#include <string>

struct Rectangle;
struct SDL_Rect;

namespace SDLHelper {

void print_SDL_Error(const std::string &info);
void print_IMG_Error(const std::string &info);

SDL_Rect toSDL_Rect(const Rectangle& rect);

} /* namespace SDLHelper */

#endif /* SDL_UTILS_SDLHELPER_HPP_ */
