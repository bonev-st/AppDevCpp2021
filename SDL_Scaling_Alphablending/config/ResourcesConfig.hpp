/*
 * ResourcesConfig.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_RESOURCESCONFIG_HPP_
#define CONFIG_RESOURCESCONFIG_HPP_

#include <unordered_map>
#include <string>

#include "common/CommonDefines.hpp"

namespace ResourcesConfig {

typedef std::unordered_map<TextureId::ImgId_t, std::string> ImgRes_t;

struct Config_t {
	ImgRes_t m_ImgPath;
};
}

#endif /* CONFIG_RESOURCESCONFIG_HPP_ */
