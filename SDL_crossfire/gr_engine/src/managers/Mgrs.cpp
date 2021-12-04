/*
 * Mgr.cpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#include "gr_engine/managers/Mgrs.hpp"

#include <iostream>
#include <cassert>

#include "gr_engine/managers/DrawMgr.hpp"
#include "gr_engine/managers/ResMgr.hpp"
#include "gr_engine/managers/Timer2Mgr.hpp"
#include "utils/inputs/EventDefines.h"

#include "utils/drawing/Dimention.hpp"

bool Mgrs::init(const ResourcesConfig::Config_t &cfg, DisplayMode::Mode_t & out_display_mode) {
	auto * drawing_manager = DrawMgrInst::getInstance();
	auto * resources_manager = ResMgrInst::getInstance();
	auto * timer_manager = Timer2MgrInst::getInstance();

	m_Managers[MGR_DRAW] = drawing_manager;
	m_Managers[MGR_RES] = resources_manager;
    m_Managers[MGR_TIMER2] = timer_manager;

	if(!DrawMgrInst::getInstance()->init(cfg.m_DrawMgrCfg, &m_Renderer)) {
		std::cerr << "DrawMgr->init() failed." << std::endl;
        return false;
    }
    if(!ResMgrInst::getInstance()->init(cfg.m_ResMgrCfg, drawing_manager->getRendered(),
    		&m_ImageContainer, &m_TextContainer, &m_TextureContainer)) {
		std::cerr << "ResMgr->init() failed." << std::endl;
        return false;
    }
    out_display_mode = drawing_manager->getDisplayMode();
	return true;
}

std::size_t Mgrs::getActive() const {
	std::size_t rc = 0;
	for(auto &e : m_Managers) {
		rc += e->getActive();
	}
	return rc;
}

std::size_t Mgrs::getMaxActive() const {
	std::size_t rc = 0;
	for(auto &e : m_Managers) {
		rc += e->getMaxActive();
	}
	return rc;
}

bool Mgrs::handleEvent(const InputEvent &e) {
	return Timer2MgrInst::getInstance()->handleEvent(e);
}
