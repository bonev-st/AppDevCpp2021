/*
 * App.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "App.hpp"

#include <iostream>

#include "sdl_utils/SDLLoader.hpp"
#include "sdl_utils/Texture.hpp"
#include "sdl_utils/SDLHelper.hpp"
#include "sdl_utils/Timer.hpp"

#include "utils/drawing/Rectangle.hpp"


App::App() :
	m_Image(nullptr)
{
}

App::~App() {
}

int32_t App::init() {
	std::int32_t rc = EXIT_FAILURE;
	do {
	    if(EXIT_SUCCESS != SDLLoader::init()) {
	        std::cerr << "SDLLoader::init() failed." << std::endl;
	        break;
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
		rc = EXIT_SUCCESS;
	} while(0);
	return rc;
}

void App::deinit() {
    if(m_Image) {
    	Texture::freeSurface(m_Image);
    }
    m_AppWindow.deinit();
    SDLLoader::deinit();
}

int32_t App::loadResources() {
    const std::string fname = "resources/press_keys.png";
	m_Image = Texture::createSurfaceFromFile(fname);
	if(nullptr == m_Image) {
		std::cerr << "Texture::createSurfaceFromFile failed." << std::endl;
        return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t App::start() {
	std::int32_t rc = EXIT_FAILURE;
	do {
	    if(EXIT_SUCCESS != m_AppWindow.copy(m_Image, Rectangle::UNDEFINED, Rectangle::UNDEFINED)) {
	    	std::cerr << "app_window.copy failed." << std::endl;
	        return EXIT_FAILURE;
	    }
	    if(EXIT_SUCCESS != m_AppWindow.updateSurface()) {
	    	std::cerr << "app_window.updateSurface() failed." << std::endl;
	        return EXIT_FAILURE;
	    }
	    while(!m_InputEvents.checkForExitRequest()) {
	    	m_InputEvents.pollEvent();
	    }
		rc = EXIT_SUCCESS;
	} while(0);
	return rc;
}
