/*
 * EnemyCtrl.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_ENEMYCTRL_HPP_
#define GAME_GAMEPLAY_ENEMYCTRL_HPP_

#include <vector>
#include "utils/RandomNumber.hpp"

class Widget;
class EnemyContainer;
class Point;
enum class Action_t : uint8_t;

class EnemyCtrl {
public:
	bool init();
	void reset();
	void processing(const std::vector<Widget *> & enemies, const std::vector<Widget *> & target,
			const std::vector<std::vector<Widget *>> & ship2ship);

private:
	int32_t m_X_OUT = 0;
	RandomNumber m_RandomNumber;

	bool resolveShip2ShipCollision(const std::vector<std::vector<Widget *>> & ship2ship);
	Action_t getMove(bool h_move, const Point & target) const;
	Action_t getMoveOut(const Point & pos, bool back) const;
	Action_t getFire(const Point & target) const;
	Action_t maskFireAction(Action_t fire, const Point & pos) const;
	bool isActive(Widget * enemy) const;
	std::size_t getEnemiesOnFields(const std::vector<Widget *> & enemies) const;
};

#endif /* GAME_GAMEPLAY_ENEMYCTRL_HPP_ */
