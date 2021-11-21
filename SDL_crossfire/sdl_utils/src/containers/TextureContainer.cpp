/*
 * TextureContainer.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#include "sdl_utils/containers/TextureContainer.hpp"

#include <iostream>
#include <cassert>
#include <SDL_ttf.h>

#include <sdl_utils/Texture.hpp>

#include "utils/drawing/Color.hpp"
#include "utils/drawing/Dimention.hpp"
#include "utils/drawing/BlendMode.hpp"

bool TextureContainer::init(SDL_Renderer *p_renderer) {
	assert(p_renderer);
	m_Renderer = p_renderer;
	return true;
}

bool TextureContainer::create(const Dimention& dim, const Color& color, std::size_t &out_id) {
	auto surface = Texture::createRGB_Surface(dim);
	if(!surface) {
		std::cerr << "TextureContainer::create::Texture::createRGB_Surface() failed." << std::endl;
        return false;
	}
	RGB_Texture_t texture;
	texture.m_Texture = Texture::createTextureFromSurface(surface.get(), m_Renderer);
	if(nullptr == texture.m_Texture) {
		std::cerr << "TextureContainer::create::Texture::createTextureFromSurface() failed." << std::endl;
        return false;
	}
	if(!Texture::fillTexture(texture.m_Texture.get(), color, m_Renderer)) {
		std::cerr << "TextureContainer::create::Texture::fillTexture() failed." << std::endl;
        return false;
	}
	texture.m_Color = color;
	out_id = m_Texture.add(texture);
    return true;
}

bool TextureContainer::reload(const Color& color, std::size_t id) {
	auto texture = m_Texture.get(id);
	if(nullptr == texture) {
		return false;
	}
	auto tmp = *texture;
	if(!Texture::fillTexture(tmp.m_Texture.get(), color, m_Renderer)) {
		std::cerr << "TextureContainer::create::Texture::fillTexture() failed." << std::endl;
        return false;
	}
	tmp.m_Color = color;
    return m_Texture.replace(id, tmp);
}

bool TextureContainer::unload(std::size_t id) {
    return m_Texture.release(id);
}

const Texture::Texture_t* TextureContainer::get(std::size_t id) const {
	auto rc = m_Texture.get(id);
	if(nullptr == rc) {
		return nullptr;
	}
	return rc->m_Texture.get();
}
