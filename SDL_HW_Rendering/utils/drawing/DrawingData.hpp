/*
 * DrawingData.hpp
 *
 *  Created on: Oct 15, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DRAWING_DRAWINGDATA_HPP_
#define UTILS_DRAWING_DRAWINGDATA_HPP_

#include "Rectangle.hpp"

struct SDL_Surface;

namespace DrawingData {

typedef struct _Drawing_t {
	SDL_Surface * m_Surface;
	Rectangle m_SrcRect;
	Rectangle m_DstRect;
} Drawing_t;

}

#endif /* UTILS_DRAWING_DRAWINGDATA_HPP_ */
