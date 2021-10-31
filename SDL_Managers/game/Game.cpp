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
		std::cerr << "Game::init::loadKeys() failed." << std::endl;
		return false;
	}
	if(!initImgs()) {
		std::cerr << "Game::init::initImgs() failed." << std::endl;
		return false;
	}
	if(!createTexts()) {
		std::cerr << "Game:::init::createTexts() failed." << std::endl;
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
	if(GameConfig::KEY_UP_MASK & m_KeysMask) {
		m_Text[TEXT_DYNAMIC_INDX].moveUp(MOVE_STEP);
	}
	if(GameConfig::KEY_DOWN_MASK & m_KeysMask) {
		m_Text[TEXT_DYNAMIC_INDX].moveDown(MOVE_STEP);
	}
	if(GameConfig::KEY_LEFT_MASK & m_KeysMask) {
		m_Text[TEXT_DYNAMIC_INDX].moveLeft(MOVE_STEP);
	}
	if(GameConfig::KEY_RIGHT_MASK & m_KeysMask) {
		m_Text[TEXT_DYNAMIC_INDX].moveRight(MOVE_STEP);
	}
	if(GameConfig::KEY_MOVE_UP_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].moveUp(MOVE_STEP);
	}
	if(GameConfig::KEY_MOVE_DOWN_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].moveDown(MOVE_STEP);
	}
	if(GameConfig::KEY_MOVE_LEFT_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].moveLeft(MOVE_STEP);
	}
	if(GameConfig::KEY_MOVE_RIGHT_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].moveRight(MOVE_STEP);
	}
	if(GameConfig::KEY_ZOOM_UP_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].scale(1.01);
	}
	if(GameConfig::KEY_ZOOM_DOWN_MASK & m_KeysMask) {
		m_Img[IMG_BACKGROUND_INDX].scale(0.99);
	}
	if(GameConfig::KEY_OPACITY_UP_MASK & m_KeysMask) {
		auto opacity = m_Img[IMG_BACKGROUND_INDX].getOpacity();
		opacity += 1;
		if(FULL_OPACITY < opacity) {
			opacity = FULL_OPACITY;
		}
		m_Img[IMG_BACKGROUND_INDX].setOpacity(opacity);
	}
	if(GameConfig::KEY_OPACITY_DOWN_MASK & m_KeysMask) {
		auto opacity = m_Img[IMG_BACKGROUND_INDX].getOpacity();
		opacity -= 1;
		if(ZERO_OPACITY > opacity) {
			opacity = ZERO_OPACITY;
		}
		m_Img[IMG_BACKGROUND_INDX].setOpacity(opacity);
	}
	if(GameConfig::KEY_T_OPACITY_UP_MASK & m_KeysMask) {
		auto opacity = m_Text[TEXT_DYNAMIC_INDX].getOpacity();
		opacity += 1;
		if(FULL_OPACITY < opacity) {
			opacity = FULL_OPACITY;
		}
		m_Text[TEXT_DYNAMIC_INDX].setOpacity(opacity);
	}
	if(GameConfig::KEY_T_OPACITY_DOWN_MASK & m_KeysMask) {
		auto opacity = m_Text[TEXT_DYNAMIC_INDX].getOpacity();
		opacity -= 1;
		if(ZERO_OPACITY > opacity) {
			opacity = ZERO_OPACITY;
		}
		m_Text[TEXT_DYNAMIC_INDX].setOpacity(opacity);
	}

	if(!updateDynamicText()) {
		std::cerr << "Game::draw::updateDynamicText() failed." << std::endl;
		return false;
	}

	m_Img[IMG_BACKGROUND_INDX].draw();
	m_Img[IMG_L2_INDX].draw();
	m_Text[TEXT_HELLO_INDX].draw();
	m_Text[TEXT_2_INDX].draw();
	m_Text[TEXT_3_INDX].draw();
	m_Text[TEXT_DYNAMIC_INDX].draw();
	return true;
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
	return true;
}

bool Game::initImgs() {
	if(!m_Img[IMG_BACKGROUND_INDX].create(ResurcesId::IDLE_IMG)) {
		std::cerr << "Game::initImgs.create(ResurcesId::IDLE_IMG) fault" << std::endl;
		return false;
	}
	m_Img[IMG_BACKGROUND_INDX].activateAlphaModulation();
	if(!m_Img[IMG_L2_INDX].create(ResurcesId::L2_IMG)) {
		std::cerr << "Game::initImgs.create(ResurcesId::L2_IMG) fault" << std::endl;
		return false;
	}
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
