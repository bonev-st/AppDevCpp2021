/*
 * Timer1ClientIF.hpp
 *
 *  Created on: Nov 11, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_MANAGER_UTILS_TIMER_TIMER1CLIENTIF_HPP_
#define UTILS_INC_MANAGER_UTILS_TIMER_TIMER1CLIENTIF_HPP_

#include "utils/timer/Timer1Def.hpp"

class Timer1ClientIF {
public:
	virtual ~Timer1ClientIF() = default;
	virtual void removeExpired(Timer1::Timer1Handler_t id) = 0;
	virtual std::size_t getTimersNumb() const = 0;
};



#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_TIMER_TIMER1CLIENTIF_HPP_ */
