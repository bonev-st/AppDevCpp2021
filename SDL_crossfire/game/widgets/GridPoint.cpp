/*
 * GridPoint.cpp
 *
 *  Created on: Nov 29, 2021
 *      Author: stanimir
 */

#include "game/widgets/GridPoint.hpp"

#include <iostream>

bool GridPoint::init(std::size_t img_id) {
	for(std::size_t rol = 0; RelCoordinates::GRID_RECT_V_NUMB > rol; ++rol) {
		for(std::size_t col = 0; RelCoordinates::GRID_RECT_H_NUMB > col; ++col) {
			const auto rel_pos = Point(static_cast<int32_t>(col), static_cast<int32_t>(rol));
			const auto pos = Layout::getRel2AbsPosition(rel_pos);
			if(!m_ImgContainer[(RelCoordinates::GRID_RECT_H_NUMB*rol) + col].create(img_id, pos, true)) {
				std::cerr << "Image create failed" << std::endl;
				return false;
			}
		}
	}
	return true;
}

void GridPoint::draw() {
	for(auto & e : m_ImgContainer) {
		e.draw();
	}
}
