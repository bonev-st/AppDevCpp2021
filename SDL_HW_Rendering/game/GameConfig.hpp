/*
 * GameConfig.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMECONFIG_HPP_
#define GAME_GAMECONFIG_HPP_

#include <unordered_map>

#include "utils/inputs/EventDefines.h"

namespace GameBase {
enum ImgId_t {
	IDLE_IMG,
	UP_IMG,
	DOWN_IMG,
	LEFT_IMG,
	RIGHT_IMG,
	L2_IMG,
	NUMB_IMG
};

enum KeyMask_t : std::uint32_t {
	KEY_EXIT_MASK 	= 1u << 0,
	KEY_UP_MASK 	= 1u << 1,
	KEY_DOWN_MASK 	= 1u << 2,
	KEY_LEFT_MASK 	= 1u << 3,
	KEY_RIGHT_MASK 	= 1u << 4,
};

typedef Keyboard::Key Key;
typedef std::unordered_map<ImgId_t, std::string>  ImgRes_t;
typedef std::unordered_map<Key, KeyMask_t>  KeyRes_t;

struct GameConfig {
	ImgRes_t ImgPath;
	KeyRes_t Keys;
};
}

#endif /* GAME_GAMECONFIG_HPP_ */
