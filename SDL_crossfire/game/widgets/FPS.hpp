/*
 * FPS.hpp
 *
 *  Created on: Nov 14, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_FPS_HPP_
#define GAME_WIDGETS_FPS_HPP_

#include <cstdint>

#include "utils/time/Time.hpp"
#include "utils/Filter/ExpFilter.hpp"

class FPS {
public:
	void init();
	void newFrame();
	operator double() const;

private:
	static constexpr double SMOOTHING_FACTOR = 0.9;
	ExpFilter m_Filter;
	Time m_Period;

};

#endif /* GAME_WIDGETS_FPS_HPP_ */
