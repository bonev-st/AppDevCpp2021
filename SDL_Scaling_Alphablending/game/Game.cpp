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

int32_t Game::init(const GameConfig::Config_t & cfg) {
	if(!loadKeys(cfg.m_Keys)) {
		std::cerr << "loadKeys() failed." << std::endl;
		return EXIT_FAILURE;
	}
	if(!loadImgDimenstion(cfg.m_ImgDimention)) {
		std::cerr << "loadImgDimenstion() failed." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t Game::events(const InputEvent & event, bool & exit) {
	const auto it = m_Keys.find(event.m_Key);
	if(m_Keys.end() != it) {
		setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, it->second);
	}
	exit = exitRequest();
	return EXIT_SUCCESS;
}

int32_t Game::draw(std::vector<DrawingParams_t> &out) {
	DrawingParams_t data;
	if(GameConfig::KEY_UP_MASK & m_KeysMask) {
		data.m_ResrId = UP_IMG;
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	if(GameConfig::KEY_DOWN_MASK & m_KeysMask) {
		data.m_ResrId = DOWN_IMG;
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	if(GameConfig::KEY_LEFT_MASK & m_KeysMask) {
		data.m_ResrId = LEFT_IMG;
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	if(GameConfig::KEY_RIGHT_MASK & m_KeysMask) {
		data.m_ResrId = RIGHT_IMG;
		out.push_back(data);
		return EXIT_SUCCESS;
	}

	data.m_ResrId = IDLE_IMG;
	out.push_back(data);
	data.m_ResrId = L2_IMG;
	data.m_DstRect = Rectangle(0, 0, m_ImgDimetion[L2_IMG].m_W, m_ImgDimetion[L2_IMG].m_H);
	out.push_back(data);

	return EXIT_SUCCESS;
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

