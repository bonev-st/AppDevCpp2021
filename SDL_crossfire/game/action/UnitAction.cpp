/*
 * UnitAction.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#include "game/action/UnitAction.hpp"

#include <cmath>
#include <iostream>

#include "utils/geometry/Geometry.hpp"

#include "game/widgets/AnimatedImage.hpp"

bool UnitAction::init(AnimatedImage *unit, const Point& pos, uint32_t grid_size, double speed, const Layout::GridData_t &grid_data) {
	m_RelPos = pos;
	m_ActionBuffer.init(this);
	m_Grid = &grid_data;
	m_Unit = unit;
	m_GridSize = grid_size;
	setSpeed(speed);
	reset();
	m_Unit->setPositionCenter(getGridDataEntity(m_RelPos).m_Pos);
	return true;
}

void UnitAction::setSpeed(double speed) {
	m_Speed = speed;
}

void UnitAction::event(Action_t type) {
	m_ActionBuffer = type;
}

void UnitAction::reset() {
	m_PathToNext = 0;
}

volatile int tt = 0;
void UnitAction::tick() {
	const auto current_dir = m_Unit->getDir();
	bool next_cross_point = true;
	if(MoveDirection_t::NONE != current_dir) {
		Point move_delta = Point::ZERO;
		bool n_sing = 0 > m_PathToNext;
		prepareMoveAction(current_dir, move_delta);
		next_cross_point = m_GridSize <= std::abs(m_PathToNext);
		const auto new_cross_point = m_RelPos + move_delta;
		if(next_cross_point) {
			std::cout << "New cross point {" << m_RelPos.m_X << ", " << m_RelPos.m_Y << "}" << std::endl;
			if(0 > m_PathToNext) {
				m_PathToNext += m_GridSize;
			} else {
				m_PathToNext -= m_GridSize;
			}
			m_RelPos = new_cross_point;
			if(!isMoveAllowed(current_dir)) {
				std::cout << "Stop moving" << std::endl;
				m_Unit->setPositionCenter(getGridDataEntity(m_RelPos).m_Pos);
				m_Unit->dir(MoveDirection_t::NONE);
				reset();
			}
		} else if((0 > m_PathToNext) != n_sing) {
			std::cout << "Reach cross point {" << m_RelPos.m_X << ", " << m_RelPos.m_Y << "}" << std::endl;
			next_cross_point = true;
			if(!isMoveAllowed(current_dir)) {
				std::cout << "Stop moving" << std::endl;
				m_Unit->setPositionCenter(getGridDataEntity(m_RelPos).m_Pos);
				m_Unit->dir(MoveDirection_t::NONE);
				reset();
			}
		}
		m_Unit->setPositionCenter(getGridDataEntity(m_RelPos).m_Pos);
		if(move_delta.m_X) {
			move_delta.m_X += static_cast<int32_t>(std::round(m_PathToNext));
		} else {
			move_delta.m_Y += static_cast<int32_t>(std::round(m_PathToNext));
		}
		m_Unit->setPositionCenter(getGridDataEntity(m_RelPos).m_Pos + move_delta);
	}
	if(next_cross_point) {
		m_ActionBuffer.force();
	}
}

bool UnitAction::process(Action_t action, bool cross_point) {
	bool rc = false;
	const auto current_dir = m_Unit->getDir();
	const auto act_move = comp(current_dir, action);

	if(ActionCompMove_t::SAME != act_move) {
		switch (action) {
		case Action_t::MOVE_UP:
			if((ActionCompMove_t::SAME_LINE == act_move)
			|| (cross_point && isMoveAllowed(MoveDirection_t::UP_DIR))) {
				m_Unit->dir(MoveDirection_t::UP_DIR);
				rc = true;
			}
			break;
		case Action_t::MOVE_DOWN:
			if((ActionCompMove_t::SAME_LINE == act_move)
			|| (cross_point && isMoveAllowed(MoveDirection_t::DOWN_DIR))) {
				m_Unit->dir(MoveDirection_t::DOWN_DIR);
				rc = true;
			}
			break;
		case Action_t::MOVE_LEFT:
			if((ActionCompMove_t::SAME_LINE == act_move)
			|| (cross_point && isMoveAllowed(MoveDirection_t::LEFT_DIR))) {
				m_Unit->dir(MoveDirection_t::LEFT_DIR);
				rc = true;
			}
			break;
		case Action_t::MOVE_RIGHT:
			if((ActionCompMove_t::SAME_LINE == act_move)
			|| (cross_point && isMoveAllowed(MoveDirection_t::RIGHT_DIR))) {
				m_Unit->dir(MoveDirection_t::RIGHT_DIR);
				rc = true;
			}
			break;
		case Action_t::FIRE_UP:
			if(cross_point || isFireAllowed(VERTICAL)) {
				rc = true;
			}
			break;
		case Action_t::FIRE_DOWN:
			if(cross_point || isFireAllowed(VERTICAL)) {
				rc = true;
			}
			break;
		case Action_t::FIRE_LEFT:
			if(cross_point || isFireAllowed(HORISONTAL)) {
				rc = true;
			}
			break;
		case Action_t::FIRE_RIGHT:
			if(cross_point || isFireAllowed(HORISONTAL)) {
				rc = true;
			}
			break;
		case Action_t::NONE:
			break;
		default:
			assert(0);
			break;
		}
	} else {
		rc = Action_t::NONE != action;
	}
	return rc;
}

bool UnitAction::isMoveAllowed(MoveDirection_t dir) const {
	const auto dir_type = toNeighborhoodType(dir);
	const auto dir_mask = getGridDataEntity(m_RelPos).m_NB_Mask;
	return !!(dir_mask & dir_type);
}

void UnitAction::prepareMoveAction(MoveDirection_t dir, Point & rel_pos_move) {
	switch (dir) {
	case MoveDirection_t::UP_DIR:
		m_PathToNext -= m_Speed;
		rel_pos_move.m_Y = -1;
		break;
	case MoveDirection_t::DOWN_DIR:
		m_PathToNext += m_Speed;
		rel_pos_move.m_Y = 1;
		break;
	case MoveDirection_t::LEFT_DIR:
		m_PathToNext -= m_Speed;
		rel_pos_move.m_X = -1;
		break;
	case MoveDirection_t::RIGHT_DIR:
		m_PathToNext += m_Speed;
		rel_pos_move.m_X = 1;
		break;
	case MoveDirection_t::NONE:
		break;
	default:
		assert(0);
		break;
	}
}

bool UnitAction::isFireAllowed(FireDir_t dir) const {
	return !!(getGridDataEntity(m_RelPos).m_NB_Mask & static_cast<uint8_t>(dir));
}

const Layout::GridDataEntity_t& UnitAction::getGridDataEntity(const Point& pos) const {
	return (*m_Grid)[pos.m_Y][pos.m_X];
}

uint8_t UnitAction::toNeighborhoodType(MoveDirection_t dir) const {
	uint8_t rc = Layout::NONE;
	switch(dir) {
	case MoveDirection_t::UP_DIR:
		rc = Layout::UP;
		break;
	case MoveDirection_t::DOWN_DIR:
		rc = Layout::DOWN;
		break;
	case MoveDirection_t::LEFT_DIR:
		rc = Layout::LEFT;
		break;
	case MoveDirection_t::RIGHT_DIR:
		rc = Layout::RIGHT;
		break;
	case MoveDirection_t::NONE:
		break;
	default:
		assert(0);
	}
	return rc;
}

UnitAction::ActionCompMove_t UnitAction::comp(MoveDirection_t dir, Action_t action) const {
	ActionCompMove_t rc = ActionCompMove_t::NOT_SAME;
	switch (action) {
	case Action_t::MOVE_UP:
		if(MoveDirection_t::UP_DIR == dir) {
			rc = ActionCompMove_t::SAME;
		} else if(MoveDirection_t::DOWN_DIR == dir) {
			rc = ActionCompMove_t::SAME_LINE;
		}
		break;
	case Action_t::MOVE_DOWN:
		if(MoveDirection_t::DOWN_DIR == dir) {
			rc = ActionCompMove_t::SAME;
		} else if(MoveDirection_t::UP_DIR == dir) {
			rc = ActionCompMove_t::SAME_LINE;
		}
		break;
	case Action_t::MOVE_LEFT:
		if(MoveDirection_t::LEFT_DIR == dir) {
			rc = ActionCompMove_t::SAME;
		} else if(MoveDirection_t::RIGHT_DIR == dir) {
			rc = ActionCompMove_t::SAME_LINE;
		}
		break;
	case Action_t::MOVE_RIGHT:
		if(MoveDirection_t::RIGHT_DIR == dir) {
			rc = ActionCompMove_t::SAME;
		} else if(MoveDirection_t::LEFT_DIR == dir) {
			rc = ActionCompMove_t::SAME_LINE;
		}
		break;
	case Action_t::NONE:
		rc = ActionCompMove_t::SAME;
		break;
	default:
		break;
	}
	return rc;
}
