/*
 * RadioButton.cpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#include "game/widgets/RadioButton.hpp"

void RadioButton::attachCB(RadioCB_t * fn) {
	Button::attachCB(fn);
}

bool RadioButton::getSelected() const {
	return InputStates_t::CLICKED == getState();
}

void RadioButton::setSelected() {
	if(isUnlocked()) {
		setState(InputStates_t::CLICKED);
	}
}

void RadioButton::setDeslected() {
	if(isUnlocked()) {
		setState(InputStates_t::UNCLICKED);
	}
}

std::size_t RadioButton::getId() const {
	return Button::getId();
}

