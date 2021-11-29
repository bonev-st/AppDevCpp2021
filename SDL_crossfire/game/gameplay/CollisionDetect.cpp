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

void CollisionDetect::setObj(const Widget * widget) {
	m_Obj = widget;
}

void CollisionDetect::add(const Widget * widget) {
	m_Container.push_back(widget);
}

bool CollisionDetect::remove(const Widget * widget) {
	auto it = std::find(m_Container.begin(), m_Container.end(), widget);
	if(m_Container.end() == it) {
		std::cerr << "Can't find widget" << std::endl;
		return false;
	}
	m_Container.erase(it);
	return true;
}

void CollisionDetect::processing() {
	assert(m_Processor && "CollisionDetect not initialized");
	if(m_Obj) {
		std::vector<const Widget *> data = (*m_Processor)(m_Obj, m_Container);
		if(data.empty()) {
			return;
		}
		if(m_CB) {
			m_CB(data);
		}
	}
}

