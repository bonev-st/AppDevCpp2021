/*
 * Layout.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#include "game/config/Layout.hpp"

#include <cassert>

#include "game/config/GameConfig.hpp"
#include "utils/drawing/BlendMode.hpp"

using GridNeighborhoodData_t = std::array<std::array<uint8_t, Layout::GRID_RECT_H_NUMB>, Layout::GRID_RECT_V_NUMB>;

static constexpr int32_t X_OFFSET = 79;
static constexpr int32_t Y_OFFSET = 55;

static constexpr int32_t GRID_SIZE = 32;

static const auto & GAME_TEXT_COLOR = Colors::GREEN;
static const auto & DEBUG_TEXT_COLOR = Colors::WHITE;

static constexpr double ENEMY_SPEED = 0.35;
static constexpr double ENEMY_BULLET_SPEED = ENEMY_SPEED * 4.0;
static constexpr double SHIP_SPEED = ENEMY_SPEED*2.0;
static constexpr double SHIP_BULLET_SPEED = SHIP_SPEED * 4.0;

static const Point POS_SHIP_REL{8, 10};

static const std::array<Point, static_cast<size_t>(BonusId_t::BONUS_NUMB)> BonusPos = {
	Point{5, 5},
	Point{5, 9},
	Point{7, 5},
	Point{7, 9}
};

static const std::array<Point, static_cast<size_t>(EnemyId_t::ENEMY_NUMB)> EnemyPos = {
	Point{0, 11},
	Point{0, 7},
	Point{0, 3},
	Point{3, 0},
	Point{5, 0},
	Point{7, 0},
	Point{9, 0},
	Point{11, 0},
	Point{13, 0},
	Point{15, 7},
	Point{15, 9},
};

static const Layout::ImgCfg_t ImgCfg[GameConfig::IMG_ARRAY_SIZE] {
	// IMG_BACKGROUND_INDX
	{
		{0, 0},
		FULL_OPACITY,
	},
	// IMG_CROSSFIRE_INDX,
	{
		{36 + X_OFFSET, 30 + Y_OFFSET},
		FULL_OPACITY,
	},
	// IMG_GRID_BKGRND_INDX
	{
		{66 + X_OFFSET, 0 + Y_OFFSET},
		170,
	},
	// IMG_GRID_INDX,
	{
		{66 + X_OFFSET, 0 + Y_OFFSET},
		FULL_OPACITY,
	},
	// IMG_SHIP_INDX,
	{
		{240 + 66 + 32 + X_OFFSET, 336 + Y_OFFSET},
		FULL_OPACITY,
	},
};

static const Layout::TextCfg_t TextCfg[GameConfig::TEXT_ARRAY_SIZE] {
	// TEXT_SCORE_LABLE_INDX
	{
		.m_Pos = {557 + X_OFFSET, 70 + Y_OFFSET},
		.m_Color = GAME_TEXT_COLOR,
		.m_Text = "Score",
	},
	// TEXT_SCORE_INDX,
	{
		.m_Pos = {553+X_OFFSET,90+Y_OFFSET},
		.m_Color = GAME_TEXT_COLOR,
		.m_Text = "000000",
	},
	// TEXT_HI_SCORE_LABLE_INDX,
	{
		.m_Pos = {550+X_OFFSET,195+Y_OFFSET},
		.m_Color = GAME_TEXT_COLOR,
		.m_Text = "HiScore",
	},
	// TEXT_HI_SCORE_INDX,
	{
		.m_Pos = {553+X_OFFSET, 215+Y_OFFSET},
		.m_Color = GAME_TEXT_COLOR,
		.m_Text = "000000",
	},
	// TEXT_SHIPS_LABLE_INDX,
	{
		.m_Pos = {562+X_OFFSET,325+Y_OFFSET},
		.m_Color = GAME_TEXT_COLOR,
		.m_Text = "Ships",
	},
	// TEXT_SHIPS_INDX,
	{
		.m_Pos = {575+X_OFFSET,345+Y_OFFSET},
		.m_Color = GAME_TEXT_COLOR,
		.m_Text = "00",
	},
	// TEXT_FPS_INDX,
	{
		.m_Pos = {0, 0},
		.m_Color = DEBUG_TEXT_COLOR,
		.m_Text = "FPS: ",
	},
	// TEXT_ACTIVE_TIMER_INDX,
	{
		.m_Pos = {0, 20},
		.m_Color = DEBUG_TEXT_COLOR,
		.m_Text = "Tim: ",
	},
	// TEXT_MAX_ACTIVE_TIMER_INDX,
	{
		.m_Pos = {0, 40},
		.m_Color = DEBUG_TEXT_COLOR,
		.m_Text = "MaxT: ",
	}
};

static const GridNeighborhoodData_t GridNeighborhood = {{
	//0
	{
		Layout::NONE,
		Layout::NONE,
		Layout::DOWN | Layout::RIGHT,
		Layout::LEFT,
		Layout::DOWN | Layout::RIGHT,
		Layout::LEFT,
		Layout::DOWN | Layout::RIGHT,
		Layout::LEFT,
		Layout::DOWN | Layout::RIGHT,
		Layout::LEFT,
		Layout::DOWN | Layout::RIGHT,
		Layout::LEFT,
		Layout::DOWN | Layout::RIGHT,
		Layout::LEFT,
		Layout::NONE
	},
	//1
	{
		Layout::NONE,
		Layout::NONE,
		Layout::DOWN,
		Layout::NONE,
		Layout::DOWN,
		Layout::NONE,
		Layout::DOWN,
		Layout::NONE,
		Layout::DOWN,
		Layout::NONE,
		Layout::DOWN,
		Layout::NONE,
		Layout::DOWN,
		Layout::NONE,
		Layout::NONE
	},
	//2
	{
		Layout::RIGHT | Layout::DOWN,
		Layout::RIGHT,
		Layout::DOWN | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::DOWN | Layout::LEFT,
		Layout::NONE,
		Layout::NONE
	},
	//3
	{
		Layout::UP,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::NONE
	},
	//4
	{
		Layout::NONE,
		Layout::NONE,
		Layout::UP | Layout::DOWN | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT,
		Layout::LEFT,
		Layout::LEFT | Layout::DOWN
	},
	//5
	{
		Layout::NONE,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP
	},
	//6
	{
		Layout::DOWN | Layout::RIGHT,
		Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT,
		Layout::NONE,
		Layout::NONE
	},
	//7
	{
		Layout::UP,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::NONE
	},
	//8
	{
		Layout::NONE,
		Layout::NONE,
		Layout::UP | Layout::DOWN | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::DOWN | Layout::LEFT,
		Layout::LEFT,
		Layout::LEFT | Layout::DOWN
	},
	//9
	{
		Layout::NONE,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP | Layout::DOWN,
		Layout::NONE,
		Layout::UP
	},
	//10
	{
		Layout::DOWN | Layout::RIGHT,
		Layout::RIGHT,
		Layout::UP | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::LEFT | Layout::RIGHT,
		Layout::LEFT | Layout::RIGHT,
		Layout::UP | Layout::LEFT,
		Layout::NONE,
		Layout::NONE
	},
	//11
	{
		Layout::UP,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE,
		Layout::NONE
	},
}};

static Layout::GridData_t GridData;

const Layout::ImgCfg_t & Layout::getImgData(std::size_t id) {
	assert(GameConfig::IMG_ARRAY_SIZE > id);
	return ImgCfg[id];
}

const Layout::TextCfg_t & Layout::getTextData(std::size_t id) {
	assert(GameConfig::TEXT_ARRAY_SIZE > id);
	return TextCfg[id];
}

const Layout::GridData_t & Layout::getGridData() {
	static bool no_initialized = true;
	if(no_initialized) {
		no_initialized = false;
		Point cross_point = ImgCfg[GameConfig::IMG_GRID_INDX].m_Pos;
		Point rol_start_point = cross_point.move(GRID_SIZE/2, GRID_SIZE/2);
		for(size_t rol_indx = 0; GRID_RECT_V_NUMB > rol_indx; ++rol_indx) {
			auto & row_data = GridData[rol_indx];
			for(size_t col_indx = 0; GRID_RECT_H_NUMB > col_indx; ++col_indx) {
				auto type = GridNeighborhood[rol_indx][col_indx];
				row_data[col_indx].m_NB_Mask = type;
				row_data[col_indx].m_Pos = cross_point;
				cross_point.move(GRID_SIZE, 0);
			}
			rol_start_point.move(0, GRID_SIZE);
			cross_point = rol_start_point;
		}
	}
	return GridData;
}

double Layout::getShipSpeed() {
	return SHIP_SPEED;
}

double Layout::getShipBulletSpeed() {
	return SHIP_BULLET_SPEED;
}

double Layout::getEnemySpeed() {
	return ENEMY_SPEED;
}

double Layout::getEnemyBulletSpeed() {
	return ENEMY_BULLET_SPEED;
}

uint32_t Layout::getGridSize() {
	return GRID_SIZE;
}

const Point & Layout::getShipRelPos() {
	return POS_SHIP_REL;
}

const Point & Layout::getBonusRelPos(std::size_t id) {
	assert(static_cast<std::size_t>(BonusId_t::BONUS_NUMB) > id);
	return BonusPos[id];
}

const Point & Layout::getEnemyRelPos(std::size_t id) {
	assert(static_cast<std::size_t>(EnemyId_t::ENEMY_NUMB) > id);
	return EnemyPos[id];
}
