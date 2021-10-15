/*
 * Kaleidoscope.cpp
 *
 *  Created on: Oct 11, 2021
 *      Author: stanimir
 */

#include "Kaleidoscope.hpp"

#include <iostream>

#include "sdl_utils/Texture.hpp"

#include "utils/drawing/Rectangle.hpp"

Kaleidoscope::Kaleidoscope(SDL_Surface * surface) :
	m_Surface(surface)
,	Offset(0)
{
}

std::int32_t Kaleidoscope::update() {
	std::uint32_t * p_pix_data = reinterpret_cast<uint32_t*>(Texture::getSurfacePixelData(m_Surface));
	if(nullptr == p_pix_data) {
		std::cerr << "Texture::getSurfacePixelData." << std::endl;
		return EXIT_FAILURE;
	}
	Rectangle rect = Texture::getSurfaceRectangle(m_Surface);
	for(std::int32_t i = 0; i < (rect.m_H*rect.m_W); i++) {
		p_pix_data[i] = (i << 8) | 0x00FF0000;
	}
	return EXIT_SUCCESS;
}
