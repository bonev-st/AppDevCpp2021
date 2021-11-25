/*
 * Timer.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "sdl_utils/Timer.hpp"

#include <iostream>
#include <SDL_timer.h>
#include <SDL_events.h>

#include "utils/timer/Timer2Cfg.hpp"
#include "utils/inputs/EventDefines.h"

static uint32_t timerCB([[maybe_unused]]std::uint32_t period, void* param) {
    SDL_UserEvent userevent {};
    userevent.type = EventType::TIMER_EXPIRE;
    userevent.data1 = param;
	auto data = reinterpret_cast<Timer2::TimerCfg_t *>(param);
    const auto enabled = Timer2::INVALID_TIMER_HANDLER != data->m_TimerSDL_Handler;
    if(!enabled) {
    	std::cerr << "Enter in timerCB with invalid SDL timer handler" << std::endl;
    	return 0;
    }
    if(!SDL_PushEvent(reinterpret_cast<SDL_Event*>(&userevent))) {
    	std::cerr << "SDL_PushEvent() from timerCB() failed." << std::endl;
    }
    ++data->m_SDL_CB_Counter;
    if(Timer2::TimerMode_t::RELOAD != data->m_Mode) {
		data->m_TimerSDL_Handler = Timer2::INVALID_SLD_TIMER_HANDLER;
		return 0;
    }
	return data->m_Period;
}

namespace SDL_Timer {

void delay(std::uint32_t ms) {
	SDL_Delay(ms);
}

bool createTimer(Timer2::TimerCfg_t & cfg) {
	const auto id = SDL_AddTimer(cfg.m_Period, &timerCB, &cfg);
	cfg.m_TimerSDL_Handler = id;
	if(Timer2::INVALID_SLD_TIMER_HANDLER == id) {
		std::cerr << "SDL_AddTimer() failed." << std::endl;
		return false;
	}
	return true;
}

bool deleteTimer(int32_t id) {
	bool rc = true;
	if(Timer2::INVALID_SLD_TIMER_HANDLER != id) {
		rc = SDL_RemoveTimer(id);
		if(!rc) {
			std::cerr << "SDL_RemoveTimer() failed." << std::endl;
		}
	}
	return rc;
}

} /* namespace SDL_Timer */
