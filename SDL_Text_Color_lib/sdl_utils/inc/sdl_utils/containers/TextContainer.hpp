/*
 * TextContainer.hpp
 *
 *  Created on: Oct 23, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_SRC_CONTAINERS_TEXTCONTAINER_HPP_
#define SDL_UTILS_SRC_CONTAINERS_TEXTCONTAINER_HPP_

#include <cstdint>
#include <memory>
#include <string>

#include "utils/containers/FirstFreeContainer.hpp"

#include "sdl_utils/containers/FontContainer.hpp"
#include "sdl_utils/Texture.hpp"

struct Color;

class TextContainer {
public:
	TextContainer() = default;

	bool init(const FontConfig::FontRes_t & cfg, SDL_Renderer *p_renderer);
	bool createText(const std::string &text, const Color &color, std::size_t font_id, std::size_t &out_text_id);
	bool reloadText(const std::string &text, const Color &color, std::size_t font_id, std::size_t out_text_id);
	bool unloadText(std::size_t out_text_id);

	const Texture::Texture_t* get(std::size_t id) const;

private:
	typedef std::shared_ptr<Texture::Texture_t> Text_t;
	FontContainer m_Font;
	FirstFreeContainer<Text_t> m_Text;
	SDL_Renderer * m_Renderer = nullptr;
};

#endif /* SDL_UTILS_SRC_CONTAINERS_TEXTCONTAINER_HPP_ */
