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

bool Bullets::init(std::size_t bullet_img_id, double scale, double speed, int8_t max_bullets, uint32_t reload, const Rectangle & field) {
	m_ImgId = bullet_img_id;
	m_Scale = scale;
	m_ReloadTime = reload;
	m_Speed = speed;
	m_BulletsRemaining = max_bullets;
	m_Field = field;
	return true;
}

bool Bullets::event(const Action_t action, uint8_t line_of_fire, const Rectangle & shooter_rect) {
	assert(INVALID_RESR_ID != m_ImgId);
	if(m_ReloadTimer.isRunning()) {
		return false;
	}
	if(!Action::isFireAction(action)) {
		return false;
	}
	if(!m_BulletsRemaining) {
		return true;
	}
	if(Action::toNeighborhoodMask(action) & line_of_fire) {
		auto bullet = std::make_shared<Bullet_t>();
		if(!bullet->m_Image.create(m_ImgId)) {
			std::cerr << "Bullets::event() image create() failed" << std::endl;
			return false;
		}
		if(!bullet->m_Scaled.init(m_Scale, &bullet->m_Image)) {
			std::cerr << "Bullets::event() Init scaled image failed" << std::endl;
			return false;
		}
		if(!bullet->m_Scaled.initBulletAction(shooter_rect, m_Speed, action, m_Field)) {
			std::cerr << "Bullets::event() Init bullet action failed" << std::endl;
		}
		m_BulletsContainer.add(bullet);

		m_ReloadTimer.start(m_ReloadTime, Timer2::TimerMode_t::ONESHOT, nullptr);
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
	for(size_t i = 0; m_BulletsContainer.getMaxValid() > i; ++i) {
		auto e = m_BulletsContainer.get(i);
		if(e) {
			if(!*e) {
				std::cerr << "Bullets::tick() invalid pointer" << std::endl;
				continue;
			}
			if(!(*e)->m_Scaled.tick()) {
				m_BulletsContainer.release(i);
				continue;
			}
		}
	}
	return rc;
}

void Bullets::draw() {
	if(!m_BulletsContainer.empty()) {
		for(size_t i = 0; m_BulletsContainer.getMaxValid() > i; ++i) {
			auto * e =  m_BulletsContainer.get(i);
			if(e) {
				if(!*e) {
					std::cerr << "Bullets::tick() invalid pointer" << std::endl;
					continue;
				}
				(*e)->m_Scaled.draw();
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
