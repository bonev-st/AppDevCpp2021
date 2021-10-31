/*
 * Image.hpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_IMAGE_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_IMAGE_HPP_

#include "manager_utils/drawing/Widget.hpp"

class Image : public Widget {
public:
	bool create(int32_t image_id, const Point &pos = Point::ZERO);

};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_IMAGE_HPP_ */
