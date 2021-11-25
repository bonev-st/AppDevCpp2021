/*
 * GameConfig.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMECONFIG_HPP_
#define GAME_GAMECONFIG_HPP_

#include <unordered_map>
#include <string>
#include <array>

#include "utils/inputs/EventDefines.h"

namespace GameConfig {
enum KeyMask_t : std::uint32_t {
	KEY_EXIT_MASK 			= 1u << 0,
	KEY_UP_MASK 			= 1u << 1,
	KEY_DOWN_MASK 			= 1u << 2,
	KEY_LEFT_MASK 			= 1u << 3,
	KEY_RIGHT_MASK 			= 1u << 4,
	KEY_FIRE_UP_MASK 		= 1u << 5,
	KEY_FIRE_DOWN_MASK 		= 1u << 6,
	KEY_FIRE_LEFT_MASK 		= 1u << 7,
	KEY_FIRE_RIGHT_MASK 	= 1u << 8,
	KEY_PAUSE_MASK 			= 1u << 9,
	KEY_INFO_MASK 			= 1u << 10,
	KEY_MENU_MASK 			= 1u << 11,
};

using Key = Keyboard::Key;
using KeyRes_t = std::unordered_map<Key, KeyMask_t>;

enum ImgIndx_t : uint32_t {
	IMG_BACKGROUND_INDX = 0,
	IMG_CROSSFIRE_INDX,
	IMG_GRID_BKGRND_INDX,
	IMG_GRID_INDX,
	IMG_SHIP_INDX,
	IMG_ENEMY1_INDX,
	IMG_ENEMY2_INDX,
	IMG_ENEMY3_INDX,
	IMG_ENEMY4_INDX,
	IMG_OWN_BULLED_INDX,
	IMG_ENEMY_BULLED_INDX,
	IMG_BONUS_INDX,
	IMG_AMMU_INDX,

	IMG_ARRAY_SIZE
};

using ImgRes_t = std::unordered_map<ImgIndx_t, std::size_t>;

enum TextIndx_t : uint32_t {
	TEXT_SCORE_LABLE_INDX = 0,
	TEXT_SCORE_INDX,
	TEXT_HI_SCORE_LABLE_INDX,
	TEXT_HI_SCORE_INDX,
	TEXT_SHIPS_LABLE_INDX,
	TEXT_SHIPS_INDX,

	TEXT_FPS_INDX,
	TEXT_ACTIVE_TIMER_INDX,
	TEXT_MAX_ACTIVE_TIMER_INDX,
	TEXT_ARRAY_SIZE
};

using TextRes_t = std::unordered_map<TextIndx_t, std::size_t>;

struct Config_t {
	KeyRes_t m_Keys;
	ImgRes_t m_Img;
	TextRes_t m_Text;
};

}

#endif /* GAME_GAMECONFIG_HPP_ */
