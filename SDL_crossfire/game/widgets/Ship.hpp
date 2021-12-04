/*
 * Ship.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_SHIP_HPP_
#define GAME_WIDGETS_SHIP_HPP_

#include "gr_engine/drawing/Image.hpp"
#include "game/config/Layout.hpp"
#include "game/widgets/SpriteAnimation.hpp"
#include "game/widgets/ScaleTexture.hpp"
#include "game/action/ActionBuffer.hpp"
#include "game/action/UnitAction.hpp"
#include "game/gameplay/BulletsCtrl.hpp"

class Ship : public ScaleTexture {
public:
	bool init(std::size_t ship_img_id, double scale_factor, const Point& pos, uint32_t grid_size);
	bool init_bullet(std::size_t bullet_img_id, double scale_factor, int8_t max_bullets, uint32_t reload_time, const Rectangle & field);
	bool event(const Action_t type);
	void tick();
	void draw() override;
	void setCallback(const BulletsCtrl::Callback_t & callback);
	void reload(int8_t bullets);
	void destroy();
	bool isDestroy() const;
	void reset();
	void setShipSpeed(double speed);
	void setBulletsSpeed(double speed);
	std::vector<Widget *> getBullets();

private:
	ActionBuffer m_ActionBuffer;
	UnitAction m_UnitAction;
	SpriteAnimation<Image> m_Image;
	BulletsCtrl m_BulletsCtrl;

	using ScaleTexture::init;
};

#endif /* GAME_WIDGETS_SHIP_HPP_ */
