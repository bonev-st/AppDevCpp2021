/*
 * DrawMgrConfig.hpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_CONFIG_DRAWMGRCONFIG_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_CONFIG_DRAWMGRCONFIG_HPP_

#include "utils/drawing/MainWindowCfg.hpp"

namespace DrawMgrConfig {
struct Config_t {
	MainWindowCfg::Config_t m_WindowCfg;
	std::uint32_t m_MaxFrameRate;
};
}

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_CONFIG_DRAWMGRCONFIG_HPP_ */
