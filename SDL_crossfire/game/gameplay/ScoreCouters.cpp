/*
 * ScoreCouters.cpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#include "game/gameplay/ScoreCouters.hpp"


void ScoreCouters::attachHiScore(const Variable<std::uint32_t>::Callback_t & cb) {
	m_HiScore.attach(cb);
}

void ScoreCouters::attachScore(const Variable<std::uint32_t>::Callback_t & cb) {
	m_Score.attach(cb);
}

uint32_t ScoreCouters::getHiScore() const {
	return m_HiScore;
}

uint32_t ScoreCouters::getScore() const {
	return m_Score;
}

uint32_t ScoreCouters::addPoints(uint32_t points) {
	const auto score = m_Score += points;
	if(m_HiScore < score) {
		m_HiScore = score;
	}
	return m_Score;
}

void ScoreCouters::reset() {
	m_Score = 0;
}
