/*
 * Point.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DRAWING_POINT_HPP_
#define UTILS_DRAWING_POINT_HPP_

#include <cstdint>

struct Point;

struct Points {
	static const Point ZERO;
	static const Point UNDEFINED;
};

struct Point {
	Point() = default;

	constexpr Point(std::int32_t x, std::int32_t y) : m_X(x), m_Y(y) {
	}

	std::int32_t m_X = UNDEF_VAL;
	std::int32_t m_Y = UNDEF_VAL;

	bool operator == (const Point& other) const;
	bool operator != (const Point& other) const;

	Point operator - (const Point& other) const;
	Point operator + (const Point& other) const;
	Point &operator += (const Point& other);

	Point & move (int32_t x, int32_t y);

	static constexpr int32_t UNDEF_VAL = 1000000;
};

#endif /* UTILS_DRAWING_POINT_HPP_ */
