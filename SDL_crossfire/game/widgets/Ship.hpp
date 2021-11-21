/*
 * Ship.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_SHIP_HPP_
#define GAME_WIDGETS_SHIP_HPP_

#include "game/widgets/AnimatedImage.hpp"
#include "game/config/Layout.hpp"
#include "game/widgets/AnimatedImage.hpp"

class Ship {
	bool init(std::size_t ship_img_id, const Layout::GridData_t& motion_data, const Point &pos);
	bool event();

private:
	AnimatedImage m_Ship;

};

#endif /* GAME_WIDGETS_SHIP_HPP_ */
