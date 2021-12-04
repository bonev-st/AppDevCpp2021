/*
 * Level1.cpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#include "game/widgets/Level1.hpp"

#include <iostream>

#include "utils/drawing/DisplayMode.hpp"

#include "game/config/Layout.hpp"
#include "game/config/GameConfigDef.hpp"
#include "game/config/ConfigData.hpp"

bool Level1::init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode) {
	Dimention disp_dim;
	disp_dim.m_W = display_mode.m_W;
	disp_dim.m_H = display_mode.m_H;
	if(!m_Container.init(disp_dim, Points::ZERO)) {
		std::cerr << "WidgetContainer init() failed." << std::endl;
		return false;
	}
	if(!initImages(cfg.m_Img)) {
		std::cerr << "initImages() failed." << std::endl;
		return false;
	}
	if(!initTexts(cfg.m_Text)) {
		std::cerr << "initTexts() failed." << std::endl;
		return false;
	}
	m_Container.add(&m_ImgCrossfire.m_ScaleContainer);
	m_Container.add(&m_ImgGrid.m_ScaleContainer);
	m_Container.add(&m_TextScore.m_ScaleContainer);
	m_Container.add(&m_TextHiScore.m_ScaleContainer);
	m_Container.add(&m_TextShips.m_ScaleContainer);
	return true;
}

void Level1::draw() {
	m_Container.draw();
}

bool Level1::initImages(const GameConfig::ImgRes_t & cfg) {
	// CrossfireImage
	std::size_t img_id;
	const AbsCoordinates::ImgCfg_t * config;
	const auto scale = Layout::getScaleFactor();
	if(!ConfigData::configImage(cfg, GameConfig::IMG_CROSSFIRE_INDX, img_id, config)) {
		std::cerr << "ConfigData::configImage(GameConfig::IMG_GRID_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledImage(m_ImgCrossfire, img_id, config->m_BackgroundColor,
			config->m_Alpha, config->m_Pos, scale)) {
		std::cerr << "init Cossfire failed" << std::endl;
		return false;
	}
	// GridImage
	if(!ConfigData::configImage(cfg, GameConfig::IMG_GRID_INDX, img_id, config)) {
		std::cerr << "ConfigData::configImage(GameConfig::IMG_GRID_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledImage(m_ImgGrid, img_id, config->m_BackgroundColor,
			config->m_Alpha, config->m_Pos, scale)) {
		std::cerr << "init Grid failed" << std::endl;
		return false;
	}
	return true;
}

bool Level1::initTexts(const GameConfig::TextRes_t & cfg) {
	const auto scale = Layout::getScaleFactor();
	// Score text
	std::size_t font_id;
	const AbsCoordinates::TextCfg_t * config;
	if(!ConfigData::configText(cfg, GameConfig::TEXT_SCORE_LABLE_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_SCORE_LABLE_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextScore, font_id, config->m_Text,
			config->m_Color, config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Score text failed" << std::endl;
		return false;
	}
	// Hi Score text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_HI_SCORE_LABLE_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_HI_SCORE_LABLE_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextHiScore, font_id, config->m_Text,
			config->m_Color, config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Hi Score text failed" << std::endl;
		return false;
	}
	// Hi Score text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_SHIPS_LABLE_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_SHIPS_LABLE_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextShips, font_id, config->m_Text,
			config->m_Color, config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Ships text failed" << std::endl;
		return false;
	}
	return true;
}
