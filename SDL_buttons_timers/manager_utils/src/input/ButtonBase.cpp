/*
 * ButtonBase.cpp
 *
 *  Created on: Nov 3, 2021
 *      Author: stanimir
 */

#include "manager_utils/input/ButtonBase.hpp"

#include "sdl_utils/InputEvent.hpp"

void ButtonBase::draw() const {
	Image::draw();
}

bool ButtonBase::isUnlocked() const {
	return getVisible() && InputStates_t::DISABLED != getState();
}

bool ButtonBase::containsEvent(const InputEvent &e) {
	return isUnlocked() && isContains(e.m_Pos);
}

void ButtonBase::setState(InputStates_t state) {
	setFrame(static_cast<std::size_t>(state));
}

InputStates_t ButtonBase::getState() const {
	return getVisible() ? static_cast<InputStates_t>(getFrame())
						: InputStates_t::DISABLED;
}
