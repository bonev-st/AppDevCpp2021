/*
 * RGB_Texture.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#include "manager_utils/drawing/RGB_Texture.hpp"

#include <iostream>

#include "manager_utils/managers/ResMgr.hpp"
#include "manager_utils/managers/DrawMgr.hpp"

bool RGB_Texture::create(const Dimention &dim, const Color &color, const Point &pos) {
	if(WidgetType_t::UNKNOWN != m_DrawParams.m_WidgetType) {
		std::cout << "Warning: RGB_Texture::create() override RGB texture with ID " << m_DrawParams.m_ResrId << std::endl;
	}
	m_DrawParams.m_Dimention = dim;
	if(!ResMgrInst::getInstance()->createTexture(color, m_DrawParams)) {
		std::cerr << "RGB_Texture::create.createTexture() failed"<< std::endl;
		return false;
	}
	m_DrawParams.m_DstRect.m_Pos = pos;
	return true;
}

bool RGB_Texture::setColor(const Color &color) {
	if(!ResMgrInst::getInstance()->createTexture(color, m_DrawParams)) {
		std::cerr << "RGB_Texture::setColor() createTexture() failed"<< std::endl;
		return false;
	}
	return true;
}

std::shared_ptr<SDL_Texture> RGB_Texture::getLock() {
	return ResMgrInst::getInstance()->getTextureRenderLock(m_DrawParams);
}

bool RGB_Texture::copy(Widget * src) {
	src->draw();
	return true;
}
