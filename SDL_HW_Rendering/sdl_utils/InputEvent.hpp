/*
 * InputEvent.hpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INPUT_INPUTEVENT_HPP_
#define UTILS_INPUT_INPUTEVENT_HPP_

#include "utils/drawing/Point.hpp"
#include "utils/inputs/EventDefines.h"

union SDL_Event;

class InputEvent {
public:
	typedef const void * Handler_t;
	InputEvent() = default;
	~InputEvent() = default;

	bool pollEvent();

	bool isExitRequest() const {
		return m_ExitRequest;
	}

	void setExitRequest() {
		m_ExitRequest = true;
	}

	/* Holds event position on the screen */
	Point m_Pos = Point::UNDEFINED;
	/* See EventDefines.h for more information */
	Keyboard::Key m_Key = Keyboard::KEY_UNKNOWN;
	Mouse::MouseKey m_MouseButton = Mouse::UNKNOWN;
	TouchEvent m_Type = TouchEvent::UNKNOWN;

private:
	bool m_ExitRequest = false;

	void setEventTypeImpl(const SDL_Event &event);
};

#endif /* UTILS_INPUT_INPUTEVENT_HPP_ */
