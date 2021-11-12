/*
 * Timer1Mgr.hpp
 *
 *  Created on: Nov 7, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMER1MGR_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMER1MGR_HPP_

#include <unordered_set>

#include "manager_utils/managers/BaseMgr.hpp"
#include "utils/timer/Timer1Cfg.hpp"

class Timer1ClientIF;

class Timer1Mgr: public BaseMgr {
public:
	bool init(int32_t min_period);
	bool startTimer(Timer1::Timer1Cfg_t & cfg);
	bool stopTimer(Timer1::Timer1Handler_t id);

private:
	int32_t m_MinPeriod = 0;
};

extern Timer1Mgr * G_pTimer1Mgr;

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMER1MGR_HPP_ */
