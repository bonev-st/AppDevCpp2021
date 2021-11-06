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

#include "game/config/GameConfig.hpp"
#include "manager_utils/drawing/Image.hpp"
#include "manager_utils/drawing/Text.hpp"
#include "manager_utils/input/RadioContainer.hpp"

#include "widgets/Hero.hpp"
#include "widgets/Button.hpp"
#include "widgets/RadioButton.hpp"
#include "widgets/ToggleButton.hpp"
#include <functional>

class InputEvent;

class Game {
public:
	bool init(const GameConfig::Config_t & cfg);
	bool events(const InputEvent & event, bool & exit);
	bool draw() const;
	bool process();

private:
	enum ButtonIndx_t {
		BTN_RADIO_START_INDX = 0,
		BTN_RADIO_STOP_INDX,
		BTN_RADIO_STOP_DISABLED_INDX,
		BTN_RADIO_START_HIDDEN_INDX,

		BTN_START_INDX,
		BTN_STOP_DISABLED_INDX,

		BTN_TOGGLE_START_INDX,
		BTN_TOGGLE_STOP_DISABLED_INDX,
		BTN_ARRAY_SIZE
	};

	enum ImgIndx_t {
		IMG_WHEEL_INDX = 0,
		IMG_RUNNING_GIRL_BIG_INDX,
		IMG_RUNNING_GIRL_SMALL_INDX,
		IMG_START_BUTTON_INDX,
		IMG_STOP_BUTTON_INDX,

		IMG_ARRAY_SIZE
	};

	enum TextIndx_t {
		TEXT_HELLO_INDX = 0,
		TEXT_2_INDX,
		TEXT_3_INDX,
		TEXT_DYNAMIC_INDX,
		TEXT_BUTTON_INDX,

		TEXT_ARRAY_SIZE
	};

	static const int32_t MOVE_STEP = 1;

	Hero m_Hero;
	RadioContainer m_RadioGroup;
	RadioButton m_RadioButtonStart;
	RadioButton m_RadioButtonStop;
	RadioButton m_RadioButtonStopDisabled;
	RadioButton m_RadioButtonStartHidden;
	Button m_ButtonStart;
	Button m_ButtonStopDisabled;
	ToggleButton m_ToggleButtonStart;
	ToggleButton m_ToggleButtonStopDisabled;

	std::array<Image, IMG_ARRAY_SIZE> m_Img;
	std::array<Text, TEXT_ARRAY_SIZE> m_Text;

	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;
	uint32_t m_KeysMaskHold = 0;

	std::function<void(std::size_t)> m_ButtonCB;
	std::function<void(std::size_t, bool)> m_ToggleButtonCB;

	bool loadKeys(const GameConfig::KeyRes_t & cfg);
	bool initImgs();
	bool createTexts();
	bool initButtons();
	bool updateDynamicText();

	void setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask);
	bool exitRequest() const;

	void buttonHandler(std::size_t id);
	void toggleButtonHandler(std::size_t id, bool state);
};

#endif /* GAME_GAME_HPP_ */
