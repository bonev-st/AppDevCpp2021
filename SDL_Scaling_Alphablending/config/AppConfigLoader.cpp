/*
 * AppConfigLoader.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "config/AppConfigLoader.hpp"

#include "config/AppConfig.hpp"

constexpr auto WINDOW_WIDTH  = 640;
constexpr auto WINDOW_HEIGHT = 480;
constexpr auto L2_WIDTH  = 150;
constexpr auto L2_HEIGHT = 150;

static void populateAppWindowCfg(MainWindow::Config_t &cfg) {
	constexpr auto app_name = "Scaling and Alpha blending";
	cfg.m_Name = app_name;
	cfg.m_Rect = Rectangle(Point::UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT);
	cfg.m_Flags = MainWindow::WINDOW_SHOWN;
}

static void populateResourcesCfg(ResourcesConfig::Config_t &cfg) {
	cfg.m_ImgPath[IDLE_IMG]		= "resources/press_keys.png";
	cfg.m_ImgPath[UP_IMG]		= "resources/up.png";
	cfg.m_ImgPath[DOWN_IMG]		= "resources/down.png";
	cfg.m_ImgPath[LEFT_IMG]		= "resources/left.png";
	cfg.m_ImgPath[RIGHT_IMG]	= "resources/right.png";
	cfg.m_ImgPath[L2_IMG]		= "resources/layer_2.png";
}

static void populateGameCfg(GameConfig::Config_t &cfg) {
	cfg.m_Keys[Keyboard::KEY_ESCAPE]	= GameConfig::KEY_EXIT_MASK;
	cfg.m_Keys[Keyboard::KEY_UP]		= GameConfig::KEY_UP_MASK;
	cfg.m_Keys[Keyboard::KEY_DOWN]		= GameConfig::KEY_DOWN_MASK;
	cfg.m_Keys[Keyboard::KEY_LEFT]		= GameConfig::KEY_LEFT_MASK;
	cfg.m_Keys[Keyboard::KEY_RIGHT]		= GameConfig::KEY_RIGHT_MASK;

	cfg.m_ImgDimention[IDLE_IMG]		= GameConfig::ImgDimetion_t{.m_W = WINDOW_WIDTH,	.m_H = WINDOW_HEIGHT};
	cfg.m_ImgDimention[UP_IMG]			= GameConfig::ImgDimetion_t{.m_W = WINDOW_WIDTH,	.m_H = WINDOW_HEIGHT};
	cfg.m_ImgDimention[DOWN_IMG]		= GameConfig::ImgDimetion_t{.m_W = WINDOW_WIDTH,	.m_H = WINDOW_HEIGHT};
	cfg.m_ImgDimention[LEFT_IMG]		= GameConfig::ImgDimetion_t{.m_W = WINDOW_WIDTH,	.m_H = WINDOW_HEIGHT};
	cfg.m_ImgDimention[RIGHT_IMG]		= GameConfig::ImgDimetion_t{.m_W = WINDOW_WIDTH,	.m_H = WINDOW_HEIGHT};
	cfg.m_ImgDimention[L2_IMG]			= GameConfig::ImgDimetion_t{.m_W = L2_WIDTH,		.m_H = L2_HEIGHT};
}

namespace AppConfigLoader {

AppConfig Loader() {
	AppConfig cfg;
	populateAppWindowCfg(cfg.m_WindowCfg);
	populateResourcesCfg(cfg.m_ResourcesCfg);
	populateGameCfg(cfg.m_GameCfg);
	return cfg;
}

} /* namespace AppConfigLoader */
