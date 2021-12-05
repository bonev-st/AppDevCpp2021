/*
 * LifeCounter.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GAME_GAMEPLAY_LIFECOUNTER_HPP_
#define GAME_GAMEPLAY_LIFECOUNTER_HPP_

#include <cstdint>

#include "utils/containers/Variable.hpp"

class LifeCounter {
public:
	void reset();
	void points(std::uint32_t val);
	operator std::uint32_t () const;
	std::uint32_t get();
	void attach(const Variable<std::uint32_t>::Callback_t &cb);

private:
	Variable<std::uint32_t> m_Value = 0;
	std::uint32_t m_PointsNewLife = 0;
};

#endif /* GAME_GAMEPLAY_LIFECOUNTER_HPP_ */
