/*
 * Color.cpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#include "utils/drawing/Color.hpp"

const Color Colors::RED(255, 0, 0, 255);
const Color Colors::GREEN(0, 255, 0, 255);
const Color Colors::BLUE(0, 0, 255, 255);
const Color Colors::BLACK(0, 0, 0, 255);
const Color Colors::WHITE(255, 255, 255, 255);
const Color Colors::GRAY(192, 192, 192, 255);
const Color Colors::CYAN(0, 255, 255, 255);
const Color Colors::MAGENTA(255, 0, 255, 255);
const Color Colors::YELLOW(255, 255, 0, 255);
const Color Colors::ORANGE(255, 128, 0, 255);
const Color Colors::PURPLE(128, 0, 128, 255);
const Color Colors::FULL_TRANSPARENT(0, 0, 0, 0);
const Color Colors::DEBUG_BACKGROUND(255, 0, 0, 150);

Color::Color() {
	*this = Colors::FULL_TRANSPARENT;
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
