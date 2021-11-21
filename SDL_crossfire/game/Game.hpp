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

#include "game/widgets/AnimatedImage.hpp"
#include "game/widgets/FPS.hpp"

#include "game/action/UnitAction.hpp"

class InputEvent;
class InputEventIF;

class Game {
public:
	bool init(const GameConfig::Config_t & cfg);
	bool events(const InputEvent & event, bool & exit);
	bool draw() const;
	bool new_frame();

private:
	static const uint32_t REFRESH_RATE;
	static const uint32_t MOTION_PERIOD;

	FPS m_FPS;

	std::array<Image, GameConfig::IMG_ARRAY_SIZE> m_Img;
	std::array<Text, GameConfig::TEXT_ARRAY_SIZE> m_Text;
	std::vector<InputEventIF*> m_InputEvetntContainer;

	AnimatedImage m_Ship;
	UnitAction m_ShipAction;

	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;
	uint32_t m_KeysMaskHold = 0;
	std::size_t m_StartPressCounter = 0;

	Timer2Client m_RefreshTimer;
	Timer2Client m_MotionTimer;

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
};

#endif /* GAME_GAME_HPP_ */
