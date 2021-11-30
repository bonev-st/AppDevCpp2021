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
	BACKGROUND_IMG,
	CROSSFIRE_TEXT_IMG,
	GRID_BKGRND_IMG,
	GRID_IMG,
	SHIP_IMG,
	ENEMY1_IMG,
	ENEMY2_IMG,
	ENEMY3_IMG,
	ENEMY4_IMG,
	BONUS_IMG,
	AMMUN_IMG,
	OWN_BULLET_IMG,
	ENEMY_BULLET_IMG,
	EXPLOSION_IMG,
	NUMB_IMG
};

enum FontId_t : std::size_t {
	ANGELINE_UNLEARNE_20_TTF,
	NUMB_TTF
};

}

#endif /* COMMON_COMMONDEFINES_HPP_ */
