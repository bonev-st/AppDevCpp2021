/*
 * SpriteAnimation.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_SPRITEANIMATION_HPP_
#define GAME_WIDGETS_SPRITEANIMATION_HPP_

#include <cassert>

#include "manager_utils/timer/Timer2Client.hpp"

enum class SpriteMode_t {
	FORWARD, BACKWARD,
};

template<class T>
class SpriteAnimation : public T {
public:
	bool init(uint32_t period, SpriteMode_t dir);
	SpriteMode_t setMode(SpriteMode_t dir);
	int32_t setPeriod(uint32_t period);

private:
	SpriteMode_t m_Mode = SpriteMode_t::FORWARD;
	Timer2Client m_Timer;

	void onTimeout(const Timer2::TimerHandler_t & handler);
};

template<class T>
bool SpriteAnimation<T>::init(uint32_t period, SpriteMode_t mode) {
	setMode(mode);
	if(!m_Timer.start(period, Timer2::TimerMode_t::RELOAD, [this](Timer2::TimerHandler_t id) {
		this->onTimeout(id);
	})) {
		return false;
	}
	return false;
}

template<class T>
SpriteMode_t SpriteAnimation<T>::setMode(SpriteMode_t mode) {
	m_Mode = mode;
	return mode;
}

template<class T>
int32_t SpriteAnimation<T>::setPeriod(uint32_t period) {
	return m_Timer.changePeriod(period);
}

template<class T>
void SpriteAnimation<T>::onTimeout(const Timer2::TimerHandler_t & handler) {
	assert(m_Timer == handler);
	SpriteMode_t::FORWARD == m_Mode ? T::setNextFrame() : T::setPrevFrame();
}

#endif /* GAME_WIDGETS_SPRITEANIMATION_HPP_ */
