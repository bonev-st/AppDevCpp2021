/*
 * ResourcesConfig.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_RESOURCESCONFIG_HPP_
#define CONFIG_RESOURCESCONFIG_HPP_

#include "common/CommonDefines.hpp"

#include "sdl_utils/MainWindow.hpp"
#include "sdl_utils/config/ImgConfig.hpp"
#include "sdl_utils/config/FontConfig.hpp"

namespace ResourcesConfig {

struct Config_t {
	MainWindow::Config_t m_WindowCfg;
	ImgConfig::ImgRes_t m_ImgRes;
	FontConfig::FontRes_t m_FontRes;
};
}

#endif /* CONFIG_RESOURCESCONFIG_HPP_ */
