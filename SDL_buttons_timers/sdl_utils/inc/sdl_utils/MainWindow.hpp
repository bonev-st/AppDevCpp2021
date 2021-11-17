/*
 * MainWindow.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_MAINWINDOW_HPP_
#define SDL_UTILS_MAINWINDOW_HPP_

#include <string>
#include <functional>

#include "utils/drawing/MainWindowCfg.hpp"
#include "utils/drawing/Rectangle.hpp"
#include "utils/RAII_Handler.hpp"

#include "utils/NoCopy.hpp"

#include "sdl_utils/DiplayMode.hpp"

struct SDL_Window;

class MainWindow : private NoCopy {
public:
	bool init(const MainWindowCfg::Config_t &cfg);
	operator SDL_Window *() const;
	const Rectangle & getRect() const;
	const DiplayMode::Mode_t & getDisplayMode() const;

private:
	struct SDL_DisplayMode_t {
		DiplayMode::Mode_t Mode;
	    void *driverdata = nullptr;		/**< driver-specific data, initialize to 0 */
	};

	RAII_Handler<SDL_Window*, nullptr, std::function<void(SDL_Window*)>> m_Window;
	Rectangle m_Rect = Rectangle::UNDEFINED;
	SDL_DisplayMode_t m_DispyMode;
};
#endif /* SDL_UTILS_MAINWINDOW_HPP_ */
