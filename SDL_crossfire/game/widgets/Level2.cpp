/*
 * Level2.cpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#include "game/widgets/Level2.hpp"

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
	m_Container.add(&m_TextFPS.m_ScaleContainer);
	m_Container.add(&m_TextMaxTim.m_ScaleContainer);
	m_Container.add(&m_TextActiveTim.m_ScaleContainer);
	return true;
}

void Level2::draw() {
	m_Container.draw();
}

bool Level2::setScore(uint32_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_SCORE_INDX)->m_Text;
	std::string text_num = std::to_string(val);
	auto src_size = text_num.size();
	for(auto it = text.rbegin(); src_size && (text.rend() != it); ++it) {
		*it = text_num[--src_size];
	}
	return m_TextScore.m_Text.setText(text);
}

bool Level2::setScoreMax(uint32_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_HI_SCORE_INDX)->m_Text;
	std::string text_num = std::to_string(val);
	auto src_size = text_num.size();
	for(auto it = text.rbegin(); src_size && (text.rend() != it); ++it) {
		*it = text_num[--src_size];
	}
	return m_TextHiScore.m_Text.setText(text);
}

bool Level2::setShips(uint8_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_SHIPS_INDX)->m_Text;
	std::string text_num = std::to_string(val);
	auto src_size = text_num.size();
	for(auto it = text.rbegin(); src_size && (text.rend() != it); ++it) {
		*it = text_num[--src_size];
	}
	return m_TextShips.m_Text.setText(text);
}

bool Level2::setFPS(double val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_FPS_INDX)->m_Text;
	std::ostringstream oss;
	oss.setf(std::ios::fixed);
	oss << std::setprecision(1) << val;
	text += oss.str();
	return m_TextFPS.m_Text.setText(text);
}

bool Level2::setActiveTim(std::size_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_ACTIVE_TIMER_INDX)->m_Text;
	text += std::to_string(val);
	return m_TextActiveTim.m_Text.setText(text);
}

bool Level2::setMaxTim(std::size_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_ACTIVE_TIMER_INDX)->m_Text;
	text += std::to_string(val);
	return m_TextMaxTim.m_Text.setText(text);
}

bool Level2::initTexts(const GameConfig::TextRes_t & cfg) {
	const auto scale = Layout::getScaleFactor();
	// Score text
	std::size_t font_id;
	const AbsCoordinates::TextCfg_t * config;
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
	// FPS text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_FPS_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_FPS_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextFPS, font_id, config->m_Text,
			config->m_Color, config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Ships text failed" << std::endl;
		return false;
	}
	// Active timers text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_ACTIVE_TIMER_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_FPS_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextActiveTim, font_id, config->m_Text,
			config->m_Color, config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Ships text failed" << std::endl;
		return false;
	}
	// Max timers text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_FPS_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextMaxTim, font_id, config->m_Text,
			config->m_Color, config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Ships text failed" << std::endl;
		return false;
	}
	return true;
}


