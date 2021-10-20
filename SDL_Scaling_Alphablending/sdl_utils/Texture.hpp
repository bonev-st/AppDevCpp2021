/*
 * Texture.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_TEXTURE_HPP_
#define SDL_UTILS_TEXTURE_HPP_

#include <string>
#include <memory>

#include "utils/drawing/Rectangle.hpp"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

namespace Texture {

struct Texture_t {
	std::shared_ptr<SDL_Texture> m_Texture;
	int32_t m_W;
	int32_t m_H;
};

std::shared_ptr<SDL_Surface> createSurfaceFromFile(const std::string &fname);
std::shared_ptr<Texture_t> createTextureFromFile(const std::string &fname, SDL_Renderer * p_renderer);
std::shared_ptr<Texture_t> createTextureFromSurface(SDL_Surface* surface, SDL_Renderer * p_renderer);

};

#endif /* SDL_UTILS_TEXTURE_HPP_ */
