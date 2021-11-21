/*
 * PointR.cpp
 *
 *  Created on: Nov 7, 2021
 *      Author: stanimir
 */

#include "utils/geometry/PointR.hpp"

#include <cmath>

#include "utils/drawing/Point.hpp"

namespace Geometry {
PointR::PointR(const Point & point) {
	m_X = point.m_X;
	m_Y = point.m_Y;
}

PointR & PointR::operator = (const Point & point) {
	m_X = point.m_X;
	m_Y = point.m_Y;
	return *this;
}

PointR::operator Point() const {
	return Point(static_cast<int32_t>(std::round(m_X)),
				 static_cast<int32_t>(std::round(m_Y)));
}

PointR::PointR(double x, double y) {
	m_X = x;
	m_Y = y;
}

bool operator == (const PointR & ls, const PointR & rs) {
	return (ls.m_X == rs.m_X) && (ls.m_Y == rs.m_Y) ;
}

PointR operator - (const PointR & ls, const PointR & rs) {
	return PointR(ls.m_X - rs.m_X , ls.m_Y - rs.m_Y);
}

}
