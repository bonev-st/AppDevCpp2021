/*
 * Timer.cpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#include "Timer.hpp"

#include <SDL_timer.h>

namespace Timer {

void Delay(std::uint32_t ms) {
	SDL_Delay(ms);
}

} /* namespace Timer */
