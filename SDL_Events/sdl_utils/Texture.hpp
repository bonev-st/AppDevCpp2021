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

struct SDL_Surface;

namespace Texture {

std::shared_ptr<SDL_Surface> createSurfaceFromFile(const std::string &fname);

};

#endif /* SDL_UTILS_TEXTURE_HPP_ */
