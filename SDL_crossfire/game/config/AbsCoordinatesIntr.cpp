/*
 * AbsCoordinatesIntr.cpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#include "game/config/AbsCoordinatesIntr.hpp"

#include "utils/drawing/BlendMode.hpp"

#include "game/config/GameConfig.hpp"
#include "game/config/GameConfigDef.hpp"

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

static Color getImageDefColor() {
	static const auto color = Color(0, 0, 0, 0);
	return color;
}

static Color getImageColor() {
	static const auto color = Color(0, 0, 0, 130);
	return color;
}

static Color getTextDefColor() {
	static const auto color = Color(0, 0, 0, 130);
	return color;
}

namespace AbsCoordinates {
const AbsCoordinates::ImgCfg_t ImgCfg[GameConfig::IMG_ARRAY_SIZE] {
	// IMG_BACKGROUND_INDX
	{
		{0, 0},
		210,
		getImageDefColor(),
	},
	// IMG_CROSSFIRE_INDX,
	{
		{32 + X_OFFSET, 30 + Y_OFFSET},
		FULL_OPACITY,
		getImageColor(),
	},
	// IMG_GRID_INDX,
	{
		{66 + X_OFFSET, 0 + Y_OFFSET},
		FULL_OPACITY,
		getImageColor(),
	},
	// IMG_SHIP_INDX,
	{
		{240 + 66 + 32 + X_OFFSET, 336 + Y_OFFSET},
		FULL_OPACITY,
		getImageDefColor(),
	},
	// IMG_ENEMY1_INDX,
	{
		{0, 0},
		FULL_OPACITY,
		getImageDefColor(),
	},
	// IMG_ENEMY2_INDX,
	{
		{0, 0},
		FULL_OPACITY,
		getImageDefColor(),
	},
	// IMG_ENEMY3_INDX,
	{
		{0, 0},
		FULL_OPACITY,
		getImageDefColor(),
	},
	// IMG_ENEMY4_INDX,
	{
		{0, 0},
		FULL_OPACITY,
		getImageDefColor(),
	},
	// IMG_OWN_BULLED_INDX,
	{
		{0, 0},
		FULL_OPACITY,
		getImageDefColor(),
	},
	// IMG_ENEMY_BULLED_INDX,
	{
		{0, 0},
		FULL_OPACITY,
		getImageDefColor(),
	},
	// IMG_BONUS_INDX,
	{
		{0, 0},
		FULL_OPACITY,
		getImageDefColor(),
	},
	// IMG_AMMU_INDX,
	{
		{0, 0},
		FULL_OPACITY,
		getImageDefColor(),
	},
	// 	IMG_EXPLOSION_INDX,
	{
		{0, 0},
		FULL_OPACITY,
		getImageDefColor(),
	},
};

const AbsCoordinates::TextCfg_t TextCfg[GameConfig::TEXT_ARRAY_SIZE] {
	// TEXT_SCORE_LABLE_INDX
	{
		{557 + X_OFFSET, 70 + Y_OFFSET},
		getTextColor(),
		getTextDefColor(),
		"Score",
	},
	// TEXT_SCORE_INDX,
	{
		{553 + X_OFFSET, 90 + Y_OFFSET},
		getTextColor(),
		getTextDefColor(),
		"000000",
	},
	// TEXT_HI_SCORE_LABLE_INDX,
	{
		{550 + X_OFFSET, 195 + Y_OFFSET},
		getTextColor(),
		getTextDefColor(),
		"HiScore",
	},
	// TEXT_HI_SCORE_INDX,
	{
		{553 + X_OFFSET, 215 + Y_OFFSET},
		getTextColor(),
		getTextDefColor(),
		"000000",
	},
	// TEXT_SHIPS_LABLE_INDX,
	{
		{562 + X_OFFSET, 325 + Y_OFFSET},
		getTextColor(),
		getTextDefColor(),
		"Ships",
	},
	// TEXT_SHIPS_INDX,
	{
		{575 + X_OFFSET, 345 + Y_OFFSET},
		getTextColor(),
		getTextDefColor(),
		"00",
	},
	// TEXT_FPS_INDX,
	{
		{0+DEBUG_OFFSET_X, 0+DEBUG_OFFSET_Y},
		getDebugColor(),
		getTextDefColor(),
		"FPS: ",
	},
	// TEXT_ACTIVE_TIMER_INDX,
	{
		{0+DEBUG_OFFSET_X, 20+DEBUG_OFFSET_Y},
		getDebugColor(),
		getTextDefColor(),
		"Tim: ",
	},
	// TEXT_MAX_ACTIVE_TIMER_INDX,
	{
		{0+DEBUG_OFFSET_X, 40+DEBUG_OFFSET_Y},
		getDebugColor(),
		getTextDefColor(),
		"MaxT: ",
	}
};

} /* namespace AbsCoordinates */
