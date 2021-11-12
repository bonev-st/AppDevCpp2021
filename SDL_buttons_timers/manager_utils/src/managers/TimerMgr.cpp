/*
 * TimerMgr.cpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/TimerMgr.hpp"

#include <iostream>

#include "manager_utils/timer/TimerClient.hpp"

TimerMgr *G_pTimerMgr = nullptr;

TimerHandler_t TimerMgr::m_TimerID;

bool TimerMgr::init(int64_t min_period) {
	m_MinPeriod = min_period;
	return true;
}

bool TimerMgr::process() {
	removeTimers();
	m_ElapsedTime.start();
	const int64_t elapsed_ms = m_ElapsedTime.toTime<Time::Milliseconds_t>();
	for(auto& [id, data] : m_TimerMap) {
		data.m_Remaining -= elapsed_ms;
		if (0 > data.m_Remaining) {
			onTimerTimeout(id, data);
		}
	}
	removeTimers();
	return true;
}

bool TimerMgr::startTimer(TimerHandler_t &id, int64_t interval, TimerClient *client, TimerType_t type) {
	id = m_TimerID++;
	if(m_MinPeriod > interval) {
		std::cerr << "For Timer " << id << ", try to set too small interval "
				   << interval << " the minimum interval is " << m_MinPeriod << std::endl;
		return false;
	}
	m_TimerMap.emplace(id, TimerData(interval, client, type));
	return true;
}

bool TimerMgr::stopTimer(TimerHandler_t & id) {
	if(INVALID_TIMER_HANDLER == id) {
		return true;
	}
	if(m_TimerMap.end() == m_TimerMap.find(id)) {
		std::cerr << "Timer " << id << "not exist" << std::endl;
		return false;
	}
	m_RemoveTimerSet.insert(id);
	id = INVALID_TIMER_HANDLER;
	return true;
}

void TimerMgr::detachTimerClient(const TimerClient *client) {
	for(const auto& [id, data] : m_TimerMap) {
		if (data.m_Client == client) {
			m_RemoveTimerSet.insert(id);
		}
	}
}

bool TimerMgr::isActiveTimerId(TimerHandler_t id) const {
	return (m_RemoveTimerSet.end() == m_RemoveTimerSet.find(id))
		&& (m_TimerMap.end() != m_TimerMap.find(id));
}

void TimerMgr::onStart() {
	m_ElapsedTime.start();
}

void TimerMgr::removeTimers() {
	for (const auto id : m_RemoveTimerSet) {
		auto it = m_TimerMap.find(id);
		if (m_TimerMap.end() != it) {
			m_TimerMap.erase(id);
		} else {
			std::cerr << "TimerMgr::removeTimers() failed, Can't find timer " << id << std::endl;
		}
	}
	m_RemoveTimerSet.clear();
}

void TimerMgr::onTimerTimeout(TimerHandler_t id, TimerData & data) {
	data.m_Client->onTimeout(id);
	if(TimerType_t::ONESHOT == data.m_Type) {
		m_RemoveTimerSet.insert(id);
	} else {
		data.m_Remaining += data.m_Interval;
	}
}
