/*
 * EnemyCtrl.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_ENEMYCTRL_HPP_
#define GAME_GAMEPLAY_ENEMYCTRL_HPP_

#include <vector>

class EnemyContainer;

class EnemyCtrl {
public:
	bool init();
	void reset();
	void processing(EnemyContainer & enemies);

private:
	enum class State_t {
		IDLE = 0,
		REFUGE,
		BATTLEFIELD,
		KILLED
	};

	std::vector<State_t> m_State;
};

#endif /* GAME_GAMEPLAY_ENEMYCTRL_HPP_ */
