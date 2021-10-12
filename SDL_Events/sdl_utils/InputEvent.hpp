/*
 * InputEvent.hpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INPUT_INPUTEVENT_HPP_
#define UTILS_INPUT_INPUTEVENT_HPP_

#include "utils/drawing/Point.hpp"
#include "utils/input/EventDefines.h"

union SDL_Event;

class InputEvent {
public:
	InputEvent() = default;
	~InputEvent();

	bool pollEvent();

	bool checkForExitRequest() const {
		return m_ExitRequest;
	}

	/* Holds event position on the screen */
	Point m_Pos = Point::UNDEFINED;
	/* See EventDefines.h for more information */
	int32_t m_Key = Keyboard::KEY_UNKNOWN;
	uint8_t m_MouseButton = Mouse::UNKNOWN;
	TouchEvent m_Type = TouchEvent::UNKNOWN;

private:
	  bool m_ExitRequest = false;

	  void setEventTypeImpl(const SDL_Event & event);

	  void handleExitKey();
};

#endif /* UTILS_INPUT_INPUTEVENT_HPP_ */
