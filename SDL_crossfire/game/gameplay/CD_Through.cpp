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

std::vector<Widget*> CD_Through::operator ()(Widget* obj, const std::vector<Widget *> & others) const {
	std::vector<Widget*> rc;
	rc.reserve(2);
	if(obj) {
		Rectangle rect_obj = m_Tolerance;
		rect_obj.m_Pos = obj->getRectangle().getCenter();
		Rectangle rect = m_Tolerance;
		for(const auto e : others) {
			if(!e->getVisible()) {
				continue;
			}
			rect.m_Pos = e->getRectangle().getCenter();
			if(rect_obj.isToched(rect)) {
				rc.push_back(e);
				break;
			}
		}
	}
	return rc;
}
