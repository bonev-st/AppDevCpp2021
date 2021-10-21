/*
 * ResourcesConfig.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_RESOURCESCONFIG_HPP_
#define CONFIG_RESOURCESCONFIG_HPP_

#include <unordered_map>

#include "common/CommonDefines.hpp"
#include "config/ImgConfig.hpp"
#include "config/FontConfig.hpp"

namespace ResourcesConfig {

typedef std::unordered_map<ResurcesId::ImgId_t,  ImgConfig::Config_t> ImgRes_t;
typedef std::unordered_map<ResurcesId::FontId_t, FontConfig::Config_t> TextRes_t;

struct Config_t {
	ImgRes_t m_ImgRes;
	TextRes_t m_TextRes;
};
}

#endif /* CONFIG_RESOURCESCONFIG_HPP_ */
