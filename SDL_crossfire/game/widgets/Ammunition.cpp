/*
 * Ammunition.cpp
 *
 *  Created on: Nov 22, 2021
 *      Author: stanimir
 */

#include "game/widgets/Ammunition.hpp"

#include <iostream>

bool Ammunition::init(std::size_t image_id, double scale_factor) {
	if(!m_Img.create(image_id, Points::ZERO)) {
		std::cerr << "m_Img.create(" << image_id << ") failed." << std::endl;
		return false;
	}
	if(!initBlinkingAnimation(BLINKNIG_PERIOD)) {
		std::cerr << "initBlinkingAnimation() failed." << std::endl;
		return false;
	}
	setVisible(false);
	if(!BlinkingAnimation<ScaleTexture>::init(scale_factor, &m_Img)) {
		std::cerr << "BlinkingAnimation<ScaleTexture>::init() failed." << std::endl;
		return false;
	}
	return true;
}

bool Ammunition::show(const Point &pos) {
	setPositionCenter(pos);
	setVisible(true);
	return start();
}

void Ammunition::collision() {
	setVisible(false);
	stop();
}

std::vector<Widget *> Ammunition::get() {
	std::vector<Widget *> rc;
	if(getVisible()) {
		rc.push_back(this);
	}
	return rc;
}

