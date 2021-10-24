/*
 * App.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "App.hpp"

#include <iostream>

#include "config/AppConfig.hpp"

#include "utils/drawing/DrawParams.hpp"
#include "utils/thread/ThreadUtils.hpp"
#include "utils/time/Time.hpp"

bool App::init(const AppConfig& cfg) {
	bool rc = false;
	do {
	    if(!m_Loader.init()) {
	        std::cerr << "App::init::m_Loader.init() failed." << std::endl;
	        return false;
	    }
		if(!m_Renderer.init(cfg.m_ResourcesCfg.m_WindowCfg)) {
			std::cerr << "App::init::m_Renderer.init() failed." << std::endl;
	        break;
		}
		if(!m_ImageContainer.init(cfg.m_ResourcesCfg.m_ImgRes, m_Renderer.get())) {
			std::cerr << "App::init::m_ImageContainer.init() failed." << std::endl;
	        break;
		}
		if(!m_TextContainer.init(cfg.m_ResourcesCfg.m_FontRes, m_Renderer.get())) {
			std::cerr << "App::init::m_TextContainer.init() failed." << std::endl;
	        break;
		}
		if(!m_Game.init(cfg.m_GameCfg, &m_ImageContainer, &m_TextContainer)) {
			std::cerr << "App::init::m_Game.init() failed." << std::endl;
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
	std::vector<DrawParams_t> buffer;
	bool update = false;
	if(!m_Game.draw(buffer, update)) {
		std::cerr << "App::drawFrame::m_Game.draw() failed." << std::endl;
		return false;
	}
	if(update) {
		if(!m_Renderer.clearScreen()) {
			std::cerr << "App::drawFrame::m_Renderer.clearScreen() failed." << std::endl;
			return false;
		}
		for(auto e : buffer) {
			if(WidgetType_t::IMAGE == e.m_WidgetType) {
				if(!drawImage(e)) {
					std::cerr << "App::drawFrame::drawImage() failed, id:" << e.m_ResrId << " type: " << static_cast<uint8_t>(e.m_WidgetType) << std::endl;
					return false;
				}
			} else if (WidgetType_t::TEXT == e.m_WidgetType) {
				if(!drawText(e)) {
					std::cerr << "App::drawFrame::drawText() failed, id:" << e.m_ResrId << " type: " << static_cast<uint8_t>(e.m_WidgetType) << std::endl;
					return false;
				}
			} else {
				std::cerr << "App::drawFrame::drawFrame() failed, unknown widget type" << static_cast<uint8_t>(e.m_WidgetType) << std::endl;
				return false;
			}
		}
		m_Renderer.finishFrame();
	}
	return true;
}

void App::limitFPS(int64_t elapsed_us) {
	constexpr int64_t MAX_FRAMES_PER_SEC = 60;
	constexpr int64_t FRAME_DURATION_US = (int64_t)1E6/MAX_FRAMES_PER_SEC;
	if(FRAME_DURATION_US > elapsed_us) {
		ThreadUtils::sleep_usec(FRAME_DURATION_US - elapsed_us);
	}
}

bool App::drawImage(DrawParams_t & img) {
	bool rc = false;
	do {
		auto p_data = m_ImageContainer.get(img.m_ResrId);
		if(nullptr == p_data) {
			std::cerr << "App::drawImage::m_ImageContainer.get failed, for image id " << img.m_ResrId  << std::endl;
			break;
		}
		auto p_texture = p_data->m_Texture.get();
		if (FULL_OPACITY == img.m_Opacity) {
			if(!m_Renderer.copy(p_texture, img.m_SrcRect, img.m_DstRect)) {
				std::cerr << "App::drawImage::drawText::m_Renderer.copy() failed, for image id " << img.m_ResrId  << std::endl;
				break;
			};
		} else {
			if(!Texture::setAlphaTexture(p_data, img.m_Opacity)) {
				std::cerr << "App::drawImage::Texture::setAlphaTexture() failed, for image id " << img.m_ResrId << std::endl;
				break;
			}
			if(!m_Renderer.copy(p_texture, img.m_SrcRect, img.m_DstRect)) {
				std::cerr << "App::drawImage::m_Renderer.copy() failed, for image id " << img.m_ResrId << std::endl;
				break;
			}
			if(!Texture::setAlphaTexture(p_data, FULL_OPACITY)) {
				std::cerr << "App::drawImage::Texture::setAlphaTexture(FULL_OPACITY) failed, for id " << img.m_ResrId << std::endl;
				break;
			}
		}
		rc = true;
	} while(0);
	return rc;
}

bool App::drawText(DrawParams_t & text) {
	auto p_data = m_TextContainer.get(text.m_ResrId);
	if(!Texture::setAlphaTexture(p_data, text.m_Opacity)) {
		std::cerr << "App::drawText::Texture::setAlphaTexture() failed, for text id " << text.m_ResrId << std::endl;
		return false;
	}
	if(!m_Renderer.copy(p_data->m_Texture.get(), text.m_SrcRect, text.m_DstRect)) {
		std::cerr << "App::drawText::m_Renderer.copy() failed, for text id " << text.m_ResrId  << std::endl;
		return false;
	};
	return true;
}
