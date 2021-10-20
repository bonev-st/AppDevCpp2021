/*
 * AppConfig.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_APPCONFIG_HPP_
#define CONFIG_APPCONFIG_HPP_

#include "sdl_utils/MainWindow.hpp"
#include "config/ResourcesConfig.hpp"
#include "config/GameConfig.hpp"

struct AppConfig {
	MainWindow::Config_t m_WindowCfg;
	ResourcesConfig::Config_t m_ResourcesCfg;
	GameConfig::Config_t m_GameCfg;
};


#endif /* CONFIG_APPCONFIG_HPP_ */
