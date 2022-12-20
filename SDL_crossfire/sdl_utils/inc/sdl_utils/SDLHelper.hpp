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
struct Point;
struct SDL_Point;

namespace SDLHelper {

void print_SDL_Error(const std::string &info);
void print_IMG_Error(const std::string &info);

SDL_Rect toRect(const Rectangle& rect);
Rectangle toRect(const SDL_Rect& rect);

SDL_Point toPoint(const Point& point);
Point toPoint(const SDL_Point& point);

} /* namespace SDLHelper */

#endif /* SDL_UTILS_SDLHELPER_HPP_ */
