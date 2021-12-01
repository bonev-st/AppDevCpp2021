/*
 * CollisionDetect.cpp
 *
 *  Created on: Nov 23, 2021
 *      Author: stanimir
 */


#include "game/gameplay/CollisionDetect.hpp"

#include <iostream>
#include <algorithm>
#include <cassert>

#include "manager_utils/drawing/Widget.hpp"
#include "game/gameplay/ProcessorIF.hpp"

bool CollisionDetect::init(const Callback_t & cb, ProcessorIF * proc) {
	if(!cb) {
		std::cerr << "Invalid callback function" << std::endl;
		return false;
	}
	if(!proc) {
		std::cerr << "Invalid Collision processor function" << std::endl;
		return false;
	}
	m_CB = cb;
	m_Processor = proc;
	return true;
}

void CollisionDetect::setObj(Widget * widget) {
	m_Obj = widget;
}


void CollisionDetect::processing(std::vector<Widget*> container) {
	assert(m_Processor && "CollisionDetect not initialized");
	if(m_Obj && !container.empty()) {
		std::vector<Widget *> data = (*m_Processor)(m_Obj, container);
		if(data.empty()) {
			return;
		}
		if(m_CB) {
			m_CB(data);
		}
	}
}

