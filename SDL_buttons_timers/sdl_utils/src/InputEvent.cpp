/*
 * InputEvent.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "sdl_utils/InputEvent.hpp"
#include "sdl_utils/Timer.hpp"

#include <SDL_events.h>

bool InputEvent::pollEvent() {
	SDL_Event event;
	if (!SDL_PollEvent(&event)) {
		return false;
	}
	SDL_GetMouseState(&m_Pos.m_X, &m_Pos.m_Y);
	setEventTypeImpl(event);
	return true;
}

void InputEvent::setEventTypeImpl(const SDL_Event &event) {
	switch (event.type) {
	case EventType::KEYBOARD_PRESS:
		m_Key = static_cast<Keyboard::Key>(event.key.keysym.sym);
		m_MouseButton = Mouse::UNKNOWN;
		m_Type = TouchEvent::KEYBOARD_PRESS;
		break;
	case EventType::KEYBOARD_RELEASE:
		m_Key = static_cast<Keyboard::Key>(event.key.keysym.sym);
		m_MouseButton = Mouse::UNKNOWN;
		m_Type = TouchEvent::KEYBOARD_RELEASE;
		break;
	case EventType::MOUSE_PRESS:
	case EventType::FINGER_PRESS:
		m_MouseButton = static_cast<Mouse::MouseKey>(event.button.button);
		m_Key = Keyboard::KEY_UNKNOWN;
		m_Type = TouchEvent::TOUCH_PRESS;
		break;
	case EventType::MOUSE_RELEASE:
	case EventType::FINGER_RELEASE:
		m_MouseButton = static_cast<Mouse::MouseKey>(event.button.button);
		m_Key = Keyboard::KEY_UNKNOWN;
		m_Type = TouchEvent::TOUCH_RELEASE;
		break;
	case EventType::QUIT:
		//X is pressed on the window (or CTRL-C signal is sent)
		m_ExitRequest = true;
		break;

	case EventType::TIMER_EXPIRE:
		m_Timer = reinterpret_cast<TimerData_t>(reinterpret_cast<const SDL_UserEvent *>(&event)->data1);
		m_Type  = TouchEvent::TIMER_EXPIRE;
		break;

	default:
		m_Type = TouchEvent::UNKNOWN;
		break;
	}
}
