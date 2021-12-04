/*
 * GridPoint.hpp
 *
 *  Created on: Nov 29, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_GRIDPOINT_HPP_
#define GAME_WIDGETS_GRIDPOINT_HPP_

#include <array>

#include "gr_engine/drawing/Image.hpp"
#include "game/config/Layout.hpp"

class GridPoint {
public:
	bool init(std::size_t img_id);
	void draw();
private:
	std::array<Image, RelCoordinates::GRID_RECT_H_NUMB * RelCoordinates::GRID_RECT_V_NUMB> m_ImgContainer;
};

#endif /* GAME_WIDGETS_GRIDPOINT_HPP_ */
