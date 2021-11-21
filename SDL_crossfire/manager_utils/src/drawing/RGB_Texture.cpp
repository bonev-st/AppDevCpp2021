/*
 * RGB_Texture.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#include "manager_utils/drawing/RGB_Texture.hpp"

#include <iostream>

#include "manager_utils/managers/ResMgr.hpp"

bool RGB_Texture::create(const Dimention &dim, const Color &color, const Point &pos) {
	if(WidgetType_t::UNKNOWN != m_DrawParams.m_WidgetType) {
		std::cerr << "Warning: Image::create() override RGB texture with ID " << m_DrawParams.m_ResrId << std::endl;
	}
	m_DrawParams.m_Dimention = dim;
	if(!ResMgrInst::getInstance()->createTexture(color, m_DrawParams)) {
		std::cerr << "Text::create.createTexture() failed"<< std::endl;
		return false;
	}
	m_DrawParams.m_DstRect.m_Pos = pos;
	return true;
}

bool RGB_Texture::setColor(const Color &color) {
	if(!ResMgrInst::getInstance()->createTexture(color, m_DrawParams)) {
		std::cerr << "Text::setColor.createTexture() failed"<< std::endl;
		return false;
	}
	return true;
}
