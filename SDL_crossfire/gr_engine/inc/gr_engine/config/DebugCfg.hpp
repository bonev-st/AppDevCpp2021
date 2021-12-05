/*
 * DebugCfg.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_CONFIG_DEBUGCFG_HPP_
#define GR_ENGINE_INC_GR_ENGINE_CONFIG_DEBUGCFG_HPP_

#include <cstdint>

struct DebugCfg {
	static bool m_Enable;
	static uint32_t m_TimerPeiod;
};

#endif /* GR_ENGINE_INC_GR_ENGINE_DEBUG_DEBUGCFG_HPP_ */
