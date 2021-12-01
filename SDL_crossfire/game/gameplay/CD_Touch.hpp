/*
 * CD_Touch.hpp
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_CD_TOUCH_HPP_
#define GAME_GAMEPLAY_CD_TOUCH_HPP_

#include "game/gameplay/ProcessorIF.hpp"

class CD_Touch : public ProcessorIF {
	std::vector<Widget*> operator ()(Widget* obj, const std::vector<Widget *> & others) const final;
};

#endif /* GAME_GAMEPLAY_CD_TOUCH_HPP_ */
