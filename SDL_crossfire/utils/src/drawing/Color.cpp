/*
 * Color.cpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#include "utils/drawing/Color.hpp"

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
const Color DEBUG_BACKGROUND(255, 0, 0, 150);
} //namespace Colors

const Color Color::RED(255, 0, 0, 255);
const Color Color::GREEN(0, 255, 0, 255);
const Color Color::BLUE(0, 0, 255, 255);
const Color Color::BLACK(0, 0, 0, 255);
const Color Color::WHITE(255, 255, 255, 255);
const Color Color::GRAY(192, 192, 192, 255);
const Color Color::CYAN(0, 255, 255, 255);
const Color Color::MAGENTA(255, 0, 255, 255);
const Color Color::YELLOW(255, 255, 0, 255);
const Color Color::ORANGE(255, 128, 0, 255);
const Color Color::PURPLE(128, 0, 128, 255);
const Color Color::FULL_TRANSPARENT(0, 0, 0, 0);
const Color Color::DEBUG_BACKGROUND(255, 0, 0, 150);

Color::Color() {
	*this = FULL_TRANSPARENT;
}

Color::Color(const uint8_t red,  const uint8_t green,
	  const uint8_t blue, const uint8_t alpha) {
	m_RGBA.r = red;
	m_RGBA.g = green;
	m_RGBA.b = blue;
	m_RGBA.a = alpha;
}

bool Color::operator == (const Color& other) const {
	return (other.m_RGBA.a == m_RGBA.a)
		&& (other.m_RGBA.b == m_RGBA.b)
		&& (other.m_RGBA.g == m_RGBA.g)
		&& (other.m_RGBA.r == m_RGBA.r);
}

bool Color::operator != (const Color& other) const  {
	return !operator==(other);
}
