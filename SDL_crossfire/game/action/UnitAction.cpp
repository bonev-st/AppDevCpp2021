/*
 * UnitAction.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#include "game/action/UnitAction.hpp"

#include <cmath>
#include <cassert>
#include <iostream>

#include "utils/geometry/Geometry.hpp"

#include "manager_utils/drawing/Widget.hpp"

bool UnitAction::init(Widget *unit, const Point& pos, uint32_t grid_size, double speed, const Layout::GridData_t &grid_data) {
	m_Grid = &grid_data;
	m_Unit = unit;
	m_GridSize = grid_size;
	m_RelPos = pos;
	setSpeed(speed);
	reset();
	m_Unit->setPositionCenter(getGridDataEntity(m_RelPos).m_Pos);
	return true;
}

void UnitAction::setSpeed(double speed) {
	m_Speed = speed;
}

void UnitAction::reset() {
	m_PathToNext = 0;
	m_CurrentDirection = Action_t::NONE;
}

bool UnitAction::event(const Action_t action) {
	return action == m_CurrentDirection;
}

volatile int tt = 0;
bool UnitAction::tick(Action_t pending_action) {
	if(!isMoveAction(pending_action)) {
		pending_action = Action_t::NONE;
	}
	Point move_delta = Point::ZERO;
	if(Action_t::NONE == m_CurrentDirection) {
		if(Action_t::NONE == pending_action) {
			return false;
		}
		assert(0 == m_PathToNext);
		if(!isMoveAllowed(pending_action)) {
			return true;
		}
		m_CurrentDirection = pending_action;
		prepareMoveAction(m_CurrentDirection, move_delta);
		m_RelPos += move_delta;
		m_PathToNext += m_GridSize;
	} else {
		if(Action_t::NONE == pending_action) {
			prepareMoveAction(m_CurrentDirection, move_delta);
			if(0 >= m_PathToNext) {
				if(isMoveAllowed(m_CurrentDirection)) {
					m_RelPos += move_delta;
					m_PathToNext += m_GridSize;
				} else {
					reset();
				}
			}
		} else {
			const auto act_move = comp(m_CurrentDirection, pending_action);
			if(Action2Dir_t::SAME_LINE == act_move) {
				if(isMoveAllowed(pending_action)) {
					m_PathToNext = m_GridSize - m_PathToNext;
					m_CurrentDirection = pending_action;
					prepareMoveAction(m_CurrentDirection, move_delta);
					m_RelPos += move_delta;
					if(0 >= m_PathToNext) {
						if(isMoveAllowed(m_CurrentDirection)) {
							m_RelPos += move_delta;
							m_PathToNext += m_GridSize;
						} else {
							reset();
						}
					}
				} else {
					prepareMoveAction(m_CurrentDirection, move_delta);
					if(0 >= m_PathToNext) {
						if(isMoveAllowed(m_CurrentDirection)) {
							m_RelPos += move_delta;
							m_PathToNext += m_GridSize;
						} else {
							reset();
						}
					}
				}
			} else {
				prepareMoveAction(m_CurrentDirection, move_delta);
				if(0 >= m_PathToNext) {
					if(isMoveAllowed(pending_action)) {
						const auto path_tmp = m_PathToNext;
						m_CurrentDirection = pending_action;
						move_delta = Point::ZERO;
						prepareMoveAction(m_CurrentDirection, move_delta);
						m_RelPos += move_delta;
						m_PathToNext = path_tmp;
						m_PathToNext += m_GridSize;
					} else {
						if(isMoveAllowed(m_CurrentDirection)) {
							m_RelPos += move_delta;
							m_PathToNext += m_GridSize;
							// XXX: do not clear command buffer
							pending_action = Action_t::NONE;
						} else {
							reset();
						}
					}
				} else {
					// XXX: do not clear command buffer
					pending_action = Action_t::NONE;
				}
			}
		}
	}
	assert(0 <= m_PathToNext);
	m_Unit->setPositionCenter(getGridDataEntity(m_RelPos).m_Pos);
	if(move_delta.m_X) {
		const auto path = m_PathToNext*move_delta.m_X*-1.0;
		move_delta.m_X += static_cast<int32_t>(std::round(path));
	} else {
		const auto path = m_PathToNext*move_delta.m_Y*-1.0;
		move_delta.m_Y += static_cast<int32_t>(std::round(path));
	}
	m_Unit->setPositionCenter(getGridDataEntity(m_RelPos).m_Pos + move_delta);

	return Action_t::NONE != pending_action;
}

bool UnitAction::isMoveAction(Action_t action) const {
	return (Action_t::MOVE_ACTION_START <= action)
		&& (Action_t::MOVE_ACTION_END >= action);
}

bool UnitAction::isMoveAllowed(Action_t dir) const {
	const auto dir_type = toNeighborhoodType(dir);
	const auto dir_mask = getGridDataEntity(m_RelPos).m_NB_Mask;
	return !!(dir_mask & dir_type);
}

void UnitAction::prepareMoveAction(Action_t dir, Point & rel_pos_move) {
	switch (dir) {
	case Action_t::MOVE_UP:
		m_PathToNext -= m_Speed;
		rel_pos_move.m_Y = -1;
		break;
	case Action_t::MOVE_DOWN:
		m_PathToNext -= m_Speed;
		rel_pos_move.m_Y = 1;
		break;
	case Action_t::MOVE_LEFT:
		m_PathToNext -= m_Speed;
		rel_pos_move.m_X = -1;
		break;
	case Action_t::MOVE_RIGHT:
		m_PathToNext -= m_Speed;
		rel_pos_move.m_X = 1;
		break;
	case Action_t::NONE:
		break;
	default:
		assert(0);
		break;
	}
}

const Layout::GridDataEntity_t& UnitAction::getGridDataEntity(const Point& pos) const {
	return (*m_Grid)[pos.m_Y][pos.m_X];
}

uint8_t UnitAction::toNeighborhoodType(Action_t dir) const {
	uint8_t rc = Layout::NONE;
	switch(dir) {
	case Action_t::MOVE_UP:
		rc = Layout::UP;
		break;
	case Action_t::MOVE_DOWN:
		rc = Layout::DOWN;
		break;
	case Action_t::MOVE_LEFT:
		rc = Layout::LEFT;
		break;
	case Action_t::MOVE_RIGHT:
		rc = Layout::RIGHT;
		break;
	case Action_t::NONE:
		break;
	default:
		assert(0);
	}
	return rc;
}

UnitAction::Action2Dir_t UnitAction::comp(const Action_t new_act, const Action_t curr_act) const {
	if(new_act == curr_act) {
		return Action2Dir_t::SAME;
	}
	Action2Dir_t rc = Action2Dir_t::NOT_SAME;
	switch (new_act) {
	case Action_t::MOVE_UP:
		if(Action_t::MOVE_UP == curr_act) {
			rc = Action2Dir_t::SAME;
		} else if(Action_t::MOVE_DOWN == curr_act) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::MOVE_DOWN:
		if(Action_t::MOVE_DOWN == curr_act) {
			rc = Action2Dir_t::SAME;
		} else if(Action_t::MOVE_UP == curr_act) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::MOVE_LEFT:
		if(Action_t::MOVE_LEFT == curr_act) {
			rc = Action2Dir_t::SAME;
		} else if(Action_t::MOVE_RIGHT == curr_act) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	case Action_t::MOVE_RIGHT:
		if(Action_t::MOVE_RIGHT == curr_act) {
			rc = Action2Dir_t::SAME;
		} else if(Action_t::MOVE_LEFT == curr_act) {
			rc = Action2Dir_t::SAME_LINE;
		}
		break;
	default:
		break;
	}
	return rc;
}
