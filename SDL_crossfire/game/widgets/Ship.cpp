/*
 * Ship.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#include "game/widgets/Ship.hpp"

#include <iostream>

bool Ship::init(std::size_t ship_img_id, const Point& pos, uint32_t grid_size, double speed, const Layout::GridData_t &grid_data) {
	if(!create(ship_img_id, pos, true)) {
		std::cerr << "Ship::init().create() failed"<< std::endl;
		return false;
	}
	if(!m_UnitAction.init(this, pos, grid_size, speed, grid_data)) {
		std::cerr << "Ship::init().m_UnitAction.init() failed"<< std::endl;
		return false;
	}
	m_ActionBuffer.clear();
	return true;
}

bool Ship::event(const Action_t type) {
	m_ActionBuffer = type;
	if(!m_ActionBuffer.empty()) {
		if(m_UnitAction.event(m_ActionBuffer)) {
			m_ActionBuffer.clear();
			return true;
		}
		// fire action
	}
	return false;
}

void Ship::tick() {
	if(m_UnitAction.tick(m_ActionBuffer)) {
		m_ActionBuffer.clear();
	}
}
