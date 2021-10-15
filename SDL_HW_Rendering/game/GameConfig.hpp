/*
 * GameConfig.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMECONFIG_HPP_
#define GAME_GAMECONFIG_HPP_

#include <unordered_map>

typedef enum _ImgId_t {
	IDLE_IMG,
	UP_IMG,
	DOWN_IMG,
	LEFT_IMG,
	RIGHT_IMG,
	NUMB_IMG
} ImgId_t;

struct GameConfig {
	std::unordered_map<ImgId_t, std::string> ImgPath;
};


#endif /* GAME_GAMECONFIG_HPP_ */
