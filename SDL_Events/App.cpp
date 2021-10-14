/*
 * App.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "App.hpp"

#include <iostream>

#include "sdl_utils/Texture.hpp"
#include "sdl_utils/SDLHelper.hpp"
#include "sdl_utils/Timer.hpp"

#include "utils/drawing/Rectangle.hpp"
#include "utils/thread/ThreadUtils.hpp"
#include "utils/time/Time.hpp"

int32_t App::init() {
	std::int32_t rc = EXIT_FAILURE;
	do {
	    if(EXIT_SUCCESS != m_Loader.init()) {
	        std::cerr << "m_Loader.init() failed." << std::endl;
	        return EXIT_FAILURE;
	    }
	    MainWindowCfg_t app_window_cfg = {
			.Name = "SDL runtime",
			.Rect = Rectangle(Point::UNDEFINED, 640, 480),
			.Flags = WINDOW_SHOWN
		};
		if(EXIT_SUCCESS != m_AppWindow.init(app_window_cfg)) {
			std::cerr << "m_AppWindow.init() failed." << std::endl;
	        break;
		}
		if(EXIT_SUCCESS != loadResources()) {
			std::cerr << "loadResources() failed." << std::endl;
	        break;
		}
		// registering events
		m_InputEvents.registerKeyboard(Keyboard::KEY_ESCAPE,
			[this](const InputEvent & input) {
				if(TouchEvent::KEYBOARD_PRESS == input.m_Type) {
					this->setExitRequest();
				}
			}
		);
		m_InputEvents.registerKeyboard(Keyboard::KEY_RIGHT,
			[this](const InputEvent & input) {
				this->setKeyRequest(TouchEvent::KEYBOARD_PRESS == input.m_Type, KEY_RIGHT_MASK);
			}
		);
		m_InputEvents.registerKeyboard(Keyboard::KEY_LEFT,
			[this](const InputEvent & input) {
				this->setKeyRequest(TouchEvent::KEYBOARD_PRESS == input.m_Type, KEY_LEFT_MASK);
			}
		);
		m_InputEvents.registerKeyboard(Keyboard::KEY_DOWN,
			[this](const InputEvent & input) {
				this->setKeyRequest(TouchEvent::KEYBOARD_PRESS == input.m_Type, KEY_DOWN_MASK);
			}
		);
		m_InputEvents.registerKeyboard(Keyboard::KEY_UP,
			[this](const InputEvent & input) {
				this->setKeyRequest(TouchEvent::KEYBOARD_PRESS == input.m_Type, KEY_UP_MASK);
			}
		);
		rc = EXIT_SUCCESS;
	} while(0);
	return rc;
}

int32_t App::loadResources() {
	m_Image[IDLE_IMG] = Texture::createSurfaceFromFile("resources/press_keys.png");
	if(nullptr == m_Image[IDLE_IMG]) {
		std::cerr << "Texture::createSurfaceFromFile failed." << std::endl;
        return EXIT_FAILURE;
	}
	m_Image[UP_IMG] = Texture::createSurfaceFromFile("resources/up.png");
	if(nullptr == m_Image[UP_IMG]) {
		std::cerr << "Texture::createSurfaceFromFile failed." << std::endl;
        return EXIT_FAILURE;
	}
	m_Image[DOWN_IMG] = Texture::createSurfaceFromFile("resources/down.png");
	if(nullptr == m_Image[DOWN_IMG]) {
		std::cerr << "Texture::createSurfaceFromFile failed." << std::endl;
        return EXIT_FAILURE;
	}
	m_Image[RIGHT_IMG] = Texture::createSurfaceFromFile("resources/right.png");
	if(nullptr == m_Image[RIGHT_IMG]) {
		std::cerr << "Texture::createSurfaceFromFile failed." << std::endl;
        return EXIT_FAILURE;
	}
	m_Image[LEFT_IMG] = Texture::createSurfaceFromFile("resources/left.png");
	if(nullptr == m_Image[LEFT_IMG]) {
		std::cerr << "Texture::createSurfaceFromFile failed." << std::endl;
        return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
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
	    	std::cerr << "m_InputEvents() failed." << std::endl;
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

int32_t App::drawFrame() {
	if(EXIT_SUCCESS != m_AppWindow.updateSurface()) {
		std::cerr << "m_AppWindow.updateSurface() failed." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t App::processFrame() {
    while(m_InputEvents.pollEvent()) {
    }
	if(EXIT_SUCCESS != handleEvent()) {
		std::cerr << "handleEvent() failed." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t App::handleEvent() {
	do {
		if(KEY_UP_MASK & m_KeysMask) {
			if(EXIT_SUCCESS != m_AppWindow.copy(m_Image[UP_IMG].get(), Rectangle::UNDEFINED, Rectangle::UNDEFINED)) {
				std::cerr << "app_window.copy failed." << std::endl;
				return EXIT_FAILURE;
			}
			break;
		}
		if(KEY_DOWN_MASK & m_KeysMask) {
			if(EXIT_SUCCESS != m_AppWindow.copy(m_Image[DOWN_IMG].get(), Rectangle::UNDEFINED, Rectangle::UNDEFINED)) {
				std::cerr << "app_window.copy failed." << std::endl;
				return EXIT_FAILURE;
			}
			break;
		}
		if(KEY_RIGHT_MASK & m_KeysMask) {
			if(EXIT_SUCCESS != m_AppWindow.copy(m_Image[RIGHT_IMG].get(), Rectangle::UNDEFINED, Rectangle::UNDEFINED)) {
				std::cerr << "app_window.copy failed." << std::endl;
				return EXIT_FAILURE;
			}
			break;
		}
		if(KEY_LEFT_MASK & m_KeysMask) {
			if(EXIT_SUCCESS != m_AppWindow.copy(m_Image[LEFT_IMG].get(), Rectangle::UNDEFINED, Rectangle::UNDEFINED)) {
				std::cerr << "app_window.copy failed." << std::endl;
				return EXIT_FAILURE;
			}
			break;
		}
		if(EXIT_SUCCESS != m_AppWindow.copy(m_Image[IDLE_IMG].get(), Rectangle::UNDEFINED, Rectangle::UNDEFINED)) {
			std::cerr << "app_window.copy failed." << std::endl;
			return EXIT_FAILURE;
		}
	} while(0);
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

void App::setKeyRequest(bool pressed, KeyMask_t key_mask) {
	if(pressed) {
		m_KeysMask |=  key_mask;
	} else {
		m_KeysMask &= ~key_mask;
	}
}
