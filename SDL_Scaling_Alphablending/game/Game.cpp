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
	if(!loadImgDimenstion(cfg.m_ImgDimention)) {
		std::cerr << "loadImgDimenstion() failed." << std::endl;
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

bool Game::draw(std::vector<DrawingParams_t> &out) {
	DrawingParams_t data;
	if(GameConfig::KEY_UP_MASK & m_KeysMask) {
		data.m_ResrId = UP_IMG;
		out.push_back(data);
		return true;
	}
	if(GameConfig::KEY_DOWN_MASK & m_KeysMask) {
		data.m_ResrId = DOWN_IMG;
		out.push_back(data);
		return true;
	}
	if(GameConfig::KEY_LEFT_MASK & m_KeysMask) {
		data.m_ResrId = LEFT_IMG;
		out.push_back(data);
		return true;
	}
	if(GameConfig::KEY_RIGHT_MASK & m_KeysMask) {
		data.m_ResrId = RIGHT_IMG;
		out.push_back(data);
		return true;
	}
	data.m_ResrId = IDLE_IMG;
	out.push_back(data);
	data.m_ResrId = L2_IMG;
	data.m_DstRect = getImgDimension(L2_IMG);
	out.push_back(data);
	return true;
}

bool Game::loadImgDimenstion(const GameConfig::ImgDimetionRes_t & cfg) {
	for(const auto & e : cfg) {
		m_ImgDimetion[e.first] = e.second;
	}
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

Rectangle Game::getImgDimension(int32_t id) const {
	auto dim = m_ImgDimetion[id];
	if(dim.m_H && dim.m_W) {
		return Rectangle(0, 0, dim.m_W, dim.m_H);
	}
	return Rectangle::UNDEFINED;
}
