/*
 * Button.cpp
 *
 *  Created on: Nov 3, 2021
 *      Author: stanimir
 */

#include "game/widgets/Button.hpp"

#include <iostream>

#include "sdl_utils/InputEvent.hpp"

bool Button::create(std::size_t button_id, std::size_t image_id, const Point &pos) {
	m_Id = button_id;
	return ButtonBase::create(image_id, pos);
}

bool Button::attachCB(const ButtonCB_t & fn) {
	m_CB = fn;
	return true;
}

bool Button::handleEvent(const InputEvent &e) {
	bool rc = false;
	const auto state = getState();
	if(InputStates_t::DISABLED != state) {
		if(TouchEvent::TOUCH_PRESS == e.m_Type) {
			if(containsEvent(e)) {
				if((InputStates_t::CLICKED != state)) {
					m_Touched = true;
					setState(InputStates_t::CLICKED);
				}
				rc = true;
			}
		} else if(TouchEvent::TOUCH_RELEASE == e.m_Type) {
			if(m_Touched) {
				m_Touched = false;
				setState(InputStates_t::UNCLICKED);
				if(m_CB && containsEvent(e)) {
					m_CB(m_Id);
					rc = true;
				}
			}
		}
	}
	return rc;
}

std::size_t Button::getId() const {
	return m_Id;
}
