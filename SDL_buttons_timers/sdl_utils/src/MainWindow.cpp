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

namespace MainWindow {

std::unique_ptr<MainWindow_t> createMainWindow(const Config_t &cfg) {
	Rectangle rect = cfg.m_Rect;
	if (Point::UNDEFINED == rect.m_Pos) {
		rect.m_Pos = Point(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	auto data = MainWindow_t {
		.m_Window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(cfg.m_Name.c_str()
										, rect.m_Pos.m_X, rect.m_Pos.m_Y
										, rect.m_W, rect.m_H
										, cfg.m_Flags)
							, Destroy::free<SDL_Window, SDL_DestroyWindow>),
		.m_Rect = cfg.m_Rect
	};
#ifdef SHOW_MEM_ALLOC_INFO
	std::cout << "+ SDL_CreateWindow() create SDL_Window " << data.m_Window.get() << std::endl;
#endif
	if(nullptr == data.m_Window) {
		SDLHelper::print_SDL_Error("MainWindow::createMainWindow::SDL_CreateWindow() fault.");
		return std::unique_ptr<MainWindow_t>(nullptr);
	}
	return std::make_unique<MainWindow_t>(data);
}

}
