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
class Rectangle;

namespace Texture {

struct RGB_SurfaceCfg_t {
	std::uint32_t Flags = 0;
	std::int32_t W = 0;
	std::int32_t H = 0;
	std::int32_t D = 0;
	std::uint32_t R_Mask = 0;
	std::uint32_t G_Mask = 0;
	std::uint32_t B_Mask = 0;
	std::uint32_t A_Mask = 0;
};

SDL_Surface* createSurfaceFromFile(const std::string &fname);
SDL_Surface* createRGB_Surface(const RGB_SurfaceCfg_t & cfg);
void* getSurfacePixelData(SDL_Surface * surface);
Rectangle getSurfaceRectangle(SDL_Surface * surface);
void freeSurface(SDL_Surface *& surface);

};

#endif /* SDL_UTILS_TEXTURE_HPP_ */
