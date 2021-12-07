/*
 * Ship.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#include "game/widgets/Ship.hpp"

#include <iostream>

bool Ship::init(std::size_t ship_img_id, double scale_factor, const Point& pos, uint32_t grid_size) {
	if(!m_Image.create(ship_img_id, Point(), true)) {
		std::cerr << "Ship::init().create() failed"<< std::endl;
		return false;
	}
	if(!init(scale_factor, &m_Image)) {
		std::cerr << "ScaleTexture::init() failed"<< std::endl;
		return false;
	}
	if(!m_UnitAction.init(this, pos, grid_size)) {
		std::cerr << "Ship::init().m_UnitAction.init() failed"<< std::endl;
		return false;
	}
	m_ActionBuffer.clear();
	return true;
}

bool Ship::init_bullet(std::size_t bullet_img_id, double scale_factor, const Rectangle & field) {
	if(!m_BulletsCtrl.initDraw(bullet_img_id, scale_factor, field)) {
		std::cerr << "m_Bullets.initDraw() failed"<< std::endl;
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
		if(m_BulletsCtrl.event(m_ActionBuffer, m_UnitAction.getLineOfFire(), getRectangle())) {
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
	if(m_BulletsCtrl.tick(m_ActionBuffer, m_UnitAction.getLineOfFire(), getRectangle())) {
		m_ActionBuffer.clear();
	}
}

void Ship::draw() {
	ScaleTexture::draw();
	m_BulletsCtrl.draw();
}

void Ship::setCallback(const BulletsCtrl::Callback_t & callback) {
	m_BulletsCtrl.setCallback(callback);
}

void Ship::reload(int32_t bullets) {
	m_BulletsCtrl.reload(bullets);
}

void Ship::reloadTime(uint32_t dly) {
	m_BulletsCtrl.setReloadTime(dly);
}

void Ship::destroy() {
	m_UnitAction.destroy();
}

bool Ship::isDestroy() const {
	return m_UnitAction.isDestroy();
}

void Ship::reset() {
	m_UnitAction.reset();
	setVisible(true);
	setOpacity(FULL_OPACITY);
}

void Ship::setShipSpeed(double speed) {
	m_UnitAction.setSpeed(speed);
}

void Ship::setBulletsSpeed(double speed) {
	m_BulletsCtrl.setSpeed(speed);
}

std::vector<Widget *> Ship::getBullets() {
	return m_BulletsCtrl.getWidgets();
}

std::vector<Widget *> Ship::get() {
	std::vector<Widget *> rc;
	if(!m_UnitAction.isDestroy() && getVisible()) {
		rc.push_back(this);
	}
	return rc;
}

Point Ship::getCrossPoint() const {
	return m_UnitAction.getCrossPoint();
}

