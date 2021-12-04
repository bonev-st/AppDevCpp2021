/*
 * Ammunition.hpp
 *
 *  Created on: Nov 22, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_AMMUNITION_HPP_
#define GAME_WIDGETS_AMMUNITION_HPP_

#include <functional>

#include "gr_engine/drawing/Image.hpp"
#include "game/widgets/BlinkingAnimation.hpp"
#include "game/widgets/ScaleTexture.hpp"
#include "game/gameplay/CD_ClientIF.hpp"

class Ammunition : public CD_ClientIF, public BlinkingAnimation<ScaleTexture> {
public:
	bool init(std::size_t image_id, double scale_factor);
	bool show(const Point &pos);
	void collision() final;

private:
	static constexpr double BLINKNIG_PERIOD = 500;
	Image m_Img;
};

#endif /* GAME_WIDGETS_AMMUNITION_HPP_ */
