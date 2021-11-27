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

#include "game/gameplay/CollisionDetect.hpp"
#include "game/gameplay/CD_Through.hpp"
#include "game/gameplay/CollitionMgr.hpp"


class InputEvent;
class InputEventIF;

class Game {
public:
	bool init(const GameConfig::Config_t & cfg);
	bool events(const InputEvent & event, bool & exit);
	bool draw();
	bool new_frame();
	bool processing();

private:
	static const uint32_t REFRESH_RATE;
	static const uint32_t MOTION_PERIOD;

	double m_Scale = 1;

	FPS m_FPS;

	std::array<Image, GameConfig::IMG_ARRAY_SIZE> m_Img;
	std::array<Text, GameConfig::TEXT_ARRAY_SIZE> m_Text;
	std::vector<InputEventIF*> m_InputEvetntContainer;

	Ship m_Ship;
	Ammunition m_Ammunition;
	Bonuses m_Bonuses;

	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;
	uint32_t m_KeysMaskHold = 0;
	std::size_t m_StartPressCounter = 0;

	Timer2Client m_RefreshTimer;
	Timer2Client m_MotionTimer;

	CollitionMgr m_CollitionMgr;

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

	void onCB_Ammun(const std::vector<const Widget *> data);
	void onCB_Bonus(const std::vector<const Widget *> data);
	void onCB_Ship(const std::vector<const Widget *> data);
	void onCB_Enemy(const std::vector<const Widget *> data);
};

#endif /* GAME_GAME_HPP_ */
