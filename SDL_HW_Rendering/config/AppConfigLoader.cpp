/*
 * AppConfigLoader.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "config/AppConfigLoader.hpp"

#include "config/AppConfig.hpp"

static void populateAppWindowCfg(MainWindowCfg_t &cfg) {
	cfg.Name = "HW rendering";
	cfg.Rect = Rectangle(Point::UNDEFINED, 640, 480);
	cfg.Flags = WINDOW_SHOWN;
}

static void populateGameCfg(GameConfig &cfg) {
	cfg.ImgPath[IDLE_IMG]	= "resources/press_keys.png";
	cfg.ImgPath[UP_IMG]		= "resources/up.png";
	cfg.ImgPath[DOWN_IMG]	= "resources/down.png";
	cfg.ImgPath[LEFT_IMG]	= "resources/left.png";
	cfg.ImgPath[RIGHT_IMG]	= "resources/right.png";
}

namespace AppConfigLoader {

AppConfig Loader() {
	AppConfig cfg;
	populateAppWindowCfg(cfg.WindowCfg);
	populateGameCfg(cfg.GameCfg);
	return cfg;
}

} /* namespace AppConfigLoader */
