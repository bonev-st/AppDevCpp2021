/*
 * LayoutMain.hpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#ifndef GAME_CONFIG_LAYOUT_HPP_
#define GAME_CONFIG_LAYOUT_HPP_

#include <string>
#include <array>
#include "utils/drawing/Color.hpp"
#include "utils/drawing/Point.hpp"

enum class BonusId_t {
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

namespace Layout {

static constexpr uint32_t GRID_RECT_H_NUMB = 15;
static constexpr uint32_t GRID_RECT_V_NUMB = 12;

enum GridNeighborhoodType_t : uint8_t {
	NONE  = 0,
	UP 	  = 1 << 0,
	DOWN  = 1 << 1,
	LEFT  = 1 << 2,
	RIGHT = 1 << 3
};

struct GridDataEntity_t {
	Point m_Pos;
	uint8_t m_NB_Mask; // bitmask of type GridNeighborhoodType_t
};

using GridData_t = std::array<std::array<GridDataEntity_t, GRID_RECT_H_NUMB>, GRID_RECT_V_NUMB>;

struct TextCfg_t {
	Point m_Pos;
	const Color &m_Color;
	std::string m_Text;
};

struct ImgCfg_t {
	Point m_Pos;
	uint8_t m_Alpha;
};

const GridData_t & getGridData();
const ImgCfg_t	 & getImgData(std::size_t id);
const TextCfg_t	 & getTextData(std::size_t id);

double getShipSpeed();
double getShipBulletSpeed();
double getEnemySpeed();
double getEnemyBulletSpeed();

uint32_t getGridSize();

const Point & getShipRelPos();
const Point & getBonusRelPos(std::size_t id);
const Point & getEnemyRelPos(std::size_t id);

}

#endif /* GAME_CONFIG_LAYOUT_HPP_ */
