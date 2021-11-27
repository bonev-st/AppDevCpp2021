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
	Widget::setDebug(true);
	m_Scale = 2.0;
	if(!loadKeys(cfg.m_Keys)) {
		std::cerr << "loadKeys() failed." << std::endl;
		return false;
	}
	if(!createImages(cfg.m_Img)) {
		std::cerr << "createImages() failed." << std::endl;
		return false;
	}
	if(!createTexts(cfg.m_Text)) {
		std::cerr << "createTexts() failed." << std::endl;
		return false;
	}
	if(!initButtons()) {
		std::cerr << "initButtons() failed." << std::endl;
		return false;
	}
	if(!initInput()) {
		std::cerr << "initInput() failed." << std::endl;
		return false;
	}
	if(!initTimers()) {
		std::cerr << "initTimers() failed." << std::endl;
		return false;
	}
	m_Ship.reload(5);
	m_Ship.setCallback(std::bind(&Game::onShipFire, this, std::placeholders::_1, std::placeholders::_2));
	m_FPS.init();

	if(!m_CollitionMgr.init(std::bind(&Game::onCB_Ammun, this, std::placeholders::_1),
							std::bind(&Game::onCB_Bonus, this, std::placeholders::_1),
							std::bind(&Game::onCB_Ship, this, std::placeholders::_1),
							std::bind(&Game::onCB_Enemy, this, std::placeholders::_1))) {
		std::cerr << "m_CollitionMgr.init() failed." << std::endl;
		return false;
	}

	const std::vector<const Widget*> tmp;
	m_CollitionMgr.addUnits(&m_Ship, tmp);
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

bool Game::draw() {
	//m_Img[GameConfig::IMG_BACKGROUND_INDX].draw();
	m_Img[GameConfig::IMG_GRID_BKGRND_INDX].draw();
	m_Img[GameConfig::IMG_CROSSFIRE_INDX].draw();
	m_Img[GameConfig::IMG_GRID_INDX].draw();
	m_Bonuses.draw();
	m_Ammunition.draw();
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

bool Game::processing() {
	m_CollitionMgr.processing();
	return true;
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
	return true;
}

bool Game::createImages(const GameConfig::ImgRes_t & cfg) {
	size_t bulled_id = INVALID_RESR_ID;
	for(const auto & [key, data]: cfg) {
		const auto & config = Layout::getImgData(key);
		if(GameConfig::IMG_SHIP_INDX == key) {
			if(!m_Ship.init(data, m_Scale, Layout::getShipRelPos(), Layout::getGridSize(), Layout::getShipSpeed())) {
				std::cerr << "Game::createImages.m_Ship.init() failed"<< std::endl;
				return false;
			}
		} else if(GameConfig::IMG_BONUS_INDX == key) {
			if(!m_Bonuses.init(data, m_Scale, Layout::getBonusRelPosEna(), Layout::getBonusRelPosDis(),
					0, Color::GREEN)) {
				std::cerr << "Game::createImages() m_Bonuses.init() failed"<< std::endl;
				return false;
			}
		} else if(GameConfig::IMG_OWN_BULLED_INDX == key) {
			bulled_id = data;
		} else if(GameConfig::IMG_AMMU_INDX == key) {
			if(!m_Ammunition.init(data, m_Scale)) {
				std::cerr << "Game::createImages() m_Ammunition.init() failed"<< std::endl;
				return false;
			}
		} else {
			if(!m_Img[key].create(data, config.m_Pos)) {
				std::cerr << "Game::createImages() m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			if(FULL_OPACITY != config.m_Alpha) {
				m_Img[GameConfig::IMG_GRID_BKGRND_INDX].activateAlphaModulation();
				m_Img[GameConfig::IMG_GRID_BKGRND_INDX].setOpacity(config.m_Alpha);
			}
		}
	}
	if(INVALID_RESR_ID == bulled_id) {
		return false;
	}
	if(!m_Ship.init_bullet(bulled_id, m_Scale, Layout::getShipBulletSpeed(), Layout::getOwnMaxBulled(), Layout::getOwnReloadTime(), Layout::getArenaRectangle())) {
		std::cerr << "Game::createImages() m_Ship.init_bullet() failed"<< std::endl;
		return false;
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
#if 1
	if(!m_RefreshTimer.start(REFRESH_RATE, Timer2::TimerMode_t::RELOAD, std::bind(&Game::onFPS_Timeout, this, std::placeholders::_1))) {
		std::cerr << "startTimer() failed." << std::endl;
		return false;
	}
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
			m_Ship.event(Action_t::MOVE_UP);
			break;
		case GameConfig::KEY_DOWN_MASK:
			std::cout << "New keyboard event MOVE_DOWN" << std::endl;
			m_Ship.event(Action_t::MOVE_DOWN);
			break;
		case GameConfig::KEY_LEFT_MASK:
			std::cout << "New keyboard event MOVE_LEFT" << std::endl;
			m_Ship.event(Action_t::MOVE_LEFT);
			break;
		case GameConfig::KEY_RIGHT_MASK:
			std::cout << "New keyboard event MOVE_RIGHT" << std::endl;
			m_Ship.event(Action_t::MOVE_RIGHT);
			break;
		case GameConfig::KEY_FIRE_UP_MASK:
			std::cout << "New keyboard event FIRE_UP" << std::endl;
			m_Ship.event(Action_t::FIRE_UP);
			break;
		case GameConfig::KEY_FIRE_DOWN_MASK:
			std::cout << "New keyboard event FIRE_DOWN" << std::endl;
			m_Ship.event(Action_t::FIRE_DOWN);
			break;
		case GameConfig::KEY_FIRE_LEFT_MASK:
			std::cout << "New keyboard event FIRE_LEFT" << std::endl;
			m_Ship.event(Action_t::FIRE_LEFT);
			break;
		case GameConfig::KEY_FIRE_RIGHT_MASK:
			std::cout << "New keyboard event FIRE_RIGHT" << std::endl;
			m_Ship.event(Action_t::FIRE_RIGHT);
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
	m_Ship.tick();
}

void Game::onShipFire(const Point &pos, int8_t rem) {
	static uint8_t id = 0;
	static uint8_t count = 0;

	std::cout << "Shoot start point X " << pos.m_X << " , Y " << pos.m_Y
			  << ", remaining bullets " << static_cast<int32_t>(rem) << std::endl;
	if(0 > rem) {
		return;
	}
	++count;
	if(m_Bonuses.getEnabledWidget() && (4 < count)) {
		m_CollitionMgr.removeBonus(m_Bonuses.getEnabledWidget());
		m_Bonuses.disable();
		count = 0;
	}
	if((6 < count) && (static_cast<uint8_t>(BonusId_t::BONUS_NUMB) > id)) {
		m_Bonuses.enable(static_cast<BonusId_t>(id));
		m_CollitionMgr.addBonus(m_Bonuses.getEnabledWidget());
		count = 0;
		++id;
	}
	if(2 == rem) {
		if(!m_Ammunition.show(Geometry::getRotation180(pos, Layout::getArenaRectangle().getCenter()))) {
			std::cerr << "Game::createImages() m_Ammunition.show() failed"<< std::endl;
		}
		m_CollitionMgr.addAmmun(&m_Ammunition);
	}
}

void Game::onCB_Ammun([[maybe_unused]]const std::vector<const Widget *> data) {
	m_CollitionMgr.removeAmmun(&m_Ammunition);
	m_Ammunition.collision();
	m_Ship.reload(5);
}

void Game::onCB_Bonus([[maybe_unused]]const std::vector<const Widget *> data) {
	uint32_t points = 0;
	switch(m_Bonuses.getId()) {
	case BonusId_t::BONUS1:
		points = 100;
		break;
	case BonusId_t::BONUS2:
		points = 200;
		break;
	case BonusId_t::BONUS3:
		points = 400;
		break;
	case BonusId_t::BONUS4:
		points = 800;
		break;
	default:
		assert(0);
	}
	m_CollitionMgr.removeBonus(m_Bonuses.getEnabledWidget());
	m_Bonuses.hide(points);
}

void Game::onCB_Ship([[maybe_unused]]const std::vector<const Widget *> data) {

}

void Game::onCB_Enemy([[maybe_unused]]const std::vector<const Widget *> data) {

}
