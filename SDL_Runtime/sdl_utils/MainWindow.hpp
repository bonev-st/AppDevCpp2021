/*
 * MainWindow.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_MAINWINDOW_HPP_
#define SDL_UTILS_MAINWINDOW_HPP_

#include <string>

#include "utils/drawing/Rectangle.hpp"

struct SDL_Window;
struct SDL_Surface;

enum WindowFlags_t {
	WINDOW_NONE = 0, WINDOW_FULLSCREEN = 0x00000001, 	// SDL_WINDOW_FULLSCREEN
	WINDOW_SHOWN = 0x00000004, 			// SDL_WINDOW_SHOWN
	WINDOW_BORDERLESS = 0x00000010, 	// SDL_WINDOW_BORDERLESS
	WINDOW_DESKTOP = 0x00001000,		// SDL_WINDOW_DESKTOP
};

struct MainWindowCfg_t {
	std::string Name = "";
	Rectangle Rect = Rectangle::UNDEFINED;
	WindowFlags_t Flags = WINDOW_NONE;
};

class MainWindow {
public:
	MainWindow() = default;
	~MainWindow();

	MainWindow(const MainWindow&) = delete;
	MainWindow& operator =(const MainWindow&) = delete;

	MainWindow(MainWindow&&) = delete;
	MainWindow& operator =(MainWindow&&) = delete;

	std::int32_t init(const MainWindowCfg_t &cfg);
	void deinit();

	SDL_Surface* getSurface();
	const Rectangle* getRectangle() const {
		return &m_Rect;
	}

	std::int32_t updateSurface();

	std::int32_t copy(SDL_Surface *src, const Rectangle &src_rec,
			const Rectangle &dst_rec);

private:
	SDL_Window *m_Window = nullptr;
	Rectangle m_Rect = Rectangle::UNDEFINED;
};

#endif /* SDL_UTILS_MAINWINDOW_HPP_ */
