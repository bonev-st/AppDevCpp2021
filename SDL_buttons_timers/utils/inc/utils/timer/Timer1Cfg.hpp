/*
 * Timer1Cfg.hpp
 *
 *  Created on: Nov 11, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_TIMER1_CFG_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_TIMER1_CFG_HPP_

#include <cstdint>
#include <functional>
#include "utils/timer/Timer1Def.hpp"

class Timer1ClientIF;

namespace Timer1 {

struct Timer1Cfg_t {
	uint32_t m_Period = 0;
	Timer1Mode_t m_Mode = Timer1Mode_t::INVALID;
	Timer1Handler_t m_Handler = INVALID_TIMER1_HANDLER;
	Timer1CB_t m_CB;
	Timer1ClientIF *m_Client = nullptr;
};

}

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_TIMER1_CFG_HPP_ */
