/*
 * Wheel.hpp
 *
 *  Created on: Nov 4, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_WHEEL_HPP_
#define GAME_WIDGETS_WHEEL_HPP_

#include <cstdint>

#include "utils/inputs/InputEventIF.hpp"
#include "manager_utils/drawing/Image.hpp"
#include "manager_utils/timer/TimerClient.hpp"

class InputEvent;
class Point;

class Wheel : public TimerClient, public InputEventIF {
public:
	bool init(std::size_t id, const Point &pos = Point::ZERO);
	void draw() const;
	void startAnimation();
	void stopAnimation();

private:
	Image m_Img;
	bool m_AnimationEna = false;
	std::size_t m_RotationTimerId = -1;

	void onTimeout(std::size_t id) final;

	void processAnimation();
};

#endif /* GAME_WIDGETS_WHEEL_HPP_ */
