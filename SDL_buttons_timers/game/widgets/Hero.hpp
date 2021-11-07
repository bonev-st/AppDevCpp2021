/*
 * Hero.hpp
 *
 *  Created on: Nov 2, 2021
 *      Author: stanimir
 */

#ifndef GAME_ENTITIES_HERO_HPP_
#define GAME_ENTITIES_HERO_HPP_

#include "utils/inputs/InputEventIF.hpp"
#include "manager_utils/drawing/Image.hpp"

#include "game/widgets/MoveAnimation.hpp"

class InputEvent;

class Hero : public InputEventIF {
public:
	bool init(std::size_t id, const Point &pos = Point::ZERO);
	void draw() const;
	bool handleEvent(const InputEvent& e) final;

private:
	MoveAnimation<Image> m_Img;
};

#endif /* GAME_ENTITIES_HERO_HPP_ */
