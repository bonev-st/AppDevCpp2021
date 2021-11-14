/*
 * Timer2Def.hpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_TIMER_TIMER2DEF_HPP_
#define UTILS_INC_UTILS_TIMER_TIMER2DEF_HPP_

#include <memory>
#include <functional>

namespace Timer2 {

using TimerHandler_t = std::size_t;
static constexpr TimerHandler_t INVALID_TIMER_HANDLER = -1;

using TimerCB_t = std::function<void(const TimerHandler_t &)>;

enum class TimerMode_t : uint8_t {
	ONESHOT,
	RELOAD,
	INVALID
};
}

#endif /* UTILS_INC_UTILS_TIMER_TIMER2DEF_HPP_ */
