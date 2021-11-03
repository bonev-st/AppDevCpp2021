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
	std::shared_ptr<SDL_Window> m_Window;
	Rectangle m_Rect;
} MainWindow_t;

enum WindowFlags_t {
	WINDOW_NONE = 0,
	WINDOW_FULLSCREEN = 0x00000001, 	// SDL_WINDOW_FULLSCREEN
	WINDOW_SHOWN = 0x00000004, 			// SDL_WINDOW_SHOWN
	WINDOW_BORDERLESS = 0x00000010, 	// SDL_WINDOW_BORDERLESS
	WINDOW_DESKTOP = 0x00001000,		// SDL_WINDOW_DESKTOP
};

struct Config_t {
	std::string m_Name = "";
	Rectangle m_Rect = Rectangle::UNDEFINED;
	WindowFlags_t m_Flags = WINDOW_NONE;
};

std::shared_ptr<MainWindow_t> createMainWindow(const Config_t &cfg);

}

#endif /* SDL_UTILS_MAINWINDOW_HPP_ */
