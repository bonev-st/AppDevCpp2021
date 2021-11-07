/*
 * Button.hpp
 *
 *  Created on: Nov 3, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_BUTTON_HPP_
#define GAME_WIDGETS_BUTTON_HPP_

#include <functional>

#include "manager_utils/input/ButtonBase.hpp"

using ButtonCB_t = std::function<void(std::size_t)>;

class Button : public ButtonBase {
public:
	bool create(std::size_t button_id, std::size_t image_id, const Point &pos = Point::ZERO);
	bool attachCB(ButtonCB_t * fn);
	bool handleEvent(const InputEvent &e) override;
	std::size_t getId() const;

private:
	std::size_t m_Id = -1;
	ButtonCB_t * m_CB = nullptr;
	bool m_Touched = false;
};

#endif /* GAME_WIDGETS_BUTTON_HPP_ */
