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

#include "utils/geometry/PointR.hpp"

namespace Geometry {

Point getPosToCenter(const Point & pos, const Dimention & dimention) {
	Point rc = pos;
	rc.m_X -= dimention.m_H/2;
	rc.m_Y -= dimention.m_H/2;
	return rc;
}

double getDistance(PointR start, PointR end) {
	auto delta = end - start;
	auto rc = delta.m_X*delta.m_X + delta.m_Y * delta.m_Y;
	rc = std::sqrt(rc);
	return rc;
}

double getAngle(const PointR &  start, const PointR & end) {
	auto delta = end - start;
	return rad2deg(std::atan2(delta.m_Y, delta.m_X));
}

PointR getPoint(const PointR & start, const PointR & end, double distance) {
	auto lenght = getDistance(start, end);
	if(distance > lenght) {
		return PointR(end);
	}
	const auto ratio = distance / lenght; ;
	const auto delta = end - start;
	const double delta_x = delta.m_X * ratio + start.m_X;
	const double delta_y = delta.m_Y * ratio + start.m_Y;
	return PointR(delta_x, delta_y);
}

double rad2deg(double rad) {
	return rad*180.0*M_1_PI;
}

double deg2rad(double deg) {
	return deg*M_PI/180.0;
}

}

