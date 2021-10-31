/*
 * Mgr.cpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/Mgrs.hpp"

#include <cassert>

#include "manager_utils/managers/ResMgr.hpp"
#include "manager_utils/managers/DrawMgr.hpp"

#include <iostream>

Mgrs::~Mgrs() {
	for(auto &e : m_Managers) {
		if(nullptr != e) {
			resetPointer(e.get());
		}
	}
}

void Mgrs::resetPointer(BaseMgr * const p_obj) {
	if(p_obj == G_pDrawMgr) {
		G_pDrawMgr = nullptr;
	} else if (p_obj == G_pResMgr) {
		G_pResMgr = nullptr;
	} else {
		assert(0);
	}
}

bool Mgrs::init(const ResourcesConfig::Config_t &cfg) {
	m_Managers[MGR_DRAW] = std::make_unique<DrawMgr>();
	G_pDrawMgr = reinterpret_cast<DrawMgr*>(m_Managers[MGR_DRAW].get());
	if(nullptr == G_pDrawMgr) {
		std::cerr << "Mgrs::init() failed. Bad alloc new DrawMgr" << std::endl;
        return false;
	}
    if(G_pDrawMgr->init(cfg.m_DrawMgrCfg)) {
		std::cerr << "Mgrs::init(cfg.m_DrawMgrCfg) failed." << std::endl;
        return false;
    }

	m_Managers[MGR_RES] = std::make_unique<ResMgr>();
	G_pResMgr = reinterpret_cast<ResMgr*>(m_Managers[MGR_RES].get());
	if(nullptr == G_pResMgr) {
		std::cerr << "Mgrs::init() failed. Bad alloc new ResMgr" << std::endl;
        return false;
	}
    if(G_pResMgr->init(cfg.m_ResMgrCfg, G_pDrawMgr->getRendered())) {
		std::cerr << "Mgrs::init(cfg.m_ResMgrCfg) failed." << std::endl;
        return false;
    }
	return true;
}

void Mgrs::process() {
	for(auto &e : m_Managers) {
		e->process();
	}
}
