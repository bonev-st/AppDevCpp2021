/*
 * Rectangle.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include <cmath>
#include "utils/drawing/Rectangle.hpp"

const Rectangle Rectangle::ZERO(0, 0, 0, 0);
const Rectangle Rectangle::UNDEFINED(1000000, 1000000, 1000000, 1000000);

Rectangle::Rectangle(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h) :
	m_Pos(x,y)
,	m_W(w)
,	m_H(h)
{
}

Rectangle::Rectangle(Point pos,std::int32_t w, std::int32_t h) :
	m_Pos(pos)
,	m_W(w)
,	m_H(h)
{
}

bool Rectangle::operator == (const Rectangle& other) const {
	return (other.m_Pos == m_Pos)
		&& (other.m_W == m_W)
		&& (other.m_H == m_H)
		;
}

void Rectangle::scale(double scaling_factor) {
	m_W = static_cast<int32_t>(std::round(m_W * scaling_factor));
	m_H = static_cast<int32_t>(std::round(m_H * scaling_factor));
}

