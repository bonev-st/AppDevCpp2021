/*
 * Ammunition.hpp
 *
 *  Created on: Nov 22, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_AMMUNITION_HPP_
#define GAME_WIDGETS_AMMUNITION_HPP_

#include <functional>

#include "manager_utils/drawing/Image.hpp"

#include "game/widgets/BlinkingAnimation.hpp"

class Ammunition {
public:
	bool init(std::size_t image_id);
	bool show(const Point &pos);
	void clear();
	void draw() const;
	Rectangle getRect() const;

	const Widget & getWidget() const {
		return m_Img;
	}

private:
	BlinkingAnimation<Image> m_Img;
	static const double BLINKNIG_SPEED;
};

#endif /* GAME_WIDGETS_AMMUNITION_HPP_ */
