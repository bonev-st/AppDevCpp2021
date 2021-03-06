/*
 * ResMgr.cpp
 *
 *  Created on: Oct 24, 2021
 *      Author: stanimir
 */

#include "gr_engine/managers/ResMgr.hpp"

#include <cassert>
#include <iostream>

#include "gr_engine/config/ResMgrConfig.hpp"
#include "utils/drawing/DrawParams.hpp"
#include "sdl_utils/containers/ImageContainer.hpp"
#include "sdl_utils/containers/TextContainer.hpp"
#include "sdl_utils/containers/TextureContainer.hpp"
#include "sdl_utils/Renderer.hpp"


ResMgr * G_pResMgr = nullptr;

bool ResMgr::init(const ResMgrConfig::Config_t &cfg, SDL_Renderer* render, ImageContainer  *img
		, TextContainer* text, TextureContainer* texture) {
	assert(render);
	assert(img);
	assert(text);
	assert(texture);
	m_Rerender = render;
	m_ImageContainer = img;
	m_TextContainer = text;
	m_TextureContainer = texture;

	if(!m_ImageContainer->init(cfg.m_ImgRes, m_Rerender)) {
		std::cerr << "ResMgr::init.m_ImageContainer->.init() failed." << std::endl;
		return false;
	}
	if(!m_TextContainer->init(cfg.m_FontRes, m_Rerender)) {
		std::cerr << "ResMgr::init.m_TextContainer->init() failed." << std::endl;
		return false;
	}
	if(!m_TextureContainer->init(m_Rerender)) {
		std::cerr << "ResMgr::init.m_TextureContainer->init() failed." << std::endl;
		return false;
	}
	return true;
}

const Texture::Texture_t* ResMgr::get(const DrawParams_t & param) const {
	if(WidgetType_t::IMAGE == param.m_WidgetType) {
		return m_ImageContainer->get(param.m_ResrId);
	} else if (WidgetType_t::TEXT == param.m_WidgetType) {
		return m_TextContainer->get(param.m_ResrId);
	} else if (WidgetType_t::RGB_TEXTURE == param.m_WidgetType) {
		return m_TextureContainer->get(param.m_ResrId);
	}
	std::cerr << "ResMgr::get() failed, unknown resource type: " << static_cast<int>(param.m_WidgetType) << " for id: " << param.m_ResrId << std::endl;
	return nullptr;
}

bool ResMgr::release(DrawParams_t & param) {
	if (WidgetType_t::TEXT == param.m_WidgetType) {
		if(!m_TextContainer->unload(param.m_ResrId)) {
			std::cerr << "release text with id(" << param.m_ResrId <<") failed" << std::endl;
			return false;
		}
	} else if (WidgetType_t::RGB_TEXTURE == param.m_WidgetType) {
		if(!m_TextureContainer->unload(param.m_ResrId)) {
			std::cerr << "release texture with id(" << param.m_ResrId <<") failed" << std::endl;
			return false;
		}
	} else {
		std::cerr << "ResMgr::release() failed, unknown resource type: " << static_cast<int>(param.m_WidgetType) << " for id: " << param.m_ResrId << std::endl;
		return false;
	}
	return true;
}

bool ResMgr::populateImg(DrawParams_t & param) {
	auto texture = m_ImageContainer->get(param.m_ResrId);
	if(nullptr == texture) {
		std::cerr << "ResMgr::populateImg::m_ImageContainer->get("<< param.m_ResrId << ") failed" << std::endl;
		return false;
	}
	auto frames = m_ImageContainer->getFrames(param.m_ResrId);
	assert(frames);

	setDimention(param, texture->m_W, texture->m_H, frames);
	param.m_WidgetType = WidgetType_t::IMAGE;
	return true;
}

bool ResMgr::createText(const std::string &str, const Color & color, std::size_t font_id, DrawParams_t & param) {
	if(WidgetType_t::UNKNOWN == param.m_WidgetType) {
		if(!m_TextContainer->create(str, color, font_id, param.m_ResrId)) {
			std::cerr << "ResMgr::createTexts::m_TextContainer->createText() failed" << std::endl;
			return false;
		}
		param.m_WidgetType = WidgetType_t::TEXT;
	} else if (WidgetType_t::TEXT == param.m_WidgetType) {
		if(!m_TextContainer->reload(str, color, font_id, param.m_ResrId)) {
			std::cerr << "ResMgr::createTexts::m_TextContainer->reloadText() failed" << std::endl;
			return false;
		}
	} else {
		std::cerr << "ResMgr::createText() failed, invalid resource type: " << static_cast<int>(param.m_WidgetType) << std::endl;
		return false;
	}
	const auto texture = get(param);
	if(nullptr == texture) {
		return false;
	}
	setDimention(param, texture->m_W, texture->m_H);
	return true;
}

bool ResMgr::createTexture(const Dimention &dim, const Color & color, DrawParams_t & param) {
	if(WidgetType_t::UNKNOWN == param.m_WidgetType) {
		if(!m_TextureContainer->create(dim, color, param.m_ResrId)) {
			std::cerr << "ResMgr::createTexture::m_TextureContainer->create() failed" << std::endl;
			return false;
		}
		param.m_WidgetType = WidgetType_t::RGB_TEXTURE;
	} else if (WidgetType_t::RGB_TEXTURE == param.m_WidgetType) {
		if(!m_TextureContainer->reload(dim, color, param.m_ResrId)) {
			std::cerr << "ResMgr::createTexts::m_TextureContainer->reload() failed" << std::endl;
			return false;
		}
	} else {
		std::cerr << "ResMgr::createTexture() failed, invalid resource type: " << static_cast<int>(param.m_WidgetType) << std::endl;
		return false;
	}
	const auto texture = get(param);
	if(nullptr == texture) {
		return false;
	}
	setDimention(param, texture->m_W, texture->m_H);
	param.m_BlendMode = BlendMode_t::NONE;
	return true;
}

bool ResMgr::setTextureColor(const Color & color, DrawParams_t & param) {
	if(WidgetType_t::RGB_TEXTURE != param.m_WidgetType) {
		std::cerr << "Invalid resource type: " << static_cast<int>(param.m_WidgetType) << std::endl;
		return false;
	}
	if(!m_TextureContainer->setColor(color, param.m_ResrId)) {
		std::cerr << "setColor(" << param.m_ResrId <<") failed" << std::endl;
		return false;
	}
	return true;
}

std::shared_ptr<SDL_Texture> ResMgr::getTextureRenderLock(const DrawParams_t & param) {
	if(WidgetType_t::RGB_TEXTURE != param.m_WidgetType) {
		std::cerr << "Invalid resource type: " << static_cast<int>(param.m_WidgetType) << std::endl;
		return nullptr;
	}
	auto rc = m_TextureContainer->getLock(param.m_ResrId);
	if(nullptr == rc) {
		std::cerr << "Get render lock failed, texture id " << param.m_ResrId << std::endl;
	}
	return rc;
}

void ResMgr::setDimention(DrawParams_t & param, int32_t w, int32_t h, const ImageContainer::Frames_t * frames) {
	Rectangle rec(0, 0, w, h);
	param.m_Dimention = Dimention(w, h);
	if(frames && !frames->empty()) {
		param.m_Frames = frames;
		rec = frames->front();
	} else {
		param.m_Frames = nullptr;
	}
	param.m_SrcRect = rec;
	param.m_DstRect = rec;
}
