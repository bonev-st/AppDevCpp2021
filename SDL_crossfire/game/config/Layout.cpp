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
#include "utils/drawing/Rectangle.hpp"

using GridNeighborhoodData_t = std::array<std::array<uint8_t, Layout::GRID_RECT_H_NUMB>, Layout::GRID_RECT_V_NUMB>;

static constexpr int32_t X_OFFSET = 80;
static constexpr int32_t Y_OFFSET = 56;

static constexpr int32_t DEBUG_OFFSET_X = 0;
static constexpr int32_t DEBUG_OFFSET_Y = 100;

static constexpr int32_t GRID_SIZE = 32;

static const auto GAME_TEXT_COLOR = Color::GREEN;
static const auto DEBUG_TEXT_COLOR = Color::WHITE;

static constexpr double ENEMY_SPEED = 0.35;
static constexpr double ENEMY_BULLET_SPEED = ENEMY_SPEED * 4.0;
static constexpr double SHIP_SPEED = ENEMY_SPEED*2.0;
static constexpr double SHIP_BULLET_SPEED = SHIP_SPEED * 4.0;

static const Point POS_SHIP_REL{8, 10};

static constexpr int32_t FIELD_H = 480;
static constexpr int32_t FIELD_V = 416;

static constexpr int8_t OWN_MAX_BULLED = 35;
static constexpr int8_t ENEMY_MAX_BULLED = -1;

static constexpr uint32_t OWN_RELOAD_TIME = 800;

static const std::array<Point, static_cast<size_t>(BonusId_t::BONUS_NUMB)> BonusPosDis = {
	Point{5, 7},
	Point{9, 7},
	Point{9, 5},
	Point{5, 5}
};

static const std::array<Point, static_cast<size_t>(BonusId_t::BONUS_NUMB)> BonusPosEna = {
	Point{5, 8},
	Point{9, 8},
	Point{9, 4},
	Point{5, 4}
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
	Point{14, 5},
	Point{14, 9},
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
	// IMG_ENEMY1_INDX,
	{
		{0, 0},
		FULL_OPACITY,
	},
	// IMG_ENEMY2_INDX,
	{
		{0, 0},
		FULL_OPACITY,
	},
	// IMG_ENEMY3_INDX,
	{
		{0, 0},
		FULL_OPACITY,
	},
	// IMG_ENEMY4_INDX,
	{
		{0, 0},
		FULL_OPACITY,
	},
	// IMG_OWN_BULLED_INDX,
	{
		{0, 0},
		FULL_OPACITY,
	},
	// IMG_ENEMY_BULLED_INDX,
	{
		{0, 0},
		FULL_OPACITY,
	},
	// IMG_BONUS_INDX,
	{
		{0, 0},
		FULL_OPACITY,
	},
	// IMG_AMMU_INDX,
	{
		{0, 0},
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
		.m_Pos = {0+DEBUG_OFFSET_X, 0+DEBUG_OFFSET_Y},
		.m_Color = DEBUG_TEXT_COLOR,
		.m_Text = "FPS: ",
	},
	// TEXT_ACTIVE_TIMER_INDX,
	{
		.m_Pos = {0+DEBUG_OFFSET_X, 20+DEBUG_OFFSET_Y},
		.m_Color = DEBUG_TEXT_COLOR,
		.m_Text = "Tim: ",
	},
	// TEXT_MAX_ACTIVE_TIMER_INDX,
	{
		.m_Pos = {0+DEBUG_OFFSET_X, 40+DEBUG_OFFSET_Y},
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

static const Rectangle GridRect(0, 0, Layout::GRID_RECT_H_NUMB, Layout::GRID_RECT_V_NUMB);
static Layout::GridData_t GridData;

static const Layout::GridData_t & getGridData() {
	static bool no_initialized = true;
	if(no_initialized) {
		no_initialized = false;
		Point cross_point = ImgCfg[GameConfig::IMG_GRID_INDX].m_Pos;
		Point rol_start_point = cross_point.move(GRID_SIZE/2, GRID_SIZE/2);
		for(size_t rol_indx = 0; Layout::GRID_RECT_V_NUMB > rol_indx; ++rol_indx) {
			auto & row_data = GridData[rol_indx];
			for(size_t col_indx = 0; Layout::GRID_RECT_H_NUMB > col_indx; ++col_indx) {
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

const Layout::ImgCfg_t & Layout::getImgData(std::size_t id) {
	assert(GameConfig::IMG_ARRAY_SIZE > id);
	return ImgCfg[id];
}

const Layout::TextCfg_t & Layout::getTextData(std::size_t id) {
	assert(GameConfig::TEXT_ARRAY_SIZE > id);
	return TextCfg[id];
}

const Layout::GridDataEntity_t* Layout::getGridDataEntity(const Point& rel) {
	if(!GridRect.isInside(rel)) {
		assert(0);
		return nullptr;
	}
	return &getGridData()[rel.m_Y][rel.m_X];
}

Point Layout::getRel2AbsPosition(const Point& rel) {
	const auto p_data = getGridDataEntity(rel);
	if(!p_data) {
		assert(0);
		return Point::UNDEFINED;
	}
	return p_data->m_Pos;
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

const Point * Layout::getBonusRelPosDis() {
	return BonusPosDis.begin();
}

const Point * Layout::getBonusRelPosEna() {
	return BonusPosEna.begin();
}

const Point & Layout::getEnemyRelPos(std::size_t id) {
	assert(static_cast<std::size_t>(EnemyId_t::ENEMY_NUMB) > id);
	return EnemyPos[id];
}

Rectangle Layout::getArenaRectangle() {
	return Rectangle(ImgCfg[GameConfig::IMG_GRID_INDX].m_Pos , FIELD_H, FIELD_V);
}

int8_t Layout::getOwnMaxBulled() {
	return OWN_MAX_BULLED;
}

uint32_t Layout::getOwnReloadTime() {
	return OWN_RELOAD_TIME;
}

int8_t Layout::getEnemyMaxBulled() {
	return ENEMY_MAX_BULLED;
}
