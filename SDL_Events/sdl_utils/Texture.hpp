/*
 * Texture.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_TEXTURE_HPP_
#define SDL_UTILS_TEXTURE_HPP_

#include <string>

struct SDL_Surface;

namespace Texture {

SDL_Surface * createSurfaceFromFile(const std::string &fname);
void freeSurface(SDL_Surface *& surface);

};

#endif /* SDL_UTILS_TEXTURE_HPP_ */
