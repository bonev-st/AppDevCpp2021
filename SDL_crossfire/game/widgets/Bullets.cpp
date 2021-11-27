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

bool Bullets::init(std::size_t bullet_img_id, double scale, double speed, const Rectangle & field) {
	m_ImgId = bullet_img_id;
	m_Scale = scale;
	m_Speed = speed;
	m_Field = field;
	return true;
}

bool Bullets::shoot(const Action_t action, const Rectangle & shooter_rect) {
	assert(INVALID_RESR_ID != m_ImgId && "Bullets not initialized");
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
	return true;
}

bool Bullets::tick() {
	for(auto & e : m_BulletsContainer) {
		if(nullptr != e) {
			if(!e->m_Scaled.tick()) {
				m_BulletsContainer.release(e);
			}
		}
	}
	return true;
}

void Bullets::draw() {
	for(auto & e : m_BulletsContainer) {
		if(nullptr == e) {
			std::cerr << "Bullets::tick() invalid pointer" << std::endl;
			continue;
		}
		e->m_Scaled.draw();
	}
}
