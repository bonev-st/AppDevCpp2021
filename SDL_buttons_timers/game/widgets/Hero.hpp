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

class InputEvent;

class Hero : public InputEventIF {
public:
	bool init(std::size_t id, const Point &pos = Point::ZERO);
	void draw() const;
	bool handleEvent(const InputEvent& e) final;

	void setNextFrame() {
		m_Img.setNextFrame();
	}

	void setPosition(const Point& pos) {
		m_Img.setPosition(pos);
	}

	const Point& getPosition() const {
		return m_Img.getPosition();
	}

	void setFlipMode(FlipMode_t flip) {
		m_Img.setFlipMode(flip);
	}

	void setRotation(double angle) {
		m_Img.setRotation(angle);
	}

private:
	Image m_Img;
};

#endif /* GAME_ENTITIES_HERO_HPP_ */
