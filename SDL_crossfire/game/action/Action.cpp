/*
 * Action.cpp
 *
 *  Created on: Nov 21, 2021
 *      Author: stanimir
 */

#include "game/action/Action.hpp"

#include <cassert>

#include "game/config/Layout.hpp"

Action2Dir_t Action::compare(const Action_t a, const Action_t b) {
	if(a == b) {
		return Action2Dir_t::SAME;
	}
	Action2Dir_t rc = Action2Dir_t::NOT_SAME;
	switch (a) {
	case Action_t::MOVE_UP:
		if(Action_t::MOVE_DOWN == b) {
			rc = Action2Dir_t::SAME_LINE;
		} else if((Action_t::FIRE_UP == b)
			   || (Action_t::FIRE_DOWN == b)) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::MOVE_DOWN:
		if(Action_t::MOVE_UP == b) {
			rc = Action2Dir_t::SAME_LINE;
		} else if((Action_t::FIRE_UP == b)
			   || (Action_t::FIRE_DOWN == b)) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::MOVE_LEFT:
		if(Action_t::MOVE_RIGHT == b) {
			rc = Action2Dir_t::SAME_LINE;
		} else if((Action_t::FIRE_LEFT == b)
			   || (Action_t::FIRE_RIGHT == b)) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::MOVE_RIGHT:
		if(Action_t::MOVE_LEFT == b) {
			rc = Action2Dir_t::SAME_LINE;
		} else if((Action_t::FIRE_LEFT == b)
			   || (Action_t::FIRE_RIGHT == b)) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::FIRE_UP:
		if(Action_t::FIRE_DOWN == b) {
			rc = Action2Dir_t::SAME_LINE;
		} else if((Action_t::MOVE_UP == b)
			   || (Action_t::MOVE_DOWN == b)) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::FIRE_DOWN:
		if(Action_t::FIRE_UP == b) {
			rc = Action2Dir_t::SAME_LINE;
		} else if((Action_t::MOVE_UP == b)
			   || (Action_t::MOVE_DOWN == b)) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::FIRE_LEFT:
		if(Action_t::FIRE_RIGHT == b) {
			rc = Action2Dir_t::SAME_LINE;
		} else if((Action_t::MOVE_LEFT == b)
			   || (Action_t::MOVE_RIGHT == b)) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::FIRE_RIGHT:
		if(Action_t::FIRE_LEFT == b) {
			rc = Action2Dir_t::SAME_LINE;
		} else if((Action_t::MOVE_LEFT == b)
			   || (Action_t::MOVE_RIGHT == b)) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	default:
		break;
	}
	return rc;
}

bool Action::isMoveAction(const Action_t a) {
	return (Action_t::MOVE_ACTION_START <= a)
		&& (Action_t::MOVE_ACTION_END >= a);
}

bool Action::isFireAction(const Action_t a) {
	return (Action_t::FIRE_ACTION_START <= a)
		&& (Action_t::FIRE_ACTION_END >= a);
}

uint8_t Action::toNeighborhoodMask(Action_t action) {
	uint8_t rc = Layout::NONE;
	switch(action) {
	case Action_t::MOVE_UP:
		rc = Layout::UP;
		break;
	case Action_t::MOVE_DOWN:
		rc = Layout::DOWN;
		break;
	case Action_t::MOVE_LEFT:
		rc = Layout::LEFT;
		break;
	case Action_t::MOVE_RIGHT:
		rc = Layout::RIGHT;
		break;
	case Action_t::FIRE_UP:
		rc = Layout::UP;
		break;
	case Action_t::FIRE_DOWN:
		rc = Layout::DOWN;
		break;
	case Action_t::FIRE_LEFT:
		rc = Layout::LEFT;
		break;
	case Action_t::FIRE_RIGHT:
		rc = Layout::RIGHT;
		break;
	case Action_t::NONE:
		break;
	default:
		assert(0);
	}
	return rc;
}

uint8_t Action::toLineOfFireMask(Action_t action) {
	uint8_t rc = Layout::NONE;
	switch(action) {
	case Action_t::MOVE_UP:
	case Action_t::MOVE_DOWN:
		rc = Layout::UP | Layout::DOWN;
		break;
	case Action_t::MOVE_LEFT:
	case Action_t::MOVE_RIGHT:
		rc = Layout::RIGHT | Layout::LEFT;
		break;
	case Action_t::NONE:
		rc = Layout::UP | Layout::DOWN | Layout::RIGHT | Layout::LEFT;
		break;
	default:
		assert(0);
	}
	return rc;
}
