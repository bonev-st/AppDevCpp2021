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
#include <iomanip>

#include "sdl_utils/InputEvent.hpp"
#include "manager_utils/managers/Timer2Mgr.hpp"
#include "utils/drawing/Color.hpp"
#include "common/CommonDefines.hpp"

#include "game/config/Layout.hpp"

const uint32_t Game::REFRESH_RATE = 333;	// ms
const uint32_t Game::MOTION_PERIOD = 15;	// ms

bool Game::init(const GameConfig::Config_t & cfg) {
	if(!loadKeys(cfg.m_Keys)) {
		std::cerr << "loadKeys() failed." << std::endl;
		return false;
	}
	if(!createImages(cfg.m_Img)) {
		std::cerr << "Game:::init.createImages() failed." << std::endl;
		return false;
	}
	const Layout::GridData_t &motion_grid = Layout::getGridData();

	if(!m_ShipAction.init(&m_Ship, Layout::getEnemyRelPos(0), Layout::getGridSize(), Layout::getShipSpeed(), motion_grid)) {
		std::cerr << "Game::createImages.m_ShipAction.init() failed"<< std::endl;
		return false;
	}

	if(!createTexts(cfg.m_Text)) {
		std::cerr << "Game:::init.createTexts() failed." << std::endl;
		return false;
	}
	if(!initButtons()) {
		std::cerr << "Game:::init.initButtons() failed." << std::endl;
		return false;
	}
	if(!initInput()) {
		std::cerr << "Game:::init.initInput() failed." << std::endl;
		return false;
	}
	if(!initTimers()) {
		std::cerr << "Game:::init.initTimers() failed." << std::endl;
		return false;
	}

	m_FPS.init();
	return true;
}

bool Game::events(const InputEvent & event, bool & exit) {
	const auto it = m_Keys.find(event.m_Key);
	if(m_Keys.end() != it) {
		setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, it->second);
	}
	exit = exitRequest();
	return true;
}

bool Game::draw() const {
	//m_Img[GameConfig::IMG_BACKGROUND_INDX].draw();
	m_Img[GameConfig::IMG_GRID_BKGRND_INDX].draw();
	m_Img[GameConfig::IMG_CROSSFIRE_INDX].draw();
	m_Img[GameConfig::IMG_GRID_INDX].draw();
	m_Ship.draw();
	for(auto & t : m_Text) {
		t.draw();
	}
	return true;
}

bool Game::new_frame() {
	m_FPS.newFrame();
	return true;
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
	return true;
}

bool Game::createImages(const GameConfig::ImgRes_t & cfg) {
	for(const auto & [key, data]: cfg) {
		const auto & config = Layout::getImgData(key);
		if(GameConfig::IMG_SHIP_INDX == key) {
			if(!m_Ship.create(data, config.m_Pos, true)) {
				std::cerr << "Game::createImages.m_Ship.create() failed"<< std::endl;
				return false;
			}
		} else {
			if(!m_Img[key].create(data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			if(FULL_OPACITY != config.m_Alpha) {
				m_Img[GameConfig::IMG_GRID_BKGRND_INDX].activateAlphaModulation();
				m_Img[GameConfig::IMG_GRID_BKGRND_INDX].setOpacity(config.m_Alpha);
			}
		}
	}
	return true;
}

bool Game::createTexts(const GameConfig::TextRes_t & cfg) {
	for(const auto & [key, data]: cfg) {
		const auto & config = Layout::getTextData(key);
		if(!m_Text[key].create(config.m_Text, config.m_Color, data, config.m_Pos)) {
			std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
			return false;
		}
	}
	return true;
}

bool Game::initButtons() {
	return true;
}

bool Game::initInput() {
	return true;
}

bool Game::initTimers() {
#if 0
	if(!m_RefreshTimer.start(REFRESH_RATE, Timer2::TimerMode_t::RELOAD, std::bind(&Game::onFPS_Timeout, this, std::placeholders::_1))) {
		std::cerr << "startTimer() failed." << std::endl;
		return false;
	}
#endif
	if(!m_MotionTimer.start(MOTION_PERIOD, Timer2::TimerMode_t::RELOAD, std::bind(&Game::onMotion_Timeout, this, std::placeholders::_1))) {
		std::cerr << "startTimer() failed." << std::endl;
		return false;
	}
	return true;
}

bool Game::exitRequest() const {
	return !!(GameConfig::KEY_EXIT_MASK & m_KeysMask);
}

void Game::setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask) {
	if(pressed) {
		switch(key_mask) {
		case GameConfig::KEY_UP_MASK:
			std::cout << "New keyboard event MOVE_UP" << std::endl;
			m_ShipAction.event(Action_t::MOVE_UP);
			break;
		case GameConfig::KEY_DOWN_MASK:
			std::cout << "New keyboard event MOVE_DOWN" << std::endl;
			m_ShipAction.event(Action_t::MOVE_DOWN);
			break;
		case GameConfig::KEY_LEFT_MASK:
			std::cout << "New keyboard event MOVE_LEFT" << std::endl;
			m_ShipAction.event(Action_t::MOVE_LEFT);
			break;
		case GameConfig::KEY_RIGHT_MASK:
			std::cout << "New keyboard event MOVE_RIGHT" << std::endl;
			m_ShipAction.event(Action_t::MOVE_RIGHT);
			break;
		case GameConfig::KEY_FIRE_UP_MASK:
			std::cout << "New keyboard event FIRE_UP" << std::endl;
			m_ShipAction.event(Action_t::FIRE_UP);
			break;
		case GameConfig::KEY_FIRE_DOWN_MASK:
			std::cout << "New keyboard event FIRE_DOWN" << std::endl;
			m_ShipAction.event(Action_t::FIRE_DOWN);
			break;
		case GameConfig::KEY_FIRE_LEFT_MASK:
			std::cout << "New keyboard event FIRE_LEFT" << std::endl;
			m_ShipAction.event(Action_t::FIRE_LEFT);
			break;
		case GameConfig::KEY_FIRE_RIGHT_MASK:
			std::cout << "New keyboard event FIRE_RIGHT" << std::endl;
			m_ShipAction.event(Action_t::FIRE_RIGHT);
			break;
		default:
			break;
		}
		m_KeysMask |=  key_mask;
	} else {
		m_KeysMask &= ~key_mask;
	}
}

void Game::onFPS_Timeout([[maybe_unused]]Timer2::TimerHandler_t id) {
	assert((m_RefreshTimer == id) && m_RefreshTimer.isRunning());

	auto text = Layout::getTextData(GameConfig::TEXT_FPS_INDX).m_Text;
	std::ostringstream oss;
	oss.setf(std::ios::fixed);
	oss << std::setprecision(1) << m_FPS;

	text += oss.str();
	m_Text[GameConfig::TEXT_FPS_INDX].setText(text);

	text = Layout::getTextData(GameConfig::TEXT_ACTIVE_TIMER_INDX).m_Text;
	text += std::to_string(Timer2MgrInst::getInstance()->getActive());
	m_Text[GameConfig::TEXT_ACTIVE_TIMER_INDX].setText(text);

	text = Layout::getTextData(GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX).m_Text;
	text += std::to_string(Timer2MgrInst::getInstance()->getMaxActive());
	m_Text[GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX].setText(text);
}

void Game::onMotion_Timeout([[maybe_unused]]Timer2::TimerHandler_t id) {
	assert((m_MotionTimer == id) && m_MotionTimer.isRunning());
	m_ShipAction.tick();
}
