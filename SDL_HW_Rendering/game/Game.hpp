/*
 * Game.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include <array>
#include <memory>
#include <vector>

#include "utils/drawing/DrawingData.hpp"
#include "game/GameConfig.hpp"

class InputEvent;

class Game {
public:
	Game();
	~Game();

	int32_t init(const GameConfig& cfg);
	int32_t events(const InputEvent & event, bool & exit);
	int32_t draw(std::vector<DrawingData::Drawing_t> &out);

private:
	typedef enum _KeyMask_t : std::uint32_t {
		KEY_UP_MASK 	= 1u << 0,
		KEY_DOWN_MASK 	= 1u << 1,
		KEY_LEFT_MASK 	= 1u << 2,
		KEY_RIGHT_MASK 	= 1u << 3,
	} KeyMask_t;


	std::array<std::shared_ptr<SDL_Surface>, NUMB_IMG> m_Image;
	uint32_t m_KeysMask = 0;

	int32_t loadResources(const std::unordered_map<ImgId_t, std::string> & cfg);
	void setKeyRequest(bool pressed, KeyMask_t key_mask);
	bool exitRequest(const InputEvent & event);
};

#endif /* GAME_GAME_HPP_ */
