/*
 * Timer2Client.cpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#include "manager_utils/timer/Timer2Client.hpp"

#include "manager_utils/managers/Timer2Mgr.hpp"

using namespace Timer2;

Timer2Client::Timer2Client() :
	m_Singleton(*Timer2MgrInst::getInstance())
{
}

bool Timer2Client::start(uint32_t period, TimerMode_t mode, const TimerCB_t& cb) {
	m_Handler.set(m_Singleton.start(period, mode, cb), [](TimerHandler_t handler) {
		Timer2MgrInst::getInstance()->stop(handler);
	});
	return INVALID_TIMER_HANDLER != m_Handler;
}

void Timer2Client::stop() {
	m_Handler.reset();
}

bool Timer2Client::isRunning() const {
	return m_Singleton.isRunning(m_Handler);
}

bool Timer2Client::operator == (Timer2::TimerHandler_t handler) const {
	return m_Handler == handler;
}
