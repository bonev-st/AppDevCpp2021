/*
 * Point.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "utils/drawing/Point.hpp"

const Point Points::ZERO = Point(0, 0);
const Point Points::UNDEFINED  = Point(Point::UNDEF_VAL, Point::UNDEF_VAL);

bool Point::operator == (const Point& other) const {
	return (other.m_X == m_X) && (other.m_Y == m_Y);
}

bool Point::operator != (const Point& other) const {
	return !operator == (other);
}

Point Point::operator - (const Point& other) const {
	return Point(m_X - other.m_X, m_Y - other.m_Y);
}

Point Point::operator + (const Point& other) const {
	return Point(m_X + other.m_X, m_Y + other.m_Y);
}

Point &Point::operator += (const Point& other) {
	m_X += other.m_X;
	m_Y += other.m_Y;
	return *this;
}

Point & Point::move(int32_t x, int32_t y) {
	m_X += x;
	m_Y += y;
	return *this;
}
