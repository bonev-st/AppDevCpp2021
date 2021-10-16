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
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ createSurfaceFromFile() create SDL_Surface " << p_surface << std::endl;
#endif
	std::shared_ptr<SDL_Surface> rc(p_surface, Destroy::free<SDL_Surface, SDL_FreeSurface>);
	return rc;
}

std::shared_ptr<Texture_t> createTextureFromFile(const std::string &fname, SDL_Renderer * p_renderer) {
	auto p_surface = createSurfaceFromFile(fname);
	if(nullptr == p_surface.get()) {
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
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ createTextureFromSurface() create SDL_Texture " << p_texture << std::endl;
#endif
	auto data = new Texture_t {
		.m_Texture = p_texture,
		.m_W = surface->w,
		.m_H = surface->h,
		};
	if(nullptr == data) {
		SDL_DestroyTexture(p_texture);
		std::cerr << "Create Texture_t failed." << std::endl;
		return std::shared_ptr<Texture_t>(nullptr);
	}
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ createTextureFromSurface() create Texture_t " << data << std::endl;
#endif
	return std::shared_ptr<Texture_t> (data,
		[](Texture_t * p) {
			if(p) {
#ifdef SHOW_MEM_ALLOC_INFO
				std::cout << "- Destroy with SDL_DestroyTexture(" << p->m_Texture <<")" << std::endl;
				std::cout << "- Destroy with delete " << p << std::endl;
#endif
				SDL_DestroyTexture(p->m_Texture);
				delete p;
			}
#ifdef SHOW_MEM_ALLOC_INFO
			else {
				std::cout << "- Try to destroy with SDL_DestroyTexture(nullptr)" << std::endl;
			}
#endif
		}
	);
}
}
