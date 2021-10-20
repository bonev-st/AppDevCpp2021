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
	KEY_EXIT_MASK 	= 1u << 0,
	KEY_UP_MASK 	= 1u << 1,
	KEY_DOWN_MASK 	= 1u << 2,
	KEY_LEFT_MASK 	= 1u << 3,
	KEY_RIGHT_MASK 	= 1u << 4,
};

struct ImgDimetion_t {
	std::int32_t m_W = 0;
	std::int32_t m_H = 0;
};

typedef Keyboard::Key Key;
typedef std::unordered_map<Key, KeyMask_t>  KeyRes_t;
typedef std::unordered_map<uint32_t, ImgDimetion_t>  ImgDimetionRes_t;

struct Config_t {
	ImgDimetionRes_t m_ImgDimention;
	KeyRes_t m_Keys;
};

}

#endif /* GAME_GAMECONFIG_HPP_ */
