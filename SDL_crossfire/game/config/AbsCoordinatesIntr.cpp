/*
 * AbsCoordinatesIntr.cpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#include "game/config/AbsCoordinatesIntr.hpp"

#include "utils/drawing/BlendMode.hpp"

#include "game/config/GameConfig.hpp"

static constexpr int32_t X_OFFSET = 80;
static constexpr int32_t Y_OFFSET = 56;

static constexpr int32_t DEBUG_OFFSET_X = 0;
static constexpr int32_t DEBUG_OFFSET_Y = 100;

static Color getTextColor() {
	static const auto color = Color(0, 255, 0, 255);
	return color;
}

static Color getDebugColor() {
	static const auto color = Color(255, 255, 255, 255);
	return color;
}

namespace AbsCoordinates {
const AbsCoordinates::ImgCfg_t ImgCfg[GameConfig::IMG_ARRAY_SIZE] {
	// IMG_BACKGROUND_INDX
	{
		{0, 0},
		210,
	},
	// IMG_CROSSFIRE_INDX,
	{
		{32 + X_OFFSET, 30 + Y_OFFSET},
		FULL_OPACITY,
	},
	// IMG_GRID_BKGRND_INDX
	{
		{66 + X_OFFSET, 0 + Y_OFFSET},
		130,
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

const AbsCoordinates::TextCfg_t TextCfg[GameConfig::TEXT_ARRAY_SIZE] {
	// TEXT_SCORE_LABLE_INDX
	{
		.m_Pos = {557 + X_OFFSET, 70 + Y_OFFSET},
		.m_Color = getTextColor(),
		.m_Text = "Score",
	},
	// TEXT_SCORE_INDX,
	{
		.m_Pos = {553 + X_OFFSET, 90 + Y_OFFSET},
		.m_Color = getTextColor(),
		.m_Text = "000000",
	},
	// TEXT_HI_SCORE_LABLE_INDX,
	{
		.m_Pos = {550 + X_OFFSET, 195 + Y_OFFSET},
		.m_Color = getTextColor(),
		.m_Text = "HiScore",
	},
	// TEXT_HI_SCORE_INDX,
	{
		.m_Pos = {553 + X_OFFSET, 215 + Y_OFFSET},
		.m_Color = getTextColor(),
		.m_Text = "000000",
	},
	// TEXT_SHIPS_LABLE_INDX,
	{
		.m_Pos = {562 + X_OFFSET, 325 + Y_OFFSET},
		.m_Color = getTextColor(),
		.m_Text = "Ships",
	},
	// TEXT_SHIPS_INDX,
	{
		.m_Pos = {575 + X_OFFSET, 345 + Y_OFFSET},
		.m_Color = getTextColor(),
		.m_Text = "00",
	},
	// TEXT_FPS_INDX,
	{
		.m_Pos = {0+DEBUG_OFFSET_X, 0+DEBUG_OFFSET_Y},
		.m_Color = getDebugColor(),
		.m_Text = "FPS: ",
	},
	// TEXT_ACTIVE_TIMER_INDX,
	{
		.m_Pos = {0+DEBUG_OFFSET_X, 20+DEBUG_OFFSET_Y},
		.m_Color = getDebugColor(),
		.m_Text = "Tim: ",
	},
	// TEXT_MAX_ACTIVE_TIMER_INDX,
	{
		.m_Pos = {0+DEBUG_OFFSET_X, 40+DEBUG_OFFSET_Y},
		.m_Color = getDebugColor(),
		.m_Text = "MaxT: ",
	}
};

} /* namespace AbsCoordinates */
