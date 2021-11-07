/*
 * RotateAnimation.hpp
 *
 *  Created on: Nov 7, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_ROTATEANIMATION_HPP_
#define GAME_WIDGETS_ROTATEANIMATION_HPP_

#include <cassert>
#include <functional>

#include "utils/drawing/Point.hpp"
#include "utils/geometry/Geometry.hpp"
#include "manager_utils/timer/TimerClient.hpp"

template<class T>
class RotateAnimation : public T, public TimerClient {
public:
	void initAnimation(double deg_per_frame, int64_t period, double angle = 0, const Point &rot_center = Point::UNDEFINED);
	void setPeriod(int64_t period);
	void setRotCenter(const Point &pos);
	bool setAngle(double angle, bool infinite = false);
	void attachDone(std::function<void()> *fn);
	bool isReady() const;
	void cancel();

private:
	bool m_Infinite = false;
	double m_Angle;
	Point m_RotCenter =  Point::UNDEFINED;
	TimerHandler_t m_TimerId = INVALID_TIMER_HANDLER;
	double m_DegFrame = 0;
	int64_t m_Period = 0;
	std::function<void()> * m_CB = nullptr;

	void onTimeout(TimerHandler_t id);
	void callCB();
};

template<class T>
void RotateAnimation<T>::initAnimation(double deg_per_frame, int64_t period, double angle, const Point &rot_center) {
	m_DegFrame = deg_per_frame;
	m_Period = period;
	m_RotCenter = rot_center;
	T::setRotation(angle);
}

template<class T>
void RotateAnimation<T>::setPeriod(int64_t period) {
	m_Period = period;
}

template<class T>
bool RotateAnimation<T>::setAngle(double angle, bool infinite) {
	if(!isReady()) {
		return false;
	}
	if(!startTimer(m_TimerId, m_Period, TimerType_t::RELOAD)) {
		return false;
	}
	m_Infinite = infinite;
	m_Angle = angle;
	return true;
}

template<class T>
void RotateAnimation<T>::attachDone(std::function<void()> *fn) {
	m_CB = fn;
}

template<class T>
bool RotateAnimation<T>::isReady() const {
	return !isActiveTimerId(m_TimerId);
}

template<class T>
void RotateAnimation<T>::cancel() {
	if(!isReady()) {
		stopTimer(m_TimerId);
		callCB();
	}
}

template<class T>
void RotateAnimation<T>::onTimeout(TimerHandler_t id) {
	if(INVALID_TIMER_HANDLER != id) {
		assert(id == m_TimerId);
		auto angle = m_DegFrame;
		if(!m_Infinite) {
			if(0 > m_Angle) {
				m_Angle += angle;
				if(0 < m_Angle) {
					angle -= m_Angle;
					m_Angle = 0;
				}
				angle = -angle;
			} else if (0 < m_Angle) {
				m_Angle -= angle;
				if(0 > m_Angle) {
					angle -= m_Angle;
					m_Angle = 0;
				}
			} else {
				cancel();
				return;
			}
		} else if(0 > m_Angle) {
			angle = -angle;
		}
		T::rotate(angle);
	}
}

template<class T>
void RotateAnimation<T>::callCB() {
	if(m_CB) {
		(*m_CB)();
	}
}

#endif /* GAME_WIDGETS_ROTATEANIMATION_HPP_ */
