/*
 * FPS.cpp
 *
 *  Created on: Nov 14, 2021
 *      Author: stanimir
 */

#include "game/widgets/FPS.hpp"

void FPS::init() {
	m_Filter.setSmootingFactor(SMOOTHING_FACTOR);
}

void FPS::newFrame() {
	m_Period.start();
	double elapsed = static_cast<double>(m_Period.toTime<Time::Microseconds_t>());
	m_Filter = 1E6/elapsed;
}

FPS::operator double() const {
	return m_Filter;
}
