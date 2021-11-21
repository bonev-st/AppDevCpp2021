/*
 * ActionBuffer.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_ACTION_ACTIONBUFFER_HPP_
#define GAME_ACTION_ACTIONBUFFER_HPP_

#include "game/action/ActionClientIF.hpp"

class ActionBuffer {
public:
	bool init(ActionClientIF * client);
	Action_t operator = (Action_t action);
	void force();

private:
	Action_t m_ActionBuffer = Action_t::NONE;
	ActionClientIF * m_Client = nullptr;
};

#endif /* GAME_ACTION_ACTIONBUFFER_HPP_ */
