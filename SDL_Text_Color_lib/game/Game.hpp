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

class ImageContainer;
class TextContainer;
class InputEvent;
class Rectangle;

class Game {
public:
	bool init(const GameConfig::Config_t & cfg, const ImageContainer * img_if, TextContainer * text_if);
	bool events(const InputEvent & event, bool & exit);
	bool draw(std::vector<DrawParams_t> &out, bool &update);

private:
	static const int32_t MOVE_STEP = 1;

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
	std::array<DrawParams_t, IMG_ARRAY_SIZE> m_Img;
	std::array<DrawParams_t, TEXT_ARRAY_SIZE> m_Text;

	GameConfig::KeyRes_t m_Keys;
	uint32_t m_KeysMask = 0;
	uint32_t m_KeysMaskHold = 0;
	bool m_ForceUpdate = true;

	const ImageContainer *m_ImageContainerIF = nullptr;
	TextContainer *m_TextContainerIF = nullptr;

	bool loadKeys(const GameConfig::KeyRes_t & cfg);
	bool initImgs();
	bool loadImgDimention();
	bool createTexts();
	bool updateDynamicText(bool &update);

	void setKeyRequest(bool pressed, GameConfig::KeyMask_t key_mask);
	bool exitRequest() const;
};

#endif /* GAME_GAME_HPP_ */
