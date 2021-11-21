/*
 * ImageContainer.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#include "sdl_utils/containers/FontContainer.hpp"

#include <iostream>

#include <SDL_ttf.h>
#include "utils/Destroy.hpp"

#include "sdl_utils/SDLHelper.hpp"

bool FontContainer::init(const FontConfig::FontRes_t & cfg) {
	for(const auto & [key , val] : cfg) {
		auto & font = m_Container[key];
		font.set(TTF_OpenFont(val.m_Path.c_str(), val.m_TextSize), Destroy::free<TTF_Font, TTF_CloseFont>);
#ifdef SHOW_MEM_ALLOC_INFO
		std::cout << "+ TTF_OpenFont() create Font " << font << std::endl;
#endif
		if(nullptr == font) {
			SDLHelper::print_SDL_Error("FontContainer::init::TTF_OpenFont() fault.");
			return false;
		}
	}
	return true;
}

const TTF_Font* FontContainer::get(std::size_t id) const {
	auto it = m_Container.find(id);
	if(m_Container.end() == it) {
		return nullptr;
	}
	return it->second;
}
