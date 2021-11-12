/*
 * ToggleButton.cpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#include "game/widgets/ToggleButton.hpp"

#include <iostream>

#include "sdl_utils/InputEvent.hpp"

bool ToggleButton::create(std::size_t button_id, std::size_t image_id, const Point &pos) {
	m_Id = button_id;
	return ButtonBase::create(image_id, pos);
}

bool ToggleButton::attachCB(const ToggleButtonCB_t & fn) {
	if(nullptr == fn) {
		std::cerr << "Try to initialize Callback for button with ID " << m_Id << " with nullptr" << m_Id << std::endl;
		return false;
	} else if(m_CB) {
		std::cerr << "Warning: Callback for button with ID " << m_Id << " is already initialized will be overwritten" << std::endl;
	}
	m_CB = fn;
	return true;
}

bool ToggleButton::handleEvent(const InputEvent &e) {
	bool rc = false;
	const auto state = getState();
	if(InputStates_t::DISABLED != state) {
		if(TouchEvent::TOUCH_PRESS == e.m_Type) {
			if(containsEvent(e)) {
				m_Touched = true;
				if(InputStates_t::CLICKED != state) {
					setState(InputStates_t::CLICKED);
				}
				rc = true;
			}
		} else if(TouchEvent::TOUCH_RELEASE == e.m_Type) {
			if(m_Touched) {
				m_Touched = false;
				if(containsEvent(e)) {
					m_Pressed ^= true;
					if(m_CB) {
						m_CB(m_Id, m_Pressed);
					}
					rc = true;
				}
				setState(m_Pressed?InputStates_t::CLICKED:InputStates_t::UNCLICKED);
			}
		}
	}
	return rc;
}

std::size_t ToggleButton::getId() const {
	return m_Id;
}
