/*
 * Rectangle.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DRAWING_RECTANGLE_HPP_
#define UTILS_DRAWING_RECTANGLE_HPP_

#include "utils/drawing/Point.hpp"

struct Rectangle {
	Rectangle()  = default;

	Rectangle(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h);
	Rectangle(Point pos, std::int32_t w, std::int32_t h);

	Point m_Pos = Point::UNDEFINED;
	std::int32_t m_W = 0;
	std::int32_t m_H = 0;

	bool operator == (const Rectangle& other) const;
	bool operator != (const Rectangle& other) const;

	bool isInside(const Point & pos) const;
	bool isInside(const Rectangle & rec) const;
	bool isToched(const Rectangle & rec) const;

	Point getCenter() const;
	Point getRigth() const;
	Point getBottom() const;
	Point getBottomRigth() const;
	void setToCenter(const Point & point);


	static const Rectangle ZERO;
	static const Rectangle UNDEFINED;
};

#endif /* UTILS_DRAWING_RECTANGLE_HPP_ */
