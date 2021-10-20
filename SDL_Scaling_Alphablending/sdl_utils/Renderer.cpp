/*
 * Renderer.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "Renderer.hpp"

#include <cstdlib>
#include <iostream>

#include <SDL_render.h>
#include <SDL_pixels.h>
#include <SDL_hints.h>

#include "sdl_utils/SDLHelper.hpp"

#include "utils/Destroy.hpp"
#include "utils/drawing/Rectangle.hpp"


bool Renderer::init(const MainWindow::Config_t &cfg) {
	m_AppWindow = MainWindow::createMainWindow(cfg);
	if(nullptr == m_AppWindow) {
		std::cerr << "MainWindow::createMainWindow() failed." << std::endl;
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		SDLHelper::print_SDL_Error("SDL_CreateRenderer() failed.");
		return false;
	}
	constexpr auto UNSPEC_DRIVER_ID = -1;
	m_Renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(m_AppWindow->m_Window.get()
													, UNSPEC_DRIVER_ID, SDL_RENDERER_ACCELERATED)
					, Destroy::free<SDL_Renderer, SDL_DestroyRenderer>);
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ Renderer::init() create SDL_Renderer " << m_Renderer << std::endl;
#endif
	if (nullptr == m_Renderer) {
		SDLHelper::print_SDL_Error("SDL_CreateRenderer() failed.");
		return false;
	}
	if(EXIT_SUCCESS != SDL_SetRenderDrawColor(m_Renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE)) {
		SDLHelper::print_SDL_Error("SDL_SetRenderDrawColor() failed.");
		return false;
	}
	return true;
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
	auto src_rect = SDL_Rect {};
	auto dst_rect = SDL_Rect {};
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
