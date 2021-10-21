/*
 * Color.cpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#include "Color.hpp"

namespace Colors {
const Color RED(255, 0, 0, 255);
const Color GREEN(0, 255, 0, 255);
const Color BLUE(0, 0, 255, 255);
const Color BLACK(0, 0, 0, 255);
const Color WHITE(255, 255, 255, 255);
const Color GRAY(192, 192, 192, 255);
const Color CYAN(0, 255, 255, 255);
const Color MAGENTA(255, 0, 255, 255);
const Color YELLOW(255, 255, 0, 255);
const Color ORANGE(255, 128, 0, 255);
const Color PURPLE(128, 0, 128, 255);
const Color FULL_TRANSPARENT(0, 0, 0, 0);
} //namespace Colors

Color::Color(const uint8_t red,  const uint8_t green,
	  const uint8_t blue, const uint8_t alpha) {
	m_RGBA.r = red;
	m_RGBA.g = green;
	m_RGBA.b = blue;
	m_RGBA.a = alpha;
}
