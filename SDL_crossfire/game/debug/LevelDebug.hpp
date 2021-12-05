/*
 * Debug.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GAME_DEBUG_LEVELDEBUG_HPP_
#define GAME_DEBUG_LEVELDEBUG_HPP_

#include "gr_engine/timer/Timer2Client.hpp"
#include "gr_engine/widgets/WidgetContainer.hpp"
#include "gr_engine/widgets/InitHelper.hpp"
#include "game/config/GameConfig.hpp"
#include "game/debug/FPS.hpp"

namespace DisplayMode {
struct Mode_t;
}

class LevelDebug {
public:
	bool init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode);
	void newFrame();
	void draw();
	bool enable();
	void disable();

private:
	static const uint32_t REFRESH_RATE;

	FPS m_FPS;
	Timer2Client m_RefreshTimer;
	WidgetContainer m_Container;
	InitHelper::TextData_t m_TextFPS;
	InitHelper::TextData_t m_TextActiveTim;
	InitHelper::TextData_t m_TextMaxTim;

	bool initTexts(const GameConfig::TextRes_t & cfg);
	bool setFPS(double val);
	bool setActiveTim(std::size_t val);
	bool setMaxTim(std::size_t val);

	void onDebugRefresh(Timer2::TimerHandler_t handler);
};
#endif /* GAME_DEBUG_LEVELDEBUG_HPP_ */
