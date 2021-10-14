/*
 * Texture.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "Texture.hpp"

#include <SDL_image.h>

#include "SDLHelper.hpp"
#include "Destroy.hpp"

namespace Texture {

std::shared_ptr<SDL_Surface> createSurfaceFromFile(const std::string &fname) {
	SDL_Surface * p_surface = IMG_Load(fname.c_str());
	if(nullptr == p_surface) {
		SDLHelper::print_IMG_Error("IMG_Load() fault.");
		return std::shared_ptr<SDL_Surface>(nullptr);
	}
	std::shared_ptr<SDL_Surface> rc(p_surface, Destroy::free<SDL_Surface, SDL_FreeSurface>);
	return rc;
}

}
