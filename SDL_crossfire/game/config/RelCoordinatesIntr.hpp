/*
 * RelCoordinatesIntr.hpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#ifndef GAME_CONFIG_RELCOORDINATESINTR_HPP_
#define GAME_CONFIG_RELCOORDINATESINTR_HPP_

#include <array>
#include <cstddef>
#include "game/config/RelCoordinates.hpp"

namespace RelCoordinates {
extern const Point POS_SHIP_REL;
extern const std::array<Point, static_cast<std::size_t>(BonusId_t::BONUS_NUMB)> BonusPosDis;
extern const std::array<Point, static_cast<std::size_t>(BonusId_t::BONUS_NUMB)> BonusPosEna;
extern const std::array<Point, static_cast<std::size_t>(EnemyId_t::ENEMY_NUMB)> EnemyPos;
extern const GridNeighborhoodData_t GridNeighborhood;
} /* namespace RelCoordinates */

#endif /* GAME_CONFIG_RELCOORDINATES_HPP_ */
