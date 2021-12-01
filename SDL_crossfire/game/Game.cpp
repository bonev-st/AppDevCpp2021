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

#include "utils/inc/utils/drawing/DisplayMode.hpp"
#include "sdl_utils/InputEvent.hpp"
#include "manager_utils/managers/Timer2Mgr.hpp"
#include "utils/drawing/Color.hpp"
#include "common/CommonDefines.hpp"

#include "game/config/Layout.hpp"

const uint32_t Game::REFRESH_RATE = 333;	// ms
const uint32_t Game::MOTION_PERIOD = 15;	// ms

bool Game::init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode) {
	//Widget::setDebug(true);
	Layout::init(display_mode);
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
	Dimention disp_dim;
	disp_dim.m_W = display_mode.m_W;
	disp_dim.m_H = display_mode.m_H;
	{
		const auto & config = Layout::getImgData(0);
		if(!m_Background.init(0, config.m_Alpha, 0.25, disp_dim, Layout::getMotionArea(), m_Ship)) {
			std::cerr << "m_Background.init() failed." << std::endl;
			return false;
		}
	}

	if(!m_BackgroundFieldImageL1.create(2)) {
		std::cerr << "m_BackgroundFieldImageL1.create() failed." << std::endl;
	}
	if(!m_ScaledBackgroundFieldImageL1.init(Layout::getScaleFactor(),&m_BackgroundFieldImageL1)) {
		std::cerr << "m_BackgroundFieldImageL1.create() failed." << std::endl;
	}
	{
		const auto & config = Layout::getImgData(2);
		m_ScaledBackgroundFieldImageL1.setOpacity(config.m_Alpha);
		m_ScaledBackgroundFieldImageL1.setPosition(config.m_Pos);
	}

	if(!m_CrossfireImageL1.create(1)) {
		std::cerr << "m_BackgroundFieldImageL1.create() failed." << std::endl;
	}
	if(!m_ScaledCrossfireImageL1.init(Layout::getScaleFactor(),&m_CrossfireImageL1)) {
		std::cerr << "m_BackgroundFieldImageL1.create() failed." << std::endl;
	}
	{
		const auto & config = Layout::getImgData(1);
		m_ScaledCrossfireImageL1.setOpacity(config.m_Alpha);
		m_ScaledCrossfireImageL1.setPosition(config.m_Pos);
	}

	if(!m_GridImageL1.create(3)) {
		std::cerr << "m_BackgroundFieldImageL1.create() failed." << std::endl;
	}
	if(!m_ScaledGridImageL1.init(Layout::getScaleFactor(),&m_GridImageL1)) {
		std::cerr << "m_BackgroundFieldImageL1.create() failed." << std::endl;
	}
	{
		const auto & config = Layout::getImgData(3);
		m_ScaledGridImageL1.setOpacity(config.m_Alpha);
		m_ScaledGridImageL1.setPosition(config.m_Pos);
	}

	if(!m_ScaledTextScoreLableL1.init(Layout::getScaleFactor(),&m_TextScoreLableL1)) {
		std::cerr << "m_ScaledTextScoreLableL1.create() failed." << std::endl;
	}
	if(!m_ScaledTextHiScoreLableL1.init(Layout::getScaleFactor(),&m_TextHiScoreLableL1)) {
		std::cerr << "m_ScaledTextScoreLableL1.create() failed." << std::endl;
	}
	if(!m_ScaledTextShipsLableL1.init(Layout::getScaleFactor(),&m_TextShipsLableL1)) {
		std::cerr << "m_ScaledTextScoreLableL1.create() failed." << std::endl;
	}
	if(!m_ScaledTextScoreL2.init(Layout::getScaleFactor(),&m_TextScoreL2)) {
		std::cerr << "m_ScaledTextScoreLableL1.create() failed." << std::endl;
	}
	if(!m_ScaledTextHiScoreL2.init(Layout::getScaleFactor(),&m_TextHiScoreL2)) {
		std::cerr << "m_ScaledTextScoreLableL1.create() failed." << std::endl;
	}
	if(!m_ScaledTextShipsL2.init(Layout::getScaleFactor(),&m_TextShipsL2)) {
		std::cerr << "m_ScaledTextScoreLableL1.create() failed." << std::endl;
	}
	if(!m_ScaledTextFPSL2.init(Layout::getScaleFactor(),&m_TextFPSL2)) {
		std::cerr << "m_ScaledTextScoreLableL1.create() failed." << std::endl;
	}
	if(!m_ScaledTextActiveTimL2.init(Layout::getScaleFactor(),&m_TextActiveTimL2)) {
		std::cerr << "m_ScaledTextScoreLableL1.create() failed." << std::endl;
	}
	if(!m_ScaledTextMaxTimL2.init(Layout::getScaleFactor(),&m_TextMaxTimL2)) {
		std::cerr << "m_ScaledTextScoreLableL1.create() failed." << std::endl;
	}
	{
		const auto & config = Layout::getTextData(GameConfig::TEXT_SCORE_LABLE_INDX);
		m_ScaledTextScoreLableL1.setPosition(config.m_Pos);
	}
	{
		const auto & config = Layout::getTextData(GameConfig::TEXT_SCORE_INDX);
		m_ScaledTextScoreL2.setPosition(config.m_Pos);
	}
	{
		const auto & config = Layout::getTextData(GameConfig::TEXT_HI_SCORE_LABLE_INDX);
		m_ScaledTextHiScoreLableL1.setPosition(config.m_Pos);
	}
	{
		const auto & config = Layout::getTextData(GameConfig::TEXT_HI_SCORE_INDX);
		m_ScaledTextHiScoreL2.setPosition(config.m_Pos);
	}
	{
		const auto & config = Layout::getTextData(GameConfig::TEXT_SHIPS_LABLE_INDX);
		m_ScaledTextShipsLableL1.setPosition(config.m_Pos);
	}
	{
		const auto & config = Layout::getTextData(GameConfig::TEXT_SHIPS_INDX);
		m_ScaledTextShipsL2.setPosition(config.m_Pos);
	}
	{
		const auto & config = Layout::getTextData(GameConfig::TEXT_FPS_INDX);
		m_ScaledTextFPSL2.setPosition(config.m_Pos);
	}
	{
		const auto & config = Layout::getTextData(GameConfig::TEXT_ACTIVE_TIMER_INDX);
		m_ScaledTextActiveTimL2.setPosition(config.m_Pos);
	}
	{
		const auto & config = Layout::getTextData(GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX);
		m_ScaledTextMaxTimL2.setPosition(config.m_Pos);
	}

	if(!m_L1.init(disp_dim, Points::ZERO)) {
		std::cerr << "m_L1.init() failed." << std::endl;
	}
	m_L1.add(&m_ScaledBackgroundFieldImageL1);
	m_L1.add(&m_ScaledCrossfireImageL1);
	//m_L1.add(&m_ScaledGridImageL1);
	m_L1.add(&m_ScaledTextScoreLableL1);
	m_L1.add(&m_ScaledTextHiScoreLableL1);
	m_L1.add(&m_ScaledTextShipsLableL1);

	if(!m_L2.init(disp_dim, Points::ZERO)) {
		std::cerr << "m_L2.init() failed." << std::endl;
	}
	m_L2.add(&m_ScaledTextScoreL2);
	m_L2.add(&m_ScaledTextHiScoreL2);
	m_L2.add(&m_ScaledTextShipsL2);
	m_L2.add(&m_ScaledTextFPSL2);
	m_L2.add(&m_ScaledTextActiveTimL2);
	m_L2.add(&m_ScaledTextMaxTimL2);

	//m_L2.add(&m_Ship);

	m_Ship.reload(5);
	m_Ship.setCallback(std::bind(&Game::onShipFire, this, std::placeholders::_1, std::placeholders::_2));

	m_Enemy.reload(100);

	m_FPS.init();
	m_GridPoint.init(12);

	if(!m_ExplosionContainer.init(13, Layout::getScaleFactor())) {
		std::cerr << "ExplosionContainer init() failed." << std::endl;
		return false;
	}

	if(!m_CollitionMgr.init(std::bind(&Game::onCB_Ammun, this, std::placeholders::_1),
							std::bind(&Game::onCB_Bonus, this, std::placeholders::_1),
							std::bind(&Game::onCB_Ship, this, std::placeholders::_1),
							std::bind(&Game::onCB_Enemy, this, std::placeholders::_1),
							std::bind(&Game::onCB_Ship2Ship, this, std::placeholders::_1))) {
		std::cerr << "m_CollitionMgr.init() failed." << std::endl;
		return false;
	}

	std::vector<Widget*> tmp;
	tmp.push_back(&m_Enemy);
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
	m_Background.draw();
	//m_ScaledBackgroundFieldImageL1.draw();
	//m_ScaledCrossfireImageL1.draw();

	//m_ScaledTextScoreLableL1.draw();
	//m_ScaledTextHiScoreLableL1.draw();
	//m_ScaledTextShipsLableL1.draw();
	m_L1.draw();
	m_L2.draw();
	//m_ScaledTextScoreL2.draw();
	//m_ScaledTextHiScoreL2.draw();
	//m_ScaledTextShipsL2.draw();
	//m_ScaledTextFPSL2.draw();
	//m_ScaledTextActiveTimL2.draw();
	//m_ScaledTextMaxTimL2.draw();
	m_ScaledGridImageL1.draw();
	m_Bonuses.draw();
	m_Ammunition.draw();
	m_Ship.draw();
	m_Enemy.draw();
	m_GridPoint.draw();
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
	std::vector<Widget *> enemy;
	if(!m_Enemy.isDestroy()) {
		enemy.push_back(&m_Enemy);
	}
	m_CollitionMgr.processing(m_Ship.getBullets(), m_Enemy.getBullets()
			,enemy , m_Bonuses.getWidgets(), ammun);
	return true;
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
	return true;
}

bool Game::createImages(const GameConfig::ImgRes_t & cfg) {
	size_t bulled_id = INVALID_RESR_ID;
	size_t enemy_bulled_id = INVALID_RESR_ID;
	for(const auto & [key, data]: cfg) {
		if(GameConfig::IMG_SHIP_INDX == key) {
			if(!m_Ship.init(data, Layout::getScaleFactor(), Layout::getShipRelPos(), Layout::getGridSize())) {
				std::cerr << "Game::createImages.m_Ship.init() failed"<< std::endl;
				return false;
			}
			m_Ship.setShipSpeed(Layout::getShipSpeed());
		} else if(GameConfig::IMG_BONUS_INDX == key) {
			if(!m_Bonuses.init(data, Layout::getScaleFactor(), Layout::getBonusRelPosEna(), Layout::getBonusRelPosDis(),
					0, Colors::GREEN)) {
				std::cerr << "Game::createImages() m_Bonuses.init() failed"<< std::endl;
				return false;
			}
		} else if(GameConfig::IMG_OWN_BULLED_INDX == key) {
			bulled_id = data;
		} else if(GameConfig::IMG_ENEMY_BULLED_INDX == key) {
			enemy_bulled_id = data;
		} else if(GameConfig::IMG_AMMU_INDX == key) {
			if(!m_Ammunition.init(data, Layout::getScaleFactor())) {
				std::cerr << "Game::createImages() m_Ammunition.init() failed"<< std::endl;
				return false;
			}
		} else if(GameConfig::IMG_ENEMY1_INDX == key) {
			if(!m_Enemy.init(data, Layout::getScaleFactor(), Point(12,10), Layout::getGridSize())) {
				std::cerr << "Game::createImages.m_Enemy.init() failed"<< std::endl;
				return false;
			}
			m_Enemy.setShipSpeed(Layout::getShipSpeed());
		}
	}
	if((INVALID_RESR_ID == bulled_id) || (INVALID_RESR_ID == enemy_bulled_id)) {
		return false;
	}
	if(!m_Ship.init_bullet(bulled_id, Layout::getScaleFactor(), Layout::getOwnMaxBulled(), Layout::getOwnReloadTime(), Layout::getArenaRectangle())) {
		std::cerr << "Game::createImages() m_Ship.init_bullet() failed"<< std::endl;
		return false;
	}
	m_Ship.setBolletsSpeed(Layout::getShipBulletSpeed());
	if(!m_Enemy.init_bullet(bulled_id, Layout::getScaleFactor(), Layout::getEnemyMaxBulled(), Layout::getEnemyReloadTime(), Layout::getArenaRectangle())) {
		std::cerr << "Game::createImages() m_Enemy.init_bullet() failed"<< std::endl;
		return false;
	}
	m_Ship.setBolletsSpeed(Layout::getEnemyBulletSpeed());
	return true;
}

bool Game::createTexts(const GameConfig::TextRes_t & cfg) {
	for(const auto & [key, data]: cfg) {
		const auto & config = Layout::getTextData(key);
		switch(key) {
		case GameConfig::TEXT_SCORE_LABLE_INDX:
			if(!m_TextScoreLableL1.create(config.m_Text, config.m_Color, data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			break;
		case GameConfig::TEXT_SCORE_INDX:
			if(!m_TextScoreL2.create(config.m_Text, config.m_Color, data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			break;
		case GameConfig::TEXT_HI_SCORE_LABLE_INDX:
			if(!m_TextHiScoreLableL1.create(config.m_Text, config.m_Color, data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			break;
		case GameConfig::TEXT_HI_SCORE_INDX:
			if(!m_TextHiScoreL2.create(config.m_Text, config.m_Color, data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			break;
		case GameConfig::TEXT_SHIPS_LABLE_INDX:
			if(!m_TextShipsLableL1.create(config.m_Text, config.m_Color, data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			break;
		case GameConfig::TEXT_SHIPS_INDX:
			if(!m_TextShipsL2.create(config.m_Text, config.m_Color, data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			break;
		case GameConfig::TEXT_FPS_INDX:
			if(!m_TextFPSL2.create(config.m_Text, config.m_Color, data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			break;
		case GameConfig::TEXT_ACTIVE_TIMER_INDX:
			if(!m_TextActiveTimL2.create(config.m_Text, config.m_Color, data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			break;
		case GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX:
			if(!m_TextMaxTimL2.create(config.m_Text, config.m_Color, data, config.m_Pos)) {
				std::cerr << "Game::createImages.m_Img[" << key << "].create() failed"<< std::endl;
				return false;
			}
			break;
		default:
			break;
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

	std::string text = Layout::getTextData(GameConfig::TEXT_FPS_INDX).m_Text;
	std::ostringstream oss;
	oss.setf(std::ios::fixed);
	oss << std::setprecision(1) << m_FPS;

	text += oss.str();
	m_TextFPSL2.setText(text);

	text = Layout::getTextData(GameConfig::TEXT_ACTIVE_TIMER_INDX).m_Text;
	text += std::to_string(Timer2MgrInst::getInstance()->getActive());
	m_TextActiveTimL2.setText(text);

	text = Layout::getTextData(GameConfig::TEXT_MAX_ACTIVE_TIMER_INDX).m_Text;
	text += std::to_string(Timer2MgrInst::getInstance()->getMaxActive());
	m_TextMaxTimL2.setText(text);
}

void Game::onMotion_Timeout([[maybe_unused]]Timer2::TimerHandler_t id) {
	assert((m_MotionTimer == id) && m_MotionTimer.isRunning());
	m_Ship.tick();
	m_Enemy.tick();
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
	m_Enemy.destroy();
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
