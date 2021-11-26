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
#include "sdl_utils/SDLHelper.hpp"

#include "utils/drawing/Color.hpp"
#include "utils/drawing/Dimention.hpp"
#include "utils/drawing/BlendMode.hpp"

bool TextureContainer::init(SDL_Renderer *p_renderer) {
	assert(p_renderer);
	m_Renderer = p_renderer;
	return true;
}

bool TextureContainer::create(const Dimention& dim, const Color& color, std::size_t &out_id) {
	const auto texture = create(dim, color);
	if(!texture.m_Texture) {
		std::cerr << "TextureContainer::create() create new failed." << std::endl;
        return false;
	}
	out_id = m_Texture.add(texture);
    return true;
}

bool TextureContainer::reload(const Dimention& dim, const Color& color, std::size_t id) {
	const auto texture = create(dim, color);
	if(!texture.m_Texture) {
		std::cerr << "TextureContainer::reload() create new failed." << std::endl;
        return false;
	}
	const auto rc = m_Texture.replace(id, texture);
	if(!rc) {
		std::cerr << "TextureContainer::reload() m_Texture.replace() failed." << std::endl;
        return false;
	}
    return rc;
}

bool TextureContainer::unload(std::size_t id) {
    return m_Texture.release(id);
}

std::shared_ptr<SDL_Texture> TextureContainer::getLock(std::size_t id) {
	auto texture = getTexture(id);
	if(!texture) {
		std::cerr << "Invalid Texture Id " << id << std::endl;
		return nullptr;
	}
	auto lock = Texture::getLockRender(texture->m_Texture->m_Texture.get(), texture->m_Color, m_Renderer);
	if(nullptr == lock) {
		std::cerr << "Texture::getLockRender() failed" << std::endl;
		return nullptr;
	}
	return lock;
}

const Texture::Texture_t* TextureContainer::get(std::size_t id) const {
	auto rc = getTexture(id);
	if(nullptr == rc) {
		return nullptr;
	}
	return rc->m_Texture.get();
}

TextureContainer::RGB_Texture_t TextureContainer::create(const Dimention& dim, const Color& color) {
	RGB_Texture_t texture;
	texture.m_Texture = Texture::createTextureRGBA32(dim, m_Renderer);
	if(nullptr == texture.m_Texture) {
		std::cerr << "TextureContainer::create() Texture::createTextureRGBA32() failed." << std::endl;
        return RGB_Texture_t();
	}
	if(!Texture::fillTexture(texture.m_Texture.get(), color, m_Renderer)) {
		std::cerr << "TextureContainer::create() Texture::fillTexture() failed." << std::endl;
        return RGB_Texture_t();
	}
	texture.m_Color = color;
    return texture;
}

const TextureContainer::RGB_Texture_t* TextureContainer::getTexture(std::size_t id) const {
	auto rc = m_Texture.get(id);
	if(nullptr == rc) {
		return nullptr;
	}
	return rc;
}
