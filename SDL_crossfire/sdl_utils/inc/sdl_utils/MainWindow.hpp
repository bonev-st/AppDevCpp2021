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

#include "utils/drawing/DisplayMode.hpp"

struct SDL_Window;

class MainWindow : private NoCopy {
public:
	bool init(const MainWindowCfg::Config_t &cfg);
	operator SDL_Window *() const;
	const Rectangle & getRect() const;
	const DisplayMode::Mode_t & getDisplayMode() const;

private:
	struct SDL_DisplayMode_t {
	    uint32_t format;
	    int32_t w;
	    int32_t h;
	    int refresh_rate;
	    void *driverdata = nullptr;
	};

	RAII_Handler<SDL_Window*, nullptr, std::function<void(SDL_Window*)>> m_Window;
	Rectangle m_Rect = Rectangles::UNDEFINED;
	SDL_DisplayMode_t m_DispyMode;
	DisplayMode::Mode_t m_WindowDim;
};
#endif /* SDL_UTILS_MAINWINDOW_HPP_ */
