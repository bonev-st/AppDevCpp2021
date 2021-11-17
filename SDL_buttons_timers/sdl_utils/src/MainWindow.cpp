/*
 * MainWindow.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "sdl_utils/MainWindow.hpp"

#include <iostream>

#include <SDL_video.h>
#include "utils/Destroy.hpp"

#include "sdl_utils/SDLHelper.hpp"

bool MainWindow::init(const MainWindowCfg::Config_t &cfg) {
	Rectangle rect = cfg.m_Rect;
	if (Point::UNDEFINED == rect.m_Pos) {
		rect.m_Pos = Point(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	m_Window.reset();
	m_Window.set(SDL_CreateWindow(cfg.m_Name.c_str()
			, rect.m_Pos.m_X, rect.m_Pos.m_Y
			, rect.m_W, rect.m_H
			, cfg.m_Flags), [this](SDL_Window * p) {
		if(p) {
	#ifdef SHOW_MEM_ALLOC_INFO
			std::cout << "- Destroy with SDL_DestroyWindow(" << p << ")" << std::endl;
	#endif
			if(m_DispyMode.driverdata) {
				SDL_SetWindowDisplayMode(p, NULL);
				m_DispyMode.driverdata = nullptr;
			}
			SDL_DestroyWindow(p);
		}
	#ifdef SHOW_MEM_ALLOC_INFO
		else {
			std::cout << "- Try to destroy with SDL_DestroyWindow(nullptr)" << std::endl;
		}
	#endif
	});
	m_Rect = cfg.m_Rect;
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ SDL_CreateWindow() create SDL_Window " << m_Window << std::endl;
#endif
	if(nullptr == m_Window) {
		SDLHelper::print_SDL_Error("MainWindow::createMainWindow::SDL_CreateWindow() fault.");
		return false;
	}
	SDL_DisplayMode tmp;
	if(SDL_GetWindowDisplayMode(m_Window, &tmp)) {
		SDLHelper::print_SDL_Error("MainWindow::createMainWindow::SDL_GetWindowDisplayMode() fault.");
		return false;
	}
	m_DispyMode = *reinterpret_cast<SDL_DisplayMode_t *>(&tmp);
	return true;
}

MainWindow::operator SDL_Window *() const {
	return m_Window;
}

const Rectangle & MainWindow::getRect() const {
	return m_Rect;
}

const DiplayMode::Mode_t & MainWindow::getDisplayMode() const {
	return m_DispyMode.Mode;
}
