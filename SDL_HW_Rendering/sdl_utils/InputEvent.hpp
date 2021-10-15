/*
 * InputEvent.hpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INPUT_INPUTEVENT_HPP_
#define UTILS_INPUT_INPUTEVENT_HPP_

#include <unordered_map>
#include <list>

#include "EventReg_IF.hpp"
#include "utils/drawing/Point.hpp"
#include "utils/inputs/EventDefines.h"

union SDL_Event;

class InputEvent {
public:
	typedef const void * Handler_t;
	InputEvent() = default;
	~InputEvent() = default;

	bool pollEvent();

	void registerKeyboard(Keyboard::Key type, EventReg_IF::EventCallback callback);
	void registerMouse(Mouse::MouseKey type, EventReg_IF::EventCallback callback);

	bool isExitRequest() const {
		return m_ExitRequest;
	}

	void setExitRequest() {
		m_ExitRequest = true;
	}

	/* Holds event position on the screen */
	Point m_Pos = Point::UNDEFINED;
	/* See EventDefines.h for more information */
	int32_t m_Key = Keyboard::KEY_UNKNOWN;
	uint8_t m_MouseButton = Mouse::UNKNOWN;
	TouchEvent m_Type = TouchEvent::UNKNOWN;

private:
	typedef std::unordered_map<uint32_t, std::list<EventReg_IF::EventCallback>> Callbacks;
	bool m_ExitRequest = false;

	Callbacks m_KeyboardCallbacks;
	Callbacks m_MouseCallbacks;

	void setEventTypeImpl(const SDL_Event &event);
	void eventsHandlerImpl(const Callbacks& registered);
};

#endif /* UTILS_INPUT_INPUTEVENT_HPP_ */
