/*
 * BulletAction.hpp
 *
 *  Created on: Nov 21, 2021
 *      Author: stanimir
 */

#ifndef GAME_ACTION_BULLETACTION_HPP_
#define GAME_ACTION_BULLETACTION_HPP_

#include <cstdint>
#include <cassert>
#include <cmath>

#include "utils/drawing/Point.hpp"
#include "utils/drawing/Dimention.hpp"
#include "game/action/Action.hpp"

template <class T>
class BulletAction : public T {
public:
	bool init(std::size_t img_id, const Rectangle &shooter_rec,
			double speed, Action_t dir, const Rectangle & field);
	bool tick();

private:
	Point m_StartPos;
	double m_Path = 0;
	double m_Speed = 0;
	Action_t m_Dir = Action_t::NONE;
	Rectangle m_Field;
};

template <class T>
bool BulletAction<T>::init(std::size_t img_id, const Rectangle &shooter_rec,
				double speed, Action_t dir, const Rectangle & field) {
	if(!T::create(img_id, Point::ZERO)) {
		return false;
	}
	m_Path = 0;
	m_Dir = dir;
	m_StartPos = shooter_rec.getCenter();
	const Dimention bullet_dim = T::getDimentions();
	switch(m_Dir) {
	case Action_t::FIRE_UP:
		m_StartPos.m_Y -= bullet_dim.m_H + shooter_rec.m_H/2;
		m_StartPos.m_X -= bullet_dim.m_W/2;
		break;
	case Action_t::FIRE_DOWN:
		m_StartPos.m_Y += shooter_rec.m_H/2;
		m_StartPos.m_X -= bullet_dim.m_W/2;
		break;
	case Action_t::FIRE_LEFT:
		m_StartPos.m_Y -= bullet_dim.m_W/2;
		m_StartPos.m_X -= bullet_dim.m_H + shooter_rec.m_W/2;
		T::setRotation(90);
		break;
	case Action_t::FIRE_RIGHT:
		m_StartPos.m_Y -= bullet_dim.m_W/2;
		m_StartPos.m_X += bullet_dim.m_H/2 + shooter_rec.m_W/2;
		T::setRotation(90);
		break;
	default:
		return false;
	}
	m_Field = field;
	m_Speed = speed;
	T::setPosition(m_StartPos);
	return true;
}

template <class T>
bool BulletAction<T>::tick() {
	m_Path += m_Speed;
	const auto delta = static_cast<int32_t>(std::round(m_Path));
	Point pos = m_StartPos;
	switch(m_Dir) {
	case Action_t::FIRE_UP:
		pos.m_Y -= delta;
		break;
	case Action_t::FIRE_DOWN:
		pos.m_Y += delta;
		break;
	case Action_t::FIRE_LEFT:
		pos.m_X -= delta;
		break;
	case Action_t::FIRE_RIGHT:
		pos.m_X += delta;
		break;
	default:
		assert(0);
	}
	T::setPosition(pos);
	if(!m_Field.isToched(T::getRectangle())) {
		return false;
	}
	return true;
}

#endif /* GAME_ACTION_BULLETACTION_HPP_ */
