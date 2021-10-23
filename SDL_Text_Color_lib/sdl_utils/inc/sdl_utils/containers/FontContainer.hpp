/*
 * TextContainer.hpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_CONTAINERS_TEXTCONTAINER_HPP_
#define SDL_UTILS_CONTAINERS_TEXTCONTAINER_HPP_

#include <unordered_map>
#include <memory>

#include "sdl_utils/config/FontConfig.hpp"

#include "sdl_utils/Texture.hpp"

class TextContainer {
public:
	bool init(const FontConfig::FontRes_t & cfg, SDL_Renderer *p_renderer);
	const Texture::Texture_t* get(uint32_t id) const;

private:
	std::unordered_map<uint32_t, std::shared_ptr<Texture::Texture_t>> m_Container;
};

#endif /* SDL_UTILS_CONTAINERS_TEXTCONTAINER_HPP_ */
