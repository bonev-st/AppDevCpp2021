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

class InputEvent;
struct DrawingParams_t;

class Game {
public:
	int32_t init(const GameConfig::Config_t & cfg);
	int32_t events(const InputEvent & event, bool & exit);
	int32_t draw(std::vector<DrawingParams_t> &out);

private:
	std::array<GameConfig::ImgDimetion_t, NUMB_IMG> m_ImgDimetion{};
	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;

	bool loadKeys(const GameConfig::KeyRes_t & cfg);
	bool loadImgDimenstion(const GameConfig::ImgDimetionRes_t & cfg);
	void setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask);
	bool exitRequest() const;
};

#endif /* GAME_GAME_HPP_ */
