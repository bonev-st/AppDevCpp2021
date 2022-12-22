/*
 * Point.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "utils/drawing/Point.hpp"

const Point Point::ZERO = Point(0, 0);
const Point Point::UNDEFINED  = Point(1000000, 1000000);

Point::Point(std::int32_t x, std::int32_t y) :
	m_X(x)
,	m_Y(y)
{
}

bool Point::operator == (const Point& other) const {
	return (other.m_X == m_X) && (other.m_Y == m_Y);
}

Point Point::operator - (const Point& other) const {
	return Point(m_X - other.m_X, m_Y - other.m_Y);
}
