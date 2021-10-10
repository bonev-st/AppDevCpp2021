/*
 * Texture.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "Texture.hpp"

#include <SDL_image.h>

#include "SDLHelper.hpp"

namespace Texture {

SDL_Surface * createSurfaceFromFile(const std::string &fname) {
	SDL_Surface * rc = IMG_Load(fname.c_str());
	if(nullptr == rc) {
		SDLHelper::print_IMG_Error("IMG_Load() fault.");
	}
	return rc;
}

void freeSurface(SDL_Surface *& surface) {
	if(nullptr != surface) {
		SDL_FreeSurface(surface);
		surface = nullptr;
	}
}

}
