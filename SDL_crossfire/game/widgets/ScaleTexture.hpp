/*
 * TextureScale.hpp
 *
 *  Created on: Nov 25, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_SCALETEXTURE_HPP_
#define GAME_WIDGETS_SCALETEXTURE_HPP_

#include "manager_utils/drawing/RGB_Texture.hpp"
#include "manager_utils/timer/Timer2Client.hpp"

class ScaleTexture : public RGB_Texture {
public:
	bool init(double scale_factor, Widget * scaled);
	void reload();
	void draw() override;

private:
	static constexpr uint32_t DEBUG_TIMER_PERIOD = 100;
	double m_ScaleFactor = 1.0;
	Widget * m_Scaled = nullptr;
	Timer2Client m_DebugTimer;
	bool m_SkipDebugTimer = false;

	using RGB_Texture::create;
	using RGB_Texture::setColor;
};

#endif /* GAME_WIDGETS_SCALETEXTURE_HPP_ */
