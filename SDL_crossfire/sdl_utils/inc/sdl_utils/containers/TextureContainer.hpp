/*
 * TextureContainer.hpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_SRC_CONTAINERS_TEXTURECONTAINER_HPP_
#define SDL_UTILS_SRC_CONTAINERS_TEXTURECONTAINER_HPP_

#include <cstdint>
#include <memory>

#include "utils/containers/FirstFreeContainer.hpp"
#include "utils/drawing/Color.hpp"

#include "sdl_utils/Texture.hpp"

struct Dimention;

class TextureContainer {
public:
	bool init(SDL_Renderer *p_renderer);
	bool create(const Dimention& dim, const Color& color, std::size_t &out_id);
	bool reload(const Dimention& dim, const Color& color, std::size_t id);
	bool unload(std::size_t id);

	std::shared_ptr<SDL_Texture> getLock(std::size_t id);
	const Texture::Texture_t* get(std::size_t id) const;

private:
	struct RGB_Texture_t {
		std::shared_ptr<Texture::Texture_t> m_Texture;
		Color m_Color;
	};

	FirstFreeContainer<RGB_Texture_t> m_Texture;
	SDL_Renderer * m_Renderer = nullptr;

	RGB_Texture_t create(const Dimention& dim, const Color& color);
	const RGB_Texture_t* getTexture(std::size_t id) const;
};

#endif /* SDL_UTILS_SRC_CONTAINERS_TEXTURECONTAINER_HPP_ */
