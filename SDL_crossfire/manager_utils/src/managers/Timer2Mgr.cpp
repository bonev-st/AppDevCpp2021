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

const std::shared_ptr<TimerCfg_t> Timer2Mgr::start(uint32_t period, TimerMode_t mode, const TimerCB_t& cb) {
	if(!period) {
		std::cerr << "Invalid timer period " << period << std::endl;
		return nullptr;
	}
	if(TimerMode_t::INVALID == mode) {
		std::cerr << "Invalid timer mode " << static_cast<int32_t>(mode) << std::endl;
		return nullptr;
	}
	std::shared_ptr<TimerCfg_t> cfg(new TimerCfg_t, [](const TimerCfg_t * data) {
		SDL_Timer::deleteTimer(data->m_TimerSDL_Handler);
		delete data;
	});
	if(!cfg) {
		std::cerr << "Bad allocation" << std::endl;
		return nullptr;
	}
	auto &data = *cfg;
	data.m_Period = period;
	data.m_Mode = mode;
	data.m_CB = cb;
	if(nullptr == cfg) {
		std::cerr << "std::make_unique<TimerCfg_t>(() failed. Bad allocation" << std::endl;
        return nullptr;
	}
	if(!SDL_Timer::createTimer(*cfg)) {
		std::cerr << "SDL_Timer::createTimer() failed" << std::endl;
		return nullptr;
	}
	m_Container.push_front(cfg);
	const auto size = m_Container.size();
	if(size > m_MaxSize) {
		m_MaxSize = size;
	}
	cfg->m_Handler = m_Container.begin();
	return cfg;
}

void Timer2Mgr::stop(Iterator_t &handler) {
	release_timer_data(handler);
}

bool Timer2Mgr::isRunning(const Iterator_t &handler) const {
	assert(*handler);
	return INVALID_SLD_TIMER_HANDLER != (*handler)->m_TimerSDL_Handler;
}

bool Timer2Mgr::changePeriod(Timer2::Iterator_t &handler, uint32_t period) {
	assert(*handler);
	if(!period) {
		std::cerr << "Timer2Mgr::changePeriod failed. Invalid timer period " << period << std::endl;
		return false;
	}
	if(!isRunning(handler)) {
		std::cerr << "Timer2Mgr::changePeriod failed. Timer is inactive" << std::endl;
		return false;
	}
	(*handler)->m_Period = period;
	return true;
}


bool Timer2Mgr::handleEvent(const InputEvent & event) {
	if(TouchEvent::TIMER_EXPIRE != event.m_Type) {
		return false;
	}
	Timer2::TimerCfg_t &data = const_cast<Timer2::TimerCfg_t &>(*event.m_Timer);
	++data.m_CB_Counter;
	const auto mode = data.m_Mode;
	if(TimerMode_t::INVALID == data.m_Mode) {
		Timer2::Iterator_t &it = data.m_Handler;
		assert(*it);
		release_timer_data(it);
		return true;
	}
	auto & handler = data.m_Handler;
	auto & cb = data.m_CB;
	if(cb) {
		cb(reinterpret_cast<Timer2::TimerHandler_t>(&handler));
	} else {
		std::cout << "Warning: Timer2Mgr::events() callback is nullptr" << std::endl;
	}
	if(TimerMode_t::ONESHOT == mode) {
		assert(data.m_CB_Counter == data.m_SDL_CB_Counter);
		stop(handler);
	}
	return true;
}

void Timer2Mgr::release_timer_data(Timer2::Iterator_t & it) {
	assert(*it);
	if(Timer2::INVALID_SLD_TIMER_HANDLER != (*it)->m_TimerSDL_Handler) {
		SDL_Timer::deleteTimer((*it)->m_TimerSDL_Handler);
		(*it)->m_TimerSDL_Handler = Timer2::INVALID_SLD_TIMER_HANDLER;
	}
	(*it)->m_Mode = TimerMode_t::INVALID;
	if((*it)->m_CB_Counter == (*it)->m_SDL_CB_Counter) {
		m_Container.erase(it);
	}
}

std::size_t Timer2Mgr::getActive() const {
	return m_Container.size();
}

std::size_t Timer2Mgr::getMaxActive() const {
	return m_MaxSize;
}

Timer2::Iterator_t & Timer2Mgr::getIterator(Timer2::TimerHandler_t &handler) const {
	return *reinterpret_cast<Timer2::Iterator_t *>(&handler);
}
