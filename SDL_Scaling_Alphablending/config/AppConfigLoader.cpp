/*
 * AppConfigLoader.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "config/AppConfigLoader.hpp"

#include "config/AppConfig.hpp"

static void populateAppWindowCfg(MainWindow::MainWindowCfg_t &cfg) {
	constexpr auto app_name = "HW rendering";
	constexpr auto WINDOW_WIDTH = 640;
	constexpr auto WINDOW_HEIGHT = 480;

	cfg.Name = app_name;
	cfg.Rect = Rectangle(Point::UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT);
	cfg.Flags = MainWindow::WINDOW_SHOWN;
}

static void populateGameCfg(GameBase::GameConfig &cfg) {
	cfg.ImgPath[GameBase::IDLE_IMG]		= "resources/press_keys.png";
	cfg.ImgPath[GameBase::UP_IMG]		= "resources/up.png";
	cfg.ImgPath[GameBase::DOWN_IMG]		= "resources/down.png";
	cfg.ImgPath[GameBase::LEFT_IMG]		= "resources/left.png";
	cfg.ImgPath[GameBase::RIGHT_IMG]	= "resources/right.png";
	cfg.ImgPath[GameBase::L2_IMG]		= "resources/layer_2.png";
	cfg.Keys[Keyboard::KEY_ESCAPE]		= GameBase::KEY_EXIT_MASK;
	cfg.Keys[Keyboard::KEY_UP]			= GameBase::KEY_UP_MASK;
	cfg.Keys[Keyboard::KEY_DOWN]		= GameBase::KEY_DOWN_MASK;
	cfg.Keys[Keyboard::KEY_LEFT]		= GameBase::KEY_LEFT_MASK;
	cfg.Keys[Keyboard::KEY_RIGHT]		= GameBase::KEY_RIGHT_MASK;
}

namespace AppConfigLoader {

AppConfig Loader() {
	AppConfig cfg;
	populateAppWindowCfg(cfg.WindowCfg);
	populateGameCfg(cfg.GameCfg);
	return cfg;
}

} /* namespace AppConfigLoader */
