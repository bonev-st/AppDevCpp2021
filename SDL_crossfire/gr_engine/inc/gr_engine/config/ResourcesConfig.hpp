/*
 * ResourcesConfig.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_RESOURCESCONFIG_HPP_
#define CONFIG_RESOURCESCONFIG_HPP_

#include "gr_engine/config/DrawMgrConfig.hpp"
#include "gr_engine/config/ResMgrConfig.hpp"

namespace ResourcesConfig {

struct Config_t {
	DrawMgrConfig::Config_t m_DrawMgrCfg;
	ResMgrConfig::Config_t m_ResMgrCfg;
};

}

#endif /* CONFIG_RESOURCESCONFIG_HPP_ */
