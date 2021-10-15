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

int32_t Game::init(const GameConfig& cfg, EventReg_IF & event) {
	if(EXIT_SUCCESS != loadResources(cfg.ImgPath)) {
		std::cerr << "app_window.copy failed." << std::endl;
		return EXIT_FAILURE;
	}
	if(EXIT_SUCCESS != registeringEvents(event)) {
		std::cerr << "app_window.copy failed." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t Game::draw(std::vector<SDL_Surface *> &out) {
	if(KEY_UP_MASK & m_KeysMask) {
		out.push_back(m_Image[UP_IMG].get());
		return EXIT_SUCCESS;
	}
	if(KEY_DOWN_MASK & m_KeysMask) {
		out.push_back(m_Image[DOWN_IMG].get());
		return EXIT_SUCCESS;
	}
	if(KEY_LEFT_MASK & m_KeysMask) {
		out.push_back(m_Image[LEFT_IMG].get());
		return EXIT_SUCCESS;
	}
	if(KEY_RIGHT_MASK & m_KeysMask) {
		out.push_back(m_Image[RIGHT_IMG].get());
		return EXIT_SUCCESS;
	}
	out.push_back(m_Image[IDLE_IMG].get());
	return EXIT_SUCCESS;
}

int32_t Game::handleEvent() {
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

int32_t Game::registeringEvents(EventReg_IF & event) {
	event.registerExitKey(Keyboard::KEY_ESCAPE);
	event.registerKeyboard(Keyboard::KEY_RIGHT,
		[this](const InputEvent & input) {
			this->setKeyRequest(TouchEvent::KEYBOARD_PRESS == input.m_Type, KEY_RIGHT_MASK);
		}
	);
	event.registerKeyboard(Keyboard::KEY_LEFT,
		[this](const InputEvent & input) {
			this->setKeyRequest(TouchEvent::KEYBOARD_PRESS == input.m_Type, KEY_LEFT_MASK);
		}
	);
	event.registerKeyboard(Keyboard::KEY_DOWN,
		[this](const InputEvent & input) {
			this->setKeyRequest(TouchEvent::KEYBOARD_PRESS == input.m_Type, KEY_DOWN_MASK);
		}
	);
	event.registerKeyboard(Keyboard::KEY_UP,
		[this](const InputEvent & input) {
			this->setKeyRequest(TouchEvent::KEYBOARD_PRESS == input.m_Type, KEY_UP_MASK);
		}
	);
	return EXIT_SUCCESS;
}

void Game::setKeyRequest(bool pressed, KeyMask_t key_mask) {
	if(pressed) {
		m_KeysMask |=  key_mask;
	} else {
		m_KeysMask &= ~key_mask;
	}
}

