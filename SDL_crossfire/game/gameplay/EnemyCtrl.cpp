/*
 * EnemyCtrl.cpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#include "game/gameplay/EnemyCtrl.hpp"

#include "game/widgets/EnemyContainer.hpp"
#include "game/action/Action.hpp"
#include "game/config/Layout.hpp"

bool EnemyCtrl::init() {
	return true;
}

void EnemyCtrl::reset() {

}

void EnemyCtrl::processing(EnemyContainer & enemies) {
#if 0
	Action_t action = Action_t::MOVE_UP;
	enemies.event(action, EnemyId_t::ENEMY1);
#endif
#if 1
	static int32_t cc = 100;
	if(--cc) {
		return;
	}
	cc = 100;
	for(int i = 0; i < 11; i++) {
		const auto r = std::rand();
		double tmp = r;
		tmp /= RAND_MAX;
		tmp *= 16;
		uint8_t m = static_cast<uint8_t>(tmp);
		Action_t action = Action_t::NONE;

		switch(m) {
		case 0:
			break;
		case 1:
			action = Action_t::MOVE_UP;
			break;
		case 2:
			break;
		case 3:
			action = Action_t::MOVE_DOWN;
			break;
		case 4:
			break;
		case 5:
			action = Action_t::MOVE_LEFT;
			break;
		case 6:
			break;
		case 7:
			action = Action_t::MOVE_RIGHT;
			break;
		case 8:
			break;
#if 0
		case 9:
			action = Action_t::FIRE_UP;
			break;
		case 10:
			break;
		case 11:
			action = Action_t::FIRE_DOWN;
			break;
		case 12:
			break;
		case 13:
			action = Action_t::FIRE_LEFT;
			break;
		case 14:
			break;
		case 15:
			action = Action_t::FIRE_RIGHT;
			break;
		case 16:
			break;
#endif
		}
		enemies.event(action, static_cast<EnemyId_t>(i));
	}
#endif
}
