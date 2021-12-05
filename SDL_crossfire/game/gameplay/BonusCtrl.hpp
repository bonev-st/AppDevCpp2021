/*
 * BonusCtrl.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_BONUSCTRL_HPP_
#define GAME_GAMEPLAY_BONUSCTRL_HPP_

#include <cstdint>

enum class BonusId_t : uint8_t;

class BonusCtrl {
public:
	void reset();
	void kill();
	bool shoot();
	BonusId_t getIndx() const;
	uint32_t take();

private:
	bool m_Show = false;
	uint8_t m_Indx = 0;
	int32_t m_Counter = 0;
};

#endif /* GAME_GAMEPLAY_BONUSCTRL_HPP_ */
