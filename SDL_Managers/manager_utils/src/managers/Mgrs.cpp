/*
 * Mgr.cpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/Mgrs.hpp"

#include <cassert>

#include "manager_utils/managers/ResMgrSing.hpp"
#include "manager_utils/managers/DrawMgrSing.hpp"

#include <iostream>

bool Mgrs::init(const ResourcesConfig::Config_t &cfg) {
	auto p_draw = DrawMgrSing::getInstance();
	auto p_res = ResMgrSing::getInstance();

	m_Managers[MGR_DRAW] = p_draw;
	m_Managers[MGR_RES] = p_res;

	if(p_draw->init(cfg.m_DrawMgrCfg)) {
		std::cerr << "Mgrs::init(cfg.m_DrawMgrCfg) failed." << std::endl;
        return false;
    }

    if(p_res->init(cfg.m_ResMgrCfg, p_draw->getRendered())) {
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
