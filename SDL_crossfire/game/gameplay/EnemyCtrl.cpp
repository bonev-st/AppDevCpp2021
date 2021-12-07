/*
 * EnemyCtrl.cpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#include "game/gameplay/EnemyCtrl.hpp"

#include "utils/geometry/Geometry.hpp"

#include "game/action/Action.hpp"
#include "game/config/Rules.hpp"
#include "game/config/Layout.hpp"

#include "game/widgets/Ship.hpp"

bool EnemyCtrl::init() {
	m_X_OUT = Layout::getEnemyRelPos(static_cast<std::size_t>(EnemyId_t::ENEMY_NUMB)-1).m_X;
	m_RandomNumber.init();
	return true;
}

void EnemyCtrl::processing(const std::vector<Widget *> & enemies, const std::vector<Widget *> & target,
		const std::vector<std::vector<Widget *>> & ship2ship) {
	// resolve for enemy ships collision
	if(resolveShip2ShipCollision(ship2ship)) {
		return;
	}
	auto random_numb = m_RandomNumber.get(Rules::PROB_MIN, Rules::PROB_MAX);
	if(Rules::PROB_ACTION < random_numb) {
		return;
	}
	Point target_point;
	if(!target.empty()) {
		auto ship = target.front();
		target_point = ship->getPositionCenter();
	}
	const auto active_enemies = getEnemiesOnFields(enemies);
	for(auto e : enemies) {
		random_numb = m_RandomNumber.get(Rules::PROB_MIN, Rules::PROB_MAX);
		auto * ship = reinterpret_cast<Ship*>(e);
		Action_t pref_action_move = Action_t::NONE;
		const auto ship_next_point = ship->getPositionCenter();
		const auto target_delta = target_point - ship_next_point;
		Action_t pref_action_fire = getFire(target_delta);
		if(isActive(e)) {
			pref_action_move = getMove(Rules::PROB_50 < random_numb, target_delta);
		} else {
			if(   (Rules::MAX_ACTIVE_ENIMIES > active_enemies)
			   && (Action_t::NONE == ship->getDirection())) {
				if (Rules::PROB_OUT < random_numb) {
					random_numb = m_RandomNumber.get(Rules::PROB_MIN, Rules::PROB_MAX);
					pref_action_move = getMoveOut(ship->getCrossPoint(), Rules::PROB_50 > random_numb);
					random_numb = 0;
				} else {
					random_numb = m_RandomNumber.get(Rules::PROB_MIN, Rules::PROB_MAX);
					pref_action_fire = maskFireAction(pref_action_fire, ship->getCrossPoint());
				}
			} else {
				random_numb = 0;
			}
		}

		Action_t action = Action_t::NONE;
		if (Rules::PROB_FIRE > random_numb) {
			action = pref_action_move;
		} else {
			action = pref_action_fire;
		}
		ship->event(action);
	}
}

bool EnemyCtrl::resolveShip2ShipCollision(const std::vector<std::vector<Widget *>> & ship2ship) {
	if(!ship2ship.empty()) {
		for(auto & v : ship2ship) {
			assert(!v.empty());
			auto it = v.begin();
			auto ship1 = reinterpret_cast<Ship*>(*it);
			++it;
			for( ; v.end() != it; ++it) {
				auto ship2 = reinterpret_cast<Ship*>(*it);
				const auto next_1 = ship1->getNextPoint();
				const auto last_1 = ship1->getCrossPoint();
				const auto next_2 = ship2->getNextPoint();
				const auto last_2 = ship2->getCrossPoint();
				if(next_1 == last_2) {
					ship1->event(Action::OppositeDir(ship1->getDirection()));
				} else if(next_2 == last_1) {
					ship2->event(Action::OppositeDir(ship2->getDirection()));
				} else if(next_2 == next_1) {
					if(ship1->getDirection() == ship2->getDirection()) {
						ship2->event(Action::OppositeDir(ship2->getDirection()));
					} else {
						ship2->event(Action::OppositeDir(ship2->getDirection()));
						ship1->event(Action::OppositeDir(ship1->getDirection()));
					}
				}
				ship1 = ship2;
			}
		}
		return true;
	}
	return false;
}

Action_t EnemyCtrl::getMoveOut(const Point & pos, bool back) const {
	Action_t rc = Action_t::NONE;
	if(!pos.m_X) {
		if(3 == pos.m_Y) {
			rc = Action_t::MOVE_UP;
		} else if (7 == pos.m_Y) {
			rc = Action_t::MOVE_UP;
		} else if (11 == pos.m_Y) {
			rc = Action_t::MOVE_UP;
		} else {
			if(back) {
				rc = Action_t::MOVE_DOWN;
			} else {
				rc = Action_t::MOVE_RIGHT;
			}
		}
	} else if(!pos.m_Y) {
		if(pos.m_X & 1) {
			rc = Action_t::MOVE_LEFT;
		} else {
			if(back) {
				rc = Action_t::MOVE_RIGHT;
			} else {
				rc = Action_t::MOVE_DOWN;
			}
		}
	} else if(m_X_OUT == pos.m_X) {
		if(5 == pos.m_Y) {
			rc = Action_t::MOVE_UP;
		} else if (9 == pos.m_Y) {
			rc = Action_t::MOVE_UP;
		} else {
			if(back) {
				rc = Action_t::MOVE_DOWN;
			} else {
				rc = Action_t::MOVE_LEFT;
			}
		}
	}
	return rc;
}

Action_t EnemyCtrl::getMove(bool h_move, const Point &target) const {
	Action_t rc = Action_t::NONE;
	if(h_move) {
		if(0 > target.m_X) {
			rc = Action_t::MOVE_LEFT;
		} else {
			rc = Action_t::MOVE_RIGHT;
		}
	} else {
		if(0 > target.m_Y) {
			rc = Action_t::MOVE_UP;
		} else {
			rc = Action_t::MOVE_DOWN;
		}
	}
	return rc;
}

Action_t EnemyCtrl::getFire(const Point &target) const {
	Action_t rc = Action_t::NONE;
	if(abs(target.m_X) < abs(target.m_Y)) {
		rc = (0 > target.m_X)?Action_t::FIRE_LEFT:Action_t::FIRE_RIGHT;
	} else {
		rc = (0 > target.m_Y)?Action_t::FIRE_UP:Action_t::FIRE_DOWN;
	}
	return rc;
}

Action_t EnemyCtrl::maskFireAction(Action_t fire, const Point &pos) const {
	if(Action_t::NONE == fire) {
		return fire;
	}
	if(!pos.m_X) {
		if(2 == pos.m_Y) {
			fire = Action_t::FIRE_LEFT;
		} else if (6 == pos.m_Y) {
			fire = Action_t::FIRE_LEFT;
		} else if (10 == pos.m_Y) {
			fire = Action_t::FIRE_LEFT;
		} else {
			fire = Action_t::NONE;
		}
	} else if (m_X_OUT == pos.m_X) {
		if(4 == pos.m_Y) {
			fire = Action_t::FIRE_RIGHT;
		} else if (8 == pos.m_Y) {
			fire = Action_t::FIRE_RIGHT;
		} else {
			fire = Action_t::NONE;
		}
	} else if (!pos.m_Y) {
		if(pos.m_X & 1) {
			fire = Action_t::NONE;
		} else {
			fire = Action_t::FIRE_DOWN;
		}
	}
	return fire;
}

bool EnemyCtrl::isActive(Widget * enemy) const {
	auto * ship = reinterpret_cast<Ship*>(enemy);
	const auto pos = ship->getNextPoint();
	if(!pos.m_X) {
	} else if (m_X_OUT == pos.m_X) {
	} else if (!pos.m_Y) {
	} else {
		return true;
	}
	return false;
}

std::size_t EnemyCtrl::getEnemiesOnFields(const std::vector<Widget *> & enemies) const {
	std::size_t rc = 0;
	for(const auto & e : enemies) {
		if(isActive(e)) {
			++rc;
		}
	}
	return rc;
}
