/*
 * Geometry.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_GEOMETRY_GEOMETRY_HPP_
#define UTILS_INC_UTILS_GEOMETRY_GEOMETRY_HPP_

class Point;

namespace Geometry {

double getDistance(const Point & start, const Point & end);
double getAngle(const Point & start, const Point & end);
Point getPoint(const Point & start, const Point & end, double distance);
double rad2deg(double rad);
double deg2rad(double deg);

}

#endif /* UTILS_INC_UTILS_GEOMETRY_GEOMETRY_HPP_ */
