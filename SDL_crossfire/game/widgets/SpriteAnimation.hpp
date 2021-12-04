/*
 * SpriteAnimation.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_SPRITEANIMATION_HPP_
#define GAME_WIDGETS_SPRITEANIMATION_HPP_

#include "manager_utils/timer/Timer2Client.hpp"

enum class SpriteMode_t {
	FORWARD, BACKWARD,
};

template<class T>
class SpriteAnimation : public T {
public:
	using Callback_t = std::function<void(std::size_t, void *param)>;

	bool init(uint32_t period, SpriteMode_t dir, const Callback_t & cb = nullptr, void * param = nullptr);
	void setMode(SpriteMode_t dir);
	int32_t setPeriod(uint32_t period);
	void stop();

private:
	SpriteMode_t m_Mode = SpriteMode_t::FORWARD;
	Timer2Client m_Timer;
	void * m_Param = nullptr;
	Callback_t m_CB;

	void onTimeout(Timer2::TimerHandler_t handler);
};

template<class T>
bool SpriteAnimation<T>::init(uint32_t period, SpriteMode_t dir, const Callback_t & cb, void * param) {
	m_Mode = dir;
	if(!m_Timer.start(period, Timer2::TimerMode_t::RELOAD, [this](Timer2::TimerHandler_t id) {
		this->onTimeout(id);
	})) {
		return false;
	}
	m_Param = param;
	m_CB = cb;
	return true;
}

template<class T>
void SpriteAnimation<T>::setMode(SpriteMode_t mode) {
	m_Mode = mode;
}

template<class T>
int32_t SpriteAnimation<T>::setPeriod(uint32_t period) {
	return m_Timer.changePeriod(period);
}

template<class T>
void SpriteAnimation<T>::stop() {
	if(!m_Timer.isRunning()) {
		return;
	}
	m_Timer.stop();
}

template<class T>
void SpriteAnimation<T>::onTimeout(Timer2::TimerHandler_t handler) {
	if(m_Timer != handler) {
		return;
	}
	SpriteMode_t::FORWARD == m_Mode ? T::setNextFrame() : T::setPrevFrame();
	if(m_CB) {
		m_CB(T::getFrame(), m_Param);
	}
}

#endif /* GAME_WIDGETS_SPRITEANIMATION_HPP_ */
