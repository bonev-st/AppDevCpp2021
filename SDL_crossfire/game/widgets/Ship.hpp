/*
 * Ship.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_SHIP_HPP_
#define GAME_WIDGETS_SHIP_HPP_

#include "game/config/Layout.hpp"
#include "manager_utils/drawing/Image.hpp"
#include "game/widgets/SpriteAnimation.hpp"
#include "game/action/ActionBuffer.hpp"
#include "game/action/UnitAction.hpp"

class Ship : public SpriteAnimation<Image> {
public:
	bool init(std::size_t ship_img_id, const Point& pos, uint32_t grid_size, double speed, const Layout::GridData_t &grid_data);
	bool event(const Action_t type);
	void tick();

private:
	ActionBuffer m_ActionBuffer;
	UnitAction m_UnitAction;
};

#endif /* GAME_WIDGETS_SHIP_HPP_ */
