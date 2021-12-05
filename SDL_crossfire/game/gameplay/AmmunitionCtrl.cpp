/*
 * AmmunitionCtrl.cpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#include "game/gameplay/AmmunitionCtrl.hpp"

#include "game/config/Rules.hpp"

bool AmmunitionCtrl::operator ()(int32_t remain) const {
	return Rules::RELOAD_BULLETS >= remain;
}

AmmunitionCtrl::operator int32_t () const {
	return Rules::getShipBulled();
}

