/*
 * Bullets.hpp
 *
 *  Created on: Nov 21, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_BULLETS_HPP_
#define GAME_WIDGETS_BULLETS_HPP_

#include <memory>

#include "manager_utils/drawing/Image.hpp"
#include "utils/containers/FirstFreeContainer.hpp"
#include "game/action/BulletAction.hpp"
#include "game/widgets/ScaleTexture.hpp"

class Bullets {
public:
	bool init(std::size_t bullet_img_id, double scale, double speed, const Rectangle & field);
	bool shoot(const Action_t action, const Rectangle & shooter_rect);
	bool event(const Action_t action, uint8_t line_of_fire, const Rectangle & shooter_rect);
	bool tick();

	void draw();

private:
	struct Bullet_t {
		Image m_Image;
		BulletAction<ScaleTexture> m_Scaled;
	};

	std::size_t m_ImgId = -1;
	double m_Speed = 0;
	double m_Scale = 0;
	FirstFreeContainer<std::shared_ptr<Bullet_t>> m_BulletsContainer;
	Rectangle m_Field;
};

#endif /* GAME_WIDGETS_BULLETS_HPP_ */
