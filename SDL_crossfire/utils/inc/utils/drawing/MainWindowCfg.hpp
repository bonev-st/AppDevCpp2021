/*
 * MainWindowCfg.hpp
 *
 *  Created on: Nov 14, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_DRAWING_MAINWINDOWCFG_HPP_
#define UTILS_INC_UTILS_DRAWING_MAINWINDOWCFG_HPP_

#include <string>

#include "utils/drawing/Rectangle.hpp"

namespace MainWindowCfg {

enum WindowFlags_t : uint32_t {
	WINDOW_NONE = 0,
	WINDOW_FULLSCREEN = 0x00000001, 	// SDL_WINDOW_FULLSCREEN
	WINDOW_SHOWN = 0x00000004, 			// SDL_WINDOW_SHOWN
	WINDOW_BORDERLESS = 0x00000010, 	// SDL_WINDOW_BORDERLESS
	WINDOW_DESKTOP = 0x00001000,		// SDL_WINDOW_DESKTOP
};

struct Config_t {
	std::string m_Name = "";
	Rectangle m_Rect = Rectangles::UNDEFINED;
	uint32_t m_Flags = WINDOW_NONE;
};
}

#endif /* UTILS_INC_UTILS_DRAWING_MAINWINDOWCFG_HPP_ */
