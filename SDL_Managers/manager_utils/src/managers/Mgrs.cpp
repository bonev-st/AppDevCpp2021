/*
 * Mgr.cpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/Mgrs.hpp"

#include <iostream>

bool Mgrs::init(const ResourcesConfig::Config_t &cfg) {
	if(DrawMgr::init(cfg.m_DrawMgrCfg)) {
		std::cerr << "Mgrs::init(cfg.m_DrawMgrCfg) failed." << std::endl;
		return false;
	}
#if 0
	if(ResMgr::init(cfg.m_ResMgrCfg)) {
		std::cerr << "Mgrs::init(cfg.m_ResMgrCfg) failed." << std::endl;
		return false;
	}
#endif
	return true;
}
