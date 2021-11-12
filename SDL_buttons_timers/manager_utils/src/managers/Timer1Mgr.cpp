/*
 * Timer1Mgr.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/Timer1Mgr.hpp"

#include <iostream>

#include "utils/inputs/EventDefines.h"

#include "sdl_utils/Timer.hpp"

#include "manager_utils/timer/Timer1Client.hpp"

Timer1Mgr * G_pTimer1Mgr = nullptr;

bool Timer1Mgr::init(int32_t min_period) {
	m_MinPeriod = min_period;
	return true;
}

bool Timer1Mgr::startTimer(Timer1::Timer1Cfg_t & cfg) {
	if(Timer1::INVALID_TIMER1_HANDLER != cfg.m_Handler) {
		std::cerr << "Timer handler is already initialized" << std::endl;
		return false;
	}
	if(!SDL_Timer::createTimer(cfg)) {
		std::cerr << "SDL_Timer::createTimer() fault" << std::endl;
		return false;
	}
	return true;
}

bool Timer1Mgr::stopTimer(Timer1::Timer1Handler_t id) {
	if(!SDL_Timer::deleteTimer(id)) {
		std::cerr << "SDL_Timer::createTimer() fault" << std::endl;
		return false;
	}
	return true;
}
