/*
 * Level2.cpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#include "game/gr_layers/Level2.hpp"

#include <iostream>
#include <iomanip>

#include "utils/inc/utils/drawing/DisplayMode.hpp"

#include "game/config/Layout.hpp"
#include "game/config/GameConfigDef.hpp"
#include "game/config/ConfigData.hpp"

bool Level2::init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode) {
	Dimention disp_dim;
	disp_dim.m_W = display_mode.m_W;
	disp_dim.m_H = display_mode.m_H;
	if(!m_Container.init(disp_dim, Points::ZERO)) {
		std::cerr << "WidgetContainer init() failed." << std::endl;
		return false;
	}
	if(!initTexts(cfg.m_Text)) {
		std::cerr << "initTexts() failed." << std::endl;
		return false;
	}
	m_Container.add(&m_TextScore.m_ScaleContainer);
	m_Container.add(&m_TextHiScore.m_ScaleContainer);
	m_Container.add(&m_TextShips.m_ScaleContainer);

	m_LifeCounter.attach(std::bind(&Level2::setShips, this, std::placeholders::_1));
	m_ScoreCouters.attachHiScore(std::bind(&Level2::setHiScore, this, std::placeholders::_1));
	m_ScoreCouters.attachScore(std::bind(&Level2::setScore, this, std::placeholders::_1));

	return true;
}

void Level2::draw() {
	m_Container.draw();
}

void Level2::resetCounters() {
	m_ScoreCouters.reset();
	m_LifeCounter.reset();
}

void Level2::setPoints(uint32_t points) {
	m_LifeCounter.points(m_ScoreCouters.addPoints(points));
}

void Level2::setScore(uint32_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_SCORE_INDX)->m_Text;
	std::string text_num = std::to_string(val);
	auto src_size = text_num.size();
	for(auto it = text.rbegin(); src_size && (text.rend() != it); ++it) {
		*it = text_num[--src_size];
	}
	if(!m_TextScore.m_Text.setText(text)) {
		std::cerr << "Score setText() failed" << std::endl;
	}
}

void Level2::setHiScore(uint32_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_HI_SCORE_INDX)->m_Text;
	std::string text_num = std::to_string(val);
	auto src_size = text_num.size();
	for(auto it = text.rbegin(); src_size && (text.rend() != it); ++it) {
		*it = text_num[--src_size];
	}
	if(!m_TextHiScore.m_Text.setText(text)) {
		std::cerr << "Hi Score setText() failed" << std::endl;
	}
}

void Level2::setShips(uint32_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_SHIPS_INDX)->m_Text;
	std::string text_num = std::to_string(val);
	auto src_size = text_num.size();
	for(auto it = text.rbegin(); src_size && (text.rend() != it); ++it) {
		*it = text_num[--src_size];
	}
	if(!m_TextShips.m_Text.setText(text)) {
		std::cerr << "Ships setText() failed" << std::endl;
	}
}

bool Level2::initTexts(const GameConfig::TextRes_t & cfg) {
	const auto scale = Layout::getScaleFactor();
	std::size_t font_id;
	const AbsCoordinates::TextCfg_t * config;
	// Score text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_SCORE_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_SCORE_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextScore, font_id, config->m_Text,
			config->m_Color, config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Score text failed" << std::endl;
		return false;
	}
	// Hi Score text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_HI_SCORE_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_HI_SCORE_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextHiScore, font_id, config->m_Text,
			config->m_Color, config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Hi Score text failed" << std::endl;
		return false;
	}
	// Hi Score text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_SHIPS_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_SHIPS_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextShips, font_id, config->m_Text,
			config->m_Color, config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Ships text failed" << std::endl;
		return false;
	}
	return true;
}


