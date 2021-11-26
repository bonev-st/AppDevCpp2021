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
	bool create(std::size_t image_id, const Point &pos = Point::UNDEFINED, bool center = false);
	void setFrame(std::size_t n);
	void setNextFrame();
	void setPrevFrame();
	std::size_t getFrame() const;
	std::size_t getMaxFrames() const;

private:
	std::size_t m_CurrFrame = 0;
	std::size_t m_MaxFrames = 0;

	void setFrame();
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_IMAGE_HPP_ */
