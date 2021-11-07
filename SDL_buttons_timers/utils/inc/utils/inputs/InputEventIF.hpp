/*
 * InputEventIF.hpp
 *
 *  Created on: Nov 7, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_INPUTS_INPUTEVENTIF_HPP_
#define UTILS_INC_UTILS_INPUTS_INPUTEVENTIF_HPP_

class InputEvent;

struct InputEventIF {
	virtual ~InputEventIF() = default;
	virtual bool handleEvent([[maybe_unused]]const InputEvent &e) {
		return false;
	}
};

#endif /* UTILS_INC_UTILS_INPUTS_INPUTEVENTIF_HPP_ */
