/*
 * Hero.hpp
 *
 *  Created on: Nov 2, 2021
 *      Author: stanimir
 */

#ifndef GAME_ENTITIES_HERO_HPP_
#define GAME_ENTITIES_HERO_HPP_

#include "manager_utils/drawing/Image.hpp"

class InputEvent;

class Hero {
public:
	bool init(std::size_t id, const Point &pos = Point::ZERO);
	void draw();
	void HandleEvents(const InputEvent& e);
	void run(bool forward) {
		if(forward) {
			m_Img.setFlipMode(FlipMode_t::HORIZONTAL);
			m_Img.setNextFrame();
		} else {
			m_Img.setFlipMode(FlipMode_t::NONE);
			m_Img.setPrevFrame();
		}
	}
private:
	Image m_Img;
};

#endif /* GAME_ENTITIES_HERO_HPP_ */
