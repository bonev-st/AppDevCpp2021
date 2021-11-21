/*
 * UnitAction.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_ACTION_UNITACTION_HPP_
#define GAME_ACTION_UNITACTION_HPP_

#include "game/action/ActionDef.hpp"
#include "game/config/Layout.hpp"

class Widget;

class UnitAction {
public:
	bool init(Widget* unit, const Point& pos, uint32_t grid_size, double speed, const Layout::GridData_t &grid_data);
	void setSpeed(double speed);
	bool event(const Action_t type);
	bool tick(Action_t pending_action);
	void reset();

private:
	enum class Action2Dir_t {
		NOT_SAME,
		SAME,
		SAME_LINE
	};

	Widget* m_Unit = nullptr;
	const Layout::GridData_t* m_Grid = nullptr;
	double m_Speed = 0;
	double m_PathToNext = 0;
	uint32_t m_GridSize = 0;
	Point m_RelPos;
	Action_t m_CurrentDirection = Action_t::NONE;

	void stop_to_start(const Action_t &action, Point& rel_pos);
	void forward(Point& rel_pos);
	void reverse(const Action_t &action, Point& rel_pos);
	void turn(Action_t &action, Point& rel_pos);
	void move(const Point &rel_pos);

	bool isMoveAction(Action_t action) const;
	bool process(Action_t action, bool cross_point);
	bool isMoveAllowed(Action_t dir) const;
	Point prepareMoveAction(Action_t dir);
	const Layout::GridDataEntity_t& getGridDataEntity(const Point& pos) const;

	uint8_t toNeighborhoodType(Action_t dir) const;
	Action2Dir_t comp(const Action_t new_act, const Action_t curr_act) const;
};

#endif /* GAME_ACTION_UNITACTION_HPP_ */
