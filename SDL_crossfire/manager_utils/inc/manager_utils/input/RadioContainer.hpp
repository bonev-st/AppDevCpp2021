/*
 * RadioContainer.hpp
 *
 *  Created on: Nov 4, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_RADIOCONTAINER_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_RADIOCONTAINER_HPP_

#include <vector>
#include "manager_utils/input/RadioWidget.hpp"

class RadioContainer {
public:
	bool init(const RadioCB_t &cb);
	void add(RadioWidget * widget);
	void select(std::size_t id);
	void deselect();

private:
	std::vector<RadioWidget *> m_Container;
	RadioCB_t m_CB;
	RadioCB_t m_GroupCB;

	void handler(std::size_t id);
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_RADIOCONTAINER_HPP_ */
