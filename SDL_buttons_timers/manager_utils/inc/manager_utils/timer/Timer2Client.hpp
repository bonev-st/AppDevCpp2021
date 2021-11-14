/*
 * Timer2Client.hpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMER2CLIENT_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMER2CLIENT_HPP_

#include "utils/timer/Timer2Def.hpp"
#include "utils/RAII_Handler.hpp"

class Timer2Mgr;

class Timer2Client {
public:
	Timer2Client();
	bool start(uint32_t period, Timer2::TimerMode_t mode, const Timer2::TimerCB_t& cb);
	void stop();
	bool isRunning() const;
	bool operator == (Timer2::TimerHandler_t handler) const;

private:
	Timer2Mgr &m_Singleton;
	RAII_Handler<Timer2::TimerHandler_t, Timer2::INVALID_TIMER_HANDLER, std::function<void(Timer2::TimerHandler_t)>> m_Handler;

	void deleter();
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMER2CLIENT_HPP_ */
