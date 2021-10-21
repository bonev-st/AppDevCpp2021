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

namespace GameConfig {
enum KeyMask_t : std::uint32_t {
	KEY_EXIT_MASK 			= 1u << 0,
	KEY_UP_MASK 			= 1u << 1,
	KEY_DOWN_MASK 			= 1u << 2,
	KEY_LEFT_MASK 			= 1u << 3,
	KEY_RIGHT_MASK 			= 1u << 4,
	KEY_MOVE_UP_MASK 		= 1u << 5,
	KEY_MOVE_DOWN_MASK 		= 1u << 6,
	KEY_MOVE_LEFT_MASK 		= 1u << 7,
	KEY_MOVE_RIGHT_MASK 	= 1u << 8,
	KEY_ZOOM_UP_MASK 		= 1u << 9,
	KEY_ZOOM_DOWN_MASK 		= 1u << 10,
	KEY_OPACITY_UP_MASK		= 1u << 11,
	KEY_OPACITY_DOWN_MASK	= 1u << 12,
};

typedef Keyboard::Key Key;
typedef std::unordered_map<Key, KeyMask_t>  KeyRes_t;

struct Config_t {
	KeyRes_t m_Keys;
};

}

#endif /* GAME_GAMECONFIG_HPP_ */
