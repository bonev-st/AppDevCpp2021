/*
 * DrawMgrConfig.hpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_CONFIG_DRAWMGRCONFIG_HPP_
#define GR_ENGINE_INC_GR_ENGINE_CONFIG_DRAWMGRCONFIG_HPP_

#include "utils/drawing/MainWindowCfg.hpp"

namespace DrawMgrConfig {
struct Config_t {
	MainWindowCfg::Config_t m_WindowCfg;
	std::uint32_t m_MaxFrameRate;
};
}

#endif /* GR_ENGINE_INC_GR_ENGINE_CONFIG_DRAWMGRCONFIG_HPP_ */
