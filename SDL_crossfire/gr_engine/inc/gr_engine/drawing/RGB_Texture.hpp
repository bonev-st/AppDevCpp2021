/*
 * RGB_Texture.hpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_DRAWING_RGB_TEXTURE_HPP_
#define GR_ENGINE_INC_GR_ENGINE_DRAWING_RGB_TEXTURE_HPP_

#include <memory>

#include "gr_engine/drawing/Widget.hpp"

struct Color;
struct SDL_Texture;

class RGB_Texture : public Widget {
public:
	bool create(const Dimention &dim, const Color &color, const Point &pos = Points::UNDEFINED);
	bool setColor(const Color &color);
	std::shared_ptr<SDL_Texture> getLock();
};

#endif /* GR_ENGINE_INC_GR_ENGINE_DRAWING_RGB_TEXTURE_HPP_ */
