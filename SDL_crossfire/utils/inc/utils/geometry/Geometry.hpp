/*
 * Geometry.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_GEOMETRY_GEOMETRY_HPP_
#define UTILS_INC_UTILS_GEOMETRY_GEOMETRY_HPP_

#include <cstdint>

class Point;
class Dimention;

namespace Geometry {

//Point getPosToCenter(const Point & pos, const Dimention & dimention);
//Point getPosFromCenter(const Point & pos, const Dimention & dimention);

double getDistance(const Point & start, const Point & end);
double getAngle(const Point & start, const Point & end);
Point getPoint(const Point &start, const Point & end, double distance);
double rad2deg(double rad);
double deg2rad(double deg);
Point toPoint(double x, double y);
double getSinDeg(double x);
double getCosDeg(double x);
Point getRotation180(const Point &pos, const Point &center);
int32_t scaleVal(int32_t val, double scale);
Point scalePoint(const Point & point, double scale);

}

#endif /* UTILS_INC_UTILS_GEOMETRY_GEOMETRY_HPP_ */
