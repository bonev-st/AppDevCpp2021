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

#include "manager_utils/timer/Timer2Client.hpp"

#include "game/config/GameConfig.hpp"
#include "game/widgets/Level1.hpp"
#include "game/widgets/Level2.hpp"
#include "game/widgets/FPS.hpp"
#include "game/widgets/Ship.hpp"
#include "game/widgets/Ammunition.hpp"
#include "game/widgets/Bonuses.hpp"
#include "game/widgets/WidgetContainer.hpp"
#include "game/widgets/Background.hpp"
#ifdef DEBUG
#include "game/widgets/GridPoint.hpp"
#endif
#include "game/widgets/ExplosionContainer.hpp"
#include "game/widgets/EnemyContainer.hpp"
#include "game/gameplay/CollitionMgr.hpp"

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
	static const uint32_t REFRESH_RATE;
	static const uint32_t MOTION_PERIOD;

	FPS m_FPS;

	Background m_Background;
	Level1	m_L1;
	Level2	m_L2;

	Ship m_Ship;
	EnemyContainer m_Enemies;
	Ammunition m_Ammunition;
	Bonuses m_Bonuses;
	ExplosionContainer m_ExplosionContainer;

	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;
	uint32_t m_KeysMaskHold = 0;
	std::size_t m_StartPressCounter = 0;

	Timer2Client m_RefreshTimer;
	Timer2Client m_MotionTimer;

	CollitionMgr m_CollitionMgr;

#ifdef DEBUG
	GridPoint m_GridPoint;
#endif

	bool loadKeys(const GameConfig::KeyRes_t & cfg);
	bool initButtons();
	bool initInput();
	bool initTimers();
	bool initWidgets(const DisplayMode::Mode_t & display_mode, const GameConfig::ImgRes_t & cfg);

	void setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask);
	bool exitRequest() const;

	void onDebugRefresh(Timer2::TimerHandler_t handler);
	void onMotion_Timeout(Timer2::TimerHandler_t handler);

	void onShipFire(const Point &pos, int8_t rem);

	void onCB_Ammun(const std::vector<Widget *> &data);
	void onCB_Bonus(const std::vector<Widget *> &data);
	void onCB_Ship(const std::vector<Widget *> &data);
	void onCB_Enemy(const std::vector<Widget *> &data);
	void onCB_Ship2Ship(const std::vector<Widget *> &data);

	void onAnimation0(Widget * data);
};

#endif /* GAME_GAME_HPP_ */
