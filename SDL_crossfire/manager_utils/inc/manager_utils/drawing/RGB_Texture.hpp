/*
 * RGB_Texture.hpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_RGB_TEXTURE_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_RGB_TEXTURE_HPP_

#include <set>

#include "manager_utils/drawing/Widget.hpp"

class Color;

class RGB_Texture : public Widget {
public:
	bool create(const Dimention &dim, const Color &color, const Point &pos = Point::ZERO);
	bool setColor(const Color &color);
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_RGB_TEXTURE_HPP_ */
