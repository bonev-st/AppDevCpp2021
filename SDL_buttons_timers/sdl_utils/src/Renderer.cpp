/*
 * Renderer.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "sdl_utils/Renderer.hpp"

#include <iostream>

#include <SDL_render.h>
#include <SDL_pixels.h>
#include <SDL_hints.h>

#include "utils/Destroy.hpp"
#include "utils/drawing/DrawParams.hpp"
#include "utils/drawing/Rectangle.hpp"

#include "sdl_utils/SDLHelper.hpp"

bool Renderer::init(const MainWindow::Config_t &cfg) {
	m_AppWindow = std::move(MainWindow::createMainWindow(cfg));
	if(nullptr == m_AppWindow) {
		std::cerr << "Renderer::init::MainWindow::createMainWindow() failed." << std::endl;
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		SDLHelper::print_SDL_Error("Renderer::init::SDL_CreateRenderer() failed.");
		return false;
	}
	constexpr auto UNSPEC_DRIVER_ID = -1;
	m_Renderer = std::shared_ptr<SDL_Renderer>( SDL_CreateRenderer(m_AppWindow->m_Window.get()
												, UNSPEC_DRIVER_ID, SDL_RENDERER_ACCELERATED)
					, Destroy::free<SDL_Renderer, SDL_DestroyRenderer>);
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ Renderer::init() create SDL_Renderer " << m_Renderer.get() << std::endl;
#endif
	if (nullptr == m_Renderer) {
		SDLHelper::print_SDL_Error("Renderer::init::SDL_CreateRenderer() failed.");
		return false;
	}
	if(EXIT_SUCCESS != SDL_SetRenderDrawColor(m_Renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE)) {
		SDLHelper::print_SDL_Error("Renderer::init::SDL_SetRenderDrawColor() failed.");
		return false;
	}
	return true;
}

bool Renderer::clearScreen() const {
	if(EXIT_SUCCESS != SDL_RenderClear(m_Renderer.get())) {
		SDLHelper::print_SDL_Error("Renderer::clearScreen::SDL_RenderClear() failed.");
		return false;
	}
	return true;
}

void Renderer::finishFrame() const {
	SDL_RenderPresent(m_Renderer.get());
}

bool Renderer::copy(SDL_Texture * p_texture, const DrawParams_t & params) const {
	const SDL_Rect * p_srcrect = nullptr;
	const SDL_Rect * p_dstrect = nullptr;
	const SDL_Point * p_center = nullptr;
	auto src_rect = SDL_Rect {};
	auto dst_rect = SDL_Rect {};
	auto center = SDL_Point {};

	if (Rectangle::UNDEFINED != params.m_SrcRect) {
		src_rect = SDLHelper::toRect(params.m_SrcRect);
		p_srcrect = &src_rect;
	}
	if (Rectangle::UNDEFINED != params.m_DstRect) {
		dst_rect = SDLHelper::toRect(params.m_DstRect);
		p_dstrect = &dst_rect;
	}
	if (Point::UNDEFINED != params.m_RotationCenter) {
		center = SDLHelper::toPoint(params.m_RotationCenter);
		p_center = &center;
	}

	if(EXIT_SUCCESS != SDL_RenderCopyEx(m_Renderer.get(), p_texture, p_srcrect, p_dstrect,
			params.m_Angle, p_center, static_cast<SDL_RendererFlip>(params.m_FlipMode))) {
		SDLHelper::print_SDL_Error("Renderer::copy::SDL_RenderCopy() failed.");
		return false;
	}
	return true;

}
