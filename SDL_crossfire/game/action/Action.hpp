/*
 * Action.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_ACTION_ACTION_HPP_
#define GAME_ACTION_ACTION_HPP_

#include <cstdint>

namespace Layout {
enum GridNeighborhoodType_t : uint8_t;
}

enum class Action_t {
	NONE,
	MOVE_ACTION_START,
	MOVE_UP = MOVE_ACTION_START, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT,
	MOVE_ACTION_END = MOVE_LEFT,
	FIRE_ACTION_START,
	FIRE_UP = FIRE_ACTION_START, FIRE_RIGHT, FIRE_DOWN, FIRE_LEFT,
	FIRE_ACTION_END = FIRE_LEFT,
};


enum class Action2Dir_t {
	NOT_SAME,
	SAME,
	SAME_LINE
};

namespace Action {

Action2Dir_t compare(const Action_t a, const Action_t b);
bool isMoveAction(const Action_t a);
bool isFireAction(const Action_t a);
uint8_t toNeighborhoodMask(Action_t action);
uint8_t toLineOfFireMask(Action_t action);

}

#endif /* GAME_ACTION_ACTION_HPP_ */
