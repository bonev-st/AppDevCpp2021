/*
 * DrawMgrConfig.hpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_CONFIG_DRAWMGRCONFIG_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_CONFIG_DRAWMGRCONFIG_HPP_

#include "sdl_utils/MainWindow.hpp"

namespace DrawMgrConfig {
struct Config_t {
	MainWindow::Config_t m_WindowCfg;
	std::int64_t m_MaxFrameRate;
};
}

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_CONFIG_DRAWMGRCONFIG_HPP_ */
