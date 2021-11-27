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

void CollisionDetect::setObj(const Widget * widged) {
	m_Obj = widged;
}

void CollisionDetect::add(const Widget * widged) {
	m_Continer.push_back(widged);
}

bool CollisionDetect::remove(const Widget * widged) {
	auto it = std::find(m_Continer.begin(), m_Continer.end(), widged);
	if(m_Continer.end() == it) {
		std::cerr << "Can't find widget" << std::endl;
		return false;
	}
	m_Continer.erase(it);
	return true;
}

void CollisionDetect::processing() {
	assert(m_Processor && "CollisionDetect not initialized");
	if(m_Obj) {
		std::vector<const Widget *> data = (*m_Processor)(m_Obj, m_Continer);
		if(data.empty()) {
			return;
		}
		if(m_CB) {
			m_CB(data);
		}
	}
}

