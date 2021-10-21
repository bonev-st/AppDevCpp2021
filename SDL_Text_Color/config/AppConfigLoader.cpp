/*
 * AppConfigLoader.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "config/AppConfigLoader.hpp"

#include "config/AppConfig.hpp"

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
	cfg.m_ImgPath[TextureId::IDLE_IMG]	= "resources/press_keys.png";
	cfg.m_ImgPath[TextureId::UP_IMG]	= "resources/up.png";
	cfg.m_ImgPath[TextureId::DOWN_IMG]	= "resources/down.png";
	cfg.m_ImgPath[TextureId::LEFT_IMG]	= "resources/left.png";
	cfg.m_ImgPath[TextureId::RIGHT_IMG]	= "resources/right.png";
	cfg.m_ImgPath[TextureId::L2_IMG]	= "resources/layer_2.png";
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

	cfg.m_ImgDimention[TextureId::IDLE_IMG]		= GameConfig::ImgDimetion_t{.m_W = IMG_WIDTH,	.m_H = IMG_HEIGHT};
	cfg.m_ImgDimention[TextureId::UP_IMG]		= GameConfig::ImgDimetion_t{.m_W = IMG_WIDTH,	.m_H = IMG_HEIGHT};
	cfg.m_ImgDimention[TextureId::DOWN_IMG]		= GameConfig::ImgDimetion_t{.m_W = IMG_WIDTH,	.m_H = IMG_HEIGHT};
	cfg.m_ImgDimention[TextureId::LEFT_IMG]		= GameConfig::ImgDimetion_t{.m_W = IMG_WIDTH,	.m_H = IMG_HEIGHT};
	cfg.m_ImgDimention[TextureId::RIGHT_IMG]	= GameConfig::ImgDimetion_t{.m_W = IMG_WIDTH,	.m_H = IMG_HEIGHT};
	cfg.m_ImgDimention[TextureId::L2_IMG]		= GameConfig::ImgDimetion_t{.m_W = L2_WIDTH,	.m_H = L2_HEIGHT};
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
