/*
 * RadioButton.hpp
 *
 *  Created on: Nov 6, 2021
 *      Author: stanimir
 */

#ifndef GAME_WIDGETS_RADIOBUTTON_HPP_
#define GAME_WIDGETS_RADIOBUTTON_HPP_

#include "game/widgets/Button.hpp"
#include "manager_utils/input/RadioWidget.hpp"

class RadioButton : public RadioWidget, public Button {
public:
	void attachCB(RadioCB_t * fn) final;
	bool getSelected() const final;
	void setSelected() final;
	void setDeslected() final;
	std::size_t getId() const final;
};

#endif /* GAME_WIDGETS_RADIOBUTTON_HPP_ */
