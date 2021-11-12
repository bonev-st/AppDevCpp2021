/*
 * Timer1Client.cpp
 *
 *  Created on: Nov 11, 2021
 *      Author: stanimir
 */

#include "manager_utils/timer/Timer1Client.hpp"

#include <iostream>

#include "manager_utils/managers/Timer1Mgr.hpp"

using namespace Timer1;

Timer1Client::~Timer1Client() {
	for(auto const & [id, data] : m_TimersContainer) {
		G_pTimer1Mgr->stopTimer(id);
	}
	m_TimersContainer.clear();
}

bool Timer1Client::startTimer(Timer1Handler_t &id, int32_t interval, Timer1Mode_t mode, const Timer1CB_t &cb) {
	auto cfg = std::make_unique<Timer1::Timer1Cfg_t>();
	if(!cfg) {
		std::cerr << "std::make_unique<Timer1::Timer1Cfg_t>() failed. Bad allocation" << std::endl;
		return false;
	}
	cfg->m_CB = cb;
	cfg->m_Mode = mode;
	cfg->m_Period = interval;
	if(!G_pTimer1Mgr->startTimer(*cfg.get())) {
		std::cerr << "G_pTimer1Mgr->startTimer() failed" << std::endl;
		return false;
	}
	id = cfg->m_Handler;
	m_TimersContainer[id] = std::move(cfg);
	return true;
}

bool Timer1Client::stopTimer(Timer1Handler_t & id) {
	if(INVALID_TIMER1_HANDLER != id) {
		if(!G_pTimer1Mgr->stopTimer(id)) {
			std::cerr << "G_pTimer1Mgr->stopTimer() failed, timer Id" <<  id << std::endl;
			return false;
		}
		m_TimersContainer.erase(id);
		id = INVALID_TIMER1_HANDLER;
	}
	return true;
}

bool Timer1Client::isActiveTimerId(Timer1Handler_t id) const {
	return m_TimersContainer.end() != m_TimersContainer.find(id);
}

std::size_t Timer1Client::getTimersNumb() const {
	return m_TimersContainer.size();
}

void Timer1Client::removeExpired(Timer1::Timer1Handler_t id) {
	m_TimersContainer.erase(id);
}
