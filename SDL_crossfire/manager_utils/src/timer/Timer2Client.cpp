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

Timer2Client::Timer2Client() :
	m_Singleton(*Timer2MgrInst::getInstance())
{
}

Timer2Client::~Timer2Client() {
	stop();
}

bool Timer2Client::start(uint32_t period, TimerMode_t mode, const TimerCB_t& cb) {
	if(!cb) {
		std::cerr << "Invalid callback" << std::endl;
	}
	stop();
	auto p_data = m_Singleton.start(period, mode, cb);
	m_Handler = p_data;
	return nullptr != p_data;
}

void Timer2Client::stop() {
	auto p_data = m_Handler.lock();
	if(p_data) {
		m_Singleton.stop(*p_data);
	}
}

bool Timer2Client::isRunning() const {
	auto p_data = m_Handler.lock();
	return p_data && m_Singleton.isRunning(*p_data);
}

bool Timer2Client::changePeriod(uint32_t period) {
	auto p_data = m_Handler.lock();
	return p_data && m_Singleton.changePeriod(*p_data, period);
}

bool Timer2Client::operator == (Timer2::TimerHandler_t handler) const {
	auto p_data = m_Handler.lock();
	return p_data && (*p_data == handler);
}
