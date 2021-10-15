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

#include "game/GameConfig.hpp"

class SDL_Surface;
class InputEvent;
class EventReg_IF;

class Game {
public:
	Game();
	~Game();

	int32_t init(const GameConfig& cfg, EventReg_IF& even);
	int32_t draw(std::vector<SDL_Surface *> &out);
	int32_t handleEvent();

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
	int32_t registeringEvents(EventReg_IF & event);
	void setKeyRequest(bool pressed, KeyMask_t key_mask);
};

#endif /* GAME_GAME_HPP_ */
