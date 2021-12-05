/*
 * BonusCtrl.cpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#include "game/gameplay/BonusCtrl.hpp"

#include <cassert>

#include "game/config/Rules.hpp"
#include "game/config/Layout.hpp"

void BonusCtrl::reset() {
	m_Indx = static_cast<uint8_t>(BonusId_t::BONUS1);
	m_Counter = 0;
}

void BonusCtrl::kill() {
	if(m_Show && (0 > m_Counter)) {
		m_Counter = 0;
	}
}

bool BonusCtrl::shoot() {
	do {
		if(0 > m_Counter) {
			break;
		}
		if(static_cast<uint8_t>(BonusId_t::BONUS_NUMB) <= m_Indx) {
			break;
		}
		++m_Counter;
		if(m_Show) {
			if(Rules::BONUS_HIDE <= m_Counter) {
				m_Counter = 0;
				m_Show = false;
				++m_Indx;
			}
		} else {
			if(Rules::BONUS_SHOW <= m_Counter) {
				m_Counter = -1;
				m_Show = true;
			}
		}
	} while(0);
	return m_Show;
}

uint32_t BonusCtrl::take() {
	uint32_t points = 0;
	switch(static_cast<BonusId_t>(m_Indx)) {
	case BonusId_t::BONUS1:
		points = Rules::POINTS_BONUS1;
		break;
	case BonusId_t::BONUS2:
		points = Rules::POINTS_BONUS2;
		break;
	case BonusId_t::BONUS3:
		points = Rules::POINTS_BONUS3;
		break;
	case BonusId_t::BONUS4:
		points = Rules::POINTS_BONUS4;
		break;
	default:
		assert(0);
	}
	++m_Indx;
	m_Counter = 0;
	m_Show = false;
	return points;
}

BonusId_t BonusCtrl::getIndx() const {
	return static_cast<BonusId_t>(m_Indx);
}
