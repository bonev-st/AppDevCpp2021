/*
 * Text.hpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_DRAWING_TEXT_HPP_
#define GR_ENGINE_INC_GR_ENGINE_DRAWING_TEXT_HPP_

#include <string>

#include "gr_engine/drawing/Widget.hpp"
#include "utils/drawing/Color.hpp"

class Text : public Widget {
public:
	bool create(const std::string &text, const Color &color, std::size_t font_id, const Point &pos = Points::UNDEFINED);
	bool setText(const std::string &text, const Point &pos = Points::UNDEFINED);
	bool setColor(const Color &color);

private:
	Color m_Color = Colors::BLACK;
	std::string m_Text;
	std::size_t m_FontId = -1;

	bool create(const Point &pos);
};

#endif /* GR_ENGINE_INC_GR_ENGINE_DRAWING_TEXT_HPP_ */
