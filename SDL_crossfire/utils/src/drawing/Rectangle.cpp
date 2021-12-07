/*
 * Rectangle.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include <cmath>
#include "utils/drawing/Rectangle.hpp"

const Rectangle Rectangles::ZERO(0, 0, 0, 0);
const Rectangle Rectangles::UNDEFINED(Point::UNDEF_VAL, Point::UNDEF_VAL, Point::UNDEF_VAL, Point::UNDEF_VAL);

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

bool Rectangle::operator != (const Rectangle& other) const {
	return !operator == (other);
}
bool Rectangle::isInside(const Point & pos) const {
	return ( m_Pos.m_X <= pos.m_X)
		&& ( getRigth().m_X >= pos.m_X)
		&& ( m_Pos.m_Y <= pos.m_Y)
		&& (getBottom().m_Y >= pos.m_Y);
}

bool Rectangle::isInside(const Rectangle & rec) const {
	return isInside(rec.m_Pos)
		&& isInside(rec.getRigth())
		&& isInside(rec.getBottom())
		&& isInside(rec.getBottomRigth());
}

bool Rectangle::isToched(const Rectangle & rec) const {
	return isInside(rec.m_Pos)
		|| isInside(rec.getRigth())
		|| isInside(rec.getBottom())
		|| isInside(rec.getBottomRigth());
}

Point Rectangle::getCenter() const {
	return Point(m_Pos.m_X + m_W/2, m_Pos.m_Y + m_H/2);
}

Point Rectangle::getRigth() const {
	return Point(m_Pos.m_X + m_W, m_Pos.m_Y);
}

Point Rectangle::getBottom() const {
	return Point(m_Pos.m_X, m_Pos.m_Y + m_H);
}

Point Rectangle::getBottomRigth() const {
	return Point(m_Pos.m_X + m_W, m_Pos.m_Y + m_H);
}

void Rectangle::setToCenter(const Point & pos) {
	const Point point {m_W/2, m_H/2};
	m_Pos = pos - point;
}

