/*
 * Timer2Cfg.hpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_TIMER2_CFG_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_TIMER2_CFG_HPP_

#include <cstdint>
#include "utils/timer/Timer2Def.hpp"

namespace Timer2 {

using TimerSDL_Hadler_t = int32_t;
static constexpr TimerSDL_Hadler_t INVALID_SLD_TIMER_HADLER = 0;

struct TimerCfg_t {
	uint32_t m_Period = 0;
	TimerMode_t m_Mode = TimerMode_t::INVALID;
	TimerHandler_t m_Handler = INVALID_TIMER_HANDLER;
	TimerCB_t m_CB;
	TimerSDL_Hadler_t m_TimerSDL_Hadler = 0;
	std::size_t  m_SDL_CB_Counter = 0;
	std::size_t  m_CB_Counter = 0;
};

}

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_TIMER1_CFG_HPP_ */
