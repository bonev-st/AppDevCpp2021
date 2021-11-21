/*
 * ActionClientIF.hpp
 *
 *  Created on: Nov 20, 2021
 *      Author: stanimir
 */

#ifndef GAME_ACTION_ACTIONCLIENTIF_HPP_
#define GAME_ACTION_ACTIONCLIENTIF_HPP_

#include <cstdint>
#include "game/action/ActionDef.hpp"

class ActionClientIF {
public:
	virtual ~ActionClientIF() = default;
	virtual bool process(Action_t action, bool cross_point = false) = 0;
};


#endif /* GAME_ACTION_ACTIONCLIENT_HPP_ */
