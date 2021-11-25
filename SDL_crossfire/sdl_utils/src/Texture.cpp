/*
 * Texture.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "sdl_utils/Texture.hpp"

#include <cassert>

#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "utils/Destroy.hpp"
#include "utils/drawing/Color.hpp"
#include "utils/drawing/Dimention.hpp"
#include "utils/drawing/BlendMode.hpp"
#include "utils/drawing/Rectangle.hpp"

#include "sdl_utils/SDLHelper.hpp"

namespace Texture {

std::shared_ptr<SDL_Surface> createRGB_Surface(const Dimention dim) {
	auto rc = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurface(SDL_PIXELFORMAT_RGBA32
			, dim.m_W, dim.m_H, 32
			, 0, 0, 0, 0), Destroy::free<SDL_Surface, SDL_FreeSurface>);
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ SDL_CreateRGBSurface() create SDL_Surface " << rc << std::endl;
#endif
	if(nullptr == rc) {
		SDLHelper::print_SDL_Error("Texture::createRGB_Surface::SDL_CreateRGBSurface() failed.");
		return std::shared_ptr<SDL_Surface>(nullptr);
	}
	return rc;
}

std::shared_ptr<SDL_Surface> createSurfaceFromFile(const std::string &fname) {
	auto rc = std::shared_ptr<SDL_Surface>(IMG_Load(fname.c_str()), Destroy::free<SDL_Surface, SDL_FreeSurface>);
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ IMG_Load() create SDL_Surface " << rc << std::endl;
#endif
	if(nullptr == rc) {
		SDLHelper::print_IMG_Error("Texture::createSurfaceFromFile::IMG_Load() failed.");
		return std::shared_ptr<SDL_Surface>(nullptr);
	}
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
		SDLHelper::print_SDL_Error("Texture::createTextureFromSurface::SDL_CreateTextureFromSurface() failed.");
		return std::shared_ptr<Texture_t>(nullptr);
	}
	return std::make_shared<Texture_t>(data);
}

std::shared_ptr<SDL_Surface> createSurfaceFromText(const std::string &text, const Color &color, const TTF_Font* font) {
	const SDL_Color * sdl_color =  reinterpret_cast<const SDL_Color *>(&color.m_RGBA);
	auto rc = std::shared_ptr<SDL_Surface>(TTF_RenderText_Blended(const_cast<TTF_Font*>(font), text.c_str(), *sdl_color), Destroy::free<SDL_Surface, SDL_FreeSurface>);
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ TTF_RenderText_Blended() create SDL_Surface " << rc << std::endl;
#endif
	if(nullptr == rc) {
		SDLHelper::print_SDL_Error("Texture::createSurfaceFromText::TTF_RenderText_Blended() failed.");
		return std::shared_ptr<SDL_Surface>(nullptr);
	}
	return rc;
}

std::shared_ptr<Texture_t> createTextureFromFont(const std::string &text, const Color &color, const TTF_Font* font, SDL_Renderer * p_renderer) {
	auto p_surface = createSurfaceFromText(text, color, font);
	if(nullptr == p_surface) {
		return std::shared_ptr<Texture_t>(nullptr);
	}
	return createTextureFromSurface(p_surface.get(), p_renderer);
}

bool setBlendModeTexture(const Texture_t *texture, BlendMode_t blendMode) {
	if(EXIT_SUCCESS != SDL_SetTextureBlendMode(texture->m_Texture.get(), static_cast<SDL_BlendMode>(blendMode))) {
		SDLHelper::print_SDL_Error("Texture::setBlendModeTexture::SDL_SetTextureBlendMode() failed.");
		return false;
	}
	return true;
}

bool setAlphaTexture(const Texture_t *texture, int32_t alpha) {
	if((ZERO_OPACITY > alpha) || (FULL_OPACITY < alpha)) {
		std::cerr << "Texture::setAlphaTexture::setBlendModeTexture() failed, invalid alpha value" << alpha << std::endl;
		return false;
	}
	if(EXIT_SUCCESS != SDL_SetTextureAlphaMod(texture->m_Texture.get(), static_cast<uint8_t>(alpha))) {
		SDLHelper::print_SDL_Error("Texture::setAlphaTexture::SDL_SetTextureBlendMode() failed.");
		return false;
	}
	return true;
}

bool fillTexture(Texture_t *texture,  const Color &color, SDL_Renderer * p_renderer) {
	if(!setBlendModeTexture(texture, (FULL_OPACITY == color.m_RGBA.a)?BlendMode_t::NONE:BlendMode_t::BLEND)) {
		std::cerr << "Texture::fillTexture::setBlendModeTexture() failed" << std::endl;
		return false;
	}
	Color tmp_color;
	if(!SDL_GetRenderDrawColor(p_renderer, &tmp_color.m_RGBA.r, &tmp_color.m_RGBA.g
			, &tmp_color.m_RGBA.b, &tmp_color.m_RGBA.a)) {
		SDLHelper::print_SDL_Error("Texture::fillTexture::SDL_GetRenderDrawColor() failed.");
		return false;
	}
	if(!SDL_SetRenderTarget(p_renderer, texture->m_Texture.get())) {
		SDLHelper::print_SDL_Error("Texture::fillTexture::SDL_SetRenderTarget() failed.");
		return false;
	}
	bool rc = true;
	do {
		if(SDL_SetRenderDrawColor(p_renderer, color.m_RGBA.r, color.m_RGBA.g, color.m_RGBA.b, color.m_RGBA.a)) {
			SDLHelper::print_SDL_Error("Texture::fillTexture::SDL_SetRenderDrawColor() failed.");
			return false;
		}
		do {
			if(SDL_RenderClear(p_renderer)) {
				SDLHelper::print_SDL_Error("Texture::fillTexture::SDL_RenderClear() failed.");
				rc = false;
				break;
			}
		} while(0);
		if(SDL_SetRenderDrawColor(p_renderer, tmp_color.m_RGBA.r, tmp_color.m_RGBA.g, tmp_color.m_RGBA.b, tmp_color.m_RGBA.a)) {
			SDLHelper::print_SDL_Error("Texture::fillTexture::SDL_SetRenderDrawColor() failed.");
			rc = false;
			break;
		}
	} while(0);
	if(SDL_SetRenderTarget(p_renderer, nullptr)) {
		SDLHelper::print_SDL_Error("Texture::fillTexture::SDL_SetRenderTarget() failed.");
		rc = false;
	}
	return rc;
}

}

