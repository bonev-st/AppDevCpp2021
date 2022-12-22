/*
 * Wheel.hpp
 *
 *  Created on: Nov 4, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_WHEEL_HPP_
#define GAME_WIDGETS_WHEEL_HPP_

#include <cstdint>
#include <functional>

#include "utils/inputs/InputEventIF.hpp"
#include "manager_utils/drawing/Image.hpp"

#include "game/widgets/RotateAnimation.hpp"

class InputEvent;
struct Point;

class Wheel : public InputEventIF {
public:
	bool init(std::size_t id, const Point &pos = Point::ZERO);
	void draw() const;
	void startAnimation(double angle, bool infinite);
	void stopAnimation();
	void attachDone(const std::function<void()> & cb);

private:
	RotateAnimation<Image> m_Img;
};

#endif /* GAME_WIDGETS_WHEEL_HPP_ */
