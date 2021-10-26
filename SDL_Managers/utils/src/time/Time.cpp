/*
 * Time.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "utils/time/Time.hpp"

void Time::start() {
	m_ElapsedTime = m_Now;
	m_Now = std::chrono::steady_clock::now();
}
