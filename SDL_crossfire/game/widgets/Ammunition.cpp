/*
 * Ammunition.cpp
 *
 *  Created on: Nov 22, 2021
 *      Author: stanimir
 */

#include "game/widgets/Ammunition.hpp"

#include <iostream>

bool Ammunition::init(std::size_t image_id, double scale_factor) {
	if(!m_Img.create(image_id, Point::ZERO)) {
		std::cerr << "Ammunition::init() m_Img.create(" << image_id << ") failed." << std::endl;
		return false;
	}
	if(!m_ScaleImage.initBlinkingAnimation(BLINKNIG_PERIOD)) {
		std::cerr << "Ammunition::init() m_Img.initBlinkingAnimation() failed." << std::endl;
		return false;
	}
	m_ScaleImage.setVisible(false);
	if(!m_ScaleImage.init(scale_factor, &m_Img)) {
		std::cerr << "Ammunition::init() m_ScaleImage.init() failed." << std::endl;
		return false;
	}
	return true;
}

bool Ammunition::show(const Point &pos) {
	m_ScaleImage.setPositionCenter(pos);
	m_ScaleImage.setVisible(true);
	return m_ScaleImage.start();
}

void Ammunition::clear() {
	m_ScaleImage.setVisible(false);
	m_ScaleImage.stop();
}

void Ammunition::draw() {
	m_ScaleImage.draw();
}

Rectangle Ammunition::getRect() const {
	if(m_ScaleImage.getVisible()) {
		return m_ScaleImage.getRectangle();
	}
	return Rectangle::UNDEFINED;
}
