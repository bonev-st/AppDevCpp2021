/*
 * MoveAnimation.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_MOVEANIMATION_HPP_
#define GAME_WIDGETS_MOVEANIMATION_HPP_

#include <cassert>
#include <functional>

#include "utils/drawing/Point.hpp"
#include "utils/geometry/Geometry.hpp"
#include "manager_utils/timer/TimerClient.hpp"

template<class T>
class MoveAnimation : public T, public TimerClient {
public:
	void initAnimation(int32_t pix_per_frame, int64_t period, bool left = false, double angle = 0);
	void setSpeed(int32_t pix_per_step);
	bool setPosition(const Point & pos);
	void attachDone(std::function<void> *fn);
	bool isReady() const;
	void cancel();

private:
	Point m_Pos =  Point::UNDEFINED;
	std::size_t m_TimerId = -1;
	int32_t m_PixFrame = 0;
	int32_t m_PixStep = 0;
	int64_t m_Period = 0;
	int32_t m_Disance = 0;
	bool m_Left = false;
	std::function<void()> * m_CB = nullptr;

	void onTimeout(std::size_t id);
	void callCB();
};

template<class T>
void MoveAnimation<T>::initAnimation(int32_t pix_per_frame, int64_t period, bool left, double angle) {
	m_PixFrame = pix_per_frame;
	m_Period = period;
	m_Left = left;
	if(m_Left) {
		T::setFlipMode(FlipMode_t::HORIZONTAL);
	}
	T::setRotation(angle);
	m_Pos = T::getPosition();
}

template<class T>
void MoveAnimation<T>::setSpeed(int32_t pix_per_step) {
	m_PixStep = pix_per_step;
}

template<class T>
bool MoveAnimation<T>::setPosition(const Point & pos) {
	if(!isReady()) {
		return false;
	}
	const auto distance = Geometry::getDistance(T::getPosition(), pos);
	if(!distance) {
		return true;
	}
	if(!startTimer(m_TimerId, m_Period, TimerType_t::RELOAD)) {
		return false;
	}
	m_Disance = 0;
	auto angle = Geometry::getAngle(T::getPosition(), pos);
	if(90 < angle) {
		T::setFlipMode(m_Left?FlipMode_t::NONE:FlipMode_t::HORIZONTAL);
		angle -= 180;
	} else if(-90 > angle) {
		T::setFlipMode(m_Left?FlipMode_t::NONE:FlipMode_t::HORIZONTAL);
		angle += 180;
	}
	T::setRotation(angle);
	T::setNextFrame();
	m_Pos = pos;
	return true;
}

template<class T>
void MoveAnimation<T>::attachDone(std::function<void> *fn) {
	m_CB = fn;
}

template<class T>
bool MoveAnimation<T>::isReady() const {
	return !isActiveTimerId(m_TimerId);
}

template<class T>
void MoveAnimation<T>::cancel() {
	if(!isReady()) {
		stopTimer(m_TimerId);
		callCB();
	}
}

template<class T>
void MoveAnimation<T>::onTimeout(std::size_t id) {
	assert(id == m_TimerId);
	m_Disance += m_PixStep;
	if(m_PixFrame < m_Disance) {
		m_Disance -= m_PixFrame;
		T::setNextFrame();
	}
	const auto distance = Geometry::getDistance(T::getPosition(), m_Pos);
	if(!distance) {
		cancel();
		return;
	}
	T::setPosition(Geometry::getPoint(T::getPosition(), m_Pos, m_PixStep));
}

template<class T>
void MoveAnimation<T>::callCB() {
	if(m_CB) {
		(*m_CB)();
	}
}



#endif /* GAME_WIDGETS_MOVEANIMATION_HPP_ */
