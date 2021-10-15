#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include "sdl_utils/MainWindow.hpp"
#include "sdl_utils/SDLLoader.hpp"
#include "sdl_utils/SDLHelper.hpp"
#include "sdl_utils/Texture.hpp"
#include "sdl_utils/Timer.hpp"

#include "utils/drawing/Rectangle.hpp"

#include "Kaleidoscope.hpp"

static int32_t init(MainWindow & app_window, SDL_Surface *& surface) {
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
		if(EXIT_SUCCESS != app_window.init(app_window_cfg)) {
			std::cerr << "app_window.init() failed." << std::endl;
	        break;
		}
	    const auto * main_rect = app_window.getRectangle();
	    Texture::RGB_SurfaceCfg_t rgb_cfg = {
	    	.Flags = 0,
	    	.W = main_rect->m_W,
	    	.H = main_rect->m_H,
	    	.D = 32,
	    	.R_Mask = 0,
	    	.G_Mask = 0,
	    	.B_Mask = 0,
	    	.A_Mask = 0,
	    };
		surface = Texture::createRGB_Surface(rgb_cfg);
		if(nullptr == surface) {
			std::cerr << "Texture::createRGB_Surface." << std::endl;
			return EXIT_FAILURE;
		}
		rc = EXIT_SUCCESS;
	} while(0);
	return rc;
}

static void deinit(MainWindow & app_window, SDL_Surface *& surface) {
    if(surface) {
    	Texture::freeSurface(surface);
    }
    app_window.deinit();
}

static int32_t draw(MainWindow & app_window, Kaleidoscope & kscope) {
	for(uint32_t i = 0; 20 > i; ++i) {
		if(EXIT_SUCCESS != kscope.update()) {
	    	std::cerr << "kscope.update() failed." << std::endl;
	        return EXIT_FAILURE;
		}
	    if(EXIT_SUCCESS != app_window.copy(kscope.getSurface(), Rectangle::UNDEFINED, Rectangle::UNDEFINED)) {
	    	std::cerr << "app_window.copy() failed." << std::endl;
	        return EXIT_FAILURE;
	    }
	    if(EXIT_SUCCESS != app_window.updateSurface()) {
	    	std::cerr << "app_window.updateSurface() failed." << std::endl;
	        return EXIT_FAILURE;
	    }
	    Timer::Delay(300);
	}
    return EXIT_SUCCESS;
}

std::int32_t runApplication() {
	MainWindow app_window;
	SDL_Surface * surface = nullptr;
    if(EXIT_SUCCESS != init(app_window, surface)) {
        std::cerr << "init() failed." << std::endl;
        return EXIT_FAILURE;
    }
	Kaleidoscope kscope(surface);
	if(EXIT_SUCCESS != draw(app_window, kscope)) {
		std::cerr << "draw failed." << std::endl;
		return EXIT_FAILURE;
	}
	deinit(app_window, surface);
	return EXIT_SUCCESS;
}

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char* argv[]) {
    if(EXIT_SUCCESS != SDLLoader::init()) {
        std::cerr << "SDLLoader::init() failed." << std::endl;
    	return EXIT_FAILURE;
    }
    if(EXIT_SUCCESS != runApplication()) {
    	std::cerr << "runApplication() failed." << std::endl;
    }
    SDLLoader::deinit();
	return EXIT_SUCCESS;
}
