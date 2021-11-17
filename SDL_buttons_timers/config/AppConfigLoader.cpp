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
constexpr auto APP_NAME	 				= "Buttons and timers";
constexpr auto WINDOW_WIDTH				= 1024;
constexpr auto WINDOW_HEIGHT			= 768;

constexpr std::uint32_t MAX_REFRESH_RATE	= 100;

constexpr std::int32_t RUNNING_GIRL_FRAMES	= 6;
constexpr std::int32_t RUNNING_GIRL_BIG_IMG_H = 256;
constexpr std::int32_t RUNNING_GIRL_BIG_IMG_W = 256;
constexpr std::int32_t RUNNING_GIRL_SMALL_IMG_H = 220;
constexpr std::int32_t RUNNING_GIRL_SMALL_IMG_W = 256;

constexpr std::int32_t BUTTON_FRAMES	= 3;
constexpr std::int32_t BUTTON_IMG_H 	= 50;
constexpr std::int32_t BUTTON_IMG_W 	= 150;

}

static void populateAppWindowCfg(MainWindowCfg::Config_t &cfg) {
	constexpr auto app_name = APP_NAME;
	cfg.m_Name = app_name;
	cfg.m_Rect = Rectangle(Point::UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT);
	cfg.m_Flags = MainWindowCfg::WINDOW_DESKTOP | MainWindowCfg::WINDOW_BORDERLESS;
}

static void populateDrawingCfg(DrawMgrConfig::Config_t &cfg) {
	populateAppWindowCfg(cfg.m_WindowCfg);
	cfg.m_MaxFrameRate = MAX_REFRESH_RATE;
}

void populateImgCfg(ImgConfig::ImgRes_t &cfg) {
	cfg[ResurcesId::WHEEL_IMG].m_Path = "resources/images/wheel.png";

	cfg[ResurcesId::RUNNING_GIRL_BIG_IMG].m_Path = "resources/images/running_girl_big.png";
	Rectangle rec(0, 0, RUNNING_GIRL_BIG_IMG_W, RUNNING_GIRL_BIG_IMG_H);
	auto & frames_b = cfg[ResurcesId::RUNNING_GIRL_BIG_IMG].m_Frames;
	for(int32_t i = 0; RUNNING_GIRL_FRAMES > i; ++i ) {
		frames_b.emplace_back(rec);
		rec.m_Pos.m_X += RUNNING_GIRL_BIG_IMG_W;
	}

	cfg[ResurcesId::RUNNING_GIRL_SMALL_IMG].m_Path = "resources/images/running_girl_small.png";
	rec = Rectangle(0, 0, RUNNING_GIRL_SMALL_IMG_W, RUNNING_GIRL_SMALL_IMG_H);
	auto & frames_s = cfg[ResurcesId::RUNNING_GIRL_SMALL_IMG].m_Frames;
	for(int32_t i = 0; RUNNING_GIRL_FRAMES > i; ++i ) {
		frames_s.emplace_back(rec);
		rec.m_Pos.m_X += RUNNING_GIRL_SMALL_IMG_W;
	}

	cfg[ResurcesId::BUTTON_START_IMG].m_Path = "resources/images/button_start.png";
	rec = Rectangle(0, 0, BUTTON_IMG_W, BUTTON_IMG_H);
	auto & frames_start = cfg[ResurcesId::BUTTON_START_IMG].m_Frames;
	for(int32_t i = 0; BUTTON_FRAMES > i; ++i ) {
		frames_start.emplace_back(rec);
		rec.m_Pos.m_X += BUTTON_IMG_W;
	}

	cfg[ResurcesId::BUTTON_STOP_IMG].m_Path = "resources/images/button_stop.png";
	rec = Rectangle(0, 0, BUTTON_IMG_W, BUTTON_IMG_H);
	auto & frames_stop = cfg[ResurcesId::BUTTON_STOP_IMG].m_Frames;
	for(int32_t i = 0; BUTTON_FRAMES > i; ++i ) {
		frames_stop.emplace_back(rec);
		rec.m_Pos.m_X += BUTTON_IMG_W;
	}
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
