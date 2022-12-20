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
#include <vector>
#include <string>

#include "utils/drawing/Rectangle.hpp"

namespace ImgConfig {

struct Config_t {
	std::string m_Path = "";
	std::vector<Rectangle> m_Frames;
};

typedef std::unordered_map<uint32_t,  ImgConfig::Config_t> ImgRes_t;
}

#endif /* CONFIG_IMGCONFIG_HPP_ */
