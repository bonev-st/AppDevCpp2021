/*
 * Image.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#include "manager_utils/drawing/Image.hpp"

#include <iostream>

#include "utils/geometry/Geometry.hpp"
#include "manager_utils/managers/ResMgr.hpp"

bool Image::create(std::size_t image_id, const Point &pos, bool center) {
	if(WidgetType_t::UNKNOWN != m_DrawParams.m_WidgetType) {
		std::cerr << "Warning: Image::create() override image with ID " << image_id << std::endl;
	}
	m_DrawParams.m_WidgetType = WidgetType_t::IMAGE;
	m_DrawParams.m_ResrId = image_id;
	if(!ResMgrInst::getInstance()->populateImg(m_DrawParams)) {
		std::cerr << "Image::create.G_pResMgr->populateImg() fault" << std::endl;
		return false;
	}
	if(Point::UNDEFINED != pos) {
		center?setPositionCenter(pos):setPosition(pos);
	}
	m_MaxFrames = 0;
	if(m_DrawParams.m_Frames) {
		m_MaxFrames = m_DrawParams.m_Frames->size();
	}
	return true;
}

void Image::setFrame(std::size_t n) {
	if(m_MaxFrames > n) {
		m_CurrFrame = n;
		setFrame();
	} else {
		std::cerr << "Image::setFrame(), try to set non existing frame " << n << " to image with ID " << m_DrawParams.m_ResrId << std::endl;
	}
}

void Image::setNextFrame() {
	if(m_MaxFrames) {
		++m_CurrFrame;
		if(m_MaxFrames <= m_CurrFrame) {
			m_CurrFrame = 0;
		}
		setFrame();
	} else {
		std::cerr << "Image::setNextFrame(), try to set frame to non sprite image with ID " << m_DrawParams.m_ResrId << std::endl;
	}
}

void Image::setPrevFrame() {
	if(m_MaxFrames) {
		if(0 == m_CurrFrame) {
			m_CurrFrame = m_MaxFrames-1;
		} else {
			--m_CurrFrame;
		}
		setFrame();
	} else {
		std::cerr << "Image::setPrevFrame(), try to set frame to non sprite image with ID " << m_DrawParams.m_ResrId << std::endl;
	}
}

std::size_t Image::getFrame() const {
	return m_CurrFrame;
}

std::size_t Image::getMaxFrames() const {
	return m_MaxFrames;
}

void Image::setFrame() {
	const auto & rec = (*m_DrawParams.m_Frames)[m_CurrFrame];
	m_DrawParams.m_SrcRect = rec;
}
