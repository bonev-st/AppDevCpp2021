/*
 * Bonuses.cpp
 *
 *  Created on: Nov 25, 2021
 *      Author: stanimir
 */

#include "game/widgets/Bonuses.hpp"

#include <iostream>

#include "game/config/Layout.hpp"

bool Bonuses::init(std::size_t img_id, double scale, const Point * ena_pos, const Point * dis_pos,
		std::size_t font_id, const Color & text_color) {
	for(auto & e: m_EnablePointContaner) {
		e = Layout::getRel2AbsPosition(*ena_pos);
		++ena_pos;
	}
	for(auto & e: m_DisablePointContaner) {
		e = Layout::getRel2AbsPosition(*dis_pos);
		++dis_pos;
	}
	for(auto & e: m_ImgContaner) {
		if(!e.initBlinkingAnimation(ANIMATION_SPEED)) {
			std::cerr << "BlinkingAnimation init failed" << std::endl;
			return false;
		}
		if(!e.create(img_id)) {
			std::cerr << "Image create() failed" << std::endl;
			return false;
		}
	}
	for(std::size_t i = 0; m_ScaleImgContaner.size() > i; ++i) {
		if(!m_ScaleImgContaner[i].init(scale, &m_ImgContaner[i])) {
			std::cerr << "ScaleTexture init() failed" << std::endl;
			return false;
		}
		m_ScaleImgContaner[i].setPositionCenter(m_DisablePointContaner[i]);
	}

	if(!m_PointsText.create(" ", text_color, font_id, Point::ZERO)) {
		std::cerr << "Text create() failed" << std::endl;
		return false;
	}
	m_ScalePointsText.init(scale, &m_PointsText);
	m_ScalePointsText.setVisible(false);
	return true;
}

void Bonuses::reset() {
	for(std::size_t i = 0; m_ScaleImgContaner.size() > i; ++i) {
		m_ImgContaner[i].stop();
		m_ScaleImgContaner[i].setPositionCenter(m_DisablePointContaner[i]);
	}
	m_ScalePointsText.setVisible(false);
}

void Bonuses::enable(BonusId_t id) {
	if(BONUS_NUMB > m_Current) {
		m_ImgContaner[m_Current].stop();
		m_ScaleImgContaner[m_Current].setPositionCenter(m_DisablePointContaner[m_Current]);
	}
	m_Current = static_cast<uint8_t>(id);
	m_ImgContaner[m_Current].start();
	m_ScaleImgContaner[m_Current].setPositionCenter(m_EnablePointContaner[m_Current]);
}

void Bonuses::disable() {
	if(BONUS_NUMB > m_Current) {
		if(m_ScaleImgContaner[m_Current].getVisible()) {
			m_ImgContaner[m_Current].stop();
			m_ScaleImgContaner[m_Current].setPositionCenter(m_DisablePointContaner[m_Current]);
		}
		m_Current = BONUS_NUMB;
	}
}

void Bonuses::hide(uint32_t points) {
	if(BONUS_NUMB > m_Current) {
		const auto text = std::to_string(points);
		if(!m_PointsText.setText(text, Point::ZERO)) {
			std::cerr << "Text setText() failed" << std::endl;
		} else {
			m_ScalePointsText.setVisible(true);
			m_ScalePointsText.setPositionCenter(m_ImgContaner[m_Current].getPositionCenter());
		}
		m_ImgContaner[m_Current].stop();
		m_ScaleImgContaner[m_Current].setVisible(false);
		m_ScaleImgContaner[m_Current].setPositionCenter(m_DisablePointContaner[m_Current]);
	}
}

void Bonuses::draw() {
	for(auto & e: m_ScaleImgContaner) {
		e.draw();
	}
}
