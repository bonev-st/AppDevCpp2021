/*
 * Level1.hpp
 *
 *  Created on: Dec 4, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_LEVEL1_HPP_
#define GAME_WIDGETS_LEVEL1_HPP_

#include "game/config/GameConfig.hpp"

#include "game/widgets/WidgetContainer.hpp"
#include "game/widgets/InitHelper.hpp"

namespace DisplayMode {
struct Mode_t;
}

class Level1 {
public:
	bool init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode);

	void draw();

private:
	WidgetContainer m_Container;
	InitHelper::ImageData_t m_ImgCrossfire;
	InitHelper::ImageData_t m_ImgGrid;
	InitHelper::TextData_t m_TextScore;
	InitHelper::TextData_t m_TextHiScore;
	InitHelper::TextData_t m_TextShips;

	bool initImages(const GameConfig::ImgRes_t & cfg);
	bool initTexts(const GameConfig::TextRes_t & cfg);
};

#endif /* GAME_WIDGETS_LEVEL1_HPP_ */
