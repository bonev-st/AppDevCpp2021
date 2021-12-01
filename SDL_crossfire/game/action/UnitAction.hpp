/*
 * UnitAction.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_ACTION_UNITACTION_HPP_
#define GAME_ACTION_UNITACTION_HPP_

#include "game/action/Action.hpp"
#include "game/config/Layout.hpp"

class Widget;

class UnitAction {
public:
	bool init(Widget* unit, const Point& pos, uint32_t grid_size);
	void setSpeed(double speed);
	bool event(const Action_t type);
	bool tick(Action_t pending_action);
	void reset();
	void destroy();
	Action_t getDirection() const;
	Point getCrossPoint() const;
	uint8_t getLineOfFire() const;

private:
	bool m_Destroy = false;
	Widget* m_Unit = nullptr;
	double m_Speed = 0;
	double m_PathToNext = 0;
	uint32_t m_GridSize = 0;
	Point m_StartRelPos;
	Point m_RelPos;
	Action_t m_CurrentDirection = Action_t::NONE;
	Point m_CrossPoint;

	void stop_to_start(const Action_t &action, Point& rel_pos);
	void forward(Point& rel_pos);
	void reverse(const Action_t &action, Point& rel_pos);
	void turn(Action_t &action, Point& rel_pos);
	void move(const Point &rel_pos);

	bool process(Action_t action, bool cross_point);
	bool isMoveAllowed(Action_t dir) const;
	Point prepareMoveAction(Action_t dir);
};

#endif /* GAME_ACTION_UNITACTION_HPP_ */
