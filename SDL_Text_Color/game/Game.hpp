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

#include "config/GameConfig.hpp"
#include "common/CommonDefines.hpp"
#include "utils/drawing/DrawParams.hpp"

class InputEvent;
struct Rectangle;

class Game {
public:
	bool init(const GameConfig::Config_t & cfg);
	bool events(const InputEvent & event, bool & exit);
	bool draw(std::vector<DrawParams_t> &out);

private:
	static const int32_t MOVE_STEP = 1;
//	std::array<DrawParams_t, TextureId::NUMB_IMG> m_Img;
	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;

	bool loadKeys(const GameConfig::KeyRes_t & cfg);
	void setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask);
	bool exitRequest() const;
};

#endif /* GAME_GAME_HPP_ */
