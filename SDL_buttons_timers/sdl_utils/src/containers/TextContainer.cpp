/*
 * TextContainer.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: stanimir
 */

#include "sdl_utils/containers/TextContainer.hpp"

#include <iostream>
#include <SDL_ttf.h>

#include <sdl_utils/Texture.hpp>

bool TextContainer::init(const FontConfig::FontRes_t & cfg, SDL_Renderer *p_renderer) {
	m_Renderer = p_renderer;
	return m_Font.init(cfg);
}

bool TextContainer::createText(const std::string &text, const Color &color, std::size_t font_id, std::size_t &out_text_id) {
	auto font = m_Font.get(font_id);
	if(nullptr == font) {
		std::cerr << "TextContainer::createText::m_Font.get() failed. Reason: Font with id " << font_id << " not found" << std::endl;
		return false;
	}
	Text_t texture = Texture::createTextureFromFont(text, color, font, m_Renderer);
	if(nullptr == texture) {
		std::cerr << "TextContainer::createText::Texture::createTextureFromFont() failed."  << " for text: " << text << std::endl;
        return false;
	}
	out_text_id = m_Text.add(texture);
    return true;
}

bool TextContainer::reloadText(const std::string &text, const Color &color, std::size_t font_id, std::size_t out_text_id) {
	auto font = m_Font.get(font_id);
	if(nullptr == font) {
		std::cerr << "TextContainer::reloadText::m_Font.get() failed. Reason: Font with id " << font_id << " not found" << std::endl;
		return false;
	}
	Text_t texture = Texture::createTextureFromFont(text, color, font, m_Renderer);
	if(nullptr == texture) {
		std::cerr << "TextContainer::reloadText::Texture::createTextureFromFont() failed." << " for text: " << text << std::endl;
        return false;
	}
    return m_Text.replace(out_text_id, texture);
}

bool TextContainer::unloadText(std::size_t out_text_id) {
    return m_Text.release(out_text_id);
}

const Texture::Texture_t* TextContainer::get(std::size_t id) const {
	auto rc = m_Text.get(id);
	if(nullptr == rc) {
		return nullptr;
	}
	return rc->get();
}
