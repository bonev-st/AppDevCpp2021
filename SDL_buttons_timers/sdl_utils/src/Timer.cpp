/*
 * Timer1.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "sdl_utils/Timer.hpp"

#include <iostream>
#include <SDL_timer.h>
#include <SDL_events.h>

#include "utils/timer/Timer1Cfg.hpp"
#include "utils/timer/Timer1ClientIF.hpp"

#include "utils/inputs/EventDefines.h"
#include "sdl_utils/SDLHelper.hpp"

static uint32_t timerCB(std::uint32_t period, void* param) {
	Timer1::Timer1Cfg_t * data = reinterpret_cast<Timer1::Timer1Cfg_t *>(param);
    SDL_UserEvent userevent {};
    userevent.type = EventType::TIMER_EXPIRE;
    userevent.code  = data->m_Handler;
    userevent.data1 = param;
    userevent.data2 = nullptr;
    SDL_PushEvent(reinterpret_cast<SDL_Event*>(&userevent));
    const bool oneshot = Timer1::Timer1Mode_t::ONESHOT == data->m_Mode;
	return oneshot?0:period;
}

namespace SDL_Timer {

void delay(std::uint32_t ms) {
	SDL_Delay(ms);
}

bool createTimer(Timer1::Timer1Cfg_t & cfg) {
	const auto id = SDL_AddTimer(cfg.m_Period, &timerCB, &cfg);
	if(0 == id) {
		SDLHelper::print_SDL_Error("SDL_AddTimer() failed.");
		return false;
	}
	cfg.m_Handler = id;
	return true;
}

bool deleteTimer(int32_t id) {
	bool rc = true;
	if(Timer1::INVALID_TIMER1_HANDLER != id) {
		rc = SDL_RemoveTimer(id);
		if(!rc) {
			SDLHelper::print_SDL_Error("SDL_RemoveTimer() failed.");
		}
	}
	return rc;
}

void eventHandler(const SDL_UserEvent * event) {
	const Timer1::Timer1Cfg_t * data = reinterpret_cast<const Timer1::Timer1Cfg_t *>(event->data1);
	const auto handler = data->m_Handler;
	if(data->m_CB) {
		data->m_CB(handler);
	}
	if(Timer1::Timer1Mode_t::ONESHOT == data->m_Mode) {
		data->m_Client->removeExpired(handler);
	}
}

} /* namespace SDL_Timer */
