/*
 * ActionBuffer.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#include "game/action/ActionBuffer.hpp"

Action_t ActionBuffer::operator = (Action_t action) {
	if(Action_t::NONE != action) {
		m_ActionBuffer = action;
	}
	return action;
}

ActionBuffer::operator Action_t () const {
	return m_ActionBuffer;
}

bool ActionBuffer::empty() const {
	return Action_t::NONE == m_ActionBuffer;
}
void ActionBuffer::clear() {
	m_ActionBuffer = Action_t::NONE;
}
