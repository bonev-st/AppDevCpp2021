/*
 * ActionBuffer.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#include "game/action/ActionBuffer.hpp"

#include <iostream>

bool ActionBuffer::init(ActionClientIF * client) {
	if(!client) {
		std::cerr << "Invalid ActionClient pointer" << std::endl;
		return false;
	}
	m_Client = client;
	return true;
}

Action_t ActionBuffer::operator = (Action_t action) {
	if(Action_t::NONE != action) {
		m_ActionBuffer = action;
		if(m_Client->process(m_ActionBuffer)) {
			m_ActionBuffer = Action_t::NONE;
		}
	}
	return action;
}

void ActionBuffer::force() {
	if(m_Client->process(m_ActionBuffer, true)) {
		m_ActionBuffer = Action_t::NONE;
	}
}
