/*
 * Wheel.cpp
 *
 *  Created on: Nov 4, 2021
 *      Author: stanimir
 */

#include "game/widgets/Wheel.hpp"

#include <iostream>

bool Wheel::init(std::size_t id, const Point &pos) {
	bool rc = false;
	do {
		if(!m_Img.create(id, pos)) {
			std::cerr << "m_Img.create failed" << std::endl;
			break;
		}
		m_Img.activateAlphaModulation();
		rc = true;
	} while(0);
	return rc;
}

void Wheel::draw() const {
	m_Img.draw();
}

void Wheel::startAnimation() {
	if(isActiveTimerId(m_RotationTimerId)) {
		std::cerr << "Wheel animation already started" << std::endl;
		return;
	}
	startTimer(m_RotationTimerId, 20, TimerType_t::RELOAD);
}

void Wheel::stopAnimation() {
	if(!isActiveTimerId(m_RotationTimerId)) {
		std::cerr << "Wheel animation already stoped" << std::endl;
		return;
	}
	stopTimer(m_RotationTimerId);
}

void Wheel::onTimeout(std::size_t id) {
	if(m_RotationTimerId == id) {
		processAnimation();
	} else {
		std::cerr << "Wheel::onTimeout receive invalid timer " << id << std::endl;
	}
}

void Wheel::processAnimation() {
	m_Img.rotateRight(2.0);
}


