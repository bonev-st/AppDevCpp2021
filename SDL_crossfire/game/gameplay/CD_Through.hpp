/*
 * CPThrough.hpp
 *
 *  Created on: Nov 23, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_CD_THROUGH_HPP_
#define GAME_GAMEPLAY_CD_THROUGH_HPP_

#include "game/gameplay/ProcessorIF.hpp"
#include "utils/drawing/Rectangle.hpp"

class CD_Through : public ProcessorIF {
public:
	bool init(const Rectangle & tolerance);

private:
	Rectangle m_Tolerance;

	std::vector<Widget*> operator ()(Widget* obj, const std::vector<Widget *> & others) const final;
};

#endif /* GAME_GAMEPLAY_CD_THROUGH_HPP_ */
