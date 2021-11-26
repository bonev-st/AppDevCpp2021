/*
 * Bullets.hpp
 *
 *  Created on: Nov 21, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_BULLETS_HPP_
#define GAME_WIDGETS_BULLETS_HPP_

#include <functional>

#include "manager_utils/drawing/Image.hpp"
#include "utils/containers/FirstFreeContainer.hpp"
#include "game/action/BulletAction.hpp"
#include "manager_utils/timer/Timer2Client.hpp"

class Bullets {
public:
	using Callback_t = std::function<void(const Point&, int8_t)>;

	bool init(std::size_t bullet_img_id, double speed, int8_t max_bullets, uint32_t reload, const Rectangle & field);
	bool event(const Action_t action, uint8_t line_of_fire, const Rectangle & shooter_rect);
	bool tick(const Action_t pending_action, uint8_t line_of_fire, const Rectangle & shooter_rect);
	int8_t getRemainingBullets() const;
	void reload(int8_t numb);
	void setCallback(const Callback_t & callback);

	void draw();

private:
	std::size_t m_ImgId = -1;
	bool m_Reloading = false;
	uint32_t m_ReloadTime = 0;
	double m_Speed = 0;
	FirstFreeContainer<BulletAction<Image>> m_Bullets;
	int8_t m_BulletsRemaining = 0;
	Rectangle m_Field;
	Callback_t m_CB;
	Timer2Client m_ReloadTimer;

	void onReloadTimer(const Timer2::TimerHandler_t & h);
};

#endif /* GAME_WIDGETS_BULLETS_HPP_ */
