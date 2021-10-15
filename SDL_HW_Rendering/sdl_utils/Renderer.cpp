/*
 * Renderer.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "Renderer.hpp"

#include <cstdlib>

#include <SDL_render.h>
#include <SDL_pixels.h>

#include "sdl_utils/SDLHelper.hpp"

#include "utils/Destroy.hpp"
#include "utils/drawing/Rectangle.hpp"


int32_t Renderer::init(SDL_Window *p_window) {
	constexpr auto unspec_driver_id = -1;
	SDL_Renderer * p_render = SDL_CreateRenderer(p_window, unspec_driver_id, SDL_RENDERER_ACCELERATED);
	if (nullptr == p_render) {
		SDLHelper::print_SDL_Error("SDL_CreateRenderer() failed.");
		return EXIT_FAILURE;
	}
	m_Renderer = std::shared_ptr<SDL_Renderer>(p_render, Destroy::free<SDL_Renderer, SDL_DestroyRenderer>);
	if(EXIT_SUCCESS != SDL_SetRenderDrawColor(p_render, 0, 0, 0, SDL_ALPHA_OPAQUE)) {
		SDLHelper::print_SDL_Error("SDL_SetRenderDrawColor() failed.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t Renderer::clearScreen() {
	if(EXIT_SUCCESS != SDL_RenderClear(m_Renderer.get())) {
		SDLHelper::print_SDL_Error("SDL_RenderClear() failed.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void Renderer::finishFrame() {
	SDL_RenderPresent(m_Renderer.get());
}

int32_t Renderer::copy(SDL_Texture * p_texture, const Rectangle &src_rec, const Rectangle &dst_rec) {
	const SDL_Rect * p_srcrect = nullptr;
	const SDL_Rect * p_dstrect = nullptr;
	SDL_Rect src_rect{};
	SDL_Rect dst_rect{};
	if (Rectangle::UNDEFINED != src_rec) {
		src_rect = SDLHelper::toRect(src_rec);
		p_srcrect = &src_rect;
	}
	if (Rectangle::UNDEFINED != dst_rec) {
		dst_rect = SDLHelper::toRect(dst_rec);
		p_dstrect = &dst_rect;
	}

	if(EXIT_SUCCESS != SDL_RenderCopy(m_Renderer.get(), p_texture, p_srcrect, p_dstrect)) {
		SDLHelper::print_SDL_Error("SDL_RenderCopy() failed.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;

}
