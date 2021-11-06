#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "App.hpp"
#include "config/AppConfig.hpp"
#include "config/AppConfigLoader.hpp"

static bool runApplication() {
	App app;
    if(!app.init(AppConfigLoader::Loader())) {
        std::cerr << "app.init() failed." << std::endl;
    	return false;
    }
    if(!app.start()) {
    	std::cerr << "app.start() failed." << std::endl;
    	return false;
    }
	return true;
}

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char* argv[]) {
    if(!runApplication()) {
        std::cerr << "main::runApplication() failed." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
