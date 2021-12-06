/*
 * CollitionMgr.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#include "game/gameplay/CollitionMgr.hpp"

#include <cassert>
#include <iostream>

#include "game/config/Layout.hpp"

bool CollitionMgr::init(Callback_t cb_ammu, Callback_t cb_bonus, Callback_t cb_ship,
		Callback_t cb_enemy, Callback_t cb_ship_2_ship) {
	const auto rec = Rectangle(Points::ZERO
			, static_cast<int32_t>(5 * Layout::getScaleFactor())
			, static_cast<int32_t>(5 * Layout::getScaleFactor()));
	if(!m_ProcThrough.init(rec)) {
		std::cerr << "m_ProcThrough.init() failed" << std::endl;
		return false;
	}
	if(!m_AmmunitionColl.init(cb_ammu, &m_ProcThrough)) {
		std::cerr << "m_AmmunitionColl.init() failed" << std::endl;
		return false;
	}
	if(!m_BonusColl.init(cb_bonus, &m_ProcThrough)) {
		std::cerr << "m_BonusColl.init() failed" << std::endl;
		return false;
	}
	if(!m_Ship2BulletColl.init(cb_ship, &m_ProcTouch)) {
		std::cerr << "m_Ship2BulletColl.init() failed" << std::endl;
		return false;
	}
	if(!m_Enemy2BulletColl.init(cb_enemy, &m_ProcTouch)) {
		std::cerr << "m_Enemy2BulletColl.init() failed" << std::endl;
		return false;
	}
	if(!m_Ship2ShipColl.init(cb_ship_2_ship, &m_ProcTouch)) {
		std::cerr << "m_Ship2ShipColl.init() failed" << std::endl;
		return false;
	}
	return true;
}

void CollitionMgr::addUnits(Widget* ship, const std::vector<Widget*> & enemy) {
	assert(ship);
	m_Ship = ship;
	m_Enemy = enemy;
	m_Ship2BulletColl.setObj(ship);
	m_BonusColl.setObj(ship);
	m_AmmunitionColl.setObj(ship);
}

void CollitionMgr::processing(const std::vector<Widget*> & own_bullets,
		const std::vector<Widget*> & enemy_bullets,
		const std::vector<Widget*> & enemy,
		const std::vector<Widget*> & bonuses,
		const std::vector<Widget*> & ammunition) {
	// check for collision between ship bullets and enemies
	if(!own_bullets.empty()) {
		for(auto e : m_Enemy) {
			m_Enemy2BulletColl.setObj(e);
			m_Enemy2BulletColl.processing(own_bullets);
		}
	}
	// check for collision between enemies bullets and ship
	m_Ship2ShipColl.setObj(m_Ship);
	m_Ship2ShipColl.processing(enemy);
	// check for collision between enemies and ship
	if(!enemy_bullets.empty()) {
		m_Ship2BulletColl.processing(m_Enemy);
	}
	// check for collision between enemies and enemies
	if(!enemy_bullets.empty()) {
		const auto size = m_Enemy.size();
		for(std::size_t i = 0; (size-1) > i; ++i) {
			m_Ship2ShipColl.setObj(m_Enemy[i]);
			std::vector<Widget*> others(&m_Enemy[i+1], &m_Enemy[size]);
			for(std::size_t j = i+1; (enemy_bullets.size()-1) > j; ++j) {
				m_Ship2ShipColl.processing(others);
			}
		}
	}
	// check for collision between ship and bonuses
	if(!bonuses.empty()) {
		m_BonusColl.processing(bonuses);
	}
	// check for collision between ship and ammunitions
	if(!ammunition.empty()) {
		m_AmmunitionColl.processing(ammunition);
	}
}
