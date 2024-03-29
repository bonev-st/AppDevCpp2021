/*
 * Game.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "Game.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "utils/drawing/DisplayMode.hpp"
#include "utils/drawing/Color.hpp"

#include "sdl_utils/InputEvent.hpp"

#include "gr_engine/config/DebugCfg.hpp"

#include "common/CommonDefines.hpp"

#include "game/config/Layout.hpp"
#include "game/config/Rules.hpp"
#include "game/config/GameConfigDef.hpp"

const uint32_t Game::MOTION_PERIOD = 15;	// ms

bool Game::init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode) {
	Layout::init(display_mode);
	//DebugCfg::m_Enable = true;
	if(!m_L1.init(cfg, display_mode)) {
		std::cerr << "Level1 init failed." << std::endl;
		return false;
	}
	if(!m_L2.init(cfg, display_mode)) {
		std::cerr << "Level2 init failed." << std::endl;
		return false;
	}
	if(!m_Debug.init(cfg, display_mode)) {
		std::cerr << "Debug failed." << std::endl;
		return false;
	}
	if(!m_L_Top.init(cfg, display_mode, this)) {
		std::cerr << "Top level init failed." << std::endl;
		return false;
	}
	if(!loadKeys(cfg.m_Keys)) {
		std::cerr << "loadKeys() failed." << std::endl;
		return false;
	}
	if(!initTimers()) {
		std::cerr << "initTimers() failed." << std::endl;
		return false;
	}
	if(!initWidgets(display_mode, cfg.m_Img)) {
		std::cerr << "initWidgets() failed." << std::endl;
		return false;
	}
	newGame();
	m_Debug.enable();
	return true;
}

bool Game::events(const InputEvent& event, bool& exit) {
	exit = false;
	if(m_L_Top.events(event)) {
		return true;
	}
	const auto it = m_Keys.find(event.m_Key);
	if(m_Keys.end() != it) {
		setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, it->second);
	}
	exit = exitRequest();
	return true;
}

bool Game::draw() {
	m_Background.draw();
	m_L1.draw();
	m_L2.draw();
	m_L_Top.draw();
	m_Debug.draw();
	return true;
}

bool Game::new_frame() {
	m_Debug.newFrame();
	return true;
}

bool Game::processing() {
	return m_L_Top.processing();
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
	return true;
}

void Game::newGame() {
	// TODO: Add animated text Mission 1
	Rules::firstMission();
	m_L2.resetCounters();
	m_L_Top.reload();
}

void Game::newMission() {
	// TODO: Add animated text Mission N and wait until all bullets disappear
	Rules::nextMission();
	m_L_Top.reload();
}

void Game::restartMission() {
	// TODO: Add animated text Mission lost and wait until all bullets disappear
	m_L_Top.reload();
}

void Game::gameOver() {
	// TODO: Add animated text Game over, wait until all bullets disappear,
	// select new game or exit
	newGame();
}

bool Game::initTimers() {
	if(!m_MotionTimer.start(MOTION_PERIOD, Timer2::TimerMode_t::RELOAD,
			std::bind(&Game::onMotion_Timeout, this, std::placeholders::_1))) {
		std::cerr << "startTimer() failed." << std::endl;
		return false;
	}
	return true;
}

bool Game::initWidgets(const DisplayMode::Mode_t & display_mode, const GameConfig::ImgRes_t & cfg) {
	Dimention disp_dim;
	disp_dim.m_W = display_mode.m_W;
	disp_dim.m_H = display_mode.m_H;
	// init Background
	{
		const auto it = cfg.find(GameConfig::ImgIndx_t::IMG_ENEMY_BULLED_INDX);
		if(cfg.end() == it) {
			std::cerr << "Can't find grid point image resource id" << std::endl;
			return false;
		}
		const auto & config = Layout::getImgData(0);
		if(!m_Background.init(0, config->m_Alpha, 0.25, disp_dim, Layout::getMotionArea(), m_L_Top.getShip())) {
			std::cerr << "m_Background.init() failed." << std::endl;
			return false;
		}
	}
	return true;
}

bool Game::exitRequest() const {
	return !!(GameConfig::KEY_EXIT_MASK & m_KeysMask);
}

void Game::setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask) {
	if(pressed) {
		switch(key_mask) {
		default:
			break;
		}
		m_KeysMask |=  key_mask;
	} else {
		m_KeysMask &= ~key_mask;
	}
}

void Game::onMotion_Timeout(Timer2::TimerHandler_t id) {
	// TODO: add check for game pause
	if((m_MotionTimer != id) || !m_MotionTimer.isRunning()) {
		return;
	}
	m_L_Top.tick();
}

void Game::setPoints(std::uint32_t points) {
	m_L2.setPoints(points);
}

void Game::decLifes() {
	m_L2.decLife();
}

void Game::restart() {
	if(m_L2.isAlife()) {
		restartMission();
	} else {
		gameOver();
	}
}

void Game::nextMission() {
	newMission();
}

