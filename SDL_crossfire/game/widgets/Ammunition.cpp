/*
 * Ammunition.cpp
 *
 *  Created on: Nov 22, 2021
 *      Author: stanimir
 */

#include "game/widgets/Ammunition.hpp"

#include <iostream>

const double Ammunition::BLINKNIG_SPEED = 0.05;

bool Ammunition::init(std::size_t image_id) {
	if(!m_Img.create(image_id, Point::ZERO)) {
		std::cerr << "Ammunition::init() m_Img.create(" << image_id << ") failed." << std::endl;
		return true;
	}
	m_Img.setVisible(false);
	if(!m_Img.initBlinkingAnimation(BLINKNIG_SPEED)) {
		std::cerr << "Ammunition::init() m_Img.initBlinkingAnimation() failed." << std::endl;
		return true;
	}
	return true;
}

bool Ammunition::show(const Point &pos) {
	m_Img.setPositionCenter(pos);
	m_Img.setVisible(true);
	return m_Img.start();
}

void Ammunition::clear() {
	m_Img.setVisible(false);
	m_Img.stop();
}

void Ammunition::draw() const {
	m_Img.draw();
}

Rectangle Ammunition::getRect() const {
	if(m_Img.getVisible()) {
		return m_Img.getRectangle();
	}
	return Rectangle::UNDEFINED;
}
