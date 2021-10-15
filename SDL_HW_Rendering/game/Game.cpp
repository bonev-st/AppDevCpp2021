/*
 * Game.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "Game.hpp"

#include <iostream>

#include "sdl_utils/Texture.hpp"
#include "sdl_utils/InputEvent.hpp"

Game::Game() {
}

Game::~Game() {
}

int32_t Game::init(const GameBase::GameConfig& cfg) {
	if(EXIT_SUCCESS != loadResources(cfg.ImgPath)) {
		std::cerr << "app_window.copy failed." << std::endl;
		return EXIT_FAILURE;
	}
	if(EXIT_SUCCESS != loadKeys(cfg.Keys)) {
		std::cerr << "app_window.copy failed." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t Game::events(const InputEvent & event, bool & exit) {
	const auto it = Keys.find(event.m_Key);
	if(Keys.end() != it) {
		setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, it->second);
	}
	exit = exitRequest();
	return EXIT_SUCCESS;
}

int32_t Game::draw(std::vector<DrawingData::Drawing_t> &out) {
	DrawingData::Drawing_t data = {
		.m_Surface = nullptr,
		.m_SrcRect = Rectangle::UNDEFINED,
		.m_DstRect = Rectangle::UNDEFINED
	};

	if(GameBase::KEY_UP_MASK & m_KeysMask) {
		data.m_Surface = m_Image[GameBase::UP_IMG].get();
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	if(GameBase::KEY_DOWN_MASK & m_KeysMask) {
		data.m_Surface = m_Image[GameBase::DOWN_IMG].get();
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	if(GameBase::KEY_LEFT_MASK & m_KeysMask) {
		data.m_Surface = m_Image[GameBase::LEFT_IMG].get();
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	if(GameBase::KEY_RIGHT_MASK & m_KeysMask) {
		data.m_Surface = m_Image[GameBase::RIGHT_IMG].get();
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	data.m_Surface = m_Image[GameBase::IDLE_IMG].get();
	out.push_back(data);
	data.m_Surface = m_Image[GameBase::L2_IMG].get();
	out.push_back(data);
	return EXIT_SUCCESS;
}

int32_t Game::loadResources(const GameBase::ImgRes_t & cfg) {
	for(const auto & e : cfg) {
		m_Image[e.first] = Texture::createSurfaceFromFile(e.second);
		if(nullptr == m_Image[e.first]) {
			std::cerr << "Texture::createSurfaceFromFile failed." << std::endl;
	        return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int32_t Game::loadKeys(const GameBase::KeyRes_t & cfg) {
	Keys = cfg;
	return EXIT_SUCCESS;
}

bool Game::exitRequest() const {
	return !!(GameBase::KEY_EXIT_MASK & m_KeysMask);
}

void Game::setKeyRequest(bool pressed, GameBase::KeyMask_t key_mask) {
	if(pressed) {
		m_KeysMask |=  key_mask;
	} else {
		m_KeysMask &= ~key_mask;
	}
}

