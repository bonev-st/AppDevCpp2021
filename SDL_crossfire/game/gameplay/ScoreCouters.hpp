/*
 * ScoreCouters.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_SCORECOUTERS_HPP_
#define GAME_GAMEPLAY_SCORECOUTERS_HPP_

#include <cstdint>
#include "utils/containers/Variable.hpp"

class ScoreCouters {
public:
	void attachHiScore(const Variable<std::uint32_t>::Callback_t & cb);
	void attachScore(const Variable<std::uint32_t>::Callback_t & cb);
	void reset();
	std::uint32_t addPoints(std::uint32_t points);
	std::uint32_t getHiScore() const;
	std::uint32_t getScore() const;

private:
	Variable<std::uint32_t> m_HiScore = 0;
	Variable<std::uint32_t> m_Score = 0;
};

#endif /* GAME_GAMEPLAY_SCORECOUTERS_HPP_ */
