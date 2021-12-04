/*
 * BlinkingAnimation.hpp
 *
 *  Created on: Nov 23, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_BLINKINGANIMATION_HPP_
#define GAME_WIDGETS_BLINKINGANIMATION_HPP_

#include <cassert>
#include <cmath>

#include "gr_engine/timer/Timer2Client.hpp"
#include "utils/geometry/Geometry.hpp"

template <class T>
class BlinkingAnimation : public T {
public:
	bool initBlinkingAnimation(double period);
	bool start();
	void stop();

private:
	static constexpr uint32_t TIMER_PERIOD = 50;	// ms
	double m_Delta = 0;
	double m_State = 0;
	Timer2Client m_RefreshTimer;

	void onTimeout(Timer2::TimerHandler_t handler);
	void updateAlpha();
};

template <class T>
bool BlinkingAnimation<T>::initBlinkingAnimation(double period) {
	assert(0 < period);
	period /= TIMER_PERIOD;
	m_Delta  = 180.0/period;
	return true;
}

template <class T>
bool BlinkingAnimation<T>::start() {
	if(m_RefreshTimer.isRunning()) {
		return false;
	}
	if(!m_RefreshTimer.start(TIMER_PERIOD, Timer2::TimerMode_t::RELOAD, [this](Timer2::TimerHandler_t handler) {
		this->onTimeout(handler);
	})) {
		return false;
	}
	if(!T::isAlphaModulationActivate()) {
		T::activateAlphaModulation();
	}
	m_State = 0;
	updateAlpha();
	return true;
}

template <class T>
void BlinkingAnimation<T>::stop() {
	m_State = 0;
	m_RefreshTimer.stop();
	T::setOpacity(FULL_OPACITY);
}

template <class T>
void BlinkingAnimation<T>::onTimeout(Timer2::TimerHandler_t handler) {
	if(m_RefreshTimer != handler) {
		return;
	}
	updateAlpha();
}

template <class T>
void BlinkingAnimation<T>::updateAlpha() {
	auto opacity = std::abs(FULL_OPACITY * Geometry::getCosDeg(m_State));
	T::setOpacity(static_cast<int32_t>(opacity));
	m_State += m_Delta;
}

#endif /* GAME_WIDGETS_BLINKINGANIMATION_HPP_ */
