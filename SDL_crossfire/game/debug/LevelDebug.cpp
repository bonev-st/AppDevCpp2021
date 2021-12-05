/*
 * LevelDebug.cpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#include "game/debug/LevelDebug.hpp"

#include <iostream>
#include <iomanip>
#include <string>

#include "utils/inc/utils/drawing/DisplayMode.hpp"

#include "gr_engine/managers/Timer2Mgr.hpp"
#include "gr_engine/widgets/InitHelper.hpp"

#include "game/config/Layout.hpp"
#include "game/config/GameConfigDef.hpp"
#include "game/config/ConfigData.hpp"

const uint32_t LevelDebug::REFRESH_RATE = 333;	// ms

bool LevelDebug::init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode) {
	Dimention disp_dim;
	disp_dim.m_W = display_mode.m_W;
	disp_dim.m_H = display_mode.m_H;

	//disp_dim.m_W = 220;
	//disp_dim.m_H = 120;
	if(!m_Container.init(disp_dim, Points::ZERO)) {
	//if(!m_Container.init(disp_dim, {100,100})) {
		std::cerr << "WidgetContainer init() failed." << std::endl;
		return false;
	}
	if(!initTexts(cfg.m_Text)) {
		std::cerr << "initTexts() failed" << std::endl;
		return false;
	}
	m_Container.add(&m_TextFPS.m_ScaleContainer);
	m_Container.add(&m_TextMaxTim.m_ScaleContainer);
	m_Container.add(&m_TextActiveTim.m_ScaleContainer);
	m_FPS.init();
	m_Container.setVisible(false);
	return true;
}

void LevelDebug::newFrame() {
	m_FPS.newFrame();
}

void LevelDebug::draw() {
	m_Container.draw();
}

bool LevelDebug::enable() {
	if(!m_RefreshTimer.start(REFRESH_RATE, Timer2::TimerMode_t::RELOAD, std::bind(&LevelDebug::onDebugRefresh, this, std::placeholders::_1))) {
		std::cerr << "startTimer() failed." << std::endl;
		return false;
	}
	return true;
}

void LevelDebug::disable() {
	m_RefreshTimer.stop();
	m_Container.setVisible(false);
}

bool LevelDebug::setFPS(double val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_FPS_INDX)->m_Text;
	std::ostringstream oss;
	oss.setf(std::ios::fixed);
	oss << std::setprecision(1) << val;
	text += oss.str();
	return m_TextFPS.m_Text.setText(text);
}

bool LevelDebug::setActiveTim(std::size_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_ACTIVE_TIMER_INDX)->m_Text;
	text += std::to_string(val);
	return m_TextActiveTim.m_Text.setText(text);
}

bool LevelDebug::setMaxTim(std::size_t val) {
	std::string text = Layout::getTextData(GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX)->m_Text;
	text += std::to_string(val);
	return m_TextMaxTim.m_Text.setText(text);
}

bool LevelDebug::initTexts(const GameConfig::TextRes_t & cfg) {
	const auto scale = Layout::getScaleFactor();
	std::size_t font_id;
	const AbsCoordinates::TextCfg_t * config;
	// FPS text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_FPS_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_FPS_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextFPS, font_id, config->m_Text,
			config->m_Color, /*{0,0}*/config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Ships text failed" << std::endl;
		return false;
	}
	// Active timers text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_ACTIVE_TIMER_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_ACTIVE_TIMER_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextActiveTim, font_id, config->m_Text,
			config->m_Color, /*{0,40}*/config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Ships text failed" << std::endl;
		return false;
	}
	// Max timers text
	if(!ConfigData::configText(cfg, GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX, font_id, config)) {
		std::cerr << "ConfigData::configText(GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX) failed" << std::endl;
		return false;
	}
	if(!InitHelper::initScaledText(m_TextMaxTim, font_id, config->m_Text,
			config->m_Color, /*{0,80}*/config->m_Pos, config->m_BackgroundColor, scale)) {
		std::cerr << "init Ships text failed" << std::endl;
		return false;
	}
	return true;
}

void LevelDebug::onDebugRefresh(Timer2::TimerHandler_t id) {
	if((m_RefreshTimer != id) || !m_RefreshTimer.isRunning()) {
		return;
	}
	if(!m_Container.getVisible()) {
		m_Container.setVisible(true);
	}
	if(!setFPS(m_FPS)) {
		std::cerr << "Game::createImages() Level2.setFPS() failed"<< std::endl;
	}
	if(!setActiveTim(Timer2MgrInst::getInstance()->getActive())) {
		std::cerr << "Game::createImages() Level2.setActiveTim() failed"<< std::endl;
	}
	if(!setMaxTim(Timer2MgrInst::getInstance()->getMaxActive())) {
		std::cerr << "Game::createImages() Level2.setActiveTim() failed"<< std::endl;
	}
}

