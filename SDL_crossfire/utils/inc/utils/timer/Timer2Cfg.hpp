/*
 * Timer2Cfg.hpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_TIMER2_CFG_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_TIMER2_CFG_HPP_

#include <cstdint>
#include <list>
#include <memory>
#include "utils/timer/Timer2Def.hpp"

namespace Timer2 {

using TimerSDL_Handler_t = int32_t;
static constexpr TimerSDL_Handler_t INVALID_SLD_TIMER_HANDLER = 0;

struct TimerCfg_t;

using Iterator_t = std::list<std::shared_ptr<Timer2::TimerCfg_t>>::iterator;

struct TimerCfg_t {
	Iterator_t m_Handler;
	uint32_t m_Period = 0;
	TimerMode_t m_Mode = TimerMode_t::INVALID;
	TimerCB_t m_CB;
	TimerSDL_Handler_t m_TimerSDL_Handler = 0;
	std::size_t  m_SDL_CB_Counter = 0;
	std::size_t  m_CB_Counter = 0;
};

}

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_TIMER1_CFG_HPP_ */
