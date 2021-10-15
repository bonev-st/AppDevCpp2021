/*
 * Point.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DRAWING_POINT_HPP_
#define UTILS_DRAWING_POINT_HPP_

#include <cstdint>

struct Point {
public:
	Point() = default;
	~Point() = default;

	Point(std::int32_t x, std::int32_t y);

	std::int32_t m_X = 0;
	std::int32_t m_Y = 0;

	bool operator == (const Point& other) const;

	bool operator != (const Point& other) const {
		return !operator == (other);
	}

	static const Point ZERO;
	static const Point UNDEFINED;
};

#endif /* UTILS_DRAWING_POINT_HPP_ */
