/*
 * ImgConfig.hpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_IMGCONFIG_HPP_
#define CONFIG_IMGCONFIG_HPP_

#include <cstdint>
#include <unordered_map>

#include "utils/drawing/Dimention.hpp"

namespace ImgConfig {

struct Config_t {
	std::string m_Path = "";
};

typedef std::unordered_map<uint32_t,  ImgConfig::Config_t> ImgRes_t;
}

#endif /* CONFIG_IMGCONFIG_HPP_ */
