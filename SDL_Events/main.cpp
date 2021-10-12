#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "App.hpp"

int32_t main([[maybe_unused]]int32_t argc, [[maybe_unused]]char* argv[]) {
	App app;
    if(EXIT_SUCCESS != app.init()) {
        std::cerr << "app.init() failed." << std::endl;
    	return EXIT_FAILURE;
    }
	int32_t rc = app.start();
    if(EXIT_SUCCESS != rc) {
    	std::cerr << "app.start() failed." << std::endl;
    }
    app.deinit();
	return rc;
}
