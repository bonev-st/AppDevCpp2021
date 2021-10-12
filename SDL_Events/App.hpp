/*
 * App.hpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#ifndef APP_HPP_
#define APP_HPP_

#include <cstdint>
#include "sdl_utils/MainWindow.hpp"
#include "sdl_utils/InputEvent.hpp"

class App {
public:
	App();
	~App();

	int32_t init();
	void deinit();
	int32_t start();

private:
	MainWindow m_AppWindow;
	SDL_Surface * m_Image;
	InputEvent m_InputEvents;

	int32_t loadResources();
};

#endif /* APP_HPP_ */
