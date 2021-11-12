/*
 * App.hpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#ifndef APP_HPP_
#define APP_HPP_

#include <cstdint>
#include <vector>

#include "utils/NoCopy.hpp"

#include "sdl_utils/SDLLoader.hpp"
#include "sdl_utils/InputEvent.hpp"

#include "manager_utils/managers/Mgrs.hpp"

#include "game/Game.hpp"

struct AppConfig;

class App : private NoCopy {
public:
	bool init(const AppConfig& cfg);
	bool start();

private:
	std::int64_t m_FrameDuration = 0;

	SDLLoader m_Loader;
	InputEvent m_InputEvents;
	Mgrs m_Managers;
	Game m_Game;

	std::vector<BaseMgr *> m_ProcessConatainer;

	bool mainLoop();
	bool drawFrame();
	bool processFrame();

	void limitFPS(int64_t elapsed_us);

	void load_text();
	void show_text();
};

#endif /* APP_HPP_ */
