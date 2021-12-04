/*
 * InitHelper.hpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_WIDGETS_INITHELPER_HPP_
#define GR_ENGINE_WIDGETS_INITHELPER_HPP_

#include <cstdint>
#include <string>

class Point;
class Color;

#include "gr_engine/drawing/Image.hpp"
#include "gr_engine/drawing/Text.hpp"
#include "gr_engine/drawing/Text.hpp"
#include "gr_engine/widgets/ScaleTexture.hpp"

namespace InitHelper {

struct ImageData_t {
	Image m_Image;
	ScaleTexture m_ScaleContainer;
};

struct TextData_t {
	Text m_Text;
	ScaleTexture m_ScaleContainer;
};

bool initScaledImage(ImageData_t & data, std::size_t img_id, const Color & color,
		std::uint8_t img_aplha, const Point &pos, double scale);
bool initScaledText(TextData_t & data, std::size_t font_id, const std::string & text,
		const Color & color, const Point &pos, const Color & gnd, double scale);

} /* namespace Init */

#endif /* GAME_WIDGETS_INITHELPER_HPP_ */
