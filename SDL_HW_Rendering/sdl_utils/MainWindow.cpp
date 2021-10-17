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

namespace MainWindow {

std::shared_ptr<MainWindow_t> createMainWindow(const MainWindowCfg_t &cfg) {
	auto p_win = new MainWindow_t {
		.m_Window = nullptr,
		.m_Rect = cfg.Rect
	};
	if(nullptr == p_win) {
		std::cerr << "Create MainWindow_t failed." << std::endl;
		return std::shared_ptr<MainWindow_t>(nullptr);
	}
	if (Point::UNDEFINED == p_win->m_Rect.m_Pos) {
		p_win->m_Rect.m_Pos = Point(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ createMainWindow() create MainWindow_t " << p_win << std::endl;
#endif
	auto rc = std::shared_ptr<MainWindow_t> (p_win, Destroy::freeMember<MainWindow_t, SDL_Window, &MainWindow_t::m_Window, SDL_DestroyWindow>);
	rc->m_Window = SDL_CreateWindow(cfg.Name.c_str()
			, p_win->m_Rect.m_Pos.m_X, p_win->m_Rect.m_Pos.m_Y
			, p_win->m_Rect.m_W, p_win->m_Rect.m_H
			, cfg.Flags);
	if (nullptr == p_win->m_Window) {
		SDLHelper::print_SDL_Error("SDL_CreateWindow() failed.");
		return std::shared_ptr<MainWindow_t>(nullptr);
	}
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ createMainWindow() create SDL_Window " << p_win << std::endl;
#endif
	return rc;
}

}
