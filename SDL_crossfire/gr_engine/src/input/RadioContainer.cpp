/*
 * RadioContainer.cpp
 *
 *  Created on: Nov 4, 2021
 *      Author: stanimir
 */

#include "gr_engine/input/RadioContainer.hpp"

bool RadioContainer::init(const RadioCB_t &cb) {
	if(!cb) {
		return false;
	}
	m_CB = cb;
	m_GroupCB = std::bind(&RadioContainer::handler, this, std::placeholders::_1);
	return true;
}

void RadioContainer::add(RadioWidget * widget) {
	m_Container.push_back(widget);
	widget->attachCB(m_GroupCB);
}

void RadioContainer::select(std::size_t id) {
	handler(id);
}

void RadioContainer::deselect() {
	handler(-1);
}

void RadioContainer::handler(std::size_t id) {
	for(auto e: m_Container) {
		if(id == e->getId()) {
			if(!e->getSelected()) {
				e->setSelected();
				if(m_CB) {
					m_CB(id);
				}
			}
		} else {
			e->setDeslected();
		}
	}
}
