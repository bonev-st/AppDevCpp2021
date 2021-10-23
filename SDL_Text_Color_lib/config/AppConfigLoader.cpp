/*
 * AppConfigLoader.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "config/AppConfigLoader.hpp"

#include "sdl_utils/MainWindow.hpp"
#include "utils/drawing/Dimention.hpp"

#include "config/AppConfig.hpp"

#include "game/config/GameConfig.hpp"

constexpr auto WINDOW_WIDTH		= 640;
constexpr auto WINDOW_HEIGHT	= 480;
constexpr auto IMG_WIDTH		= WINDOW_WIDTH;
constexpr auto IMG_HEIGHT		= WINDOW_HEIGHT;
constexpr auto L2_WIDTH  		= 150;
constexpr auto L2_HEIGHT 		= 150;
constexpr auto APP_NAME	 		= "Scaling and Alpha blending";

static void populateAppWindowCfg(MainWindow::Config_t &cfg) {
	constexpr auto app_name = APP_NAME;
	cfg.m_Name = app_name;
	cfg.m_Rect = Rectangle(Point::UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT);
	cfg.m_Flags = MainWindow::WINDOW_SHOWN;
}

static void populateResourcesCfg(ResourcesConfig::Config_t &cfg) {
	ImgConfig::Config_t res;
	res.m_Path = "resources/images/press_keys.png";
	res.m_Dimention = Dimention(IMG_WIDTH, IMG_HEIGHT);
	cfg.m_ImgRes[ResurcesId::IDLE_IMG]	= res;
	res.m_Path = "resources/images/up.png";
	cfg.m_ImgRes[ResurcesId::UP_IMG]	= res;
	res.m_Path = "resources/images/down.png";
	cfg.m_ImgRes[ResurcesId::DOWN_IMG]	= res;
	res.m_Path = "resources/images/left.png";
	cfg.m_ImgRes[ResurcesId::LEFT_IMG]	= res;
	res.m_Path = "resources/images/right.png";
	cfg.m_ImgRes[ResurcesId::RIGHT_IMG]	= res;
	res.m_Path = "resources/images/layer_2.png";
	res.m_Dimention = Dimention(L2_WIDTH, L2_HEIGHT);
	cfg.m_ImgRes[ResurcesId::L2_IMG]	= res;
}

static void populateGameCfg(GameConfig::Config_t &cfg) {
	cfg.m_Keys[Keyboard::KEY_ESCAPE]			= GameConfig::KEY_EXIT_MASK;
	cfg.m_Keys[Keyboard::KEY_UP]				= GameConfig::KEY_UP_MASK;
	cfg.m_Keys[Keyboard::KEY_DOWN]				= GameConfig::KEY_DOWN_MASK;
	cfg.m_Keys[Keyboard::KEY_LEFT]				= GameConfig::KEY_LEFT_MASK;
	cfg.m_Keys[Keyboard::KEY_RIGHT]				= GameConfig::KEY_RIGHT_MASK;
	cfg.m_Keys[Keyboard::KEY_I]					= GameConfig::KEY_MOVE_UP_MASK;
	cfg.m_Keys[Keyboard::KEY_M]					= GameConfig::KEY_MOVE_DOWN_MASK;
	cfg.m_Keys[Keyboard::KEY_J]					= GameConfig::KEY_MOVE_LEFT_MASK;
	cfg.m_Keys[Keyboard::KEY_K]					= GameConfig::KEY_MOVE_RIGHT_MASK;
	cfg.m_Keys[Keyboard::KEY_NUMPAD_PLUS]		= GameConfig::KEY_ZOOM_UP_MASK;
	cfg.m_Keys[Keyboard::KEY_NUMPAD_MINUS]		= GameConfig::KEY_ZOOM_DOWN_MASK;
	cfg.m_Keys[Keyboard::KEY_A]					= GameConfig::KEY_OPACITY_UP_MASK;
	cfg.m_Keys[Keyboard::KEY_S]					= GameConfig::KEY_OPACITY_DOWN_MASK;
}

namespace AppConfigLoader {

AppConfig Loader() {
	AppConfig cfg;
	populateAppWindowCfg(cfg.m_ResourcesCfg.m_WindowCfg);
	populateResourcesCfg(cfg.m_ResourcesCfg);
	populateGameCfg(cfg.m_GameCfg);
	return cfg;
}

} /* namespace AppConfigLoader */
