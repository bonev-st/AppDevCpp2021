/*
 * Game.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include <array>
#include <vector>
#include <functional>

#include "gr_engine/timer/Timer2Client.hpp"
#include "game/config/GameConfig.hpp"
#include "game/widgets/Level1.hpp"
#include "game/widgets/Level2.hpp"
#include "game/widgets/TopLevel.hpp"
#include "game/debug/LevelDebug.hpp"

class InputEvent;
class InputEventIF;
namespace DisplayMode {
struct Mode_t;
}

class Game {
public:
	bool init(const GameConfig::Config_t & cfg, const DisplayMode::Mode_t & display_mode);
	bool events(const InputEvent & event, bool & exit);
	bool draw();
	bool new_frame();
	bool processing();

private:
	static const uint32_t MOTION_PERIOD;

	Background m_Background;
	Level1	m_L1;
	Level2	m_L2;
	TopLevel m_L_Top;
	LevelDebug m_Debug;


	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;

	Timer2Client m_MotionTimer;

	void newGame();
	void newMission();
	void gameOver();

	bool loadKeys(const GameConfig::KeyRes_t & cfg);
	bool initTimers();
	bool initWidgets(const DisplayMode::Mode_t & display_mode, const GameConfig::ImgRes_t & cfg);

	void setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask);
	bool exitRequest() const;

	void onMotion_Timeout(Timer2::TimerHandler_t handler);
};

#endif /* GAME_GAME_HPP_ */
