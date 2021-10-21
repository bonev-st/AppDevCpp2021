/*
 * ImageContainer.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#include "sdl_utils/containers/ImageContainer.hpp"

#include <iostream>

#include "sdl_utils/Texture.hpp"

bool ImageContainer::init(const ResourcesConfig::ImgRes_t & cfg, SDL_Renderer *p_renderer) {
	for(const auto & e: cfg) {
		m_Container[e.first] = Texture::createTextureFromFile(e.second, p_renderer, BlendMode_t::BLEND);
		if(nullptr == m_Container[e.first]) {
			std::cerr << "Texture::createSurfaceFromFile() failed." << std::endl;
	        return false;
		}
	}
	return true;
}

const Texture::Texture_t* ImageContainer::get(uint32_t id) const {
	auto it = m_Container.find(id);
	if(m_Container.end() == it) {
		return nullptr;
	}
	return it->second.get();
}
