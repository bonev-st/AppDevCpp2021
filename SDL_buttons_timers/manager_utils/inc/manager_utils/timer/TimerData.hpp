/*
 * TimerData.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMERDATA_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMERDATA_HPP_

#include <cstdint>

class TimerClient;

enum class TimerType_t : uint8_t {
	ONESHOT,
	RELOAD
};

struct TimerData {
	TimerData(int64_t interval, TimerClient * client, TimerType_t type) :
	  m_Interval(interval)
	, m_Remaining(interval)
	, m_Client(client)
	, m_Type(type)
	{
	}

	int64_t m_Interval = 0;
	int64_t m_Remaining = 0;
	TimerClient *m_Client = nullptr;
	TimerType_t m_Type = TimerType_t::ONESHOT;
};


#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMERDATA_HPP_ */
