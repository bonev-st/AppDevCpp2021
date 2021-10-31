/*
 * DrawMgr.cpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#include "manager_utils/managers/DrawMgr.hpp"

#include <iostream>

#include "utils/drawing/DrawParams.hpp"

#include "manager_utils/config/DrawMgrConfig.hpp"
#include "manager_utils/managers/ResMgr.hpp"

DrawMgr * G_pDrawMgr = nullptr;

bool DrawMgr::init(const DrawMgrConfig::Config_t &cfg) {
	m_MaxFrameRate = cfg.m_MaxFrameRate;
	if(!m_Renderer.init(cfg.m_WindowCfg)) {
		std::cerr << "DrawMgr::init::m_Renderer.init() failed." << std::endl;
        return false;
	}
	return true;
}

void DrawMgr::process() {
}

bool DrawMgr::clearScreen() {
	if(!m_Renderer.clearScreen()) {
		std::cerr << "App::drawFrame::m_Renderer.clearScreen() failed." << std::endl;
		return false;
	}
	return true;
}

void DrawMgr::finishFrame() {
	m_Renderer.finishFrame();
}

void DrawMgr::draw(const DrawParams_t & draw) {
	if(WidgetType_t::IMAGE == draw.m_WidgetType) {
		if(!drawImage(draw)) {
			std::cerr << "App::drawFrame::drawImage() failed, id: " << draw.m_ResrId << " type: " << static_cast<int>(draw.m_WidgetType) << std::endl;
		}
	} else if (WidgetType_t::TEXT == draw.m_WidgetType) {
		if(!drawText(draw)) {
			std::cerr << "App::drawFrame::drawText() failed, id: " << draw.m_ResrId << " type: " << static_cast<int>(draw.m_WidgetType) << std::endl;
		}
	} else {
		std::cerr << "App::drawFrame::drawFrame() failed, unknown widget type: " << static_cast<int>(draw.m_WidgetType) << std::endl;
	}
}

bool DrawMgr::drawImage(const DrawParams_t & img) {
	bool rc = false;
	do {
		auto p_data = G_pResMgr->get(img);
		if(nullptr == p_data) {
			std::cerr << "App::drawImage::m_ImageContainer.get failed, for image id " << img.m_ResrId  << std::endl;
			break;
		}
		auto p_texture = p_data->m_Texture.get();
		if (FULL_OPACITY == img.m_Opacity) {
			if(!m_Renderer.copy(p_texture, img.m_SrcRect, img.m_DstRect)) {
				std::cerr << "App::drawImage::drawText::m_Renderer.copy() failed, for image id " << img.m_ResrId  << std::endl;
				break;
			};
		} else {
			if(!Texture::setAlphaTexture(p_data, img.m_Opacity)) {
				std::cerr << "App::drawImage::Texture::setAlphaTexture() failed, for image id " << img.m_ResrId << std::endl;
				break;
			}
			if(!m_Renderer.copy(p_texture, img.m_SrcRect, img.m_DstRect)) {
				std::cerr << "App::drawImage::m_Renderer.copy() failed, for image id " << img.m_ResrId << std::endl;
				break;
			}
			if(!Texture::setAlphaTexture(p_data, FULL_OPACITY)) {
				std::cerr << "App::drawImage::Texture::setAlphaTexture(FULL_OPACITY) failed, for id " << img.m_ResrId << std::endl;
				break;
			}
		}
		rc = true;
	} while(0);
	return rc;
}

bool DrawMgr::drawText(const DrawParams_t & text) {
	auto p_data = G_pResMgr->get(text);
	if(nullptr == p_data) {
		std::cerr << "App::drawText::G_pResMgr->get() failed, Reason: can't find id " << text.m_ResrId << std::endl;
		return false;
	}
	if(!Texture::setAlphaTexture(p_data, text.m_Opacity)) {
		std::cerr << "App::drawText::Texture::setAlphaTexture() failed, for text id " << text.m_ResrId << std::endl;
		return false;
	}
	if(!m_Renderer.copy(p_data->m_Texture.get(), text.m_SrcRect, text.m_DstRect)) {
		std::cerr << "App::drawText::m_Renderer.copy() failed, for text id " << text.m_ResrId  << std::endl;
		return false;
	}
	return true;
}

SDL_Renderer* DrawMgr::getRendered() const {
	return m_Renderer.get();
}
