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

bool Button::attachCB(ButtonCB_t * fn) {
	if(nullptr == fn) {
		std::cerr << "Try to initialize Callback for button with ID " << m_Id << " with nullptr" << m_Id << std::endl;
		return false;
	} else if(m_CB) {
		std::cerr << "Warning: Callback for button with ID " << m_Id << " is already initialized will be overwritten" << std::endl;
	}
	m_CB = fn;
	return true;
}

void Button::handleEvent(const InputEvent &e) {
	const auto state = getState();
	if(InputStates_t::DISABLED != state) {
		if(TouchEvent::TOUCH_PRESS == e.m_Type) {
			if(containsEvent(e) && (InputStates_t::CLICKED != state)) {
				m_Touched = true;
				setState(InputStates_t::CLICKED);
			}
		} else if(TouchEvent::TOUCH_RELEASE == e.m_Type) {
			if(m_Touched) {
				m_Touched = false;
				setState(InputStates_t::UNCLICKED);
				if(containsEvent(e)) {
					(*m_CB)(m_Id);
				}
			}
		}
	}
}

std::size_t Button::getId() const {
	return m_Id;
}
