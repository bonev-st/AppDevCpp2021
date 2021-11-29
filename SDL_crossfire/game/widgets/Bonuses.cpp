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
	for(auto & e: m_BonusContaner) {
		e.m_Position = {Layout::getRel2AbsPosition(*ena_pos),
						Layout::getRel2AbsPosition(*dis_pos)};
		++ena_pos;
		++dis_pos;
		if(!e.m_Widget.m_Img.create(img_id)) {
			std::cerr << "Image create() failed" << std::endl;
			return false;
		}
		if(!e.m_Widget.m_Scaled.init(scale, &e.m_Widget.m_Img)) {
			std::cerr << "ScaleTexture init() failed" << std::endl;
			return false;
		}
		if(!e.m_Widget.m_Scaled.initBlinkingAnimation(ANIMATION_PERIOD)) {
			std::cerr << "BlinkingAnimation init failed" << std::endl;
			return false;
		}
		e.m_Widget.m_Scaled.setPositionCenter(e.m_Position.m_DisablePos);
	}

	if(!m_PointsText.create(" ", text_color, font_id, Points::ZERO)) {
		std::cerr << "Text create() failed" << std::endl;
		return false;
	}
	m_ScalePointsText.init(scale, &m_PointsText);
	m_ScalePointsText.initTO(TEXT_TO, nullptr);
	return true;
}

void Bonuses::reset() {
	for(auto & e : m_BonusContaner) {
		auto & widget = e.m_Widget.m_Scaled;
		widget.stop();
		widget.setPositionCenter(e.m_Position.m_DisablePos);
	}
	m_ScalePointsText.stop();
}

void Bonuses::enable(BonusId_t id) {
	if(BONUS_NUMB > m_Current) {
		setDisable();
	}
	auto index = static_cast<uint8_t>(id);
	if(BONUS_NUMB > index) {
		m_Current = index;
		setEnable();
	}
}

void Bonuses::disable() {
	if(BONUS_NUMB > m_Current) {
		setDisable();
		m_Current = BONUS_NUMB;
	}
}

void Bonuses::hide(uint32_t points) {
	if(BONUS_NUMB > m_Current) {
		setHide(points);
	}
}

void Bonuses::draw() {
	for(auto & e: m_BonusContaner) {
		e.m_Widget.m_Scaled.draw();
	}
	m_ScalePointsText.draw();
}

BonusId_t Bonuses::getId() const {
	return static_cast<BonusId_t>(m_Current);
}

const Widget* Bonuses::getEnabledWidget() const {
	if(BONUS_NUMB > m_Current) {
		return &m_BonusContaner[m_Current].m_Widget.m_Scaled;
	}
	return nullptr;
}

void Bonuses::setEnable() {
	auto & widget = m_BonusContaner[m_Current].m_Widget.m_Scaled;
	widget.start();
	widget.setPositionCenter(m_BonusContaner[m_Current].m_Position.m_EnablePos);
}

void Bonuses::setDisable() {
	auto & widget = m_BonusContaner[m_Current].m_Widget.m_Scaled;
	widget.stop();
	widget.setPositionCenter(m_BonusContaner[m_Current].m_Position.m_DisablePos);
}

void Bonuses::setHide(uint32_t number) {
	auto & widget = m_BonusContaner[m_Current].m_Widget.m_Scaled;
	if(widget.getVisible()) {
		const auto text = std::to_string(number);
		if(!m_PointsText.setText(text, Points::ZERO)) {
			std::cerr << "Text setText() failed" << std::endl;
		} else {
			m_ScalePointsText.setPositionCenter(widget.getPositionCenter());
			m_ScalePointsText.start();
		}
		widget.setVisible(false);
		widget.stop();
		widget.setPositionCenter(m_BonusContaner[m_Current].m_Position.m_DisablePos);
	}
}
