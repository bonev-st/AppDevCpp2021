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
	static const double SmoothingFactor;
	ExpFilter m_Filter;
	Time m_Period;

};

#endif /* GAME_WIDGETS_FPS_HPP_ */
