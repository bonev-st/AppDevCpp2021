/*
 * Game.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "Game.hpp"

#include <iostream>

#include "sdl_utils/InputEvent.hpp"

#include "utils/drawing/DrawParams.hpp"

bool Game::init(const GameConfig::Config_t & cfg) {
	if(!loadKeys(cfg.m_Keys)) {
		std::cerr << "loadKeys() failed." << std::endl;
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

bool Game::draw([[maybe_unused]]std::vector<DrawParams_t> &out) {
#if 0
	if(GameConfig::KEY_UP_MASK & m_KeysMask) {
		out.push_back(m_Img[ResurcesId::UP_IMG]);
		return true;
	}
	if(GameConfig::KEY_DOWN_MASK & m_KeysMask) {
		out.push_back(m_Img[ResurcesId::DOWN_IMG]);
		return true;
	}
	if(GameConfig::KEY_LEFT_MASK & m_KeysMask) {
		out.push_back(m_Img[ResurcesId::LEFT_IMG]);
		return true;
	}
	if(GameConfig::KEY_RIGHT_MASK & m_KeysMask) {
		out.push_back(m_Img[ResurcesId::RIGHT_IMG]);
		return true;
	}

	if(GameConfig::KEY_MOVE_UP_MASK & m_KeysMask) {
		m_Img[ResurcesId::IDLE_IMG].m_DstRect.m_Pos.m_Y -= MOVE_STEP;
	}
	if(GameConfig::KEY_MOVE_DOWN_MASK & m_KeysMask) {
		m_Img[ResurcesId::IDLE_IMG].m_DstRect.m_Pos.m_Y += MOVE_STEP;
	}
	if(GameConfig::KEY_MOVE_LEFT_MASK & m_KeysMask) {
		m_Img[ResurcesId::IDLE_IMG].m_DstRect.m_Pos.m_X -= MOVE_STEP;
	}
	if(GameConfig::KEY_MOVE_RIGHT_MASK & m_KeysMask) {
		m_Img[ResurcesId::IDLE_IMG].m_DstRect.m_Pos.m_X += MOVE_STEP;
	}
	if(GameConfig::KEY_ZOOM_UP_MASK & m_KeysMask) {
		m_Img[ResurcesId::IDLE_IMG].m_DstRect.scale(1.01);
	}
	if(GameConfig::KEY_ZOOM_DOWN_MASK & m_KeysMask) {
		m_Img[ResurcesId::IDLE_IMG].m_DstRect.scale(0.99);
	}
	if(GameConfig::KEY_OPACITY_UP_MASK & m_KeysMask) {
		auto & opacity = m_Img[ResurcesId::IDLE_IMG].m_Opacity;
		opacity += 1;
		if(FULL_OPACITY < opacity) {
			opacity = FULL_OPACITY;
		}
	}
	if(GameConfig::KEY_OPACITY_DOWN_MASK & m_KeysMask) {
		auto & opacity = m_Img[ResurcesId::IDLE_IMG].m_Opacity;
		opacity -= 1;
		if(ZERO_OPACITY > opacity) {
			opacity = ZERO_OPACITY;
		}
	}
	out.push_back(m_Img[ResurcesId::IDLE_IMG]);
	out.push_back(m_Img[ResurcesId::L2_IMG]);
#endif
	return true;
}

bool Game::loadKeys(const GameConfig::KeyRes_t & cfg) {
	m_Keys = cfg;
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
