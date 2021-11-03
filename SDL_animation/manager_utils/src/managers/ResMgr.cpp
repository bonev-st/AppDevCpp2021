/*
 * ResMgr.cpp
 *
 *  Created on: Oct 24, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/ResMgr.hpp"

#include <cassert>
#include <iostream>

#include "utils/drawing/DrawParams.hpp"

#include "manager_utils/config/ResMgrConfig.hpp"

ResMgr * G_pResMgr = nullptr;

bool ResMgr::init(const ResMgrConfig::Config_t &cfg, SDL_Renderer* render) {
	assert(render);
	m_Rerender = render;
	if(!m_ImageContainer.init(cfg.m_ImgRes, m_Rerender)) {
		std::cerr << "ResMgr::init.m_ImageContainer.init() failed." << std::endl;
		return false;
	}
	if(!m_TextContainer.init(cfg.m_FontRes, m_Rerender)) {
		std::cerr << "ResMgr::init.m_TextContainer.init() failed." << std::endl;
		return false;
	}
	return true;
}

const Texture::Texture_t* ResMgr::get(const DrawParams_t & param) const {
	if(WidgetType_t::IMAGE == param.m_WidgetType) {
		return m_ImageContainer.get(param.m_ResrId);
	} else if (WidgetType_t::TEXT == param.m_WidgetType) {
		return m_TextContainer.get(param.m_ResrId);
	}
	std::cerr << "ResMgr::get() fault, unknown resource type: " << static_cast<int>(param.m_WidgetType) << " for id: " << param.m_ResrId << std::endl;
	return nullptr;
}

bool ResMgr::populateImg(DrawParams_t & param) {
	auto texture = m_ImageContainer.get(param.m_ResrId);
	if(nullptr == texture) {
		std::cerr << "ResMgr::populateImg::m_ImageContainer.get("<< param.m_ResrId << ") fault" << std::endl;
		return false;
	}
	auto frames = m_ImageContainer.getFrames(param.m_ResrId);
	assert(frames);

	setDimention(param, texture->m_W, texture->m_H, frames);
	param.m_WidgetType = WidgetType_t::IMAGE;
	return true;
}

bool ResMgr::createText(const std::string &str, const Color & color, std::size_t font_id, DrawParams_t & param) {
	if(WidgetType_t::UNKNOWN == param.m_WidgetType) {
		if(!m_TextContainer.createText(str, color, font_id, param.m_ResrId)) {
			std::cerr << "ResMgr::createTexts::m_TextContainer.createText() fault" << std::endl;
			return false;
		}
		param.m_WidgetType = WidgetType_t::TEXT;
	} else if (WidgetType_t::TEXT == param.m_WidgetType) {
		if(!m_TextContainer.reloadText(str, color, font_id, param.m_ResrId)) {
			std::cerr << "ResMgr::createTexts::m_TextContainer.reloadText() fault" << std::endl;
			return false;
		}
	} else {
		std::cerr << "ResMgr::createText() fault, invalid resource type: " << static_cast<int>(param.m_WidgetType) << std::endl;
		return false;
	}
	const auto texture = get(param);
	if(nullptr == texture) {
		return false;
	}
	setDimention(param, texture->m_W, texture->m_H);
	return true;
}

bool ResMgr::releaseText(DrawParams_t & param) {
	if(!m_TextContainer.unloadText(param.m_ResrId)) {
		std::cerr << "ResMgr::releaseText(" << param.m_ResrId <<") fault" << std::endl;
		return false;
	}
	param.m_WidgetType = WidgetType_t::UNKNOWN;
	return true;
}

void ResMgr::setDimention(DrawParams_t & param, int32_t w, int32_t h, const ImageContainer::Frames_t* frames) {
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
