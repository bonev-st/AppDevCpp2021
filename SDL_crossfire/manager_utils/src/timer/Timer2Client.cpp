/*
 * Timer2Client.cpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#include "manager_utils/timer/Timer2Client.hpp"

#include <iostream>

#include "manager_utils/managers/Timer2Mgr.hpp"

using namespace Timer2;

Timer2Client::~Timer2Client() {
	stop();
}

bool Timer2Client::start(uint32_t period, TimerMode_t mode, const TimerCB_t& cb) {
	if(!cb) {
		std::cout << "Warning: invalid callback" << std::endl;
	}
	stop();
	auto p_data = Timer2MgrInst::getInstance()->start(period, mode, cb);
	m_Handler = p_data;
	return nullptr != p_data;
}

void Timer2Client::stop() {
	auto p_data = m_Handler.lock();
	if(p_data) {
		Timer2MgrInst::getInstance()->stop(p_data->m_Handler);
	}
}

bool Timer2Client::isRunning() const {
	auto p_data = m_Handler.lock();
	return p_data && Timer2MgrInst::getInstance()->isRunning(p_data->m_Handler);
}

bool Timer2Client::changePeriod(uint32_t period) {
	auto p_data = m_Handler.lock();
	return p_data && Timer2MgrInst::getInstance()->changePeriod(p_data->m_Handler, period);
}

bool Timer2Client::operator == (Timer2::TimerHandler_t handler) const {
	auto p_data = m_Handler.lock();
	return p_data && (reinterpret_cast<Timer2::TimerHandler_t>(&(p_data->m_Handler)) == handler);
}

bool Timer2Client::operator != (Timer2::TimerHandler_t handler) const {
	return !operator == (handler);
}
