/*
 * FontConfig.hpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_FONTCONFIG_HPP_
#define CONFIG_FONTCONFIG_HPP_

#include <cstdint>
#include <unordered_map>

#include "utils/drawing/Color.hpp"

namespace FontConfig {

struct Config_t {
	std::string m_Path = "";
	int32_t m_TextSize = 0;
	Color m_Color;
};

typedef std::unordered_map<uint32_t, FontConfig::Config_t> FontRes_t;

}

#endif /* CONFIG_FONTCONFIG_HPP_ */
