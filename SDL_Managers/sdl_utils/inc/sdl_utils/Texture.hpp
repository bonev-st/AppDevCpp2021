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
#include "utils/drawing/DrawParams.hpp"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
struct Color;

typedef struct _TTF_Font TTF_Font;

namespace Texture {

struct Texture_t {
	std::shared_ptr<SDL_Texture> m_Texture;
	int32_t m_W;
	int32_t m_H;
};

std::shared_ptr<SDL_Surface> createSurfaceFromFile(const std::string &fname);
std::shared_ptr<Texture_t> createTextureFromSurface(SDL_Surface* surface, SDL_Renderer * p_renderer, BlendMode_t blend_mode);
std::shared_ptr<Texture_t> createTextureFromFile(const std::string &fname, SDL_Renderer * p_renderer, BlendMode_t blend_mode);

std::shared_ptr<SDL_Surface> createSurfaceFromText(const std::string &text, const Color &color, const TTF_Font* font);
std::shared_ptr<Texture_t> createTextureFromFont(const std::string &text, const Color &color, const TTF_Font* font, SDL_Renderer * p_renderer, BlendMode_t blend_mode);

bool setBlendModeTexture(const Texture_t *texture, BlendMode_t blendMode);
bool setAlphaTexture(const Texture_t *texture, int32_t alpha);

};

#endif /* SDL_UTILS_TEXTURE_HPP_ */
