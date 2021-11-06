/*
 * Wheel.hpp
 *
 *  Created on: Nov 4, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_WHEEL_HPP_
#define GAME_WIDGETS_WHEEL_HPP_

#include <cstdint>

#include "manager_utils/drawing/Image.hpp"

class InputEvent;
class Point;

class Wheel {
public:
	bool init(std::size_t id, const Point &pos = Point::ZERO);
	void draw() const;
	void startAnimation();
	void stopAnimation();

	void process();

private:
	Image m_Img;
	bool m_AnimationEna = false;
};

#endif /* GAME_WIDGETS_WHEEL_HPP_ */
