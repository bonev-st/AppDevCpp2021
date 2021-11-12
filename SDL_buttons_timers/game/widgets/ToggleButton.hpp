/*
 * ToggleButton.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_TOGGLEBUTTON_HPP_
#define GAME_WIDGETS_TOGGLEBUTTON_HPP_

#include <functional>

#include "manager_utils/input/ButtonBase.hpp"

using ToggleButtonCB_t = std::function<void(std::size_t, bool pressed)>;

class ToggleButton : public ButtonBase {
public:
	bool create(std::size_t button_id, std::size_t image_id, const Point &pos = Point::ZERO);
	bool attachCB(const ToggleButtonCB_t & fn);
	bool handleEvent(const InputEvent &e) override;
	std::size_t getId() const;

private:
	std::size_t m_Id = -1;
	ToggleButtonCB_t m_CB;
	bool m_Touched = false;
	bool m_Pressed = false;
};

#endif /* GAME_WIDGETS_TOGGLEBUTTON_HPP_ */
