#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "App.hpp"

static int32_t runApplication() {
	App app;
    if(EXIT_SUCCESS != app.init()) {
        std::cerr << "app.init() failed." << std::endl;
    	return EXIT_FAILURE;
    }
	int32_t rc = app.start();
    if(EXIT_SUCCESS != rc) {
    	std::cerr << "app.start() failed." << std::endl;
    }
	return rc;
}

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char* argv[]) {
    int32_t rc = runApplication();
    if(EXIT_SUCCESS != rc) {
        std::cerr << "runApplication() failed." << std::endl;
    }
	return rc;
}
