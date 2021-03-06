/*
 * RGB_Texture.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#include "gr_engine/drawing/RGB_Texture.hpp"

#include <iostream>

#include "gr_engine/managers/DrawMgr.hpp"
#include "gr_engine/managers/ResMgr.hpp"

bool RGB_Texture::create(const Dimention &dim, const Color &color, const Point &pos) {
	if(!ResMgrInst::getInstance()->createTexture(dim, color, m_DrawParams)) {
		std::cerr << "RGB_Texture::create.createTexture() failed"<< std::endl;
		return false;
	}
	activateAlphaModulation();
	setPosition(pos);
	invalidate();
	return true;
}

bool RGB_Texture::setColor(const Color &color) {
	if(!ResMgrInst::getInstance()->setTextureColor(color, m_DrawParams)) {
		std::cerr << "RGB_Texture::setColor() createTexture() failed"<< std::endl;
		return false;
	}
	invalidate();
	return true;
}

std::shared_ptr<SDL_Texture> RGB_Texture::getLock() {
	return ResMgrInst::getInstance()->getTextureRenderLock(m_DrawParams);
}
