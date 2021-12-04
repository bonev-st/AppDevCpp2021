/*
 * App.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "App.hpp"

#include <iostream>

#include "config/AppConfig.hpp"
#include "gr_engine/inc/gr_engine/managers/DrawMgr.hpp"
#include "utils/thread/ThreadUtils.hpp"
#include "utils/time/Time.hpp"


bool App::init(const AppConfig& cfg) {
	bool rc = false;
	do {
	    if(!m_Loader.init()) {
	        std::cerr << "m_Loader.init() failed." << std::endl;
	        return false;
	    }
	    DisplayMode::Mode_t display_mode;
	    if(!m_Managers.init(cfg.m_ResourcesCfg, display_mode)) {
	        std::cerr << "m_Managers.init() failed." << std::endl;
	        return false;
	    }
	    if(!m_Game.init(cfg.m_GameCfg, display_mode)) {
	        std::cerr << "m_Game.init() failed." << std::endl;
	        return false;
	    }
	    m_FrameDuration = (int64_t)1E6/cfg.m_ResourcesCfg.m_DrawMgrCfg.m_MaxFrameRate;
		rc = true;
	} while(0);
	return rc;
}

bool App::start() {
	return mainLoop();
}

bool App::mainLoop() {
	bool rc = true;
	Time time;
	while(!m_InputEvents.isExitRequest()) {
		time.start();
		if(!m_Game.new_frame()) {
	    	std::cerr << "m_Game.new_frame() failed." << std::endl;
	    	rc = false;
	    	break;
		}
		if(!processFrame()) {
	    	std::cerr << "processFrame() failed." << std::endl;
	    	rc = false;
	    	break;
		}
		if(!m_Game.processing()) {
	    	std::cerr << "m_Game.processing() failed." << std::endl;
	    	rc = false;
	    	break;
		}
	    if(!drawFrame()) {
	    	std::cerr << "drawFrame() failed." << std::endl;
	    	rc = false;
	    	break;
	    }
		time.start();
	    limitFPS(time.toTime<Time::Microseconds_t>());
	}
	return rc;
}

bool App::processFrame() {
    while(m_InputEvents.pollEvent()) {
    	bool exit;
    	if(m_Managers.handleEvent(m_InputEvents)) {
    		continue;
    	}
    	if(!m_Game.events(m_InputEvents, exit)) {
	    	std::cerr << "App::processFrame::m_Game.events() failed." << std::endl;
	    	return false;
    	}
    	if(exit) {
    		m_InputEvents.setExitRequest();
    		break;
    	}
    }
	return true;
}

bool App::drawFrame() {
	auto * drawing = DrawMgrInst::getInstance();
	if(!drawing->clearScreen()) {
		std::cerr << "App::drawFrame.G_pDrawMgr->clearScreen() failed." << std::endl;
		return false;
	}
	if(!m_Game.draw()) {
		std::cerr << "App::drawFrame::m_Game.draw() failed." << std::endl;
		return false;
	}
	drawing->finishFrame();
	return true;
}

void App::limitFPS(int64_t elapsed_us) {
	if(m_FrameDuration > elapsed_us) {
		ThreadUtils::sleep_usec(m_FrameDuration - elapsed_us);
	}
}
