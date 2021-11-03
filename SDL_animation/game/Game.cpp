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

#include "sdl_utils/InputEvent.hpp"

#include "utils/drawing/Color.hpp"
#include "common/CommonDefines.hpp"

bool Game::init(const GameConfig::Config_t & cfg) {
	if(!loadKeys(cfg.m_Keys)) {
		std::cerr << "Game::init.loadKeys() failed." << std::endl;
		return false;
	}
	if(!m_Hero.init(ResurcesId::RUNNING_GIRL_SMALL_IMG)) {
		std::cerr << "Game::init.m_Hero.init() failed." << std::endl;
		return false;
	}
	if(!m_Hero1.init(ResurcesId::RUNNING_GIRL_SMALL_IMG, Point(200, 0))) {
		std::cerr << "Game::init.m_Hero.init() failed." << std::endl;
		return false;
	}
	if(!initImgs()) {
		std::cerr << "Game::init.initImgs() failed." << std::endl;
		return false;
	}
	if(!createTexts()) {
		std::cerr << "Game:::init.createTexts() failed." << std::endl;
		return false;
	}
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
	static int dly = 0;
	if(15 == ++dly) {
		dly = 0;
		m_Hero.run(true);
		m_Hero1.run(false);
		m_Img[IMG_WHEEL_INDX].rotateLeft(15.0);
	}
	m_Img[IMG_WHEEL_INDX].draw();
	m_Hero.draw();
	m_Hero1.draw();
	return true;
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
	return true;
}

bool Game::initImgs() {
	if(!m_Img[IMG_WHEEL_INDX].create(ResurcesId::WHEEL_IMG)) {
		std::cerr << "Game::initImgs.create(ResurcesId::WHEEL_IMG) fault" << std::endl;
		return false;
	}
	m_Img[IMG_WHEEL_INDX].activateAlphaModulation();

	if(!m_Img[IMG_RUNNING_GIRL_BIG_INDX].create(ResurcesId::RUNNING_GIRL_BIG_IMG)) {
		std::cerr << "Game::initImgs.create(ResurcesId::RUNNING_GIRL_BIG_IMG) fault" << std::endl;
		return false;
	}
	m_Img[IMG_RUNNING_GIRL_BIG_INDX].activateAlphaModulation();
	if(!m_Img[IMG_RUNNING_GIRL_SMALL_INDX].create(ResurcesId::RUNNING_GIRL_SMALL_IMG)) {
		std::cerr << "Game::initImgs.create(ResurcesId::RUNNING_GIRL_SMALL_IMG) fault" << std::endl;
		return false;
	}
	m_Img[IMG_RUNNING_GIRL_SMALL_INDX].activateAlphaModulation();
	return true;
}

bool Game::createTexts() {
	if(!m_Text[TEXT_HELLO_INDX].create("Hello world!", Colors::GREEN, ResurcesId::ANGELINE_VINTAGE_160_TTF)) {
		std::cerr << "Game::createTexts.m_Text[TEXT_HELLO_INDX].create() fault"<< std::endl;
		return false;
	}
	if(!m_Text[TEXT_2_INDX].create("Hello world!!", Colors::BLUE, ResurcesId::ANGELINE_VINTAGE_80_TTF)) {
		std::cerr << "Game::createTexts.m_Text[TEXT_2_INDX].create() fault"<< std::endl;
		return false;
	}
	if(!m_Text[TEXT_3_INDX].create("Hello world!!!", Colors::RED, ResurcesId::ANGELINE_VINTAGE_40_TTF)) {
		std::cerr << "Game::createTexts.m_Text[TEXT_3_INDX].create() fault"<< std::endl;
		return false;
	}
	if(!m_Text[TEXT_DYNAMIC_INDX].create("0h", Colors::ORANGE, ResurcesId::ANGELINE_VINTAGE_80_TTF)) {
		std::cerr << "Game::createTexts.m_Text[TEXT_DYNAMIC_INDX].create() fault"<< std::endl;
		return false;
	}
	m_Text[TEXT_DYNAMIC_INDX].activateAlphaModulation();
	return true;
}


bool Game::exitRequest() const {
	return !!(GameConfig::KEY_EXIT_MASK & m_KeysMask);
}

void Game::setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask) {
	if(pressed) {
		m_KeysMask |=  key_mask;
	} else {
		m_KeysMask &= ~key_mask;
	}
}

bool Game::updateDynamicText() {
	if(m_KeysMaskHold != m_KeysMask) {
		m_KeysMaskHold = m_KeysMask;
		std::ostringstream stream_txt;
		stream_txt << std::hex << m_KeysMask << "h" ;
		stream_txt.flush();
		if(!m_Text[TEXT_DYNAMIC_INDX].setText(stream_txt.str())) {
			return false;
		}
		if(m_KeysMaskHold) {
			if(!m_Text[TEXT_DYNAMIC_INDX].setColor(Colors::CYAN)) {
				return false;
			}
		} else {
			if(!m_Text[TEXT_DYNAMIC_INDX].setColor(Colors::ORANGE)) {
				return false;
			}
		}
	}
	return true;
}
