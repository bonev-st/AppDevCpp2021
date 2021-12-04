/*
 * Image.hpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_DRAWING_IMAGE_HPP_
#define GR_ENGINE_INC_GR_ENGINE_DRAWING_IMAGE_HPP_

#include "gr_engine/drawing/Widget.hpp"

class Image : public Widget {
public:
	bool create(std::size_t image_id, const Point &pos = Points::UNDEFINED, bool center = false);
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

#endif /* GR_ENGINE_INC_GR_ENGINE_DRAWING_IMAGE_HPP_ */
