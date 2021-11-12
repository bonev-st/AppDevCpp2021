/*
 * Mgr.cpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/Mgrs.hpp"

#include <cassert>

#include "utils/inputs/EventDefines.h"

#include "manager_utils/managers/ResMgr.hpp"
#include "manager_utils/managers/DrawMgr.hpp"
#include "manager_utils/managers/TimerMgr.hpp"
#include "manager_utils/managers/Timer1Mgr.hpp"

#include <iostream>
Mgrs::~Mgrs() {
	for(auto &e : m_Managers) {
		reset(e.get());
	}
}

bool Mgrs::init(const ResourcesConfig::Config_t &cfg) {
	m_Managers[MGR_DRAW] = std::make_unique<DrawMgr>();
	if(nullptr == m_Managers[MGR_DRAW]) {
		std::cerr << "std::make_unique<DrawMgr>() failed. Bad allocation" << std::endl;
        return false;
	}
	G_pDrawMgr = reinterpret_cast<DrawMgr*>(m_Managers[MGR_DRAW].get());
	m_Managers[MGR_RES] = std::make_unique<ResMgr>();
	if(nullptr == m_Managers[MGR_RES]) {
		std::cerr << "std::make_unique<ResMgr>() failed. Bad allocation" << std::endl;
        return false;
	}
	G_pResMgr = reinterpret_cast<ResMgr*>(m_Managers[MGR_RES].get());

	m_Managers[MGR_TIMER] = std::make_unique<TimerMgr>();
	if(nullptr == m_Managers[MGR_TIMER]) {
		std::cerr << "std::make_unique<TimerMgr>() failed. Bad allocation" << std::endl;
        return false;
	}
	G_pTimerMgr = reinterpret_cast<TimerMgr*>(m_Managers[MGR_TIMER].get());

	if(!G_pDrawMgr->init(cfg.m_DrawMgrCfg)) {
		std::cerr << "DrawMgr->init() failed." << std::endl;
        return false;
    }
    if(!G_pResMgr->init(cfg.m_ResMgrCfg, G_pDrawMgr->getRendered())) {
		std::cerr << "ResMgr->init() failed." << std::endl;
        return false;
    }
    const auto min_period = 1000/cfg.m_DrawMgrCfg.m_MaxFrameRate;
    if(!G_pTimerMgr->init(min_period)) {
		std::cerr << "TimerMgr->init() failed." << std::endl;
        return false;
    }

	m_Managers[MGR_TIMER1] = std::make_unique<Timer1Mgr>();
	if(nullptr == m_Managers[MGR_TIMER1]) {
		std::cerr << "std::make_unique<Timer1Mgr>() failed. Bad allocation" << std::endl;
        return false;
	}
	G_pTimer1Mgr = reinterpret_cast<Timer1Mgr*>(m_Managers[MGR_TIMER1].get());
	if(!G_pTimer1Mgr->init(min_period)) {
		std::cerr << "Timer1Mgr->init() failed." << std::endl;
        return false;
    }
	return true;
}

bool Mgrs::process() {
	for(auto &e : m_Managers) {
		if(!e->process()) {
			return false;
		}
	}
	return true;
}

void Mgrs::reset(BaseMgr * const p) {
	if(p == G_pDrawMgr) {
		G_pDrawMgr = nullptr;
	} else if(p == G_pResMgr) {
		G_pResMgr = nullptr;
	} else if(p == G_pTimerMgr) {
		G_pTimerMgr = nullptr;
	} else if(p == G_pTimer1Mgr) {
		G_pTimer1Mgr = nullptr;
	} else {
		std::cerr << "Try to reset unknown global manger pointer" << std::endl;
	}
}
