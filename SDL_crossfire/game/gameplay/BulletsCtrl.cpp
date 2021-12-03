/*
 * BulletsCtrl.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#include "game/gameplay/BulletsCtrl.hpp"

#include <iostream>

#include "utils/drawing/Rectangle.hpp"
#include "game/action/Action.hpp"

bool BulletsCtrl::init(int8_t max_bullets, uint32_t reload) {
	m_ReloadTime = reload;
	m_BulletsRemaining = max_bullets;
	return true;
}

bool BulletsCtrl::initDraw(std::size_t bullet_img_id, double scale, const Rectangle & field) {
	return m_Bullets.init(bullet_img_id, scale, field);
}

void BulletsCtrl::setSpeed(double speed) {
	return m_Bullets.setSpeed(speed);
}

int8_t BulletsCtrl::getRemainingBullets() const {
	return m_BulletsRemaining;
}

void BulletsCtrl::reload(int8_t numb) {
	m_BulletsRemaining = numb;
}

void BulletsCtrl::setCallback(const Callback_t & callback) {
	m_CB = callback;
}

bool BulletsCtrl::event(const Action_t action, uint8_t line_of_fire, const Rectangle & shooter_rect) {
	if(m_ReloadTimer.isRunning()) {
		return false;
	}
	if(!Action::isFireAction(action)) {
		return false;
	}
	if(!m_BulletsRemaining) {
		return true;
	}
	if(!(Action::toNeighborhoodMask(action) & line_of_fire)) {
		return false;
	}
	if(!m_Bullets.shoot(action, shooter_rect)) {
		std::cerr << "m_Bullets->shoot() failed" << std::endl;
		return true;
	}
	m_ReloadTimer.start(m_ReloadTime, Timer2::TimerMode_t::ONESHOT, nullptr);
	if(0 < m_BulletsRemaining) {
		--m_BulletsRemaining;
	}
	if(m_CB) {
		m_CB(shooter_rect.getCenter(), m_BulletsRemaining);
	}
	return true;
}

bool BulletsCtrl::tick(const Action_t pending_action, uint8_t line_of_fire, const Rectangle & shooter_rect) {
	bool rc = event(pending_action, line_of_fire, shooter_rect);
	m_Bullets.tick();
	return rc;
}

void BulletsCtrl::draw() {
	m_Bullets.draw();
}

std::vector<Widget *> BulletsCtrl::getWidgets() {
	return m_Bullets.get();
}

