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
#include "utils/drawing/DrawParams.hpp"

class InputEvent;

class Game {
public:
	bool init(const GameConfig::Config_t & cfg);
	bool events(const InputEvent & event, bool & exit);
	bool draw();

private:
	enum ImgIndx_t {
		IMG_BACKGROUND_INDX = 0,
		IMG_L2_INDX,

		IMG_ARRAY_SIZE
	};

	enum TextIndx_t {
		TEXT_HELLO_INDX = 0,
		TEXT_2_INDX,
		TEXT_3_INDX,
		TEXT_DYNAMIC_INDX,

		TEXT_ARRAY_SIZE
	};

	static const int32_t MOVE_STEP = 1;

	std::array<DrawParams_t, IMG_ARRAY_SIZE> m_Img;
	std::array<DrawParams_t, TEXT_ARRAY_SIZE> m_Text;

	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;
	uint32_t m_KeysMaskHold = 0;

	bool loadKeys(const GameConfig::KeyRes_t & cfg);
	bool initImgs();
	bool createTexts();
	bool updateDynamicText(bool &update);

	void setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask);
	bool exitRequest() const;
};

#endif /* GAME_GAME_HPP_ */
