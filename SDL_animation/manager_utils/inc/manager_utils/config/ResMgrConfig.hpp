/*
 * ResMgrConfig.hpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_CONFIG_RESMGRCONFIG_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_CONFIG_RESMGRCONFIG_HPP_

#include "sdl_utils/config/ImgConfig.hpp"
#include "sdl_utils/config/FontConfig.hpp"

namespace ResMgrConfig {

struct Config_t {
	ImgConfig::ImgRes_t m_ImgRes;
	FontConfig::FontRes_t m_FontRes;
};

}

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_CONFIG_RESMGRCONFIG_HPP_ */
