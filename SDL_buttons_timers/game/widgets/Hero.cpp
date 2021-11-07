/*
 * Hero.cpp
 *
 *  Created on: Nov 2, 2021
 *      Author: stanimir
 */

#include "Hero.hpp"

#include <iostream>

#include "sdl_utils/InputEvent.hpp"

bool Hero::init(std::size_t id, const Point &pos) {
	if(!m_Img.create(id, pos)) {
		std::cerr << "m_Img.create() failed" << std::endl;
		return false;
	}
	m_Img.initAnimation(52, 100, false, 0);
	return true;
}

void Hero::draw() const {
	m_Img.draw();
}

bool Hero::handleEvent(const InputEvent& e) {
	if(TouchEvent::TOUCH_PRESS == e.m_Type) {
		if(!m_Img.isReady()) {
			m_Img.cancel();
		}
		if(!m_Img.setPosition(e.m_Pos)) {
			std::cerr << "Hero::handleEvent() m_Img.setPosition failed" << std::endl;
		}
	}
	return false;
}
