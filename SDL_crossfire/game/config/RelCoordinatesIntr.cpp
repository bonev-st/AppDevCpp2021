/*
 * RelCoordinates.cpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#include "game/config/RelCoordinatesIntr.hpp"

namespace RelCoordinates {

const Point POS_SHIP_REL{8, 10};

const std::array<Point, static_cast<size_t>(BonusId_t::BONUS_NUMB)> BonusPosDis = {
	Point{5, 7},
	Point{9, 7},
	Point{9, 5},
	Point{5, 5}
};

const std::array<Point, static_cast<size_t>(BonusId_t::BONUS_NUMB)> BonusPosEna = {
	Point{5, 8},
	Point{9, 8},
	Point{9, 4},
	Point{5, 4}
};

const std::array<Point, static_cast<size_t>(EnemyId_t::ENEMY_NUMB)> EnemyPos = {
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

const GridNeighborhoodData_t GridNeighborhood = {{
	//0
	{
		NONE,
		NONE,
		DOWN | RIGHT,
		LEFT,
		DOWN | RIGHT,
		LEFT,
		DOWN | RIGHT,
		LEFT,
		DOWN | RIGHT,
		LEFT,
		DOWN | RIGHT,
		LEFT,
		DOWN | RIGHT,
		LEFT,
		NONE
	},
	//1
	{
		NONE,
		NONE,
		DOWN,
		NONE,
		DOWN,
		NONE,
		DOWN,
		NONE,
		DOWN,
		NONE,
		DOWN,
		NONE,
		DOWN,
		NONE,
		NONE
	},
	//2
	{
		RIGHT | DOWN,
		RIGHT,
		DOWN | RIGHT,
		LEFT | RIGHT,
		DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		DOWN | LEFT,
		NONE,
		NONE
	},
	//3
	{
		UP,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		NONE
	},
	//4
	{
		NONE,
		NONE,
		UP | DOWN | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT,
		LEFT,
		LEFT | DOWN
	},
	//5
	{
		NONE,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP
	},
	//6
	{
		DOWN | RIGHT,
		RIGHT,
		UP | DOWN | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT,
		NONE,
		NONE
	},
	//7
	{
		UP,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		NONE
	},
	//8
	{
		NONE,
		NONE,
		UP | DOWN | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | DOWN | LEFT,
		LEFT,
		LEFT | DOWN
	},
	//9
	{
		NONE,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP | DOWN,
		NONE,
		UP
	},
	//10
	{
		DOWN | RIGHT,
		RIGHT,
		UP | RIGHT,
		LEFT | RIGHT,
		UP | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | LEFT | RIGHT,
		LEFT | RIGHT,
		UP | LEFT,
		NONE,
		NONE
	},
	//11
	{
		UP,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE,
		NONE
	},
}};

} /* namespace RelCoordinates */
