/*
 * Ship.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_SHIP_HPP_
#define GAME_WIDGETS_SHIP_HPP_

#include "gr_engine/drawing/Image.hpp"
#include "gr_engine/widgets/SpriteAnimation.hpp"
#include "gr_engine/widgets/ScaleTexture.hpp"
#include "game/config/Layout.hpp"
#include "game/action/ActionBuffer.hpp"
#include "game/action/UnitAction.hpp"
#include "game/gameplay/BulletsCtrl.hpp"

class Ship : public ScaleTexture {
public:
	bool init(std::size_t ship_img_id, double scale_factor, const Point& pos, uint32_t grid_size);
	bool init_bullet(std::size_t bullet_img_id, double scale_factor, const Rectangle & field);
	bool event(const Action_t type);
	void tick();
	void draw() override;
	void setCallback(const BulletsCtrl::Callback_t & callback);
	void reload(int32_t bullets);
	void reloadTime(uint32_t dly);

	void destroy();
	bool isDestroy() const;
	void reset();
	void setShipSpeed(double speed);
	void setBulletsSpeed(double speed);
	std::vector<Widget *> getBullets();
	std::vector<Widget *> get();
	Point getCrossPoint() const;
	Point getNextPoint() const;
	uint8_t getLineOfFire() const;

private:
	ActionBuffer m_ActionBuffer;
	UnitAction m_UnitAction;
	SpriteAnimation<Image> m_Image;
	BulletsCtrl m_BulletsCtrl;

	using ScaleTexture::init;
};

#endif /* GAME_WIDGETS_SHIP_HPP_ */
