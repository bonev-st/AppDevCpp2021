/*
 * ActionBuffer.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_ACTION_ACTIONBUFFER_HPP_
#define GAME_ACTION_ACTIONBUFFER_HPP_

#include "game/action/Action.hpp"

class ActionBuffer {
public:
	Action_t operator = (Action_t action);
	operator Action_t () const;
	bool empty() const;
	void clear();

private:
	Action_t m_ActionBuffer = Action_t::NONE;
};

#endif /* GAME_ACTION_ACTIONBUFFER_HPP_ */
