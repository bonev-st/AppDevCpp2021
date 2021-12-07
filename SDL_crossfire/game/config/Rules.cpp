/*
 * Rules.cpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#include "game/config/Rules.hpp"

#include "game/config/Layout.hpp"

const double Rules::ENEMY_SPEED = 0.3;
const double Rules::ENEMY_BULLET_SPEED = ENEMY_SPEED * 5.0;
const double Rules::SHIP_SPEED = ENEMY_SPEED*2.0;
const double Rules::SHIP_BULLET_SPEED = SHIP_SPEED * 5.0;

uint32_t Rules::m_Mission = 0;

double Rules::getShipSpeed() {
	return SHIP_SPEED * Layout::getScaleFactor() * getSpeedIncrease();
}

double Rules::getShipBulletSpeed() {
	return SHIP_BULLET_SPEED * Layout::getScaleFactor() * getSpeedIncrease();
}

double Rules::getEnemySpeed() {
	return ENEMY_SPEED * Layout::getScaleFactor() * getSpeedIncrease();
}

double Rules::getEnemyBulletSpeed() {
	return ENEMY_BULLET_SPEED * Layout::getScaleFactor() * getSpeedIncrease();
}

int32_t Rules::getShipBulled() {
	if(((INITIAL_BULLETS - MIN_BULLETS) / DECREASE_BULLETS) < m_Mission) {
		return MIN_BULLETS;
	}
	return INITIAL_BULLETS - DECREASE_BULLETS * m_Mission;
}

uint32_t Rules::getShipReloadTime() {
	double rc = OWN_RELOAD_TIME;
	rc *= getSpeedIncrease();
	return static_cast<uint32_t>(rc);
}

int32_t Rules::getEnemyBulled() {
	return ENEMY_MAX_BULLED;
}

uint32_t Rules::getEnemyReloadTime() {
	double rc = ENEMY_RELOAD_TIME;
	rc *= getSpeedIncrease();
	return static_cast<uint32_t>(rc);
}

void Rules::firstMission() {
	m_Mission = 0;
}

void Rules::nextMission() {
	++m_Mission;
}

double Rules::getSpeedIncrease() {
	double rc = 1.0 - 0.05 * m_Mission;
	if(0.1 > rc) {
		return 0.1;
	}
	return rc;
}


