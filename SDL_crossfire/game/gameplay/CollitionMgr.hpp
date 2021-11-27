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
	bool init(Callback_t cb_ammu, Callback_t cb_bonus, Callback_t cb_ship, Callback_t cb_enemy);

	void addUnits(const Widget* ship, const std::vector<const Widget*> & enemy);
	void addBonus(const Widget* bonus);
	void removeBonus(const Widget* bonus);
	void addAmmun(const Widget* ammun);
	void removeAmmun(const Widget* ammun);

	void addBulletShipColl(Widget* bullet);
	void addBulletEnemyColl(Widget* bullet);

	void processing();

private:
	const Widget* m_Ship;
	std::vector<const Widget*> m_Enemy;

	CollisionDetect::Callback_t m_CB_AmmunitionColl;
	CollisionDetect::Callback_t m_CB_BonusColl;
	CollisionDetect::Callback_t m_CB_ShipColl;
	CollisionDetect::Callback_t m_CB_EnemyColl;

	CD_Through m_ProcThrough;
	CD_Touch m_ProcTouch;

	CollisionDetect m_AmmunitionColl;
	CollisionDetect m_BonusColl;
	CollisionDetect m_ShipColl;
	CollisionDetect m_EnemyColl;

	std::vector<CollisionDetect *> m_Container;
};

#endif /* GAME_GAMEPLAY_COLLITIONMGR_HPP_ */
