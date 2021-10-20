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
class Rectangle;
struct DrawingParams_t;

class Game {
public:
	bool init(const GameConfig::Config_t & cfg);
	bool events(const InputEvent & event, bool & exit);
	bool draw(std::vector<DrawingParams_t> &out);

private:
	std::array<GameConfig::ImgDimetion_t, NUMB_IMG> m_ImgDimetion{};
	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;

	bool loadKeys(const GameConfig::KeyRes_t & cfg);
	bool loadImgDimenstion(const GameConfig::ImgDimetionRes_t & cfg);
	void setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask);
	bool exitRequest() const;
	Rectangle getImgDimension(int32_t id) const;
};

#endif /* GAME_GAME_HPP_ */
