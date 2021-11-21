/*
 * MoveAnimation.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_MOVEANIMATION_HPP_
#define GAME_WIDGETS_MOVEANIMATION_HPP_

#include <cassert>

enum class MoveDirection_t {
	NONE, UP_DIR, DOWN_DIR, LEFT_DIR, RIGHT_DIR,
};

template<class T>
class MoveAnimation : public T {
public:
	int32_t move(uint32_t path);
	MoveDirection_t dir(MoveDirection_t dir);
	MoveDirection_t getDir() const;
private:
	MoveDirection_t m_Dir = MoveDirection_t::NONE;
};

template<class T>
int32_t MoveAnimation<T>::move(uint32_t path) {
	assert(0 < path);
	switch(m_Dir) {
	case MoveDirection_t::UP_DIR:
		T::moveUp(path);
		break;
	case MoveDirection_t::DOWN_DIR:
		T::moveDown(path);
		break;
	case MoveDirection_t::LEFT_DIR:
		T::moveLeft(path);
		break;
	case MoveDirection_t::RIGHT_DIR:
		T::moveRight(path);
		break;
	case MoveDirection_t::NONE:
		break;
	default:
		assert(0);
		break;
	}
	return path;
}

template<class T>
MoveDirection_t MoveAnimation<T>::dir(MoveDirection_t dir) {
	m_Dir = dir;
	return m_Dir;
}

template<class T>
MoveDirection_t MoveAnimation<T>::getDir() const {
	return m_Dir;
}

#endif /* GAME_WIDGETS_MOVEANIMATION_HPP_ */
