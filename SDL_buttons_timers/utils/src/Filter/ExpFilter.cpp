/*
 * ExpFilter.cpp
 *
 *  Created on: Nov 14, 2021
 *      Author: stanimir
 */

#include "utils/Filter/ExpFilter.hpp"

#include <cassert>

ExpFilter::ExpFilter(double smoothing_factor) {
	setCoef(smoothing_factor);
}

void ExpFilter::setSmootingFactor(double smoothing_factor) {
	setCoef(smoothing_factor);
}

void ExpFilter::clear() {
	m_Value = 0;
}

double ExpFilter::operator = (double val) {
	m_Value += m_SmootingFactor * (val - m_Value);
	return m_Value;
}

ExpFilter::operator double() const {
	return m_Value;
}

void ExpFilter::setCoef(double smoothing_factor) {
	assert(0 <= smoothing_factor);
	m_SmootingFactor = 1 - smoothing_factor;
}
