/*
 * ImageContainer.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#include "TextContainer.hpp"

#include <iostream>

#include "sdl_utils/Texture.hpp"

bool TextContainer::init(const ResourcesConfig::TextRes_t & cfg, SDL_Renderer *p_renderer) {
	for(const auto & e: cfg) {

//		gFont = TTF_OpenFont("resources/fonts/AngelineVintage.ttf", 80);
//		if(nullptr == gFont) {
//			SDLHelper::print_IMG_Error("TTF_OpenFont() fault.");
//			return;
//		}
//		TTF_Font *
//
//		SDL_Color color = {.r = 127, .g = 255, .b = 255, .a = 255};
//		SDL_Surface *textSurface = TTF_RenderText_Blended(gFont, "Hello world!", color);
//		m_Text = Texture::createTextureFromSurface(textSurface, m_Renderer.get(), BlendMode_t::BLEND);

		m_Container[e.first] = Texture::createTextureFromFile(e.second.m_Path, p_renderer, BlendMode_t::BLEND);
		if(nullptr == m_Container[e.first]) {
			std::cerr << "Texture::createSurfaceFromFile() failed." << std::endl;
	        return false;
		}
	}
	return true;
}

const Texture::Texture_t* TextContainer::get(uint32_t id) const {
	auto it = m_Container.find(id);
	if(m_Container.end() == it) {
		return nullptr;
	}
	return it->second.get();
}
