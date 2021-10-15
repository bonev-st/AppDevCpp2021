/*
 * Texture.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "Texture.hpp"

#include <cassert>

#include <SDL_image.h>
#include <SDL_surface.h>

#include "utils/drawing/Rectangle.hpp"
#include "SDLHelper.hpp"

namespace Texture {

SDL_Surface * createSurfaceFromFile(const std::string &fname) {
	SDL_Surface * rc = IMG_Load(fname.c_str());
	if(nullptr == rc) {
		SDLHelper::print_IMG_Error("IMG_Load() fault.");
	}
	return rc;
}

SDL_Surface * createRGB_Surface(const RGB_SurfaceCfg_t & cfg) {
	SDL_Surface* rc = SDL_CreateRGBSurface(SDL_PIXELFORMAT_RGBA32
			, cfg.W, cfg.H, cfg.D
			, cfg.R_Mask, cfg.G_Mask, cfg.B_Mask, cfg.A_Mask);
	if(nullptr == rc) {
		SDLHelper::print_IMG_Error("SDL_CreateRGBSurface() fault.");
	}
	return rc;
}

void* getSurfacePixelData(SDL_Surface * surface) {
	return surface->pixels;
}

Rectangle getSurfaceRectangle(SDL_Surface * surface) {
	assert(surface);
	return SDLHelper::toRectangle(surface->clip_rect);
}

void freeSurface(SDL_Surface *& surface) {
	if(nullptr != surface) {
		SDL_FreeSurface(surface);
		surface = nullptr;
	}
}

}
