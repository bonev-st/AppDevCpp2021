/*
 * Bullets.cpp
 *
 *  Created on: Nov 21, 2021
 *      Author: stanimir
 */

#include "game/widgets/Bullets.hpp"

#include <cassert>
#include <iostream>

#include "utils/drawing/DrawParams.hpp"

bool Bullets::init(std::size_t bullet_img_id, double speed, int8_t max_bullets, uint32_t reload, const Rectangle & field) {
	m_ImgId = bullet_img_id;
	m_ReloadTime = reload;
	m_Speed = speed;
	m_BulletsRemaining = max_bullets;
	m_Field = field;
	m_Reloading = false;
	return true;
}

bool Bullets::event(const Action_t action, uint8_t line_of_fire, const Rectangle & shooter_rect) {
	assert(INVALID_RESR_ID != m_ImgId);
	if(m_Reloading) {
		return false;
	}
	if(!Action::isFireAction(action)) {
		return false;
	}
	if(!m_BulletsRemaining) {
		return true;
	}
	if(Action::toNeighborhoodMask(action) & line_of_fire) {
		BulletAction<Image> bullet;
		if(!bullet.init(m_ImgId, shooter_rect, m_Speed, action, m_Field)) {
			std::cerr << "Bullets::event().bullet.init() failed" << std::endl;
			return true;
		}
		m_Bullets.add(bullet);
		m_Reloading = true;
		m_ReloadTimer.start(m_ReloadTime, Timer2::TimerMode_t::ONESHOT,
				std::bind(&Bullets::onReloadTimer, this, std::placeholders::_1));

		if(0 < m_BulletsRemaining) {
			--m_BulletsRemaining;
		}
		if(m_CB) {
			m_CB(shooter_rect.getCenter(), m_BulletsRemaining);
		}
		return true;
	}
	return false;
}

bool Bullets::tick(const Action_t pending_action, uint8_t line_of_fire, const Rectangle & shooter_rect) {
	bool rc = event(pending_action, line_of_fire, shooter_rect);
	for(size_t i = 0; m_Bullets.getMaxValid() > i; ++i) {
		auto * e = const_cast<BulletAction<Image> *>(m_Bullets.get(i));
		if(e) {
			if(!e->tick()) {
				m_Bullets.release(i);
			}
		}
	}
	return rc;
}

void Bullets::draw() {
	if(!m_Bullets.empty()) {
		for(size_t i = 0; m_Bullets.getMaxValid() > i; ++i) {
			auto * e =  m_Bullets.get(i);
			if(e) {
				e->draw();
			}
		}
	}
}

int8_t Bullets::getRemainingBullets() const {
	return m_BulletsRemaining;
}

void Bullets::reload(int8_t numb) {
	m_BulletsRemaining = numb;
}

void Bullets::setCallback(const Callback_t & callback) {
	assert(callback);
	m_CB = callback;
}

void Bullets::onReloadTimer(const Timer2::TimerHandler_t & h) {
	assert(this->m_ReloadTimer == h);
	m_Reloading = false;
}
