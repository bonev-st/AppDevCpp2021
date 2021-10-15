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

int32_t Game::init(const GameConfig& cfg) {
	if(EXIT_SUCCESS != loadResources(cfg.ImgPath)) {
		std::cerr << "app_window.copy failed." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t Game::events(const InputEvent & event, bool & exit) {
	int32_t rc  = EXIT_SUCCESS;
	do {
		if((exit = exitRequest(event))) {
			break;
		}
		if(Keyboard::KEY_LEFT == event.m_Key) {
			setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, KEY_LEFT_MASK);
			break;
		}
		if(Keyboard::KEY_RIGHT == event.m_Key) {
			setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, KEY_RIGHT_MASK);
			break;
		}
		if(Keyboard::KEY_UP == event.m_Key) {
			setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, KEY_UP_MASK);
			break;
		}
		if(Keyboard::KEY_DOWN == event.m_Key) {
			setKeyRequest(TouchEvent::KEYBOARD_PRESS == event.m_Type, KEY_DOWN_MASK);
			break;
		}
	} while(0);
	return rc;
}

int32_t Game::draw(std::vector<DrawingData::Drawing_t> &out) {
	DrawingData::Drawing_t data = {
		.m_Surface = nullptr,
		.m_SrcRect = Rectangle::UNDEFINED,
		.m_DstRect = Rectangle::UNDEFINED
	};

	if(KEY_UP_MASK & m_KeysMask) {
		data.m_Surface = m_Image[UP_IMG].get();
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	if(KEY_DOWN_MASK & m_KeysMask) {
		data.m_Surface = m_Image[DOWN_IMG].get();
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	if(KEY_LEFT_MASK & m_KeysMask) {
		data.m_Surface = m_Image[LEFT_IMG].get();
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	if(KEY_RIGHT_MASK & m_KeysMask) {
		data.m_Surface = m_Image[RIGHT_IMG].get();
		out.push_back(data);
		return EXIT_SUCCESS;
	}
	data.m_Surface = m_Image[IDLE_IMG].get();
	out.push_back(data);
	return EXIT_SUCCESS;
}

int32_t Game::loadResources(const std::unordered_map<ImgId_t, std::string> & cfg) {
	for(const auto & e : cfg) {
		m_Image[e.first] = Texture::createSurfaceFromFile(e.second);
		if(nullptr == m_Image[e.first]) {
			std::cerr << "Texture::createSurfaceFromFile failed." << std::endl;
	        return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

bool Game::exitRequest(const InputEvent & m_event) {
	return (TouchEvent::KEYBOARD_PRESS == m_event.m_Type)
		&& (Keyboard::KEY_ESCAPE == m_event.m_Key);
}

void Game::setKeyRequest(bool pressed, KeyMask_t key_mask) {
	if(pressed) {
		m_KeysMask |=  key_mask;
	} else {
		m_KeysMask &= ~key_mask;
	}
}

