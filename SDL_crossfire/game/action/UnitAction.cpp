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

#include "gr_engine/drawing/Widget.hpp"
#include "utils/geometry/Geometry.hpp"


bool UnitAction::init(Widget *unit, const Point& pos, uint32_t grid_size) {
	m_Unit = unit;
	m_GridSize = grid_size;
	m_RelPos = m_StartRelPos = pos;
	reset();
	m_Unit->setPositionCenter(Layout::getRel2AbsPosition(m_StartRelPos));
	return true;
}

void UnitAction::setSpeed(double speed) {
	m_Speed = speed;
}

bool UnitAction::event(const Action_t action) {
	if(m_Destroy) {
		return true;
	}
	return action == m_CurrentDirection;
}

bool UnitAction::tick(Action_t pending_action) {
	if(m_Destroy) {
		return true;
	}
	if(!Action::isMoveAction(pending_action)) {
		pending_action = Action_t::NONE;
	}
	if( (Action_t::NONE == m_CurrentDirection)
	 && (Action_t::NONE == pending_action)) {
		// stop state
		return false;
	}
	m_CrossPoint = Points::UNDEFINED;
	Point move_delta = Points::ZERO;
	if(Action_t::NONE == m_CurrentDirection) {
		// change from stop to motion
		assert(0 == m_PathToNext);
		if(!isMoveAllowed(pending_action)) {
			return true;
		}
		stop_to_start(pending_action, move_delta);
	} else {
		// motion state
		if(Action_t::NONE == pending_action) {
			// continue in the same direction
			forward(move_delta);
		} else {
			const auto act_move = Action::compare(m_CurrentDirection, pending_action);
			if(Action2Dir_t::SAME_LINE == act_move) {
				// reverse direction
				reverse(pending_action, move_delta);
			} else {
				// turn 90 degree
				turn(pending_action, move_delta);
			}
		}
	}
	assert(0 <= m_PathToNext);
	move(move_delta);
	return Action_t::NONE != pending_action;
}

void UnitAction::reset() {
	m_RelPos = m_StartRelPos;
	m_PathToNext = 0;
	m_CurrentDirection = Action_t::NONE;
	m_CrossPoint = m_RelPos;
	m_Destroy = false;
	move(Points::ZERO);
}

void UnitAction::destroy() {
	m_Destroy = true;
}

bool UnitAction::isDestroy() const {
	return m_Destroy;
}

Action_t UnitAction::getDirection() const {
	return m_CurrentDirection;
}

Point UnitAction::getCrossPoint() const {
	return m_RelPos;
}

uint8_t UnitAction::getLineOfFire() const {
	if(Action_t::NONE == m_CurrentDirection) {
		// XXX: Action_t::NONE -> all direction line of fire
		return Action::toLineOfFireMask(Action_t::NONE);
	}
	if(Points::UNDEFINED != m_CrossPoint) {
		uint8_t rc = 0;
		if(!(m_CrossPoint.m_X & 1)) {
			rc = rc | Action::toLineOfFireMask(Action_t::MOVE_UP);
		}
		if(!(m_CrossPoint.m_Y & 1)) {
			rc = rc | Action::toLineOfFireMask(Action_t::MOVE_RIGHT);
		}
		return rc;
	}
	return Action::toLineOfFireMask(m_CurrentDirection);
}

void UnitAction::stop() {
	m_PathToNext = 0;
	m_CurrentDirection = Action_t::NONE;
	m_CrossPoint = m_RelPos;
}

void UnitAction::stop_to_start(const Action_t &action, Point& rel_pos) {
	m_CurrentDirection = action;
	rel_pos = prepareMoveAction(m_CurrentDirection);
	m_RelPos += rel_pos;
	m_PathToNext = m_GridSize;
}

void UnitAction::forward(Point& rel_pos) {
	rel_pos = prepareMoveAction(m_CurrentDirection);
	if(0 >= m_PathToNext) {
		m_CrossPoint = m_RelPos;
		if(isMoveAllowed(m_CurrentDirection)) {
			m_RelPos += rel_pos;
			m_PathToNext += m_GridSize;
		} else {
			stop();
		}
	}
}

void UnitAction::reverse(const Action_t &action, Point& rel_pos) {
	if(isMoveAllowed(action)) {
		m_PathToNext = m_GridSize - m_PathToNext;
		m_CurrentDirection = action;
		rel_pos = prepareMoveAction(m_CurrentDirection);
		m_RelPos += rel_pos;
		if(0 >= m_PathToNext) {
			m_CrossPoint = m_RelPos;
			if(isMoveAllowed(m_CurrentDirection)) {
				m_RelPos += rel_pos;
				m_PathToNext += m_GridSize;
			} else {
				stop();
			}
		}
	} else {
		forward(rel_pos);
	}
}

void UnitAction::turn(Action_t &action, Point& rel_pos) {
	rel_pos = prepareMoveAction(m_CurrentDirection);
	if(0 >= m_PathToNext) {
		m_CrossPoint = m_RelPos;
		if(isMoveAllowed(action)) {
			const auto path_tmp = m_PathToNext;
			m_CurrentDirection = action;
			rel_pos = prepareMoveAction(m_CurrentDirection);
			m_RelPos += rel_pos;
			m_PathToNext = path_tmp;
			m_PathToNext += m_GridSize;
		} else {
			if(isMoveAllowed(m_CurrentDirection)) {
				m_RelPos += rel_pos;
				m_PathToNext += m_GridSize;
				// XXX: skip command buffer clear
				action = Action_t::NONE;
			} else {
				stop();
			}
		}
	} else {
		// XXX: skip command buffer clear
		action = Action_t::NONE;
	}
}

void UnitAction::move(const Point &rel_pos) {
	Point offset = Layout::getRel2AbsPosition(m_RelPos);
	if(rel_pos.m_X) {
		const auto path = m_PathToNext*rel_pos.m_X*-1.0;
		offset.m_X += static_cast<int32_t>(std::round(path));
	} else {
		const auto path = m_PathToNext*rel_pos.m_Y*-1.0;
		offset.m_Y += static_cast<int32_t>(std::round(path));
	}
	m_Unit->setPositionCenter(offset);
}

bool UnitAction::isMoveAllowed(Action_t dir) const {
	const auto dir_type = Action::toNeighborhoodMask(dir);
	const auto dir_mask = Layout::getGridDataEntity(m_RelPos)->m_NB_Mask;
	return !!(dir_mask & dir_type);
}

Point UnitAction::prepareMoveAction(Action_t dir) {
	Point rel_pos = Points::ZERO;
	switch (dir) {
	case Action_t::MOVE_UP:
		rel_pos.m_Y = -1;
		break;
	case Action_t::MOVE_DOWN:
		rel_pos.m_Y = 1;
		break;
	case Action_t::MOVE_LEFT:
		rel_pos.m_X = -1;
		break;
	case Action_t::MOVE_RIGHT:
		rel_pos.m_X = 1;
		break;
	default:
		assert(0);
		break;
	}
	m_PathToNext -= m_Speed;
	return rel_pos;
}
