/*
 * Renderer.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_RENDERER_HPP_
#define SDL_UTILS_RENDERER_HPP_

#include <cstdint>

#include "utils/NoCopy.hpp"

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;

class Renderer : private NoCopy {
public:
	Renderer();
	~Renderer();

	int32_t init(SDL_Window *window);
	int32_t clearScreen();
	int32_t finishFrame();
	int32_t renderTexture(SDL_Texture *texture);

private:

};

#endif /* SDL_UTILS_RENDERER_HPP_ */
