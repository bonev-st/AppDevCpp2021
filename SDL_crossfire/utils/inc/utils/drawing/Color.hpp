/*
 * Color.hpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DRAWING_COLOR_HPP_
#define UTILS_DRAWING_COLOR_HPP_

#include <cstdint>

struct RGBA {
	uint8_t r { 0 };
	uint8_t g { 0 };
	uint8_t b { 0 };
	uint8_t a { 255 };
};

struct Color {
	Color(const uint8_t red,  const uint8_t green,
		  const uint8_t blue, const uint8_t alpha = 255);
	Color();

	bool operator == (const Color& other) const;
	bool operator != (const Color& other) const;

	RGBA m_RGBA;

	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color BLACK;
	static const Color WHITE;
	static const Color GRAY;
	static const Color CYAN;
	static const Color MAGENTA;
	static const Color YELLOW;
	static const Color ORANGE;
	static const Color PURPLE;
	static const Color FULL_TRANSPARENT;
	static const Color DEBUG_BACKGROUND;
};

#endif /* UTILS_DRAWING_COLOR_HPP_ */
