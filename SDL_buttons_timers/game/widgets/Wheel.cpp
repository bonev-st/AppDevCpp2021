/*
 * Wheel.cpp
 *
 *  Created on: Nov 4, 2021
 *      Author: stanimir
 */

#include "game/widgets/Wheel.hpp"

bool Wheel::init(std::size_t id, const Point &pos) {
	return m_Img.create(id, pos);
}

void Wheel::draw() const {
	m_Img.draw();
}

void Wheel::startAnimation() {
	m_AnimationEna = true;
}

void Wheel::stopAnimation() {
	m_AnimationEna = false;
}

void Wheel::process() {
	if(m_AnimationEna) {
		m_Img.rotateRight(2.0);
	}
}
