/*
 * UnitAction.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_ACTION_UNITACTION_HPP_
#define GAME_ACTION_UNITACTION_HPP_

#include "game/action/ActionClientIF.hpp"
#include "game/action/ActionBuffer.hpp"
#include "game/config/Layout.hpp"
#include "game/widgets/MoveAnimation.hpp"

class AnimatedImage;

class UnitAction : private ActionClientIF {
public:
	bool init(AnimatedImage* unit, const Point& pos, uint32_t grid_size, double speed, const Layout::GridData_t &grid_data);
	void setSpeed(double speed);
	void event(Action_t type);
	void tick();
	void reset();

private:
	enum FireDir_t : uint8_t {
		VERTICAL = static_cast<uint8_t>(MoveDirection_t::UP_DIR) | static_cast<uint8_t>(MoveDirection_t::DOWN_DIR),
		HORISONTAL = static_cast<uint8_t>(MoveDirection_t::RIGHT_DIR) | static_cast<uint8_t>(MoveDirection_t::LEFT_DIR)
	};

	enum class ActionCompMove_t {
		NOT_SAME,
		SAME,
		SAME_LINE
	};

	ActionBuffer m_ActionBuffer;
	AnimatedImage* m_Unit = nullptr;
	const Layout::GridData_t* m_Grid = nullptr;
	double m_Speed = 0;
	double m_PathToNext = 0;
	uint32_t m_GridSize = 0;
	Point m_RelPos;

	bool process(Action_t action, bool cross_point) final;
	bool isMoveAllowed(MoveDirection_t dir) const;
	void prepareMoveAction(MoveDirection_t dir, Point & rel_pos_move);
	bool isFireAllowed(FireDir_t dir) const;
	const Layout::GridDataEntity_t& getGridDataEntity(const Point& pos) const;

	uint8_t toNeighborhoodType(MoveDirection_t dir) const;
	ActionCompMove_t comp(MoveDirection_t dir, Action_t action) const;
};

#endif /* GAME_ACTION_UNITACTION_HPP_ */
