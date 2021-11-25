/*
 * CollisionDetectMgr.hpp
 *
 *  Created on: Nov 23, 2021
 *      Author: stanimir
 */

#ifndef GAME_MANAGERS_COLLISIONDETECTMGR_HPP_
#define GAME_MANAGERS_COLLISIONDETECTMGR_HPP_

#include "utils/Singleton.hpp"

#include "manager_utils/managers/BaseMgr.hpp"

class CollisionDetectMgr : BaseMgr {
public:

};

using CollisionDetectMgrInst = Singleton<CollisionDetectMgr>;

#endif /* GAME_MANAGERS_COLLISIONDETECTMGR_HPP_ */
