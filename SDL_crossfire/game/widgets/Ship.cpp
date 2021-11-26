/*
 * Ship.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#include "game/widgets/Ship.hpp"

#include <iostream>

bool Ship::init(std::size_t ship_img_id, float scale_factor, const Point& pos, uint32_t grid_size, double speed) {
	if(!m_Image.create(ship_img_id, Point(), true)) {
		std::cerr << "Ship::init().create() failed"<< std::endl;
		return false;
	}
	if(!init(scale_factor, &m_Image)) {
		std::cerr << "ScaleTexture::init() failed"<< std::endl;
		return false;
	}
	if(!m_UnitAction.init(this, pos, grid_size, speed)) {
		std::cerr << "Ship::init().m_UnitAction.init() failed"<< std::endl;
		return false;
	}
	m_ActionBuffer.clear();
	return true;
}

bool Ship::init_bullet(std::size_t bullet_img_id, double speed, int8_t max_bullets, uint32_t reload_time, const Rectangle & field) {
	if(!m_Bullets.init(bullet_img_id, speed, max_bullets, reload_time, field)) {
		std::cerr << "Ship::init_bullet().m_Bullets.init() failed"<< std::endl;
		return false;
	}
	return true;
}

bool Ship::event(const Action_t type) {
	m_ActionBuffer = type;
	if(!m_ActionBuffer.empty()) {
		if(m_UnitAction.event(m_ActionBuffer)) {
			m_ActionBuffer.clear();
			return true;
		}
		if(m_Bullets.event(m_ActionBuffer, m_UnitAction.getLineOfFire(), getRectangle())) {
			m_ActionBuffer.clear();
			return true;
		}
	}
	return false;
}

void Ship::tick() {
	if(m_UnitAction.tick(m_ActionBuffer)) {
		m_ActionBuffer.clear();
	}
	if(m_Bullets.tick(m_ActionBuffer, m_UnitAction.getLineOfFire(), getRectangle())) {
		m_ActionBuffer.clear();
	}
}

void Ship::draw() {
	ScaleTexture::draw();
	m_Bullets.draw();
}

void Ship::setCallback(const Bullets::Callback_t & callback) {
	m_Bullets.setCallback(callback);
}

void Ship::reload(int8_t bullets) {
	m_Bullets.reload(bullets);
}
