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

bool Renderer::init(const MainWindowCfg::Config_t &cfg) {
	if(!m_AppWindow.init(cfg)) {
		std::cerr << "Renderer::init::MainWindow::createMainWindow() failed." << std::endl;
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		SDLHelper::print_SDL_Error("Renderer::init::SDL_CreateRenderer() failed.");
		return false;
	}
	constexpr auto UNSPEC_DRIVER_ID = -1;
	m_Renderer.reset();
	m_Renderer.set(SDL_CreateRenderer(m_AppWindow, UNSPEC_DRIVER_ID
					, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)
					, Destroy::free<SDL_Renderer, SDL_DestroyRenderer>);
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ Renderer::init() create SDL_Renderer " << m_Renderer << std::endl;
#endif
	if (nullptr == m_Renderer) {
		SDLHelper::print_SDL_Error("Renderer::init::SDL_CreateRenderer() failed.");
		return false;
	}
	if(EXIT_SUCCESS != SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)) {
		SDLHelper::print_SDL_Error("Renderer::init::SDL_SetRenderDrawColor() failed.");
		return false;
	}
	return true;
}

bool Renderer::clearScreen() const {
	if(EXIT_SUCCESS != SDL_RenderClear(m_Renderer)) {
		SDLHelper::print_SDL_Error("Renderer::clearScreen::SDL_RenderClear() failed.");
		return false;
	}
	return true;
}

void Renderer::finishFrame() const {
	SDL_RenderPresent(m_Renderer);
}

bool Renderer::copy(SDL_Texture * p_texture, const DrawParams_t & params) const {
	const SDL_Rect * p_srcrect = nullptr;
	const SDL_Rect * p_dstrect = nullptr;
	const SDL_Point * p_center = nullptr;
	auto src_rect = SDL_Rect {};
	auto dst_rect = SDL_Rect {};
	auto center = SDL_Point {};

	if (Rectangles::UNDEFINED != params.m_SrcRect) {
		src_rect = SDLHelper::toRect(params.m_SrcRect);
		p_srcrect = &src_rect;
	}
	if (Rectangles::UNDEFINED != params.m_DstRect) {
		dst_rect = SDLHelper::toRect(params.m_DstRect);
		p_dstrect = &dst_rect;
	}
	if (Points::UNDEFINED != params.m_RotationCenter) {
		center = SDLHelper::toPoint(params.m_RotationCenter);
		p_center = &center;
	}

	if(EXIT_SUCCESS != SDL_RenderCopyEx(m_Renderer, p_texture, p_srcrect, p_dstrect,
			params.m_Angle, p_center, static_cast<SDL_RendererFlip>(params.m_FlipMode))) {
		SDLHelper::print_SDL_Error("Renderer::copy::SDL_RenderCopy() failed.");
		return false;
	}
	return true;
}

Renderer::operator SDL_Renderer *() const {
	return m_Renderer;
}

const DisplayMode::Mode_t & Renderer::getDisplayMode() const {
	return m_AppWindow.getDisplayMode();
}
