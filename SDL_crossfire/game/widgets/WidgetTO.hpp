/*
 * WidgetTO.hpp
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_WIDGETTO_HPP_
#define GAME_WIDGETS_WIDGETTO_HPP_

#include <cassert>
#include "manager_utils/timer/Timer2Client.hpp"

template <class T>
class WidgetTO : public T {
public:
	bool initTO(uint32_t period, const std::function<void(const T *)> & cb);
	bool start();
	void stop();

private:
	uint32_t m_Period = 0;
	Timer2Client m_TO_Timer;
	std::function<void(const T *)> m_CB;

	void onTimeout(Timer2::TimerHandler_t handler);
};

template <class T>
bool WidgetTO<T>::initTO(uint32_t period, const std::function<void(const T *)> & cb) {
	assert(0 < period);
	m_Period = period;
	m_CB = cb;
	T::setVisible(false);
	return true;
}

template <class T>
bool WidgetTO<T>::start() {
	assert(m_Period && "WidgetTO not initialized");
	if(m_TO_Timer.isRunning()) {
		return false;
	}
	if(!m_TO_Timer.start(m_Period, Timer2::TimerMode_t::ONESHOT, [this](Timer2::TimerHandler_t handler) {
		this->onTimeout(handler);
	})) {
		return false;
	}
	T::setVisible(true);
	return true;
}

template <class T>
void WidgetTO<T>::stop() {
	m_TO_Timer.stop();
	T::setVisible(false);
}

template <class T>
void WidgetTO<T>::onTimeout(Timer2::TimerHandler_t handler) {
	if(m_TO_Timer != handler) {
		return;
	}
	T::setVisible(false);
	if(m_CB) {
		m_CB(this);
	}
}

#endif /* GAME_WIDGETS_WIDGEDTO_HPP_ */
