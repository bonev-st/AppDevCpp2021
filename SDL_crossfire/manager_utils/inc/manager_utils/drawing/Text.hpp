/*
 * Text.hpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_TEXT_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_TEXT_HPP_

#include <string>

#include "utils/drawing/Color.hpp"
#include "manager_utils/drawing/Widget.hpp"

class Text : public Widget {
public:
	bool create(const std::string &text, const Color &color, std::size_t font_id, const Point &pos = Point::UNDEFINED);
	bool setText(const std::string &text, const Point &pos = Point::UNDEFINED);
	bool setColor(const Color &color);

private:
	Color m_Color = Color::BLACK;
	std::string m_Text;
	std::size_t m_FontId = -1;

	bool create(const Point &pos);
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_TEXT_HPP_ */
