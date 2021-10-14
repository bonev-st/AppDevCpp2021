/*
 * SDLLoader.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_SDLLOADER_HPP_
#define SDL_UTILS_SDLLOADER_HPP_

#include <cstdint>

class SDLLoader {
public:
	SDLLoader() = default;
	~SDLLoader() {
		deinit();
	}
	std::int32_t init();

private:
	void deinit();
};

#endif /* SDL_UTILS_SDLLOADER_HPP_ */
