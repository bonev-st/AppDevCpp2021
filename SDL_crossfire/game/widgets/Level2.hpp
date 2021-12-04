/*
 * Level2.hpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_LEVEL2_HPP_
#define GAME_WIDGETS_LEVEL2_HPP_

#include "game/config/GameConfig.hpp"

#include "game/widgets/WidgetContainer.hpp"
#include "game/widgets/InitHelper.hpp"

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
	bool setFPS(double val);
	bool setActiveTim(std::size_t val);
	bool setMaxTim(std::size_t val);

private:
	WidgetContainer m_Container;
	InitHelper::TextData_t m_TextScore;
	InitHelper::TextData_t m_TextHiScore;
	InitHelper::TextData_t m_TextShips;
	InitHelper::TextData_t m_TextFPS;
	InitHelper::TextData_t m_TextActiveTim;
	InitHelper::TextData_t m_TextMaxTim;

	bool initTexts(const GameConfig::TextRes_t & cfg);
};

#endif /* GAME_WIDGETS_LEVEL2_HPP_ */
