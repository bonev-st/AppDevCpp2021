/*
 * ButtonBase.hpp
 *
 *  Created on: Nov 3, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_BUTTONBASE_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_BUTTONBASE_HPP_

#include "utils/inputs/InputEventIF.hpp"
#include "manager_utils/drawing/Image.hpp"
#include "manager_utils/input/InputState.hpp"

class InputEvent;

class ButtonBase : public Image, public InputEventIF {
public:
	virtual void draw() const;
	bool isUnlocked() const;
	bool containsEvent(const InputEvent &e);
	virtual void setState(InputStates_t state);
	InputStates_t getState() const;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_BUTTONBASE_HPP_ */
