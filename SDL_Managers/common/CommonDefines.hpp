/*
 * CommonDefines.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: stanimir
 */

#ifndef COMMON_COMMONDEFINES_HPP_
#define COMMON_COMMONDEFINES_HPP_

#include <cstdint>

namespace ResurcesId {

enum ImgId_t : std::size_t {
	IDLE_IMG,
	UP_IMG,
	DOWN_IMG,
	LEFT_IMG,
	RIGHT_IMG,
	L2_IMG,
	NUMB_IMG
};

enum FontId_t : std::size_t {
	ANGELINE_VINTAGE_40_TTF,
	ANGELINE_VINTAGE_80_TTF,
	ANGELINE_VINTAGE_160_TTF,
	NUMB_TTF
};

}

#endif /* COMMON_COMMONDEFINES_HPP_ */
