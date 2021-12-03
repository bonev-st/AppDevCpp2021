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

#include "game/config/GameConfig.hpp"
#include "manager_utils/managers/BaseMgr.hpp"
#include "manager_utils/drawing/Image.hpp"
#include "manager_utils/drawing/Text.hpp"
#include "manager_utils/input/RadioContainer.hpp"
#include "manager_utils/timer/Timer2Client.hpp"

#include "game/widgets/FPS.hpp"
#include "game/widgets/Ship.hpp"
#include "game/widgets/Ammunition.hpp"
#include "game/widgets/ScaleTexture.hpp"
#include "game/widgets/Bonuses.hpp"
#include "game/widgets/WidgetContainer.hpp"
#include "game/widgets/Background.hpp"
#include "game/widgets/GridPoint.hpp"
#include "game/widgets/ExplosionContainer.hpp"
#include "game/widgets/EnemyContainer.hpp"

#include "game/gameplay/CollisionDetect.hpp"
#include "game/gameplay/CD_Through.hpp"
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

	WidgetContainer m_L1;
	Image m_BackgroundFieldImageL1;
	ScaleTexture m_ScaledBackgroundFieldImageL1;
	Image m_CrossfireImageL1;
	ScaleTexture m_ScaledCrossfireImageL1;
	Image m_GridImageL1;
	ScaleTexture m_ScaledGridImageL1;

	Text m_TextScoreLableL1;
	ScaleTexture m_ScaledTextScoreLableL1;
	Text m_TextHiScoreLableL1;
	ScaleTexture m_ScaledTextHiScoreLableL1;
	Text m_TextShipsLableL1;
	ScaleTexture m_ScaledTextShipsLableL1;

	WidgetContainer m_L2;
	Text m_TextScoreL2;
	ScaleTexture m_ScaledTextScoreL2;
	Text m_TextHiScoreL2;
	ScaleTexture m_ScaledTextHiScoreL2;
	Text m_TextShipsL2;
	ScaleTexture m_ScaledTextShipsL2;

	Text m_TextFPSL2;
	ScaleTexture m_ScaledTextFPSL2;
	Text m_TextActiveTimL2;
	ScaleTexture m_ScaledTextActiveTimL2;
	Text m_TextMaxTimL2;
	ScaleTexture m_ScaledTextMaxTimL2;

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

	GridPoint m_GridPoint;

	bool loadKeys(const GameConfig::KeyRes_t & cfg);
	bool createImages(const GameConfig::ImgRes_t & cfg);
	bool createTexts(const GameConfig::TextRes_t & cfg);
	bool initButtons();
	bool initInput();
	bool initTimers();

	void setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask);
	bool exitRequest() const;

	void onFPS_Timeout(Timer2::TimerHandler_t handler);
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
