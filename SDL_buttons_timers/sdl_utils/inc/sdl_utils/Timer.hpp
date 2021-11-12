/*
 * Timer.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: stanimir
 */

#ifndef SDL_UTILS_TIMER_HPP_
#define SDL_UTILS_TIMER_HPP_

#include <cstdint>

namespace Timer1 {
class Timer1Cfg_t;
}

struct SDL_UserEvent;

namespace SDL_Timer {

void delay(std::uint32_t ms);
bool createTimer(Timer1::Timer1Cfg_t & cfg);
bool deleteTimer(int32_t id);
void eventHandler(const SDL_UserEvent * event);

} /* namespace Timer */

#endif /* SDL_UTILS_TIMER_HPP_ */
