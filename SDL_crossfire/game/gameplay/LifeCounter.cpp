/*
 * LifeCounter.cpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#include "game/gameplay/LifeCounter.hpp"

#include "game/config/Rules.hpp"

void LifeCounter::reset() {
	m_Value = Rules::INITIAL_LIFES;
	m_PointsNewLife = Rules::POINTS_FOR_NEW_LIFE;
}

void LifeCounter::points(std::uint32_t val) {
	if(m_PointsNewLife <= val) {
		m_PointsNewLife += Rules::POINTS_FOR_NEW_LIFE;
		++m_Value;
	}
}

LifeCounter::operator std::uint32_t () const {
	return m_Value;
}

std::uint32_t LifeCounter::get() {
	if(m_Value) {
		--m_Value;
	}
	return m_Value;
}

void LifeCounter::attach(const Variable<std::uint32_t>::Callback_t &cb) {
	m_Value.attach(cb);
}
