/*
 * PointR.hpp
 *
 *  Created on: Nov 7, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_GEOMETRY_POINTR_HPP_
#define UTILS_INC_UTILS_GEOMETRY_POINTR_HPP_

struct Point;

namespace Geometry {

struct PointR {
	double m_X = 0;
	double m_Y = 0;

	PointR() = default;
	PointR(double x, double y);
	PointR(const Point & point);
	PointR & operator = (const Point & point);

	operator Point() const;

	friend bool operator == (const PointR & ls, const PointR & rs);

	friend PointR operator - (const PointR & ls, const PointR & rs);
};

}

#endif /* UTILS_INC_UTILS_GEOMETRY_POINTR_HPP_ */
