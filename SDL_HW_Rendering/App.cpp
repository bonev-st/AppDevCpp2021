/*
 * App.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "App.hpp"

#include <iostream>

#include "config/AppConfig.hpp"

#include "sdl_utils/Texture.hpp"
#include "sdl_utils/SDLHelper.hpp"
#include "sdl_utils/Timer.hpp"

#include "utils/drawing/DrawingData.hpp"
#include "utils/thread/ThreadUtils.hpp"
#include "utils/time/Time.hpp"

int32_t App::init(const AppConfig& cfg) {
	std::int32_t rc = EXIT_FAILURE;
	do {
	    if(EXIT_SUCCESS != m_Loader.init()) {
	        std::cerr << "m_Loader.init() failed." << std::endl;
	        return EXIT_FAILURE;
	    }
		if(EXIT_SUCCESS != m_AppWindow.init(cfg.WindowCfg)) {
			std::cerr << "m_AppWindow.init() failed." << std::endl;
	        break;
		}
		if(EXIT_SUCCESS != m_Game.init(cfg.GameCfg)) {
			std::cerr << "m_Game.init() failed." << std::endl;
	        break;
		}
		// registering events
		rc = EXIT_SUCCESS;
	} while(0);
	return rc;
}

int32_t App::start() {
	return mainLoop();
}

int32_t App::mainLoop() {
	std::int32_t rc = EXIT_SUCCESS;
	Time time;
	while(!m_InputEvents.isExitRequest()) {
		time.start();
		rc = processFrame();
		if(EXIT_SUCCESS != rc) {
	    	std::cerr << "processFrame() failed." << std::endl;
			break;
		}
		rc = drawFrame();
	    if(EXIT_SUCCESS != rc) {
	    	std::cerr << "drawFrame() failed." << std::endl;
			break;
	    }
	    limitFPS(time.toTime<Time::Microseconds_t>());
	}
	return rc;
}

int32_t App::processFrame() {
	int32_t rc = EXIT_SUCCESS;
    while(m_InputEvents.pollEvent()) {
    	bool exit;
    	rc = m_Game.events(m_InputEvents, exit);
    	if(EXIT_SUCCESS != rc) {
	    	std::cerr << "m_Game.events() failed." << std::endl;
	    	break;
    	}
    	if(exit) {
    		setExitRequest();
    		break;
    	}
    }
	return rc;
}

int32_t App::drawFrame() {
	std::vector<DrawingData::_Drawing_t> buffer;
	m_Game.draw(buffer);
	for(auto e : buffer) {
		m_AppWindow.copy(e.m_Surface, e.m_SrcRect, e.m_DstRect);
	}
	if(EXIT_SUCCESS != m_AppWindow.updateSurface()) {
		std::cerr << "m_AppWindow.updateSurface() failed." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void App::limitFPS(int64_t elapsed_us) {
	constexpr int64_t MAX_FRAMES_PER_SEC = 100;
	constexpr int64_t FRAME_DURATION_US = (int64_t)1E6/MAX_FRAMES_PER_SEC;
	if(FRAME_DURATION_US > elapsed_us) {
		ThreadUtils::sleep_usec(FRAME_DURATION_US - elapsed_us);
	}
}

void App::setExitRequest() {
	m_InputEvents.setExitRequest();
}
