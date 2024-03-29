/*
 * Layout.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#include "game/config/Layout.hpp"

#include <cassert>
#include <cmath>

#include "utils/drawing/Rectangle.hpp"
#include "utils/drawing/DisplayMode.hpp"
#include "utils/drawing/Dimention.hpp"
#include "utils/geometry/Geometry.hpp"
#include "game/config/GameConfig.hpp"
#include "game/config/GameConfigDef.hpp"

#include "game/config/AbsCoordinatesIntr.hpp"
#include "game/config/RelCoordinatesIntr.hpp"

static constexpr int32_t FIELD_W = 480;
static constexpr int32_t FIELD_H = 416;

static const Rectangle GridRect(0, 0, RelCoordinates::GRID_RECT_H_NUMB, RelCoordinates::GRID_RECT_V_NUMB);
static RelCoordinates::GridData_t GridData;
static double Scale = 1.0;

AbsCoordinates::ImgCfg_t ImgCfg[GameConfig::IMG_ARRAY_SIZE]{};
AbsCoordinates::TextCfg_t TextCfg[GameConfig::TEXT_ARRAY_SIZE]{};

static Point scale_point(const Point & point) {
	return Geometry::scalePoint(point, Scale);
}

static int32_t scale(int32_t val) {
	return Geometry::scaleVal(val, Scale);
}

static int32_t getFieldScaledW() {
	return scale(FIELD_W);
}

static int32_t getFieldScaledH() {
	return scale(FIELD_H);
}

static const RelCoordinates::GridData_t & getGridData() {
	return GridData;
}

bool Layout::init(const DisplayMode::Mode_t & display_mode) {
	assert(0 < display_mode.m_H);
	assert(0 < display_mode.m_W);
	const double h_scale = display_mode.m_H / static_cast<double>(display_mode.m_DefH);
	const double v_scale = display_mode.m_W / static_cast<double>(display_mode.m_DefW);
	Scale = v_scale;
	if(h_scale < v_scale) {
		Scale = h_scale;
	}
	const auto grid_size = AbsCoordinates::GRID_SIZE * Scale;
	const int32_t grid_size_less = static_cast<int32_t>(std::floor(grid_size)) & ~1;
	Scale -= (grid_size - grid_size_less)/static_cast<double>(AbsCoordinates::GRID_SIZE);

	const int32_t y_offset = (display_mode.m_H - scale(display_mode.m_DefH))/2;
	const int32_t x_offset = (display_mode.m_W - scale(display_mode.m_DefW))/2;

	for(std::size_t i = 0; GameConfig::IMG_ARRAY_SIZE > i; ++i) {
		const auto & src = AbsCoordinates::ImgCfg[i];
		ImgCfg[i] = src;
		ImgCfg[i].m_Pos = scale_point(src.m_Pos);
		ImgCfg[i].m_Pos.move(x_offset, y_offset);
	}
	for(std::size_t i = 0; GameConfig::TEXT_ARRAY_SIZE > i; ++i) {
		const auto & src = AbsCoordinates::TextCfg[i];
		TextCfg[i] = src;
		TextCfg[i].m_Pos = scale_point(src.m_Pos);
		TextCfg[i].m_Pos.move(x_offset, y_offset);
	}

	Point cross_point = ImgCfg[GameConfig::IMG_GRID_INDX].m_Pos;
	Point rol_start_point = cross_point.move(scale(AbsCoordinates::GRID_SIZE/2)
										   , scale(AbsCoordinates::GRID_SIZE/2));
	for(size_t rol_indx = 0; RelCoordinates::GRID_RECT_V_NUMB > rol_indx; ++rol_indx) {
		auto & row_data = GridData[rol_indx];
		for(size_t col_indx = 0; RelCoordinates::GRID_RECT_H_NUMB > col_indx; ++col_indx) {
			auto type = RelCoordinates::GridNeighborhood[rol_indx][col_indx];
			row_data[col_indx].m_NB_Mask = type;
			row_data[col_indx].m_Pos = cross_point;
			cross_point.move(scale(AbsCoordinates::GRID_SIZE), 0);
		}
		rol_start_point.move(0, scale(AbsCoordinates::GRID_SIZE));
		cross_point = rol_start_point;
	}
	return true;
}

double Layout::getScaleFactor() {
	return Scale;
}

const AbsCoordinates::ImgCfg_t * Layout::getImgData(std::size_t id) {
	if(GameConfig::IMG_ARRAY_SIZE > id) {
		return ImgCfg + id;
	}
	return nullptr;
}

const AbsCoordinates::TextCfg_t * Layout::getTextData(std::size_t id) {
	if(GameConfig::IMG_ARRAY_SIZE > id) {
		return TextCfg + id;
	}
	return nullptr;
}

const RelCoordinates::GridDataEntity_t* Layout::getGridDataEntity(const Point& rel) {
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
		return Points::UNDEFINED;
	}
	return p_data->m_Pos;
}

uint32_t Layout::getGridSize() {
	return static_cast<uint32_t>(std::round(AbsCoordinates::GRID_SIZE*Scale));
}

const Point & Layout::getShipRelPos() {
	return RelCoordinates::POS_SHIP_REL;
}

const Point * Layout::getBonusRelPosDis() {
	return RelCoordinates::BonusPosDis.data();
}

const Point * Layout::getBonusRelPosEna() {
	return RelCoordinates::BonusPosEna.data();
}

const Point & Layout::getEnemyRelPos(std::size_t id) {
	if(!(static_cast<std::size_t>(EnemyId_t::ENEMY_NUMB) > id)) {
		return Points::UNDEFINED;
	}
	return RelCoordinates::EnemyPos[id];
}

Rectangle Layout::getArenaRectangle() {
	return Rectangle(ImgCfg[GameConfig::IMG_GRID_INDX].m_Pos, getFieldScaledW(), getFieldScaledH());
}

Rectangle Layout::getMotionArea() {
	Rectangle motion_rect;
	const auto up_left_p = getRel2AbsPosition({2,2});
	const auto down_right_p = getRel2AbsPosition({12,10});
	motion_rect.m_Pos = up_left_p;
	motion_rect.m_W = down_right_p.m_X - up_left_p.m_X;
	motion_rect.m_H = down_right_p.m_Y - up_left_p.m_Y;
	return motion_rect;
}
