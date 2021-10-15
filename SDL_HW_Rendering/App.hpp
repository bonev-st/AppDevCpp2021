/*
 * App.hpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#ifndef APP_HPP_
#define APP_HPP_

#include <cstdint>

#include "sdl_utils/SDLLoader.hpp"
#include "sdl_utils/MainWindow.hpp"
#include "sdl_utils/InputEvent.hpp"
#include "sdl_utils/Renderer.hpp"

#include "game/Game.hpp"

struct AppConfig;

class App {
public:
	App() = default;
	~App() = default;

	int32_t init(const AppConfig& cfg);
	int32_t start();

private:
	SDLLoader m_Loader;
	MainWindow m_AppWindow;
	Renderer m_Renderer;
	InputEvent m_InputEvents;
	Game m_Game;

	int32_t mainLoop();
	int32_t drawFrame();
	int32_t processFrame();

	void limitFPS(int64_t elapsed_us);
	void setExitRequest();
};

#endif /* APP_HPP_ */
