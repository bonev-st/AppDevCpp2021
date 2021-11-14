/*
 * FPS.cpp
 *
 *  Created on: Nov 14, 2021
 *      Author: stanimir
 */

#include "game/widgets/FPS.hpp"

const double FPS::SmoothingFactor = 0.9;

void FPS::init() {
	m_Filter.setSmootingFactor(SmoothingFactor);
}

void FPS::newFrame() {
	m_Period.start();
	double elapsed = static_cast<double>(m_Period.toTime<Time::Microseconds_t>());
	m_Filter = 1E6/elapsed;
}

FPS::operator double() const {
	return m_Filter;
}
