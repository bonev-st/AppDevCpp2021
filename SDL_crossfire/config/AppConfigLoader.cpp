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
constexpr auto APP_NAME	 					= "Crossfire 81";
constexpr auto WINDOW_WIDTH					= 770;
constexpr auto WINDOW_HEIGHT				= 526;

constexpr std::uint32_t MAX_REFRESH_RATE	= 100;

constexpr std::uint32_t EXPLOSION_IMG_W		= 48;
constexpr std::uint32_t EXPLOSION_IMG_H		= 48;
constexpr std::uint32_t EXPLOSION_IMG_ROL	= 6;
constexpr std::uint32_t EXPLOSION_IMG_COL	= 8;

}

static void populateAppWindowCfg(MainWindowCfg::Config_t &cfg) {
	constexpr auto app_name = APP_NAME;
	cfg.m_Name = app_name;
	cfg.m_Rect = Rectangle(Points::UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT);
	cfg.m_Flags = MainWindowCfg::WINDOW_SHOWN | MainWindowCfg::WINDOW_FULLSCREEN | MainWindowCfg::WINDOW_DESKTOP;
	//cfg.m_Flags = MainWindowCfg::WINDOW_SHOWN | MainWindowCfg::WINDOW_BORDERLESS;
}

static void populateDrawingCfg(DrawMgrConfig::Config_t &cfg) {
	populateAppWindowCfg(cfg.m_WindowCfg);
	cfg.m_MaxFrameRate = MAX_REFRESH_RATE;
}

void polulateSprite(std::vector<Rectangle> & frames_b, const int32_t rols, const int32_t cols, const int32_t w, const int32_t h) {
	Rectangle rec(0, 0, w, h);
	for(int32_t rol = 0; rols > rol; ++rol ) {
		for(int32_t col = 0; cols > col; ++col ) {
			frames_b.emplace_back(rec);
			rec.m_Pos.m_X += h;
		}
		rec.m_Pos.m_Y += h;
		rec.m_Pos.m_X  = 0;
	}
}

void populateImgCfg(ImgConfig::ImgRes_t &cfg) {
	cfg[ResurcesId::BACKGROUND_IMG].m_Path = "resources/images/background.jpg";
	cfg[ResurcesId::CROSSFIRE_TEXT_IMG].m_Path = "resources/images/crossfire_text.png";
	cfg[ResurcesId::GRID_BKGRND_IMG].m_Path = "resources/images/grid_background.png";
	cfg[ResurcesId::GRID_IMG].m_Path = "resources/images/grid.png";
	cfg[ResurcesId::SHIP_IMG].m_Path = "resources/images/ship.png";
	cfg[ResurcesId::ENEMY1_IMG].m_Path = "resources/images/enemy1.png";
	cfg[ResurcesId::ENEMY2_IMG].m_Path = "resources/images/enemy2.png";
	cfg[ResurcesId::ENEMY3_IMG].m_Path = "resources/images/enemy3.png";
	cfg[ResurcesId::ENEMY4_IMG].m_Path = "resources/images/enemy4.png";
	cfg[ResurcesId::BONUS_IMG].m_Path = "resources/images/bonus.png";
	cfg[ResurcesId::AMMUN_IMG].m_Path = "resources/images/ammu.png";
	cfg[ResurcesId::OWN_BULLET_IMG].m_Path = "resources/images/own_bullet.png";
	cfg[ResurcesId::ENEMY_BULLET_IMG].m_Path = "resources/images/alien_bullet.png";
	cfg[ResurcesId::EXPLOSION_IMG].m_Path = "resources/images/explosion.png";
	polulateSprite(cfg[ResurcesId::EXPLOSION_IMG].m_Frames, EXPLOSION_IMG_ROL,
			EXPLOSION_IMG_COL, EXPLOSION_IMG_W, EXPLOSION_IMG_H);
}

void populateFontCfg(FontConfig::FontRes_t &cfg) {
	FontConfig::Config_t res;
	res.m_Path = "resources/fonts/unlearne.ttf";
	res.m_TextSize = 20;
	cfg[ResurcesId::ANGELINE_UNLEARNE_20_TTF] = res;
}

void populateResourceCfg(ResMgrConfig::Config_t & cfg) {
	populateImgCfg(cfg.m_ImgRes);
	populateFontCfg(cfg.m_FontRes);
}

void populateResourcesCfg(ResourcesConfig::Config_t &cfg) {
	populateDrawingCfg(cfg.m_DrawMgrCfg);
	populateResourceCfg(cfg.m_ResMgrCfg);
}

void populateGameKeys(GameConfig::KeyRes_t &cfg) {
	cfg[Keyboard::KEY_ESCAPE]	= GameConfig::KEY_EXIT_MASK;
	cfg[Keyboard::KEY_I]		= GameConfig::KEY_UP_MASK;
	cfg[Keyboard::KEY_K]		= GameConfig::KEY_DOWN_MASK;
	cfg[Keyboard::KEY_J]		= GameConfig::KEY_LEFT_MASK;
	cfg[Keyboard::KEY_L]		= GameConfig::KEY_RIGHT_MASK;
	cfg[Keyboard::KEY_E]		= GameConfig::KEY_FIRE_UP_MASK;
	cfg[Keyboard::KEY_D]		= GameConfig::KEY_FIRE_DOWN_MASK;
	cfg[Keyboard::KEY_S]		= GameConfig::KEY_FIRE_LEFT_MASK;
	cfg[Keyboard::KEY_F]		= GameConfig::KEY_FIRE_RIGHT_MASK;
	cfg[Keyboard::KEY_SPACE]	= GameConfig::KEY_PAUSE_MASK;
	cfg[Keyboard::KEY_PERIOD]	= GameConfig::KEY_INFO_MASK;
	cfg[Keyboard::KEY_ENTER]	= GameConfig::KEY_MENU_MASK;
}

void populateGameImg(GameConfig::ImgRes_t &cfg) {
	cfg[GameConfig::IMG_BACKGROUND_INDX] = ResurcesId::BACKGROUND_IMG;
	cfg[GameConfig::IMG_GRID_BKGRND_INDX] = ResurcesId::GRID_BKGRND_IMG;
	cfg[GameConfig::IMG_GRID_INDX] = ResurcesId::GRID_IMG;
	cfg[GameConfig::IMG_CROSSFIRE_INDX] = ResurcesId::CROSSFIRE_TEXT_IMG;
	cfg[GameConfig::IMG_SHIP_INDX] = ResurcesId::SHIP_IMG;
	cfg[GameConfig::IMG_ENEMY1_INDX] = ResurcesId::ENEMY1_IMG;
	cfg[GameConfig::IMG_ENEMY2_INDX] = ResurcesId::ENEMY2_IMG;
	cfg[GameConfig::IMG_ENEMY3_INDX] = ResurcesId::ENEMY3_IMG;
	cfg[GameConfig::IMG_ENEMY4_INDX] = ResurcesId::ENEMY4_IMG;
	cfg[GameConfig::IMG_BONUS_INDX] = ResurcesId::BONUS_IMG;
	cfg[GameConfig::IMG_AMMU_INDX] = ResurcesId::AMMUN_IMG;
	cfg[GameConfig::IMG_OWN_BULLED_INDX] = ResurcesId::OWN_BULLET_IMG;
	cfg[GameConfig::IMG_ENEMY_BULLED_INDX] = ResurcesId::ENEMY_BULLET_IMG;
	cfg[GameConfig::IMG_EXPLOSION_INDX] = ResurcesId::EXPLOSION_IMG;
}

void populateGameText(GameConfig::TextRes_t &cfg) {
	cfg[GameConfig::TEXT_SCORE_LABLE_INDX] = ResurcesId::ANGELINE_UNLEARNE_20_TTF;
	cfg[GameConfig::TEXT_SCORE_INDX] = ResurcesId::ANGELINE_UNLEARNE_20_TTF;
	cfg[GameConfig::TEXT_HI_SCORE_LABLE_INDX] = ResurcesId::ANGELINE_UNLEARNE_20_TTF;
	cfg[GameConfig::TEXT_HI_SCORE_INDX] = ResurcesId::ANGELINE_UNLEARNE_20_TTF;
	cfg[GameConfig::TEXT_SHIPS_LABLE_INDX] = ResurcesId::ANGELINE_UNLEARNE_20_TTF;
	cfg[GameConfig::TEXT_SHIPS_INDX] = ResurcesId::ANGELINE_UNLEARNE_20_TTF;
	cfg[GameConfig::TEXT_FPS_INDX] = ResurcesId::ANGELINE_UNLEARNE_20_TTF;
	cfg[GameConfig::TEXT_ACTIVE_TIMER_INDX] = ResurcesId::ANGELINE_UNLEARNE_20_TTF;
	cfg[GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX] = ResurcesId::ANGELINE_UNLEARNE_20_TTF;
}

void populateGameCfg(GameConfig::Config_t &cfg) {
	populateGameKeys(cfg.m_Keys);
	populateGameImg(cfg.m_Img);
	populateGameText(cfg.m_Text);
}

namespace AppConfigLoader {
AppConfig Loader() {
	AppConfig cfg;
	populateResourcesCfg(cfg.m_ResourcesCfg);
	populateGameCfg(cfg.m_GameCfg);
	return cfg;
}

} /* namespace AppConfigLoader */
