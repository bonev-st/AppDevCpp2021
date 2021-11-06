/*
 * Hero.cpp
 *
 *  Created on: Nov 2, 2021
 *      Author: stanimir
 */

#include "Hero.hpp"

#include "sdl_utils/InputEvent.hpp"

bool Hero::init(std::size_t id, const Point &pos) {
	return m_Img.create(id, pos);
}

void Hero::draw() const {
	m_Img.draw();
}

void Hero::HandleEvents([[maybe_unused]]const InputEvent& e) {

}
