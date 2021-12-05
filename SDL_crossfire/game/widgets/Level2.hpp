/*
 * Level2.hpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_LEVEL2_HPP_
#define GAME_WIDGETS_LEVEL2_HPP_

#include "gr_engine/widgets/WidgetContainer.hpp"
#include "gr_engine/widgets/InitHelper.hpp"
#include "game/config/GameConfig.hpp"

namespace DisplayMode {
struct Mode_t;
}

class Level2 {
public:
	bool init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode);

	void draw();

	bool setScore(uint32_t val);
	bool setScoreMax(uint32_t val);
	bool setShips(uint8_t val);

private:
	WidgetContainer m_Container;
	InitHelper::TextData_t m_TextScore;
	InitHelper::TextData_t m_TextHiScore;
	InitHelper::TextData_t m_TextShips;

	bool initTexts(const GameConfig::TextRes_t & cfg);
};

#endif /* GAME_WIDGETS_LEVEL2_HPP_ */
