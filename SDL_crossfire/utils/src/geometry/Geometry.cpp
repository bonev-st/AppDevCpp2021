/*
 * Geometry.cpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */
#define _USE_MATH_DEFINES

#include "utils/geometry/Geometry.hpp"

#include <cmath>

#include "utils/drawing/Point.hpp"
#include "utils/drawing/Dimention.hpp"

namespace Geometry {

#if 0
Point getPosToCenter(const Point & pos, const Dimention & dimention) {
	Point rc = pos;
	rc.m_X -= dimention.m_H/2;
	rc.m_Y -= dimention.m_H/2;
	return rc;
}

Point getPosFromCenter(const Point & pos, const Dimention & dimention) {
	Point rc = pos;
	rc.m_X += dimention.m_H/2;
	rc.m_Y += dimention.m_H/2;
	return rc;
}
#endif
double getDistance(const Point &start, const Point &end) {
	auto delta = end - start;
	double rc = delta.m_X*delta.m_X + delta.m_Y * delta.m_Y;
	rc = std::sqrt(rc);
	return rc;
}

double getAngle(const Point & start, const Point & end) {
	auto delta = end - start;
	return rad2deg(std::atan2(delta.m_Y, delta.m_X));
}

Point getPoint(const Point & start, const Point & end, double distance) {
	auto lenght = getDistance(start, end);
	if(distance > lenght) {
		return Point(end);
	}
	const auto ratio = distance / lenght; ;
	const auto delta = end - start;
	const double delta_x = delta.m_X * ratio + start.m_X;
	const double delta_y = delta.m_Y * ratio + start.m_Y;
	return toPoint(delta_x, delta_y);
}

double rad2deg(double rad) {
	return rad*180.0*M_1_PI;
}

double deg2rad(double deg) {
	return deg*M_PI/180.0;
}

Point toPoint(double x, double y) {
	return {static_cast<int32_t>(std::round(x)), static_cast<int32_t>(std::round(y))};
}

double getSinDeg(double x) {
	return std::sin(rad2deg(x));
}

double getCosDeg(double x) {
	return std::cos(rad2deg(x));
}

Point getRotation180(const Point &pos, const Point &center) {
	const Point dist = pos - center;
	Point rc {-dist.m_X, -dist.m_Y};
	return rc + center;
}

}

