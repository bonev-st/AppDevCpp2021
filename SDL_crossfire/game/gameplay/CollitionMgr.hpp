/*
 * CollitionMgr.h
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_COLLITIONMGR_HPP_
#define GAME_GAMEPLAY_COLLITIONMGR_HPP_

#include <vector>

#include "game/gameplay/CollisionDetect.hpp"
#include "game/gameplay/CD_Through.hpp"
#include "game/gameplay/CD_Touch.hpp"

class CollitionMgr {
	using Callback_t = CollisionDetect::Callback_t;
public:
	bool init(Callback_t cb_ammu, Callback_t cb_bonus, Callback_t cb_ship,
			Callback_t cb_enemy, Callback_t cb_ship_2_ship);

	void processing(const std::vector<Widget*> & ship,
					const std::vector<Widget*> & own_bullets,
					const std::vector<Widget*> & enemy_bullets,
					const std::vector<Widget*> & enemy,
					const std::vector<Widget*> & bonuses,
					const std::vector<Widget*> & ammunition);

private:
	CollisionDetect::Callback_t m_CB_AmmunitionColl;
	CollisionDetect::Callback_t m_CB_BonusColl;
	CollisionDetect::Callback_t m_CB_ShipColl;
	CollisionDetect::Callback_t m_CB_EnemyColl;
	CollisionDetect::Callback_t m_CB_Ship2Ship;

	CD_Through m_ProcThrough;
	CD_Touch m_ProcTouch;

	CollisionDetect m_AmmunitionColl;
	CollisionDetect m_BonusColl;
	CollisionDetect m_Ship2ShipColl;
	CollisionDetect m_Ship2BulletColl;
	CollisionDetect m_Enemy2BulletColl;
};

#endif /* GAME_GAMEPLAY_COLLITIONMGR_HPP_ */
