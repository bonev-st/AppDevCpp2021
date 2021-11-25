/*
 * Ship.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_SHIP_HPP_
#define GAME_WIDGETS_SHIP_HPP_

#include "manager_utils/drawing/Image.hpp"
#include "game/config/Layout.hpp"
#include "game/widgets/SpriteAnimation.hpp"
#include "game/widgets/Bullets.hpp"
#include "game/action/ActionBuffer.hpp"
#include "game/action/UnitAction.hpp"

class Ship : public SpriteAnimation<Image> {
public:
	bool init(std::size_t ship_img_id, const Point& pos, uint32_t grid_size, double speed);
	bool init_bullet(std::size_t bullet_img_id, double speed, int8_t max_bullets, uint32_t reload_time, const Rectangle & field);
	bool event(const Action_t type);
	void tick();
	void draw() const final;
	void setCallback(const Bullets::Callback_t & callback);
	void reload(int8_t bullets);

private:
	ActionBuffer m_ActionBuffer;
	UnitAction m_UnitAction;
	Bullets m_Bullets;
};

#endif /* GAME_WIDGETS_SHIP_HPP_ */
