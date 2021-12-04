/*
 * Game.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#define ENA_DEBUG_INFO	1

#include "Game.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>

#include "utils/inc/utils/drawing/DisplayMode.hpp"
#include "sdl_utils/InputEvent.hpp"
#include "../gr_engine/inc/gr_engine/managers/Timer2Mgr.hpp"

#include "utils/drawing/Color.hpp"
#include "common/CommonDefines.hpp"

#include "game/config/Layout.hpp"

#include "game/config/GameConfigDef.hpp"

const uint32_t Game::REFRESH_RATE = 333;	// ms
const uint32_t Game::MOTION_PERIOD = 15;	// ms

bool Game::init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode) {
	Layout::init(display_mode);
	//Widget::setDebug(true);
	if(!m_L1.init(cfg, display_mode)) {
		std::cerr << "Level1 init failed." << std::endl;
		return false;
	}
	if(!m_L2.init(cfg, display_mode)) {
		std::cerr << "Level2 init failed." << std::endl;
		return false;
	}
	if(!loadKeys(cfg.m_Keys)) {
		std::cerr << "loadKeys() failed." << std::endl;
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
	if(!initWidgets(display_mode, cfg.m_Img)) {
		std::cerr << "initWidgets() failed." << std::endl;
		return false;
	}

	m_FPS.init();
	if(!m_CollitionMgr.init(std::bind(&Game::onCB_Ammun, this, std::placeholders::_1),
							std::bind(&Game::onCB_Bonus, this, std::placeholders::_1),
							std::bind(&Game::onCB_Ship, this, std::placeholders::_1),
							std::bind(&Game::onCB_Enemy, this, std::placeholders::_1),
							std::bind(&Game::onCB_Ship2Ship, this, std::placeholders::_1))) {
		std::cerr << "m_CollitionMgr.init() failed." << std::endl;
		return false;
	}
	m_CollitionMgr.addUnits(&m_Ship, m_Enemies.get());

	m_Ship.setBulletsSpeed(Layout::getShipBulletSpeed());
	m_Ship.reload(5);
	m_Ship.setShipSpeed(Layout::getShipSpeed());

	m_Enemies.setShipSpeed(Layout::getEnemySpeed());
	m_Enemies.setBulledSpeed(Layout::getEnemyBulletSpeed());


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
	m_Background.draw();
	m_L1.draw();
	m_L2.draw();
#ifdef DEBUG
	m_GridPoint.draw();
#endif
	m_Bonuses.draw();
	m_Ammunition.draw();
	m_Enemies.draw();
	m_Ship.draw();
	m_ExplosionContainer.draw();
	return true;
}

bool Game::new_frame() {
	m_FPS.newFrame();
	return true;
}

bool Game::processing() {
	std::vector<Widget*> ammun;
	ammun.push_back(&m_Ammunition);
	m_CollitionMgr.processing(m_Ship.getBullets(), m_Enemies.getBullets(),
			m_Enemies.get(), m_Bonuses.getWidgets(), ammun);
	return true;
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
	return true;
}

bool Game::initButtons() {
	return true;
}

bool Game::initInput() {
	return true;
}

bool Game::initTimers() {
#if ENA_DEBUG_INFO
	if(!m_RefreshTimer.start(REFRESH_RATE, Timer2::TimerMode_t::RELOAD, std::bind(&Game::onDebugRefresh, this, std::placeholders::_1))) {
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

bool Game::initWidgets(const DisplayMode::Mode_t & display_mode, const GameConfig::ImgRes_t & cfg) {
	Dimention disp_dim;
	disp_dim.m_W = display_mode.m_W;
	disp_dim.m_H = display_mode.m_H;
	// Init Ship
	{
		const auto it = cfg.find(GameConfig::ImgIndx_t::IMG_SHIP_INDX);
		if(cfg.end() == it) {
			std::cerr << "Can't find ship image resource id" << std::endl;
			return false;
		}
		if(!m_Ship.init(it->second, Layout::getScaleFactor(), Layout::getShipRelPos(), Layout::getGridSize())) {
			std::cerr << "Game::createImages.m_Ship.init() failed"<< std::endl;
			return false;
		}
		const auto it_bullets = cfg.find(GameConfig::ImgIndx_t::IMG_OWN_BULLED_INDX);
		if(cfg.end() == it_bullets) {
			std::cerr << "Can't find ship bullets image resource id" << std::endl;
			return false;
		}
		if(!m_Ship.init_bullet(it_bullets->second, Layout::getScaleFactor(), Layout::getOwnMaxBulled(),
				Layout::getOwnReloadTime(), Layout::getArenaRectangle())) {
			std::cerr << "m_Ship.init_bullet() failed"<< std::endl;
			return false;
		}
		m_Ship.setCallback(std::bind(&Game::onShipFire, this, std::placeholders::_1, std::placeholders::_2));
	}
	// Init Enemies
	{
		std::map<size_t, size_t> enemies_img_id_map;
		for(const auto & [key, data]: cfg) {
			if(GameConfig::IMG_ENEMY1_INDX == key) {
				enemies_img_id_map[key] = data;
			} else if(GameConfig::IMG_ENEMY2_INDX == key) {
				enemies_img_id_map[key] = data;
			} else if(GameConfig::IMG_ENEMY3_INDX == key) {
				enemies_img_id_map[key] = data;
			} else if(GameConfig::IMG_ENEMY4_INDX == key) {
				enemies_img_id_map[key] = data;
			}
		}
		std::vector<size_t> enemies_img_id;
		enemies_img_id.reserve(enemies_img_id_map.size());
		for(const auto & [key, data]: enemies_img_id_map) {
			enemies_img_id.push_back(data);
		}
		std::vector<Point> enemies_pos;
		for(uint8_t i = static_cast<uint8_t>(EnemyId_t::ENEMY1); true; ++i) {
			const auto pos = Layout::getEnemyRelPos(i);
			if(Points::UNDEFINED == pos) {
				break;
			}
			enemies_pos.push_back(pos);
		}

#ifdef DEBUG
		for(const auto e : enemies_img_id) {
			std::cout << "Enemy Img ID " << e << std::endl;
		}
		for(const auto e : enemies_pos) {
			std::cout << "Enemy pos X " << e.m_X << ", Y " << e.m_Y << std::endl;
		}
#endif
		if(!m_Enemies.init(enemies_img_id, Layout::getScaleFactor(), enemies_pos, Layout::getGridSize())) {
			std::cerr << "m_Enemies.init() failed"<< std::endl;
			return false;
		}
		const auto it_bullets = cfg.find(GameConfig::ImgIndx_t::IMG_ENEMY_BULLED_INDX);
		if(cfg.end() == it_bullets) {
			std::cerr << "Can't find enemy bullets image resource id" << std::endl;
			return false;
		}
		if(!m_Enemies.init_bullet(it_bullets->second, Layout::getScaleFactor(), Layout::getEnemyMaxBulled(),
				Layout::getEnemyReloadTime(), Layout::getArenaRectangle())) {
			std::cerr << "m_Enemies.init_bullet() failed"<< std::endl;
			return false;
		}
	}
	// init Background
	{
		const auto it = cfg.find(GameConfig::ImgIndx_t::IMG_ENEMY_BULLED_INDX);
		if(cfg.end() == it) {
			std::cerr << "Can't find grid point image resource id" << std::endl;
			return false;
		}
		const auto & config = Layout::getImgData(0);
		if(!m_Background.init(0, config->m_Alpha, 0.25, disp_dim, Layout::getMotionArea(), m_Ship)) {
			std::cerr << "m_Background.init() failed." << std::endl;
			return false;
		}
	}
	// init ExplosionContainer
	{
		const auto it = cfg.find(GameConfig::ImgIndx_t::IMG_EXPLOSION_INDX);
		if(cfg.end() == it) {
			std::cerr << "Can't find explosion image resource id" << std::endl;
			return false;
		}
		if(!m_ExplosionContainer.init(it->second, Layout::getScaleFactor())) {
			std::cerr << "ExplosionContainer init() failed." << std::endl;
			return false;
		}
	}
	// init Bonuses
	{
		const auto it = cfg.find(GameConfig::ImgIndx_t::IMG_BONUS_INDX);
		if(cfg.end() == it) {
			std::cerr << "Can't find bonus image resource id" << std::endl;
			return false;
		}
		if(!m_Bonuses.init(it->second, Layout::getScaleFactor(), Layout::getBonusRelPosEna(), Layout::getBonusRelPosDis(),
				0, Colors::GREEN)) {
			std::cerr << "m_Bonuses.init() failed"<< std::endl;
			return false;
		}
	}
	// init Ammunition
	{
		const auto it = cfg.find(GameConfig::ImgIndx_t::IMG_AMMU_INDX);
		if(cfg.end() == it) {
			std::cerr << "Can't find bonus image resource id" << std::endl;
			return false;
		}
		if(!m_Ammunition.init(it->second, Layout::getScaleFactor())) {
			std::cerr << "m_Ammunition.init() failed"<< std::endl;
			return false;
		}
	}
#ifdef DEBUG
	// init Grid points
	{
		const auto it = cfg.find(GameConfig::ImgIndx_t::IMG_ENEMY_BULLED_INDX);
		if(cfg.end() == it) {
			std::cerr << "Can't find grid point image resource id" << std::endl;
			return false;
		}
		m_GridPoint.init(it->second);
	}
#endif
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

void Game::onDebugRefresh(Timer2::TimerHandler_t id) {
	if((m_RefreshTimer != id) || !m_RefreshTimer.isRunning()) {
		return;
	}
	if(!m_L2.setFPS(m_FPS)) {
		std::cerr << "Game::createImages() Level2.setFPS() failed"<< std::endl;
	}
	if(!m_L2.setActiveTim(Timer2MgrInst::getInstance()->getActive())) {
		std::cerr << "Game::createImages() Level2.setActiveTim() failed"<< std::endl;
	}
	if(!m_L2.setMaxTim(Timer2MgrInst::getInstance()->getMaxActive())) {
		std::cerr << "Game::createImages() Level2.setActiveTim() failed"<< std::endl;
	}
}

void Game::onMotion_Timeout(Timer2::TimerHandler_t id) {
	if((m_MotionTimer != id) || !m_MotionTimer.isRunning()) {
		return;
	}
	m_Ship.tick();
	m_Enemies.tick();
}

void Game::onShipFire(const Point &pos, int8_t rem) {
	static uint8_t id = 0;
	static uint8_t count = 0;
#ifdef DEBUG
	std::cout << "Shoot start point X " << pos.m_X << " , Y " << pos.m_Y
			  << ", remaining bullets " << static_cast<int32_t>(rem) << std::endl;
#endif
	if(0 > rem) {
		return;
	}
	++count;
	if(!m_Bonuses.getWidgets().empty() && (4 < count)) {
		m_Bonuses.disable();
		count = 0;
	}
	if((6 < count) && (static_cast<uint8_t>(BonusId_t::BONUS_NUMB) > id)) {
		m_Bonuses.enable(static_cast<BonusId_t>(id));
		count = 0;
		++id;
	}
	if(2 == rem) {
		if(!m_Ammunition.show(Geometry::getRotation180(pos, Layout::getArenaRectangle().getCenter()))) {
			std::cerr << "Game::createImages() m_Ammunition.show() failed"<< std::endl;
		}
	}
}

void Game::onAnimation0(Widget * data) {
	data->setVisible(false);
}

void Game::onCB_Ammun([[maybe_unused]]const std::vector<Widget *> &data) {
	m_Ammunition.collision();
	m_Ship.reload(5);
}

void Game::onCB_Bonus([[maybe_unused]]const std::vector<Widget *> &data) {
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
	m_Bonuses.hide(points);
}

void Game::onCB_Ship(const std::vector<Widget *> &data) {
	ExplosionContainer::Callback_t cb;
	assert(2 <= data.size());
	auto it = data.begin();
	if(!m_ExplosionContainer.show(*it, std::bind(&Game::onAnimation0, this, std::placeholders::_1))) {
		std::cerr << "ExplosionContainer show() failed"<< std::endl;
	}
	m_Ship.destroy();
	for(++it; data.end() != it; ++it) {
		assert(*it);
		(*it)->setVisible(false);
	}
}

void Game::onCB_Enemy(const std::vector<Widget *> &data) {
	ExplosionContainer::Callback_t cb;
	assert(2 <= data.size());
	auto it = data.begin();
	if(!m_ExplosionContainer.show(*it, std::bind(&Game::onAnimation0, this, std::placeholders::_1))) {
		std::cerr << "ExplosionContainer show() failed"<< std::endl;
	}
	m_Enemies.destroy(*it);
	for(++it; data.end() != it; ++it) {
		assert(*it);
		(*it)->setVisible(false);
	}
}

void Game::onCB_Ship2Ship(const std::vector<Widget *> &data) {
	ExplosionContainer::Callback_t cb;
	assert(2 <= data.size());
	for(auto e : data) {
		if(!m_ExplosionContainer.show(e, std::bind(&Game::onAnimation0, this, std::placeholders::_1))) {
			std::cerr << "ExplosionContainer show() failed"<< std::endl;
		}
		reinterpret_cast<Ship*>(e)->destroy();
	}
}
