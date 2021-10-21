/*
 * ImgConfig.hpp
 *
 *  Created on: Oct 21, 2021
 *      Author: stanimir
 */

#ifndef CONFIG_IMGCONFIG_HPP_
#define CONFIG_IMGCONFIG_HPP_

#include <cstdint>

namespace ImgConfig {

struct ImgDimetion_t {
	std::int32_t m_W = 0;
	std::int32_t m_H = 0;
};

struct Config_t {
	std::string m_Path = "";
	ImgDimetion_t m_Dimention;
};
}

#endif /* CONFIG_IMGCONFIG_HPP_ */
