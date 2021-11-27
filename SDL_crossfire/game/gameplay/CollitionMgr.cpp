/*
 * CollitionMgr.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#include "game/gameplay/CollitionMgr.hpp"

#include <cassert>
#include <iostream>

bool CollitionMgr::init(Callback_t cb_ammu, Callback_t cb_bonus, Callback_t cb_ship, Callback_t cb_enemy) {
	const auto rec = Rectangle(Point::ZERO, 3, 3);
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
	if(!m_ShipColl.init(cb_ship, &m_ProcTouch)) {
		std::cerr << "m_ShipColl.init() failed" << std::endl;
		return false;
	}
	if(!m_EnemyColl.init(cb_enemy, &m_ProcTouch)) {
		std::cerr << "m_EnemyColl.init() failed" << std::endl;
		return false;
	}
	m_Container.push_back(&m_EnemyColl);
	m_Container.push_back(&m_ShipColl);
	m_Container.push_back(&m_AmmunitionColl);
	m_Container.push_back(&m_BonusColl);
	return true;
}

void CollitionMgr::addUnits(const Widget* ship, const std::vector<const Widget*> & enemy) {
	assert(ship);
	m_Ship = ship;
	m_Enemy = enemy;
	m_BonusColl.setObj(ship);
	m_AmmunitionColl.setObj(ship);
}

void CollitionMgr::addBonus(const Widget* bonus) {
	m_BonusColl.add(bonus);
}

void CollitionMgr::removeBonus(const Widget* bonus) {
	m_BonusColl.remove(bonus);
}

void CollitionMgr::addAmmun(const Widget* ammun) {
	m_AmmunitionColl.add(ammun);
}
void CollitionMgr::removeAmmun(const Widget* ammun) {
	m_AmmunitionColl.remove(ammun);
}

void CollitionMgr::addBulletShipColl([[maybe_unused]]Widget* bullet) {
}

void CollitionMgr::addBulletEnemyColl([[maybe_unused]]Widget* bullet) {
}

void CollitionMgr::processing() {
	for(auto & e : m_Container) {
		e->processing();
	}
}
