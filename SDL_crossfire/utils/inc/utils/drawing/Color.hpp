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

struct Color;

namespace Colors {
extern const Color RED;
extern const Color GREEN;
extern const Color BLUE;
extern const Color BLACK;
extern const Color WHITE;
extern const Color GRAY;
extern const Color CYAN;
extern const Color MAGENTA;
extern const Color YELLOW;
extern const Color ORANGE;
extern const Color PURPLE;
extern const Color FULL_TRANSPARENT;
}

struct Color {
	Color(const uint8_t red,  const uint8_t green,
		  const uint8_t blue, const uint8_t alpha = 255);
	Color() {
		*this = Colors::FULL_TRANSPARENT;
	}

	bool operator == (const Color& other) const;
	bool operator != (const Color& other) const;

	RGBA m_RGBA;
};

#endif /* UTILS_DRAWING_COLOR_HPP_ */
