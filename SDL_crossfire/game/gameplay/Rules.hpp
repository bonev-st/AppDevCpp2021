/*
 * Rules.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GAME_CONFIG_RULES_HPP_
#define GAME_CONFIG_RULES_HPP_

#include <cstdint>

struct Rules {
	static constexpr std::uint32_t INITIAL_BULLETS = 35;
	static constexpr std::uint32_t MIN_BULLETS = 15;
	static constexpr std::uint32_t RELOAD_BULLETS = 10;
	static constexpr std::uint32_t DECREASE_BULLETS = 5;

	static constexpr std::uint32_t INITIAL_LIFES = 3;
	static constexpr std::uint32_t POINTS_FOR_NEW_LIFE = 5000;

	static constexpr std::uint32_t POINTS_BONUS1 = 100;
	static constexpr std::uint32_t POINTS_BONUS2 = 200;
	static constexpr std::uint32_t POINTS_BONUS3 = 400;
	static constexpr std::uint32_t POINTS_BONUS4 = 800;

	static constexpr std::uint32_t POINTS_ENEMY1 = 10;
	static constexpr std::uint32_t POINTS_ENEMY2 = 20;
	static constexpr std::uint32_t POINTS_ENEMY3 = 40;
	static constexpr std::uint32_t POINTS_ENEMY4 = 80;
};

#endif /* GAME_CONFIG_RULES_HPP_ */
