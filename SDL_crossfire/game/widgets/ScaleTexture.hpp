/*
 * TextureScale.hpp
 *
 *  Created on: Nov 25, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_SCALETEXTURE_HPP_
#define GAME_WIDGETS_SCALETEXTURE_HPP_

#include "gr_engine/drawing/RGB_Texture.hpp"
#include "gr_engine/timer/Timer2Client.hpp"
#include "utils/drawing/Color.hpp"

class ScaleTexture : public RGB_Texture {
public:
	bool init(double scale_factor, Widget * scaled, const Color & color = Colors::FULL_TRANSPARENT);
	void setPositionCenter(const Point& pos) override;
	void draw() override;
	bool isInvalidate() const override;

private:
	static constexpr uint32_t DEBUG_TIMER_PERIOD = 1000;
	double m_ScaleFactor = 1.0;
	Color m_Color;
	Widget * m_Scaled = nullptr;
	Timer2Client m_DebugTimer;

	using RGB_Texture::create;
	using RGB_Texture::setColor;

	void dim_update();
	bool createTexture();
	bool resetTimer();
	bool redraw();
};

#endif /* GAME_WIDGETS_SCALETEXTURE_HPP_ */
