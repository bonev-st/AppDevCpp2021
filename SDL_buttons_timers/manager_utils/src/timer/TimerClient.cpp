/*
 * TimerClient.cpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#include "manager_utils/timer/TimerClient.hpp"

#include "manager_utils/managers/TimerMgr.hpp"

TimerClient::~TimerClient() {
	G_pTimerMgr->detachTimerClient(this);
}

bool TimerClient::startTimer(std::size_t &id, int64_t interval, TimerType_t type) {
	return G_pTimerMgr->startTimer(id, interval, this, type);
}

bool TimerClient::stopTimer(std::size_t id) {
	return G_pTimerMgr->stopTimer(id);
}

bool TimerClient::isActiveTimerId(std::size_t id) const {
	return G_pTimerMgr->isActiveTimerId(id);
}
