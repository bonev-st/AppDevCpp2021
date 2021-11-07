/*
 * Geometry.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_GEOMETRY_GEOMETRY_HPP_
#define UTILS_INC_UTILS_GEOMETRY_GEOMETRY_HPP_

class Point;
class Dimention;

namespace Geometry {

class PointR;

Point getPosToCenter(const Point & pos, const Dimention & dimention);
double getDistance(PointR start, PointR end);
double getAngle(const PointR & start, const PointR & end);
PointR getPoint(const PointR & start, const PointR & end, double distance);
double rad2deg(double rad);
double deg2rad(double deg);

}

#endif /* UTILS_INC_UTILS_GEOMETRY_GEOMETRY_HPP_ */
