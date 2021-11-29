/*
 * RelCoordinates.hpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#ifndef GAME_CONFIG_RELCOORDINATES_HPP_
#define GAME_CONFIG_RELCOORDINATES_HPP_

#include <array>

#include "utils/drawing/Point.hpp"

enum class BonusId_t : uint8_t {
	BONUS1  = 0,
	BONUS2,
	BONUS3,
	BONUS4,
	BONUS_NUMB
};

enum class EnemyId_t {
	ENEMY1 = 0,
	ENEMY2,
	ENEMY3,
	ENEMY4,
	ENEMY5,
	ENEMY6,
	ENEMY7,
	ENEMY8,
	ENEMY9,
	ENEMY10,
	ENEMY11,
	ENEMY_NUMB
};

enum GridNeighborhoodType_t : uint8_t {
	NONE  = 0,
	UP 	  = 1 << 0,
	DOWN  = 1 << 1,
	LEFT  = 1 << 2,
	RIGHT = 1 << 3
};

namespace RelCoordinates {
struct GridDataEntity_t {
	Point m_Pos;
	uint8_t m_NB_Mask; // bitmask of type extern GridNeighborhoodType_t
};

static constexpr uint32_t GRID_RECT_H_NUMB = 15;
static constexpr uint32_t GRID_RECT_V_NUMB = 12;

using GridNeighborhoodData_t = std::array<std::array<uint8_t, GRID_RECT_H_NUMB>, GRID_RECT_V_NUMB>;
using GridData_t = std::array<std::array<GridDataEntity_t, GRID_RECT_H_NUMB>, GRID_RECT_V_NUMB>;
} /* namespace RelCoordinates */

#endif /* GAME_CONFIG_RELCOORDINATES_HPP_ */
