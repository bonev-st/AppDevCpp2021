/*
 * SDLHelper.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "SDLHelper.hpp"

#include <iostream>

#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_rect.h>

#include "utils/drawing/Rectangle.hpp"

namespace SDLHelper {

void print_SDL_Error(const std::string &info) {
    std::cerr << info << " Reason: " << SDL_GetError() << std::endl;
}

void print_IMG_Error(const std::string &info) {
    std::cerr << info << " Reason: " << IMG_GetError() << std::endl;
}

SDL_Rect toSDL_Rect(const Rectangle& rect) {
	SDL_Rect rc = {};
	rc.x = rect.m_Pos.m_X;
	rc.y = rect.m_Pos.m_Y;
	rc.w = rect.m_W;
	rc.h = rect.m_H;
	return rc;
}

Rectangle toRectangle(const SDL_Rect& rect) {
	return Rectangle(rect.x, rect.y, rect.w, rect.h);
}

} /* namespace SDLHelper */
