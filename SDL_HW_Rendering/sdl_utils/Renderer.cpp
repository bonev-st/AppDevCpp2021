/*
 * Renderer.cpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#include "cstdlib"

#include "Renderer.hpp"

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

int32_t Renderer::init([[maybe_unused]]SDL_Window *window) {
	return EXIT_SUCCESS;
}

int32_t Renderer::clearScreen() {
	return EXIT_SUCCESS;
}

int32_t Renderer::finishFrame() {
	return EXIT_SUCCESS;
}

int32_t Renderer::renderTexture([[maybe_unused]]SDL_Texture *texture) {
	return EXIT_SUCCESS;
}
