/*
 * Game.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include <memory>
#include <array>
#include <vector>

#include "sdl_utils/Texture.hpp"
#include "utils/drawing/DrawingData.hpp"
#include "game/GameConfig.hpp"

class InputEvent;
class SDL_Renderer;

class Game {
public:
	Game();
	~Game();

	int32_t init(const GameBase::GameConfig& cfg, std::shared_ptr<SDL_Renderer> renderer);
	int32_t events(const InputEvent & event, bool & exit);
	int32_t draw(std::vector<DrawingData::Drawing_t> &out);

private:
	std::array<std::shared_ptr<Texture::Texture_t>, GameBase::NUMB_IMG> m_Image;
	GameBase::KeyRes_t Keys;
	uint32_t m_KeysMask = 0;
	std::shared_ptr<SDL_Renderer> m_Renderer;

	int32_t loadResources(const GameBase::ImgRes_t & cfg);
	int32_t loadKeys(const GameBase::KeyRes_t & cfg);
	void setKeyRequest(bool pressed, GameBase::KeyMask_t key_mask);
	bool exitRequest() const;
};

#endif /* GAME_GAME_HPP_ */
