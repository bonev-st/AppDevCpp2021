/*
 * Timer1Client.hpp
 *
 *  Created on: Nov 11, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMER1CLIENT_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMER1CLIENT_HPP_

#include <cstdint>
#include <unordered_map>
#include <memory>

#include "utils/timer/Timer1ClientIF.hpp"
#include "utils/timer/Timer1Cfg.hpp"

class Timer1Client : Timer1ClientIF {
public:
	~Timer1Client();
	bool startTimer(Timer1::Timer1Handler_t &id, int32_t interval, Timer1::Timer1Mode_t mode, const Timer1::Timer1CB_t &cb);
	bool stopTimer(Timer1::Timer1Handler_t &id);
	bool isActiveTimerId(Timer1::Timer1Handler_t id) const;

	std::size_t getTimersNumb() const final;

private:
	std::unordered_map<Timer1::Timer1Handler_t, std::unique_ptr<Timer1::Timer1Cfg_t>> m_TimersContainer;

	void removeExpired(Timer1::Timer1Handler_t id) final;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMER1CLIENT_HPP_ */
