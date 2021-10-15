/*
 * EventReg_IF.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef EVENTREG_IF_HPP_
#define EVENTREG_IF_HPP_

#include <cstdint>
#include <functional>

#include "utils/inputs/EventDefines.h"

class InputEvent;

class EventReg_IF {
public:
	virtual ~EventReg_IF() = default;

	using EventCallback = std::function<void(const InputEvent&)>;

	virtual std::int32_t registerExitKey(Keyboard::Key type) = 0;
	virtual std::int32_t registerKeyboard(Keyboard::Key type, EventCallback callback) = 0;
	virtual std::int32_t registerMouse(Mouse::MouseKey type, EventCallback callback) = 0;
};

#endif /* EVENTREG_IF_HPP_ */
