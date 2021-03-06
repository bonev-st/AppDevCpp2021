/*
 * AppConfigLoader.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "config/AppConfigLoader.hpp"

#include "common/CommonDefines.hpp"

#include "sdl_utils/MainWindow.hpp"
#include "utils/drawing/Dimention.hpp"

#include "config/AppConfig.hpp"

#include "game/config/GameConfig.hpp"

namespace {
constexpr auto APP_NAME	 				= "Managers";
constexpr auto WINDOW_WIDTH				= 640;
constexpr auto WINDOW_HEIGHT			= 480;

constexpr std::int64_t MAX_REFRESH_RATE	= 50;
}

static void populateAppWindowCfg(MainWindow::Config_t &cfg) {
	constexpr auto app_name = APP_NAME;
	cfg.m_Name = app_name;
	cfg.m_Rect = Rectangle(Point::UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT);
	cfg.m_Flags = MainWindow::WINDOW_SHOWN;
}

static void populateDrawingCfg(DrawMgrConfig::Config_t &cfg) {
	populateAppWindowCfg(cfg.m_WindowCfg);
	cfg.m_MaxFrameRate = MAX_REFRESH_RATE;
}

void populateImgCfg(ImgConfig::ImgRes_t &cfg) {
	ImgConfig::Config_t res;
	res.m_Path = "resources/images/press_keys.png";
	cfg[ResurcesId::IDLE_IMG]	= res;
	res.m_Path = "resources/images/up.png";
	cfg[ResurcesId::UP_IMG]	= res;
	res.m_Path = "resources/images/down.png";
	cfg[ResurcesId::DOWN_IMG]	= res;
	res.m_Path = "resources/images/left.png";
	cfg[ResurcesId::LEFT_IMG]	= res;
	res.m_Path = "resources/images/right.png";
	cfg[ResurcesId::RIGHT_IMG]	= res;
	res.m_Path = "resources/images/layer_2.png";
	cfg[ResurcesId::L2_IMG]	= res;
}

void populateFontCfg(FontConfig::FontRes_t &cfg) {
	FontConfig::Config_t res;
	res.m_Path = "resources/fonts/AngelineVintage.ttf";
	res.m_TextSize = 40;
	cfg[ResurcesId::ANGELINE_VINTAGE_40_TTF] = res;
	res.m_TextSize = 80;
	cfg[ResurcesId::ANGELINE_VINTAGE_80_TTF] = res;
	res.m_TextSize = 160;
	cfg[ResurcesId::ANGELINE_VINTAGE_160_TTF] = res;
}

void populateResourceCfg(ResMgrConfig::Config_t & cfg) {
	populateImgCfg(cfg.m_ImgRes);
	populateFontCfg(cfg.m_FontRes);
}

void populateResourcesCfg(ResourcesConfig::Config_t &cfg) {
	populateDrawingCfg(cfg.m_DrawMgrCfg);
	populateResourceCfg(cfg.m_ResMgrCfg);
}

void populateGameCfg(GameConfig::Config_t &cfg) {
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
	cfg.m_Keys[Keyboard::KEY_Q]					= GameConfig::KEY_T_OPACITY_UP_MASK;
	cfg.m_Keys[Keyboard::KEY_W]					= GameConfig::KEY_T_OPACITY_DOWN_MASK;
}

namespace AppConfigLoader {
AppConfig Loader() {
	AppConfig cfg;
	populateResourcesCfg(cfg.m_ResourcesCfg);
	populateGameCfg(cfg.m_GameCfg);
	return cfg;
}

} /* namespace AppConfigLoader */
