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
#include "utils/geometry/Geometry.hpp"
#include "manager_utils/timer/Timer2Client.hpp"

template <class T>
class BlinkingAnimation : public T {
public:
	bool initBlinkingAnimation(double speed);
	bool start();
	void stop();

private:
	static constexpr uint32_t TIMER_PERIOD = 50;	// ms
	double m_Speed = 0;
	double m_State = 0;
	Timer2Client m_RefreshTimer;

	void onTimeout(Timer2::TimerHandler_t handler);
	void updateAlpha();
};

template <class T>
bool BlinkingAnimation<T>::initBlinkingAnimation(double speed) {
	assert(0 < speed);
	m_Speed  = speed;
	return true;
}

template <class T>
bool BlinkingAnimation<T>::start() {
	if(m_RefreshTimer.isRunning()) {
		return false;
	}
	T::activateAlphaModulation();
	m_State = 0;
	updateAlpha();
	if(!m_RefreshTimer.start(TIMER_PERIOD, Timer2::TimerMode_t::RELOAD, [this](Timer2::TimerHandler_t handler) {
		this->onMotion_Timeout(handler);
	})) {
		return false;
	}
	return true;
}

template <class T>
void BlinkingAnimation<T>::stop() {
	m_RefreshTimer.stop();
	m_State = 0;
	updateAlpha();
}

template <class T>
void BlinkingAnimation<T>::onTimeout([[maybe_unused]]Timer2::TimerHandler_t handler) {
	assert(m_RefreshTimer == handler);
	updateAlpha();
}

template <class T>
void BlinkingAnimation<T>::updateAlpha() {
	auto opacity = std::abs(FULL_OPACITY * Geometry::getCosDeg(m_State));
	T::setOpacity(static_cast<int32_t>(opacity));
	m_State += m_Speed*90.0;
}

#endif /* GAME_WIDGETS_BLINKINGANIMATION_HPP_ */
