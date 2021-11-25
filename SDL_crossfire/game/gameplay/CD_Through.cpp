/*
 * CPThrough.cpp
 *
 *  Created on: Nov 23, 2021
 *      Author: stanimir
 */


#include "game/gameplay/CD_Through.hpp"

#include "manager_utils/drawing/Widget.hpp"

bool CD_Through::init(const Rectangle & tolerance) {
	m_Tolerance = tolerance;
	return true;
}

std::vector<const Widget*> CD_Through::operator ()(const Widget* obj, const std::deque<const Widget *> & others) const {
	std::vector<const Widget*> rc;
	rc.reserve(2);
	if(obj) {
		Rectangle rect = m_Tolerance;
		for(const auto e : others) {
			if(!e->getVisible()) {
				continue;
			}
			rect.m_Pos = e->getRectangle().getCenter();
			if(obj->getRectangle().isInside(rect)) {
				rc.push_back(obj);
				rc.push_back(e);
				break;
			}
		}
	}
	return rc;
}
