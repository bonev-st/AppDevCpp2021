/*
 * TextContainer.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: stanimir
 */

#include "sdl_utils/containers/TextContainer.hpp"

#include <iostream>
#include <cassert>
#include <SDL_ttf.h>

#include <sdl_utils/Texture.hpp>

bool TextContainer::init(const FontConfig::FontRes_t & cfg, SDL_Renderer *p_renderer) {
	assert(p_renderer);
	m_Renderer = p_renderer;
	return m_Font.init(cfg);
}

bool TextContainer::create(const std::string &text, const Color &color, std::size_t font_id, std::size_t &out_id) {
	auto font = m_Font.get(font_id);
	if(nullptr == font) {
		std::cerr << "TextContainer::create() m_Font.get() failed. Reason: Font with id " << font_id << " not found" << std::endl;
		return false;
	}
	Text_t texture = Texture::createTextureFromFont(text, color, font, m_Renderer);
	if(nullptr == texture) {
		std::cerr << "TextContainer::create() Texture::createTextureFromFont() failed."  << " for text: " << text << std::endl;
        return false;
	}
	out_id = m_Text.add(texture);
    return true;
}

bool TextContainer::reload(const std::string &text, const Color &color, std::size_t font_id, std::size_t id) {
	auto font = m_Font.get(font_id);
	if(nullptr == font) {
		std::cerr << "TextContainer::reload() m_Font.get() failed. Reason: Font with id " << font_id << " not found" << std::endl;
		return false;
	}
	Text_t texture = Texture::createTextureFromFont(text, color, font, m_Renderer);
	if(nullptr == texture) {
		std::cerr << "TextContainer::reloadText::Texture::createTextureFromFont() failed." << " for text: " << text << std::endl;
        return false;
	}
	const auto rc = m_Text.replace(id, texture);
	if(!rc) {
		std::cerr << "TextContainer::reload() m_Text.replace() failed." << std::endl;
        return false;
	}

    return m_Text.replace(id, texture);
}

bool TextContainer::unload(std::size_t out_text_id) {
    return m_Text.release(out_text_id);
}

const Texture::Texture_t* TextContainer::get(std::size_t id) const {
	auto rc = m_Text.get(id);
	if(nullptr == rc) {
		return nullptr;
	}
	return rc->get();
}
