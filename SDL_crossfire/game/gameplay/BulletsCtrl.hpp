/*
 * BulletsCtrl.hpp
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_BULLETSCTRL_HPP_
#define GAME_GAMEPLAY_BULLETSCTRL_HPP_

#include <cstdint>
#include <functional>

#include "manager_utils/timer/Timer2Client.hpp"
#include "game/widgets/Bullets.hpp"

class Point;
class Rectangle;
enum class Action_t : uint8_t;

class BulletsCtrl {
public:
	using Callback_t = std::function<void(const Point&, int8_t)>;

	bool init(int8_t max_bullets, uint32_t reload);
	bool initDraw(std::size_t bullet_img_id, double scale, const Rectangle & field);
	void setSpeed(double speed);
	int8_t getRemainingBullets() const;
	void reload(int8_t numb);
	void setCallback(const Callback_t & callback);
	bool event(const Action_t action, uint8_t line_of_fire, const Rectangle & shooter_rect);
	bool tick(const Action_t pending_action, uint8_t line_of_fire, const Rectangle & shooter_rect);
	void draw();

private:
	uint32_t m_ReloadTime = 0;
	Callback_t m_CB;
	Timer2Client m_ReloadTimer;
	int8_t m_BulletsRemaining = 0;

	Bullets m_Bullets;
};

#endif /* GAME_GAMEPLAY_BULLETSCTRL_HPP_ */
