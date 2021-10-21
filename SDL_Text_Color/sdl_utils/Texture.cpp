/*
 * Texture.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "Texture.hpp"

#include <cassert>

#include <SDL_image.h>
#include <SDL_render.h>

#include "SDLHelper.hpp"
#include "utils/Destroy.hpp"

namespace Texture {

static bool setBlendModeTexture(Texture_t *texture, BlendMode_t blendMode) {
	if(EXIT_SUCCESS != SDL_SetTextureBlendMode(texture->m_Texture.get(), static_cast<SDL_BlendMode>(blendMode))) {
		SDLHelper::print_IMG_Error("SDL_SetTextureBlendMode() fault.");
		return false;
	}
	return true;
}

std::shared_ptr<SDL_Surface> createSurfaceFromFile(const std::string &fname) {
	auto rc = std::shared_ptr<SDL_Surface>(IMG_Load(fname.c_str()), Destroy::free<SDL_Surface, SDL_FreeSurface>);
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ IMG_Load() create SDL_Surface " << rc << std::endl;
#endif
	if(nullptr == rc) {
		SDLHelper::print_IMG_Error("IMG_Load() fault.");
		return std::shared_ptr<SDL_Surface>(nullptr);
	}
	return rc;
}

std::shared_ptr<Texture_t> createTextureFromFile(const std::string &fname, SDL_Renderer * p_renderer, BlendMode_t blend_mode) {
	auto p_surface = createSurfaceFromFile(fname);
	if(nullptr == p_surface) {
		return std::shared_ptr<Texture_t>(nullptr);
	}
	return createTextureFromSurface(p_surface.get(), p_renderer, blend_mode);
}

std::shared_ptr<Texture_t> createTextureFromSurface(SDL_Surface* surface, SDL_Renderer * p_renderer, BlendMode_t blend_mode) {
	auto data = Texture_t {
		.m_Texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(p_renderer, surface)
						, Destroy::free<SDL_Texture, SDL_DestroyTexture>),
		.m_W = surface->w,
		.m_H = surface->h
	};
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ SDL_CreateTextureFromSurface() create SDL_Texture " << data.m_Texture.get() << std::endl;
#endif
	if(nullptr == data.m_Texture) {
		SDLHelper::print_IMG_Error("SDL_CreateTextureFromSurface() fault.");
		return std::shared_ptr<Texture_t>(nullptr);
	}
	if(!setBlendModeTexture(&data, blend_mode)) {
		std::cerr << "setBlendModeTexture() failed." << std::endl;
		return std::shared_ptr<Texture_t>(nullptr);
	}
	return std::make_shared<Texture_t>(data);
}

bool setAlphaTexture(const Texture_t *texture, int32_t alpha) {
	if((ZERO_OPACITY > alpha) || (FULL_OPACITY < alpha)) {
		std::cerr << "setBlendModeTexture() failed, invalid alpha value" << alpha << std::endl;
		return false;
	}
	if(EXIT_SUCCESS != SDL_SetTextureAlphaMod(texture->m_Texture.get(), static_cast<uint8_t>(alpha))) {
		SDLHelper::print_IMG_Error("SDL_SetTextureBlendMode() fault.");
		return false;
	}
	return true;
}

}

