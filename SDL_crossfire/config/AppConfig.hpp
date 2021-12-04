/*
 * AppConfig.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_APPCONFIG_HPP_
#define CONFIG_APPCONFIG_HPP_

#include "../gr_engine/inc/gr_engine/config/ResourcesConfig.hpp"
#include "game/config/GameConfig.hpp"

struct AppConfig {
	ResourcesConfig::Config_t m_ResourcesCfg;
	GameConfig::Config_t m_GameCfg;
};


#endif /* CONFIG_APPCONFIG_HPP_ */
