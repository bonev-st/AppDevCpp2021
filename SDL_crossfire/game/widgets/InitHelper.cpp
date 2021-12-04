/*
 * InitHelper.cpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#include "game/widgets/InitHelper.hpp"

#include <iostream>

namespace InitHelper {
bool initScaledImage(ImageData_t & data, std::size_t img_id, const Color & color,
		std::uint8_t img_aplha, const Point &pos, double scale) {

	if(!data.m_Image.create(img_id)) {
		std::cerr << "m_CrossfireImageL1.create() failed." << std::endl;
	}
	if(FULL_OPACITY != img_aplha) {
		data.m_Image.activateAlphaModulation();
		data.m_Image.setOpacity(FULL_OPACITY);
	}
	if(!data.m_ScaleContainer.init(scale, &data.m_Image, color)) {
		std::cerr << "Create scale container failed"<< std::endl;
		return false;
	}
	data.m_ScaleContainer.setPosition(pos);
	return true;
}


bool initScaledText(TextData_t & data, std::size_t font_id, const std::string & text,
		const Color & color, const Point &pos, const Color & gnd, double scale) {
	if(!data.m_Text.create(text, color, font_id)) {
		std::cerr << "Create text with font id " << font_id << " failed"<< std::endl;
		return false;
	}
	if(!data.m_ScaleContainer.init(scale, &data.m_Text, gnd)) {
		std::cerr << "Create scale container failed"<< std::endl;
		return false;
	}
	data.m_ScaleContainer.setPosition(pos);
	return true;
}

} /* namespace Init */
