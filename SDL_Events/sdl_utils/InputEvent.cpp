/*
 * InputEvent.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "InputEvent.hpp"

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
		m_Key = event.key.keysym.sym;
		m_MouseButton = Mouse::UNKNOWN;
		m_Type = TouchEvent::KEYBOARD_PRESS;
		eventsHandlerImpl(m_KeyboardCallbacks);
		break;

	case EventType::KEYBOARD_RELEASE:
		m_Key = event.key.keysym.sym;
		m_MouseButton = Mouse::UNKNOWN;
		m_Type = TouchEvent::KEYBOARD_RELEASE;
		eventsHandlerImpl(m_KeyboardCallbacks);
		break;

		//NOTE: the fall-through is intentional
	case EventType::MOUSE_PRESS:
	case EventType::FINGER_PRESS:
		m_MouseButton = event.button.button;
		m_Key = Keyboard::KEY_UNKNOWN;
		m_Type = TouchEvent::TOUCH_PRESS;
		eventsHandlerImpl(m_MouseCallbacks);
		break;

	case EventType::MOUSE_RELEASE:
	case EventType::FINGER_RELEASE:
		m_MouseButton = event.button.button;
		m_Key = Keyboard::KEY_UNKNOWN;
		m_Type = TouchEvent::TOUCH_RELEASE;
		eventsHandlerImpl(m_MouseCallbacks);
		break;

		//X is pressed on the window (or CTRL-C signal is sent)
	case EventType::QUIT:
		m_ExitRequest = true;
		break;

	default:
		break;
	}
}

void InputEvent::registerKeyboard(Keyboard::Key type, EventCallback callback) {
	m_KeyboardCallbacks[type].push_back(callback);
}

void InputEvent::registerMouse(Mouse::MouseKey type, EventCallback callback) {
	m_MouseCallbacks[type].push_back(callback);
}

void InputEvent::eventsHandlerImpl(const Callbacks& registered) {
	const auto it = registered.find(m_Key);
	if(m_KeyboardCallbacks.end() != it) {
		for (auto& cb : it->second) {
			cb(*this);
		}
	}
}
