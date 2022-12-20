/*
 * ButtonBase.hpp
 *
 *  Created on: Nov 3, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_BUTTONBASE_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_BUTTONBASE_HPP_

#include "gr_engine/drawing/Image.hpp"
#include "gr_engine/input/InputState.hpp"
#include "utils/inputs/InputEventIF.hpp"

class InputEvent;

class ButtonBase : public Image, public InputEventIF {
public:
	virtual void draw() override;
	bool isUnlocked() const;
	bool containsEvent(const InputEvent &e);
	virtual void setState(InputStates_t state);
	InputStates_t getState() const;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_BUTTONBASE_HPP_ */
