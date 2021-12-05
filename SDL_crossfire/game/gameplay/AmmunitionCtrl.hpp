/*
 * AmmunitionCtrl.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_AMMUNITIONCTRL_HPP_
#define GAME_GAMEPLAY_AMMUNITIONCTRL_HPP_

#include <cstdint>

class AmmunitionCtrl {
public:
	bool operator ()(int32_t remain) const;
	operator int32_t () const;
};

#endif /* GAME_GAMEPLAY_AMMUNITIONCTRL_HPP_ */
