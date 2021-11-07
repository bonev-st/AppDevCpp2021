/*
 * Geometry.cpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */
#define _USE_MATH_DEFINES

#include "utils/geometry/Geometry.hpp"

#include <iostream>
#include <cmath>

#include "utils/drawing/Point.hpp"

double Geometry::getDistance(const Point & start, const Point & end) {
	double rc = 0;
	do {
		if(Point::UNDEFINED == start) {
			std::cerr << "Geometry::getDistance() invalid start point" << std::endl;
			break;
		}
		if(Point::UNDEFINED == end) {
			std::cerr << "Geometry::getDistance() invalid end point" << std::endl;
			break;
		}
		Point delta = end - start;
		rc = delta.m_X*delta.m_X + delta.m_Y * delta.m_Y;
		rc = std::sqrt(rc);
	} while(0);
	return rc;
}

double Geometry::getAngle(const Point & start, const Point & end) {
	double rc = 0;
	do {
		if(Point::UNDEFINED == start) {
			std::cerr << "Geometry::getDistance() invalid start point" << std::endl;
			break;
		}
		if(Point::UNDEFINED == end) {
			std::cerr << "Geometry::getDistance() invalid end point" << std::endl;
			break;
		}
		Point delta = end - start;
		rc = rad2deg(std::atan2(delta.m_Y, delta.m_X));
	} while(0);
	return rc;
}

Point Geometry::getPoint(const Point & start, const Point & end, double distance) {
	auto lenght = getDistance(start, end);
	if(distance > lenght) {
		return end;
	}
	const auto ratio = distance / lenght; ;
	const auto delta = end - start;
	const auto delta_x = delta.m_X * ratio + start.m_X;
	const auto delta_y = delta.m_Y * ratio + start.m_Y;
	return Point(static_cast<int32_t>(std::round(delta_x)),
				 static_cast<int32_t>(std::round(delta_y)));
}

double Geometry::rad2deg(double rad) {
	return rad*180.0*M_1_PI;
}

double Geometry::deg2rad(double deg) {
	return deg*M_PI/180.0;
}

