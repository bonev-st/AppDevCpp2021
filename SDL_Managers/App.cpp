/*
 * App.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "App.hpp"

#include <iostream>

#include "config/AppConfig.hpp"

#include "utils/thread/ThreadUtils.hpp"
#include "utils/time/Time.hpp"

#include "manager_utils/managers/DrawMgr.hpp"

bool App::init(const AppConfig& cfg) {
	bool rc = false;
	do {
	    if(!m_Loader.init()) {
	        std::cerr << "App::init::m_Loader.init() failed." << std::endl;
	        return false;
	    }
	    if(!m_Managers.init(cfg.m_ResourcesCfg)) {
	        std::cerr << "App::init.m_Managers.init() failed." << std::endl;
	        return false;
	    }
	    if(!m_Game.init(cfg.m_GameCfg)) {
	        std::cerr << "App::init::m_Game.init() failed." << std::endl;
	        return false;
	    }
		rc = true;
	} while(0);
	return rc;
}

bool App::start() {
	return mainLoop();
}

bool App::mainLoop() {
	Time time;
	while(!m_InputEvents.isExitRequest()) {
		time.start();
		if(!processFrame()) {
	    	std::cerr << "App::mainLoop::processFrame() failed." << std::endl;
	    	return false;
		}
	    if(!drawFrame()) {
	    	std::cerr << "App::mainLoop::drawFrame() failed." << std::endl;
	    	return false;
	    }
	    limitFPS(time.toTime<Time::Microseconds_t>());
	}
	return true;
}

bool App::processFrame() {
    while(m_InputEvents.pollEvent()) {
    	bool exit;
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
	if(!G_pDrawMgr->clearScreen()) {
		std::cerr << "App::drawFrame.G_pDrawMgr->clearScreen() failed." << std::endl;
		return false;
	}
	if(!m_Game.draw()) {
		std::cerr << "App::drawFrame::m_Game.draw() failed." << std::endl;
		return false;
	}
	G_pDrawMgr->finishFrame();
	return true;
}

void App::limitFPS(int64_t elapsed_us) {
	constexpr int64_t MAX_FRAMES_PER_SEC = 60;
	constexpr int64_t FRAME_DURATION_US = (int64_t)1E6/MAX_FRAMES_PER_SEC;
	if(FRAME_DURATION_US > elapsed_us) {
		ThreadUtils::sleep_usec(FRAME_DURATION_US - elapsed_us);
	}
}
