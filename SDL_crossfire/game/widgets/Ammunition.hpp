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
#include "game/widgets/ScaleTexture.hpp"

class Ammunition {
public:
	bool init(std::size_t image_id, double scale_factor);
	bool show(const Point &pos);
	void clear();
	void draw();
	Rectangle getRect() const;

	const Widget & getWidget() const {
		return m_ScaleImage;
	}

private:
	static constexpr double BLINKNIG_SPEED = 0.05;

	ScaleTexture m_ScaleImage;
	BlinkingAnimation<Image> m_Img;
};

#endif /* GAME_WIDGETS_AMMUNITION_HPP_ */
