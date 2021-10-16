/*
 * MainWindow.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "MainWindow.hpp"

#include <cstdlib>
#include <iostream>

#include <SDL_video.h>

#include "SDLHelper.hpp"
#include "utils/Destroy.hpp"

#include "utils/drawing/Rectangle.hpp"

std::int32_t MainWindow::init(const MainWindowCfg_t &cfg) {
	m_Rect = cfg.Rect;
	if (Point::UNDEFINED == m_Rect.m_Pos) {
		m_Rect.m_Pos = Point(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	SDL_Window * p_win = SDL_CreateWindow(cfg.Name.c_str()
			, m_Rect.m_Pos.m_X, m_Rect.m_Pos.m_Y
			, m_Rect.m_W, m_Rect.m_H
			, cfg.Flags);
	if (nullptr == p_win) {
		SDLHelper::print_SDL_Error("SDL_CreateWindow() failed.");
		return EXIT_FAILURE;
	}
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ MainWindow::init() create SDL_Window " << p_win << std::endl;
#endif
	m_Window = std::shared_ptr<SDL_Window>(p_win, Destroy::free<SDL_Window, SDL_DestroyWindow>);
	return EXIT_SUCCESS;
}
