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

static int32_t init(MainWindow & app_window, SDL_Surface *& image) {
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
	    const std::string fname = "resources/hello.png";
		image = Texture::createSurfaceFromFile(fname);
		if(nullptr == image) {
			std::cerr << "Texture::createSurfaceFromFile failed." << std::endl;
	        break;
		}
		rc = EXIT_SUCCESS;
	} while(0);
	return rc;
}

static void deinit(MainWindow & app_window, SDL_Surface *& image) {
    if(image) {
    	Texture::freeSurface(image);
    }
    app_window.deinit();
}

static int32_t draw(MainWindow & app_window, SDL_Surface * image) {
    if(EXIT_SUCCESS != app_window.copy(image, Rectangle::UNDEFINED, Rectangle::UNDEFINED)) {
    	std::cerr << "app_window.copy failed." << std::endl;
        return EXIT_FAILURE;
    }
    if(EXIT_SUCCESS != app_window.updateSurface()) {
    	std::cerr << "app_window.updateSurface() failed." << std::endl;
        return EXIT_FAILURE;
    }
    Timer::Delay(3000);
    return EXIT_SUCCESS;
}

std::int32_t runApplication() {
	MainWindow app_window;
	SDL_Surface * image = nullptr;
    if(EXIT_SUCCESS != init(app_window, image)) {
        std::cerr << "init() failed." << std::endl;
        return EXIT_FAILURE;
    }
	if(EXIT_SUCCESS != draw(app_window, image)) {
		std::cerr << "draw failed." << std::endl;
		return EXIT_FAILURE;
	}
	deinit(app_window, image);
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
