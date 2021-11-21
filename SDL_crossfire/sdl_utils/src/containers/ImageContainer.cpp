/*
 * ImageContainer.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#include "sdl_utils/containers/ImageContainer.hpp"

#include <iostream>
#include <cassert>

#include "sdl_utils/Texture.hpp"

bool ImageContainer::init(const ImgConfig::ImgRes_t & cfg, SDL_Renderer *p_renderer) {
	assert(p_renderer);
	for(const auto & [key, data]: cfg) {
		m_Container[key] = Texture::createTextureFromFile(data.m_Path, p_renderer);
		m_Frames[key] = data.m_Frames;

		if(nullptr == m_Container[key]) {
			std::cerr << "ImageContainer::init::Texture::createTextureFromFile() failed." << std::endl;
	        return false;
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

const ImageContainer::Frames_t* ImageContainer::getFrames(std::size_t id) const {
	auto it = m_Frames.find(id);
	if(m_Frames.end() == it) {
		return nullptr;
	}
	return &it->second;
}
