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
#include "game/gameplay/LifeCounter.hpp"
#include "game/gameplay/ScoreCouters.hpp"

namespace DisplayMode {
struct Mode_t;
}

class Level2 {
public:
	bool init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode);

	void draw();

	void resetCounters();
	void setPoints(uint32_t points);
	void decLife();
	bool isAlife() const;

private:
	WidgetContainer m_Container;
	InitHelper::TextData_t m_TextScore;
	InitHelper::TextData_t m_TextHiScore;
	InitHelper::TextData_t m_TextShips;
	LifeCounter m_LifeCounter;
	ScoreCouters m_ScoreCouters;

	bool initTexts(const GameConfig::TextRes_t & cfg);

	void setScore(uint32_t val);
	void setHiScore(uint32_t val);
	void setShips(uint32_t val);

};

#endif /* GAME_WIDGETS_LEVEL2_HPP_ */
