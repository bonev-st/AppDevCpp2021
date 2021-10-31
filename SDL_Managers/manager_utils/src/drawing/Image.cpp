/*
 * Image.cpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#include "manager_utils/drawing/Image.hpp"

#include <iostream>

#include "manager_utils/managers/ResMgr.hpp"

bool Image::create(int32_t image_id, const Point &pos) {
	m_DrawParams.m_WidgetType = WidgetType_t::IMAGE;
	m_DrawParams.m_ResrId = image_id;
	if(!G_pResMgr->populateImg(m_DrawParams)) {
		std::cerr << "Game::initImgs.ResMgrSing::getInstance()->populateImg(e) fault" << std::endl;
		return false;
	}
	if(Point::ZERO != pos) {
		m_DrawParams.m_DstRect.m_Pos = pos;
	}
	return true;
}
