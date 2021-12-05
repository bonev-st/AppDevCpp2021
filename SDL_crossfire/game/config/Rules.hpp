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

	static constexpr std::int32_t BONUS_SHOW = 6; //11;
	static constexpr std::int32_t BONUS_HIDE = 6;

	static constexpr std::int32_t RELOAD_BULLETS = 10;

	static double getShipSpeed();
	static double getShipBulletSpeed();
	static double getEnemySpeed();
	static double getEnemyBulletSpeed();

	static int32_t getShipBulled();
	static uint32_t getShipReloadTime();

	static int32_t getEnemyBulled();
	static uint32_t getEnemyReloadTime();

	static void firstMission();
	static void nextMission();

private:
	static constexpr std::int32_t INITIAL_BULLETS = 35;
	static constexpr std::int32_t MIN_BULLETS = 15;
	static constexpr std::int32_t DECREASE_BULLETS = 5;
	static constexpr std::int32_t  ENEMY_MAX_BULLED = -1;
	static const double ENEMY_SPEED;
	static const double ENEMY_BULLET_SPEED;
	static const double SHIP_SPEED;
	static const double SHIP_BULLET_SPEED;
	static constexpr uint32_t OWN_RELOAD_TIME = 800;
	static constexpr uint32_t ENEMY_RELOAD_TIME = OWN_RELOAD_TIME/3;

	static uint32_t m_Mission;

	static double getSpeedIncrease();
};

#endif /* GAME_CONFIG_RULES_HPP_ */
