/*
 * Texture.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "Texture.hpp"

#include <SDL_image.h>
#include <SDL_render.h>

#include "SDLHelper.hpp"
#include "utils/Destroy.hpp"

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

std::shared_ptr<Texture_t> createTextureFromFile(const std::string &fname, SDL_Renderer * p_renderer) {
	auto p_surface = createSurfaceFromFile(fname);
	if(nullptr == p_surface) {
		return std::shared_ptr<Texture_t>(nullptr);
	}
	return createTextureFromSurface(p_surface.get(), p_renderer);
}

std::shared_ptr<Texture_t> createTextureFromSurface(SDL_Surface* surface, SDL_Renderer * p_renderer) {
	SDL_Texture * p_texture = SDL_CreateTextureFromSurface(p_renderer, surface);
	if(nullptr == p_texture) {
		SDLHelper::print_IMG_Error("SDL_CreateTextureFromSurface() fault.");
		return std::shared_ptr<Texture_t>(nullptr);
	}
	Texture_t* p_data = new Texture_t {
		.m_Texture = p_texture,
		.m_W = surface->w,
		.m_H = surface->h,
	};
	std::shared_ptr<Texture_t> rc(p_data, [](Texture_t * p){
		if(p) {
			SDL_DestroyTexture(p->m_Texture);
		}
	});
	return rc;
}

}
