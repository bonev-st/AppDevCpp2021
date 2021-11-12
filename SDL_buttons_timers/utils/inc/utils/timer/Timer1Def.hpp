/*
 * Timer1Def.hpp
 *
 *  Created on: Nov 11, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_TIMER1_DEF_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_TIMER1_DEF_HPP_

#include <cstdint>
#include <functional>

namespace Timer1 {
typedef std::int32_t Timer1Handler_t;
using Timer1CB_t = std::function<void(Timer1Handler_t)>;

static constexpr Timer1Handler_t INVALID_TIMER1_HANDLER = 0;

enum class Timer1Mode_t : uint8_t {
	ONESHOT,
	RELOAD,
	INVALID
};
}

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_TIMER1_DEF_HPP_ */
