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
	void draw() const;
	void HandleEvents(const InputEvent& e);

private:
	Image m_Img;
};

#endif /* GAME_ENTITIES_HERO_HPP_ */
