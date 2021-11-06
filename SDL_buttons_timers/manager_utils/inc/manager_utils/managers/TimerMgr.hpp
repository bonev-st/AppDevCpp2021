/*
 * TimerMgr.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMERMGR_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMERMGR_HPP_

#include <cstdint>
#include <unordered_set>
#include <unordered_map>

#include "utils/time/Time.hpp"

#include "manager_utils/managers/BaseMgr.hpp"
#include "manager_utils/timer/TimerData.hpp"

class TimerClient;

class TimerMgr: public BaseMgr {
public:
	bool init(int64_t min_period);
	void process() final;
	bool startTimer(std::size_t &id, int64_t interval, TimerClient *client, TimerType_t type);
	bool stopTimer(std::size_t id);
	void detachTimerClient(const TimerClient *client);
	bool isActiveTimerId(std::size_t id) const;
	void onStart();

private:
	static std::size_t m_TimerID;
	Time m_ElapsedTime;
	std::unordered_map<std::size_t, TimerData> m_TimerMap;
	std::unordered_set<std::size_t> m_RemoveTimerSet;
	int64_t m_MinPeriod = 0;

	void removeTimers();
	void onTimerTimeout(std::size_t id, TimerData & data);
};

extern TimerMgr * G_pTimerMgr;

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMERMGR_HPP_ */
