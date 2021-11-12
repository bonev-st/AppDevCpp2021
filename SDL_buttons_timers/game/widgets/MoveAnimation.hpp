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
#include "utils/geometry/PointR.hpp"
#include "manager_utils/timer/Timer1Client.hpp"

template<class T>
class MoveAnimation : public T, public Timer1Client {
public:
	void initAnimation(int32_t pix_per_frame, int32_t period, bool left = false, double angle = 0);
	void setPeriod(int32_t period);
	bool setPosition(const Point & pos);
	void attachDone(const std::function<void()> &fn);
	bool isReady() const;
	void cancel();

private:
	Geometry::PointR m_CurrentPos;
	Point m_Pos;
	Timer1::Timer1Handler_t m_TimerId = Timer1::INVALID_TIMER1_HANDLER;
	int32_t m_PixFrame = 0;
	int32_t m_Period = 0;
	bool m_Left = false;
	std::function<void()> m_CB;

	void onTimeout(Timer1::Timer1Handler_t id);
	void callCB();
	void rotation(double angle);
	void nextFrame();
};

template<class T>
void MoveAnimation<T>::initAnimation(int32_t pix_per_frame, int32_t period, bool left, double angle) {
	m_PixFrame = pix_per_frame;
	m_Period = period;
	m_Left = left;
	if(m_Left) {
		T::setFlipMode(FlipMode_t::HORIZONTAL);
	}
	rotation(angle);
	m_Pos = T::getPosition();
}

template<class T>
void MoveAnimation<T>::setPeriod(int32_t period) {
	m_Period = period;
}

template<class T>
bool MoveAnimation<T>::setPosition(const Point & pos) {
	if(!isReady()) {
		return false;
	}
	auto new_posistion = Geometry::getPosToCenter(pos, T::getDimentions());
	m_CurrentPos = T::getPosition();
	const auto distance = Geometry::getDistance(m_CurrentPos, new_posistion);
	if(!distance) {
		return true;
	}
	if(!startTimer(m_TimerId, m_Period, Timer1::Timer1Mode_t::RELOAD, [this](Timer1::Timer1Handler_t id) {
		this->onTimeout(id);
	})) {
		return false;
	}
	rotation(Geometry::getAngle(T::getPosition(), new_posistion));
	m_Pos = new_posistion;
	return true;
}

template<class T>
void MoveAnimation<T>::attachDone(const std::function<void()> &fn) {
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
void MoveAnimation<T>::onTimeout(Timer1::Timer1Handler_t id) {
	if(Timer1::INVALID_TIMER1_HANDLER != id) {
		assert(id == m_TimerId);
		const auto distance = Geometry::getDistance(T::getPosition(), m_Pos);
		if(!distance) {
			cancel();
			return;
		}
		nextFrame();
		m_CurrentPos = Geometry::getPoint(m_CurrentPos, m_Pos, m_PixFrame);
		T::setPosition(m_CurrentPos);
	}
}

template<class T>
void MoveAnimation<T>::callCB() {
	if(m_CB) {
		m_CB();
	}
}

template<class T>
void MoveAnimation<T>::rotation(double angle) {
	if(90 < angle) {
		T::setFlipMode(m_Left?FlipMode_t::NONE:FlipMode_t::HORIZONTAL);
		angle -= 180;
	} else if(-90 > angle) {
		T::setFlipMode(m_Left?FlipMode_t::NONE:FlipMode_t::HORIZONTAL);
		angle += 180;
	} else {
		T::setFlipMode(m_Left?FlipMode_t::HORIZONTAL:FlipMode_t::NONE);
	}
	T::setRotation(angle);
}

template<class T>
void MoveAnimation<T>::nextFrame() {
	m_Left?T::setPrevFrame():T::setNextFrame();
}

#endif /* GAME_WIDGETS_MOVEANIMATION_HPP_ */
