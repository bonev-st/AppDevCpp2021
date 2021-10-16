/*
 * MainWindow.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_MAINWINDOW_HPP_
#define SDL_UTILS_MAINWINDOW_HPP_

#include <string>
#include <memory>

#include "utils/drawing/Rectangle.hpp"

struct SDL_Window;
struct SDL_Surface;

namespace MainWindow {

typedef struct _MainWindow_t {
	SDL_Window * m_Window;
	Rectangle m_Rect;
} MainWindow_t;

enum WindowFlags_t {
	WINDOW_NONE = 0,
	WINDOW_FULLSCREEN = 0x00000001, 	// SDL_WINDOW_FULLSCREEN
	WINDOW_SHOWN = 0x00000004, 			// SDL_WINDOW_SHOWN
	WINDOW_BORDERLESS = 0x00000010, 	// SDL_WINDOW_BORDERLESS
	WINDOW_DESKTOP = 0x00001000,		// SDL_WINDOW_DESKTOP
};

struct MainWindowCfg_t {
	std::string Name = "";
	Rectangle Rect = Rectangle::UNDEFINED;
	WindowFlags_t Flags = WINDOW_NONE;
};

std::shared_ptr<MainWindow_t> createMainWindow(const MainWindowCfg_t &cfg);

}

#endif /* SDL_UTILS_MAINWINDOW_HPP_ */
