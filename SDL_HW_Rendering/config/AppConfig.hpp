/*
 * AppConfig.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_APPCONFIG_HPP_
#define CONFIG_APPCONFIG_HPP_

#include "sdl_utils/MainWindow.hpp"
#include "game/GameConfig.hpp"

struct AppConfig {
	MainWindowCfg_t WindowCfg;
	GameBase::GameConfig GameCfg;
};


#endif /* CONFIG_APPCONFIG_HPP_ */
