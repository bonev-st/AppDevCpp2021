/*
 * DrawMgr.cpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/DrawMgr.hpp"

#include <iostream>
#include <cassert>

#include "utils/drawing/DrawParams.hpp"

#include "sdl_utils/Renderer.hpp"
#include "sdl_utils/Texture.hpp"

#include "manager_utils/config/DrawMgrConfig.hpp"
#include "manager_utils/managers/ResMgr.hpp"

bool DrawMgr::init(const DrawMgrConfig::Config_t &cfg, Renderer* render) {
	assert(render);
	m_Renderer = render;
	m_Resources = ResMgrInst::getInstance();
	if(!m_Renderer->init(cfg.m_WindowCfg)) {
		std::cerr << "DrawMgr::init::m_Renderer->init() failed." << std::endl;
        return false;
	}
	return true;
}

bool DrawMgr::clearScreen() const {
	if(!m_Renderer->clearScreen()) {
		std::cerr << "DrawMgr::drawFrame::m_Renderer->clearScreen() failed." << std::endl;
		return false;
	}
	return true;
}

void DrawMgr::finishFrame() const {
	m_Renderer->finishFrame();
}

void DrawMgr::draw(const DrawParams_t & draw) const {
	if(WidgetType_t::IMAGE == draw.m_WidgetType) {
		if(!drawImage(draw)) {
			std::cerr << "DrawMgr::drawFrame::drawImage() failed, id: " << draw.m_ResrId << " type: " << static_cast<int>(draw.m_WidgetType) << std::endl;
		}
	} else if (WidgetType_t::TEXT == draw.m_WidgetType) {
		if(!drawText(draw)) {
			std::cerr << "DrawMgr::drawFrame::drawText() failed, id: " << draw.m_ResrId << " type: " << static_cast<int>(draw.m_WidgetType) << std::endl;
		}
	} else {
		std::cerr << "DrawMgr::drawFrame::drawFrame() failed, unknown widget type: " << static_cast<int>(draw.m_WidgetType) << std::endl;
	}
}

bool DrawMgr::drawImage(const DrawParams_t & img) const {
	bool rc = false;
	do {
		auto p_data = m_Resources->get(img);
		if(nullptr == p_data) {
			std::cerr << "DrawMgr::drawImage::ResMgrSing.m_Resources->get() failed, for image id " << img.m_ResrId  << std::endl;
			break;
		}
		auto p_texture = p_data->m_Texture.get();
		if (FULL_OPACITY == img.m_Opacity) {
			if(!m_Renderer->copy(p_texture, img)) {
				std::cerr << "DrawMgr::drawImage::drawText::m_Renderer->copy() failed, for image id " << img.m_ResrId  << std::endl;
				break;
			};
		} else {
			if(!Texture::setAlphaTexture(p_data, img.m_Opacity)) {
				std::cerr << "DrawMgr::drawImage::Texture::setAlphaTexture() failed, for image id " << img.m_ResrId << std::endl;
				break;
			}
			if(!m_Renderer->copy(p_texture, img)) {
				std::cerr << "DrawMgr::drawImage::m_Renderer->copy() failed, for image id " << img.m_ResrId << std::endl;
				break;
			}
			if(!Texture::setAlphaTexture(p_data, FULL_OPACITY)) {
				std::cerr << "DrawMgr::drawImage::Texture::setAlphaTexture(FULL_OPACITY) failed, for id " << img.m_ResrId << std::endl;
				break;
			}
		}
		rc = true;
	} while(0);
	return rc;
}

bool DrawMgr::drawText(const DrawParams_t & text) const {
	auto p_data = m_Resources->get(text);
	if(nullptr == p_data) {
		std::cerr << "DrawMgr::drawText.m_Resources->get() failed, Reason: can't find id " << text.m_ResrId << std::endl;
		return false;
	}
	if(!m_Renderer->copy(p_data->m_Texture.get(), text)) {
		std::cerr << "DrawMgr::drawText::m_Renderer->copy() failed, for text id " << text.m_ResrId  << std::endl;
		return false;
	}
	return true;
}

SDL_Renderer* DrawMgr::getRendered() const {
	return *m_Renderer;
}

bool DrawMgr::setBlendMode(const DrawParams_t & draw) {
	auto * p_texture = m_Resources->get(draw);
	if(nullptr == p_texture) {
		std::cerr << "DrawMgr::setBlendMode.m_Resources->get() failed, id: " << draw.m_ResrId << " type: " << static_cast<int>(draw.m_WidgetType) << std::endl;
		return false;
	}
	return Texture::setBlendModeTexture(p_texture, draw.m_BlendMode);
}

bool DrawMgr::setAlpha(const DrawParams_t & draw) {
	if(WidgetType_t::IMAGE == draw.m_WidgetType) {
		return true;
	}
	auto * p_texture = m_Resources->get(draw);
	if(nullptr == p_texture) {
		std::cerr << "DrawMgr::setAlpha.m_Resources->get() failed, id: " << draw.m_ResrId << " type: " << static_cast<int>(draw.m_WidgetType) << std::endl;
		return false;
	}
	return Texture::setAlphaTexture(p_texture, draw.m_Opacity);
}

const DiplayMode::Mode_t & DrawMgr::getDisplayMode() const {
	assert(m_Renderer);
	return m_Renderer->getDisplayMode();
}
