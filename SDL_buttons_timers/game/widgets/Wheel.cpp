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
		m_Img.initAnimation(1.5, 20);
		rc = true;
	} while(0);
	return rc;
}

void Wheel::attachDone(std::function<void()> * cb) {
	m_Img.attachDone(cb);
}

void Wheel::draw() const {
	m_Img.draw();
}

void Wheel::startAnimation(double angle, bool infinite) {
	if(!m_Img.isReady()) {
		std::cerr << "Wheel animation already started" << std::endl;
		return;
	}
	if(!m_Img.setAngle(angle, infinite)) {
		std::cerr << "Wheel animation start fauled" << std::endl;
		return;
	}
}

void Wheel::stopAnimation() {
	if(m_Img.isReady()) {
		std::cerr << "Wheel animation already stoped" << std::endl;
		return;
	}
	m_Img.cancel();
}

