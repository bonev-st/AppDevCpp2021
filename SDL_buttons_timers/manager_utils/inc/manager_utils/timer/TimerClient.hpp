/*
 * TimerClient.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMERCLIENT_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMERCLIENT_HPP_

#include <cstdint>

#include "manager_utils/timer/TimerData.hpp"

class TimerClient {
public:
	virtual ~TimerClient();

	virtual void onTimeout(std::size_t id) = 0;
	bool startTimer(std::size_t &id, int64_t interval, TimerType_t type);
	bool stopTimer(std::size_t id);
	bool isActiveTimerId(std::size_t id) const;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMERCLIENT_HPP_ */
