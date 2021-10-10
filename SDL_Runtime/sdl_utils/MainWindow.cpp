/*
 * MainWindow.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "MainWindow.hpp"

#include <cstdlib>

#include <SDL_video.h>

#include "SDLHelper.hpp"
#include "utils/drawing/Rectangle.hpp"

MainWindow::~MainWindow() {
	deinit();
}

std::int32_t MainWindow::init(const MainWindowCfg_t &cfg) {
	m_Rect = cfg.Rect;
	if (Point::UNDEFINED == m_Rect.m_Pos) {
		m_Rect.m_Pos = Point(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	m_Window = SDL_CreateWindow(cfg.Name.c_str()
			, m_Rect.m_Pos.m_X, m_Rect.m_Pos.m_Y
			, m_Rect.m_W, m_Rect.m_H
			, cfg.Flags);
	if (nullptr == m_Window) {
		SDLHelper::print_SDL_Error("SDL_CreateWindow() failed.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void MainWindow::deinit() {
	if (m_Window) {
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}
}

SDL_Surface* MainWindow::getSurface() {
	SDL_Surface *rc = SDL_GetWindowSurface(m_Window);
	if (nullptr == rc) {
		SDLHelper::print_SDL_Error("SDL_GetWindowSurface() failed.");
	}
	return rc;
}

std::int32_t MainWindow::updateSurface() {
	if (EXIT_SUCCESS != SDL_UpdateWindowSurface(m_Window)) {
		SDLHelper::print_SDL_Error("SDL_UpdateWindowSurface() failed.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

std::int32_t MainWindow::copy(SDL_Surface *src, const Rectangle &src_rec,
		const Rectangle &dst_rec) {
	SDL_Surface *dst = getSurface();
	if (nullptr == dst) {
		return EXIT_FAILURE;
	}
	const SDL_Rect *p_src_rect = nullptr;
	SDL_Rect *p_dst_rect = nullptr;
	SDL_Rect src_rect = { };
	SDL_Rect dst_rect = { };

	if (Rectangle::UNDEFINED != src_rec) {
		src_rect = SDLHelper::toSDL_Rect(src_rec);
		p_src_rect = &src_rect;
	}
	if (Rectangle::UNDEFINED != dst_rec) {
		dst_rect = SDLHelper::toSDL_Rect(src_rec);
		p_dst_rect = &dst_rect;
	}
	if (EXIT_SUCCESS != SDL_BlitSurface(src, p_src_rect, dst, p_dst_rect)) {
		SDLHelper::print_SDL_Error("SDL_BlitSurface() failed.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
