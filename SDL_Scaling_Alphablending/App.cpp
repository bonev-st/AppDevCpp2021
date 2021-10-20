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

#include "utils/drawing/DrawParams.hpp"
#include "utils/thread/ThreadUtils.hpp"
#include "utils/time/Time.hpp"

bool App::init(const AppConfig& cfg) {
	bool rc = false;
	do {
	    if(!m_Loader.init()) {
	        std::cerr << "m_Loader.init() failed." << std::endl;
	        return false;
	    }
		if(!m_Renderer.init(cfg.m_WindowCfg)) {
			std::cerr << "m_Renderer.init() failed." << std::endl;
	        break;
		}
		if(!m_ImageContainer.init(cfg.m_ResourcesCfg.m_ImgPath, m_Renderer.get())) {
			std::cerr << "m_ImageContainer.init() failed." << std::endl;
	        break;
		}
		if(!m_Game.init(cfg.m_GameCfg)) {
			std::cerr << "m_Game.init() failed." << std::endl;
	        break;
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
	    	std::cerr << "processFrame() failed." << std::endl;
	    	return false;
		}
	    if(!drawFrame()) {
	    	std::cerr << "drawFrame() failed." << std::endl;
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
	    	std::cerr << "m_Game.events() failed." << std::endl;
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
	std::vector<DrawingParams_t> buffer;
	m_Game.draw(buffer);
	if(EXIT_SUCCESS != m_Renderer.clearScreen()) {
		std::cerr << "m_Renderer.clearScreen() failed." << std::endl;
		return false;
	}
	for(auto e : buffer) {
		auto p_data = m_ImageContainer.get(e.m_ResrId);
		if(nullptr == p_data) {
			std::cerr << "m_ImageContainer.get failed." << std::endl;
			return false;
		}
		if(!m_Renderer.copy(p_data->m_Texture.get(), e.m_SrcRect, e.m_DstRect)) {
			std::cerr << "m_Renderer.copy() failed." << std::endl;
			return false;
		}
	}
	m_Renderer.finishFrame();
	return true;
}

void App::limitFPS(int64_t elapsed_us) {
	constexpr int64_t MAX_FRAMES_PER_SEC = 60;
	constexpr int64_t FRAME_DURATION_US = (int64_t)1E6/MAX_FRAMES_PER_SEC;
	if(FRAME_DURATION_US > elapsed_us) {
		ThreadUtils::sleep_usec(FRAME_DURATION_US - elapsed_us);
	}
}
