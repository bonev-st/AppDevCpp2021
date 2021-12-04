/*
 * Background.hpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_BACKGROUND_HPP_
#define GAME_WIDGETS_BACKGROUND_HPP_

#include "gr_engine/drawing/Image.hpp"
#include "utils/drawing/Point.hpp"
#include "game/widgets/ScaleTexture.hpp"

class Background {
public:
	bool init(std::size_t img_id, int32_t alpha, double deep, const Dimention & visible_area, const Rectangle & motion_area, const Widget & targer);
	void draw();

private:
	const Widget * m_Target = nullptr;
	Point m_BasePoint;
	Point m_OffsetPoint;
	double m_Deep = 1.0;
	Image m_Image;
	ScaleTexture m_ScaleImage;
};

#endif /* GAME_WIDGETS_BACKGROUND_HPP_ */
