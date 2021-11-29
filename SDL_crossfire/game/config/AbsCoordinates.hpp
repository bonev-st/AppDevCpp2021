/*
 * AbsCoordinates.hpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#ifndef GAME_CONFIG_ABSCOORDINATES_HPP_
#define GAME_CONFIG_ABSCOORDINATES_HPP_

#include "utils/drawing/Point.hpp"
#include "utils/drawing/Color.hpp"

namespace AbsCoordinates {
struct TextCfg_t {
	Point m_Pos;
	Color m_Color;
	const char * m_Text;
};

struct ImgCfg_t {
	Point m_Pos;
	uint8_t m_Alpha;
};

static constexpr int32_t GRID_SIZE = 32;
} /* namespace AbsCoordinates */

#endif /* GAME_CONFIG_ABSCOORDINATES_HPP_ */
