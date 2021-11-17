/*
 * Timer2Mgr.cpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/Timer2Mgr.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>

#include "utils/timer/Timer2Cfg.hpp"

#include "sdl_utils/Timer.hpp"
#include "sdl_utils/InputEvent.hpp"

using namespace Timer2;

bool Timer2Mgr::init(uint32_t min_period) {
	m_MinPeriod = min_period;
	return true;
}

TimerHandler_t Timer2Mgr::start(uint32_t period, TimerMode_t mode, const TimerCB_t& cb) {
	if(m_MinPeriod > period) {
		std::cerr << "Timer2Mgr::start failed. Try to set too small interval "
				   << period << ", the minimum interval is " << m_MinPeriod << std::endl;
		return false;
	}
	assert(period);
	assert(TimerMode_t::INVALID != mode);
	TimerCfg_t data;
	data.m_Period = period;
	data.m_Mode = mode;
	data.m_CB = cb;
	auto cfg = std::make_shared<TimerCfg_t>(data);
	if(nullptr == cfg) {
		std::cerr << "std::make_unique<TimerCfg_t>(() failed. Bad allocation" << std::endl;
        return false;
	}
	cfg->m_Handler = m_Container.add(cfg);
	if(!SDL_Timer::createTimer(*cfg)) {
		std::cerr << "SDL_Timer::createTimer() failed" << std::endl;
		return INVALID_TIMER_HANDLER;
	}
	return cfg->m_Handler;
}

void Timer2Mgr::stop(TimerHandler_t handler) {
	if(INVALID_TIMER_HANDLER == handler) {
		return;
	}
	auto &cfg = **m_Container.get(handler);
	SDL_Timer::deleteTimer(cfg.m_TimerSDL_Hadler);
	cfg.m_Mode = TimerMode_t::INVALID;
	release_timer_data(cfg);
}

bool Timer2Mgr::isRunning(TimerHandler_t handler) const {
	if(INVALID_TIMER_HANDLER == handler) {
		return false;
	}
	return TimerMode_t::INVALID != (*m_Container.get(handler))->m_Mode;
}

bool Timer2Mgr::handleEvent(const InputEvent & event) {
	if(TouchEvent::TIMER_EXPIRE != event.m_Type) {
		return false;
	}
	auto * data = event.m_Timer;
	const auto handler = data->m_Handler;
	++(*m_Container.get(handler))->m_CB_Counter;
	const auto mode = data->m_Mode;
	if(TimerMode_t::INVALID == mode) {
		release_timer_data(*data);
		return true;
	}
	auto & cb = data->m_CB;
	if(!cb) {
		std::cerr << "Timer2Mgr::events() failed. Invalid callback function for timer with handler "
				  << handler << std::endl;
		return true;
	}
	cb(handler);
	if(TimerMode_t::ONESHOT == mode) {
		assert(data->m_CB_Counter == data->m_SDL_CB_Counter);
		if(!m_Container.release(handler)) {
			std::cerr << "Timer2Mgr::events() failed, try to release invalid entity with id "
					  << handler << std::endl;
		}
	}
	return true;
}

void Timer2Mgr::release_timer_data(const Timer2::TimerCfg_t & data) {
	if(data.m_CB_Counter == data.m_SDL_CB_Counter) {
		if(!m_Container.release(data.m_Handler)) {
			std::cerr << "Timer2Mgr::events() failed, try to release invalid entity with id "
					  << data.m_Handler << std::endl;
		}
	}
}

std::size_t Timer2Mgr::getActive() const {
	return m_Container.getValid();
}

std::size_t Timer2Mgr::getMaxActive() const {
	return m_Container.getMaxValid();
}
