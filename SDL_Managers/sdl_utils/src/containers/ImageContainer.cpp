/*
 * ImageContainer.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#include "sdl_utils/containers/ImageContainer.hpp"

#include <iostream>

#include "sdl_utils/Texture.hpp"

bool ImageContainer::init(const ImgConfig::ImgRes_t & cfg, SDL_Renderer *p_renderer) {
	for(const auto & e: cfg) {
		m_Container[e.first] = Texture::createTextureFromFile(e.second.m_Path, p_renderer, BlendMode_t::BLEND);
		if(nullptr == m_Container[e.first]) {
			std::cerr << "ImageContainer::init::Texture::createTextureFromFile() failed." << std::endl;
	        return false;
		}
		const auto dim = e.second.m_Dimention;
		// replace image dimension with dimension from configuration
		// may be will be simple to scale image to desired size!!!
		if(dim.m_H && dim.m_W) {
			auto texture = m_Container[e.first].get();
			texture->m_W = dim.m_W;
			texture->m_H = dim.m_H;
		}
	}
	return true;
}

const Texture::Texture_t* ImageContainer::get(std::size_t id) const {
	auto it = m_Container.find(id);
	if(m_Container.end() == it) {
		return nullptr;
	}
	return it->second.get();
}
