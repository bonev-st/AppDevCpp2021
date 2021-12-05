/*
 * LayoutMain.hpp
 *
 *  Created on: Nov 18, 2021
 *      Author: stanimir
 */

#ifndef GAME_CONFIG_LAYOUT_HPP_
#define GAME_CONFIG_LAYOUT_HPP_

#include "game/config/AbsCoordinates.hpp"
#include "game/config/RelCoordinates.hpp"

struct Rectangle;
namespace DisplayMode {
struct Mode_t;
}

class Dimention;

namespace Layout {

bool init(const DisplayMode::Mode_t & display_mode);

double getScaleFactor();

const RelCoordinates::GridDataEntity_t* getGridDataEntity(const Point& rel);
Point getRel2AbsPosition(const Point& rel);

const AbsCoordinates::ImgCfg_t * getImgData(std::size_t id);
const AbsCoordinates::TextCfg_t * getTextData(std::size_t id);

uint32_t getGridSize();

const Point & getShipRelPos();
const Point * getBonusRelPosDis();
const Point * getBonusRelPosEna();
const Point & getEnemyRelPos(std::size_t id);

Rectangle getArenaRectangle();
Rectangle getMotionArea();

}

#endif /* GAME_CONFIG_LAYOUT_HPP_ */
