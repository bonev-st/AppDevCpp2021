/*
 * ResourceManager.cpp
 *
 *  Created on: Oct 24, 2021
 *      Author: stanimir
 */

#include "sdl_utils/resource_manager/ResourceManager.hpp"

#include <cassert>
#include <iostream>

void ResourceManager::init(SDL_Renderer* render) {
	assert(render);
	m_Rerender = render;
}

bool ResourceManager::loadImg(const ImgConfig::ImgRes_t & cfg) {
	return m_ImageContainer.init(cfg, m_Rerender);
}

bool ResourceManager::loadFonts(const FontConfig::FontRes_t & cfg) {
	return m_TextContainer.init(cfg, m_Rerender);
}

const Texture::Texture_t* ResourceManager::get(const DrawParams_t & param) const {
	if(WidgetType_t::IMAGE == param.m_WidgetType) {
		return m_ImageContainer.get(param.m_ResrId);
	} else if (WidgetType_t::TEXT == param.m_WidgetType) {
		return m_TextContainer.get(param.m_ResrId);
	}
	std::cerr << "ResourceManager::get() fault, unknown resource type: " << static_cast<int>(param.m_WidgetType) << " for id: " << param.m_ResrId << std::endl;
	return nullptr;
}

bool ResourceManager::populateImg(DrawParams_t & param) {
	auto texture = m_ImageContainer.get(param.m_ResrId);
	if(nullptr == texture) {
		std::cerr << "ResourceManager::populateImg::m_ImageContainer.get("<< param.m_ResrId << ") fault" << std::endl;
		return false;
	}
	setDimention(param, texture->m_W, texture->m_H);
	param.m_WidgetType = WidgetType_t::IMAGE;
	return true;
}

bool ResourceManager::createText(const std::string &str, const Color & color, std::size_t font_id, DrawParams_t & param) {
	if(WidgetType_t::UNKNOWN == param.m_WidgetType) {
		if(!m_TextContainer.createText(str, color, font_id, param.m_ResrId)) {
			std::cerr << "ResourceManager::createTexts::m_TextContainer.createText() fault" << std::endl;
			return false;
		}
		param.m_WidgetType = WidgetType_t::TEXT;
	} else if (WidgetType_t::TEXT == param.m_WidgetType) {
		if(!m_TextContainer.reloadText(str, color, font_id, param.m_ResrId)) {
			std::cerr << "ResourceManager::createTexts::m_TextContainer.reloadText() fault" << std::endl;
			return false;
		}
	} else {
		std::cerr << "ResourceManager::createText() fault, invalid resource type: " << static_cast<int>(param.m_WidgetType) << std::endl;
		return false;
	}
	const auto texture = get(param);
	if(nullptr == texture) {
		return false;
	}
	setDimention(param, texture->m_W, texture->m_H);
	return true;
}

bool ResourceManager::releaseText(DrawParams_t & param) {
	if(!m_TextContainer.unloadText(param.m_ResrId)) {
		std::cerr << "ResourceManager::releaseText(" << param.m_ResrId <<") fault" << std::endl;
		return false;
	}
	param.m_WidgetType = WidgetType_t::UNKNOWN;
	return true;
}

void ResourceManager::setDimention(DrawParams_t & param, int32_t w, int32_t h) {
	Rectangle rec(0, 0, w, h);
	param.m_SrcRect = rec;
	param.m_DstRect = rec;
}
